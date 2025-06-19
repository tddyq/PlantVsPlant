#pragma once
#include <graphics.h>
#include"Vector2.h"
#include"Animation.h"
#include"Atlas.h"
#include"bullet.h"
#include"PlayerID.h"
#include"Platform.h"
#include"Particle.h"

extern void putimage_alpha(const Camera& camera, int x, int y, IMAGE* img);
extern void sketch_image(IMAGE* src, IMAGE* dst);
extern Atlas atlas_run_effect;                   // 奔跑特效动画图集
extern Atlas atlas_jump_effect;                  // 跳跃特效动画图集
extern Atlas atlas_land_effect;                  // 落地特效动画图集
extern std::vector<Platform> platform_list; // 平台列表
extern std::vector<bullet*> bullet_list; // 子弹列表
extern bool is_debug;
class Camera;
class Player
{
public:

	Player(){
		current_animation = &animation_idle_right; // 默认朝向右侧的待机动画

		// 跳跃特效动画设置
		animation_jump_effect .set_atlas(&atlas_jump_effect);
		animation_jump_effect.set_interval(25);
		animation_jump_effect.set_loop(false);
		animation_jump_effect.set_callback([&]()
			{
				is_jump_effect_visible = false;
			});

		// 落地特效动画设置
		animation_land_effect.set_atlas(&atlas_land_effect);
		animation_land_effect.set_interval(50);
		animation_land_effect.set_loop(false);
		animation_land_effect.set_callback([&]()
			{
				is_land_effect_visible = false;
			});

		timer_attack_cd.set_wait_time(attack_cd);
		timer_attack_cd.set_one_shot(true);
		timer_attack_cd.set_callback([&]() {
			can_attack = true; // 攻击冷却结束，允许攻击
			});

		// 设置无敌状态定时器
		timer_invulnerable.set_wait_time(750);         // 设置750毫秒的等待时间
		timer_invulnerable.set_one_shot(true);         // 设置为单次触发模式
		timer_invulnerable.set_callback([&]()          // 设置定时器结束后的回调函数
			{
				is_invulnerable = false;                   // 取消无敌状态
			});

		// 设置无敌状态闪烁效果定时器
		timer_invulnerable_blink.set_wait_time(75);    // 设置75毫秒的等待时间
		timer_invulnerable_blink.set_callback([&]()    // 设置定时器回调函数
			{
				// 切换轮廓帧显示状态（实现闪烁效果）
				is_showing_sketch_frame = !is_showing_sketch_frame;
			});

		// 设置跑步特效生成定时器
		timer_run_effect_generation.set_wait_time(75);  // 设置75毫秒间隔
		timer_run_effect_generation.set_callback([&]()  // 设置回调函数(引用捕获)
			{
				Vector2 particle_position;                   // 粒子位置向量
				IMAGE* frame = atlas_run_effect.get_image(0); // 获取跑步特效第一帧
				// 计算粒子居中位置
				particle_position.x = position.x + (size.x - frame->getwidth()) / 2;
				particle_position.y = position.y + size.y - frame->getheight();
				// 生成新粒子并添加到列表(生命周期45帧)
				particle_list.emplace_back(particle_position, &atlas_run_effect, 45);
			});

		// 设置死亡特效生成定时器
		timer_die_effect_generation.set_wait_time(35);   // 设置更短的35毫秒间隔
		timer_die_effect_generation.set_callback([&]()   // 设置回调函数
			{
				Vector2 particle_position;                   // 粒子位置向量
				IMAGE* frame = atlas_run_effect.get_image(0); // 获取同一图集的第一帧
				// 使用相同的居中算法计算位置
				particle_position.x = position.x + (size.x - frame->getwidth()) / 2;
				particle_position.y = position.y + size.y - frame->getheight();
				// 生成新粒子(生命周期150帧)
				particle_list.emplace_back(particle_position, &atlas_run_effect, 150);
			});
	}


	~Player() = default;

	virtual void on_update(int delta) {
		int direction = is_left_key_down - is_right_key_down;

		if (direction != 0) {
			if (!is_attack_ex) { // 如果正在执行特殊攻击，则不允许移动
				is_facing_right = (direction > 0);
			}
			
			current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
			float distance = direction * run_velocity * delta; //这一帧中玩家的移动距离
			on_run(distance); // 更新玩家位置
		}
		else {
			current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;	
			timer_run_effect_generation.pause(); // 暂停跑步特效生成计时器
		}
		if (is_attack_ex) {
			current_animation = is_facing_right ? &animation_attack_ex_right : &animation_attack_ex_left;
		}
		if (current_animation == NULL) {
			std::cout << "current_animation is NULL" << std::endl;
		}
		current_animation->on_update(delta);
		animation_jump_effect.on_update(delta);        // 更新跳跃特效动画
		animation_land_effect.on_update(delta);        // 更新落地特效动画

		timer_attack_cd.on_update(delta);              // 更新攻击冷却计时器
		timer_invulnerable.on_update(delta);           // 更新无敌状态计时器
		timer_invulnerable_blink.on_update(delta);     // 更新无敌状态闪烁计时器
		timer_run_effect_generation.on_update(delta);  // 更新跑步特效生成计时器
		if (hp <= 0) {
			timer_die_effect_generation.on_update(delta); // 更新死亡特效生成计时器
		}
		//删除粒子列表中失效的粒子并对剩下的例子更新
		particle_list.erase(std::remove_if(
			particle_list.begin(), particle_list.end(),
			[](const Particle& particle) {
				return !particle.check_valid(); // 删除无效的粒子
			}
		),
			particle_list.end()
		);
		for (Particle& particle : particle_list) {
			particle.on_update(delta); // 更新每个粒子
		}

		if (is_showing_sketch_frame) {
			sketch_image(current_animation->get_frame(), &img_sketch);
		}

		move_and_collide(delta); // 更新位置和碰撞检测
	}
	virtual void on_draw(const Camera& camera) {
		if (is_jump_effect_visible) { // 如果跳跃特效可见，则绘制跳跃特效
			animation_jump_effect.on_draw(camera, jump_effect_position.x, jump_effect_position.y);
		}
		if (is_land_effect_visible) {
			animation_land_effect.on_draw(camera, land_effect_position.x, land_effect_position.y);
		}

		for (Particle& particle : particle_list) {
			particle.on_draw(camera); // 绘制每个粒子
		}
		
		if (is_invulnerable && is_showing_sketch_frame && hp > 0) {
			putimage_alpha(camera, position.x, position.y,&img_sketch);
		}
		else {
			current_animation->on_draw(camera, position.x, position.y);
		}
		
		if (is_debug) {
			setlinecolor(RGB(0, 125, 255));
			rectangle((int)position.x, (int)position.y,
				(int)(position.x + size.x), (int)(position.y + size.y));
		}
	}
	virtual void on_input(const ExMessage& msg) {
		//第一层判断按键状态
		//第二层判断玩家ID
		//第三层判断按键类型
		switch (msg.message) {
		case WM_KEYDOWN:
			switch (id) {
			case PlayerID::P1:
				switch (msg.vkcode) {
					//'A'
				case 0x44:
					is_left_key_down = true;
					break;
					//'D'
				case 0x41:
					is_right_key_down = true;
					break;
				    //'w'
				case 0x57:
					on_jump();
					break;
				case 0x46:
					if (can_attack) {
						on_attack();
						can_attack = false;
						timer_attack_cd.restart(); // 重置攻击冷却计时器
					}
					break;
				case 0x47:
					if (mp >= 100) {
						on_attack_ex();
						mp = 0;
					}
					break;
				default:
					break;
				}
				break;
			case PlayerID::P2:
				switch (msg.vkcode) {
					//'←'
				case VK_RIGHT:
					is_left_key_down = true;
					break;
					//'→'
				case VK_LEFT:
					is_right_key_down = true;
					break;
					//'↑'
				case VK_UP:
					on_jump();
					break;
				case VK_OEM_PERIOD:
					if (can_attack) {
						on_attack();
						can_attack = false;
						timer_attack_cd.restart(); // 重置攻击冷却计时器
					}
					break;
				case VK_OEM_2:
					if (mp >= 100) {
						on_attack_ex();
						mp = 0;
					}
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
			break;
		case WM_KEYUP:
			switch (id) {
			case PlayerID::P1:
				switch (msg.vkcode) {
					//'A'
				case 0x44:
					is_left_key_down = false;
					break;
					//'D'
				case 0x41:
					is_right_key_down = false;
					break;
				default:
					break;
				}
				
				break;
			case PlayerID::P2:
				switch (msg.vkcode) {
					//'←'
				case VK_RIGHT:
					is_left_key_down = false;
					break;
					//'→'
				case VK_LEFT:
					is_right_key_down = false;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	virtual void on_run(float distance) {
		if (is_attack_ex) {
			return;
		}
		position.x += distance;
		timer_run_effect_generation.resume();
	}
	virtual void on_jump() {
		
		if (velocity.y != 0 || is_attack_ex) {
			return;
		}
		velocity.y += jump_velocity;

		is_jump_effect_visible = true;
		animation_jump_effect.reset(); // 重置跳跃特效动画
		IMAGE* effect_frame = animation_jump_effect.get_frame();
		jump_effect_position.x = position.x + (size.x - effect_frame->getwidth()) / 2; // 居中跳跃特效位置
		jump_effect_position.y = position.y + size.y - effect_frame->getheight();      // 跳跃特效位置在玩家脚下
	
	}
	virtual void on_land() {
		is_land_effect_visible = true;
		animation_land_effect.reset(); // 重置跳跃特效动画
		IMAGE* effect_frame = animation_land_effect.get_frame();
		land_effect_position.x = position.x + (size.x - effect_frame->getwidth()) / 2; // 居中跳跃特效位置
		land_effect_position.y = position.y + size.y - effect_frame->getheight();      // 跳跃特效位置在玩家脚下
	}
	virtual void on_attack(){}
	virtual void on_attack_ex(){}
	void set_position(float x, float y) {
		position.x = x;
		position.y = y;

	}
	void set_id(PlayerID player_id) {
		id = player_id;
	}
	const Vector2& get_position() const
	{
		return position;
	}
	const Vector2& get_size() const
	{
		return size;
	}
	const void set_hp(int new_hp) {
		hp = new_hp;
	}
	const void set_mp(int new_mp) {
		mp = new_mp;
	}
	const int get_mp() const {
		return mp;
	}
	const int get_hp() const {
		return hp;
	}
protected:
	void move_and_collide(int delta) {
		float last_velocity = velocity.y; // 保存上一帧的垂直速度

		velocity.y += gravity * delta;
		position += velocity * (float)delta;

		if (velocity.y > 0) {
			for (const Platform& platform : platform_list) {
				const Platform::CollisionShape& shape = platform.shape;
				bool is_collide_x = (max(position.x + size.x, shape.right) - min(position.x, shape.left)
					<= size.x + (shape.right - shape.left));
				bool is_collide_y = (shape.y >= position.y && shape.y <= position.y + size.y);
				if (is_collide_x && is_collide_y) {
					float delta_pos_y = velocity.y * delta;
					float last_tick_foot_pos_y = position.y + size.y - delta_pos_y; // 上一帧脚部位置
					if (last_tick_foot_pos_y <= shape.y) {
						position.y = shape.y - size.y;
						velocity.y = 0; // 重置垂直速度

						if (last_velocity != 0) {
							on_land(); // 触发落地事件
						}

						break;
					}
					
				}
			}
		}
		if (!is_invulnerable) {
			for (bullet* bullet : bullet_list) {
				if (!bullet->get_valid() || bullet->get_collide_target() != id) {
					continue;   // 如果子弹无效或不属于当前玩家，则跳过
				}
				if (bullet->check_collision(position, size)) {
					make_invulnerable(); // 触发无敌状态
					bullet->on_collide(); // 处理子弹碰撞
					bullet->set_vaild(false); // 设置子弹为无效状态
					hp -= bullet->get_damage(); // 减少玩家生命值
				}
			}
		}
		
	}
	void make_invulnerable() {
		is_invulnerable = true; // 设置无敌状态
		timer_invulnerable.restart(); // 重置无敌状态计时器
		timer_invulnerable_blink.restart(); // 重置无敌状态闪烁计时器
	}
protected:
	const float run_velocity = 0.55f; // 跑步速度
	const float gravity = 1.6e-3f; // 重力加速度
	const float jump_velocity = -0.85f; // 跳跃初速度
protected:
	Vector2 size;     // 玩家碰撞尺寸大小
	Vector2 position;
	Vector2 velocity; // 速度向量

	Animation animation_idle_left;             // 待机动画（向左）
	Animation animation_idle_right;            // 待机动画（向右）
	Animation animation_run_left;              // 向左跑步动画
	Animation animation_run_right;             //向右跑步动画
	Animation animation_attack_ex_left;        // 朝向左的特殊攻击动画
	Animation animation_attack_ex_right;       // 朝向右的特殊攻击动画
	Animation animation_jump_effect;           // 跳跃特效动画
	Animation animation_land_effect;           // 落地特效动画

	bool is_jump_effect_visible;
	bool is_land_effect_visible;
	             
	Vector2 jump_effect_position;              // 跳跃特效位置
	Vector2 land_effect_position;              // 落地特效位置
	             
	Animation* current_animation = nullptr;

	PlayerID id = PlayerID::P1;

	bool is_left_key_down = false;
	bool is_right_key_down = false;

	bool is_facing_right = true;    // 是否面向右侧

	int attack_cd = 500; // 攻击冷却时间（毫秒）
	bool can_attack = true;
	Timer timer_attack_cd;
	
	bool is_attack_ex = false; // 是否使用特殊攻击

	int mp = 0;
	int hp = 100;

	IMAGE img_sketch; // 剪影图片
	bool is_invulnerable = false;           // 是否处于无敌状态
	bool is_showing_sketch_frame = false;   //当前帧是否显示剪影
	Timer timer_invulnerable;               // 无敌状态计时器
	Timer timer_invulnerable_blink;         // 无敌状态闪烁计时器

	std::vector<Particle> particle_list;    // 粒子列表，用于特效

	Timer timer_run_effect_generation;      // 跑步特效生成计时器
	Timer timer_die_effect_generation;      // 死亡特效生成计时器
};

