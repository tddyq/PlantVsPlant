#pragma once
#include"Player.h"
#include"Animation.h"
#include"sun_bullet.h"
#include"sun_bullet_ex.h"
#include<iostream>
// 龙日葵系列动画图集
extern Atlas atlas_sunflower_idle_left;          // 龙日葵朝向左的默认动画图集
extern Atlas atlas_sunflower_idle_right;         // 龙日葵朝向右的默认动画图集
extern Atlas atlas_sunflower_run_left;           // 龙日葵朝向左的奔跑动画图集
extern Atlas atlas_sunflower_run_right;          // 龙日葵朝向右的奔跑动画图集
extern Atlas atlas_sunflower_attack_ex_left;     // 龙日葵朝向左的特殊攻击动画图集
extern Atlas atlas_sunflower_attack_ex_right;    // 龙日葵朝向右的特殊攻击动画图集
extern Atlas atlas_sunflower_die_left;           // 龙日葵朝向左的死亡动画图集
extern Atlas atlas_sunflower_die_right;          // 龙日葵朝向右的死亡动画图集
extern Atlas atlas_sun_text;                     // “日”文本动画图集

extern Player* player_1; // 玩家1
extern Player* player_2; // 玩家2
class sunflower_player :  public Player
{
public:
	sunflower_player() {
		animation_idle_left.set_atlas(&atlas_sunflower_idle_left);
		animation_idle_right.set_atlas(&atlas_sunflower_idle_right);
		animation_run_left.set_atlas(&atlas_sunflower_run_left);
		animation_run_right.set_atlas(&atlas_sunflower_run_right);
		animation_attack_ex_left.set_atlas(&atlas_sunflower_attack_ex_left);
		animation_attack_ex_right.set_atlas(&atlas_sunflower_attack_ex_right);
		animation_sun_text.set_atlas(&atlas_sun_text);

		animation_attack_ex_left.set_loop(false);
		animation_attack_ex_right.set_loop(false);
		animation_sun_text.set_loop(false);

		animation_idle_left.set_interval(75);
		animation_idle_right.set_interval(75);
		animation_run_left.set_interval(75);
		animation_run_right.set_interval(75);
		animation_attack_ex_left.set_interval(75);
		animation_attack_ex_right.set_interval(75);
		animation_sun_text.set_interval(75);

		// 设置左侧特殊攻击动画的回调函数
		animation_attack_ex_left.set_callback([&]()
			{
				is_attack_ex = false;          // 结束特殊攻击状态
				is_sun_text_visible = false;      // 隐藏太阳计数文本
			});

		// 设置右侧特殊攻击动画的回调函数
		animation_attack_ex_right.set_callback([&]()
			{
				is_attack_ex = false;          // 结束特殊攻击状态
				is_sun_text_visible = false;      // 隐藏太阳计数文本
			});

		size.x = 96, size.y = 96;

		attack_cd = 250;
	}
	~sunflower_player() = default;

	void on_update(int delta) {
		Player::on_update(delta); // 调用基类的更新方法

	}

	void on_draw(const Camera& camera) {
		Player::on_draw(camera); // 调用基类的绘制方法

		if (is_sun_text_visible) {
			Vector2 text_position;
			IMAGE* frame = animation_sun_text.get_frame();
			text_position.x = position.x - (size.x - frame->getwidth()) / 2;
			text_position.y = position.y - frame->getheight();
			animation_sun_text.on_draw(camera, (int)text_position.x, (int)text_position.y);
		}
	
	}

	void on_input(const ExMessage& msg) {
		// 处理输入的逻辑
		Player::on_input(msg);
	}
	void on_attack() {
		bullet* bullet = new sun_bullet();

		Vector2  bullet_position;
		const Vector2& bullet_size = bullet->get_size();
		bullet_position.x = position.x + (size.x - bullet_size.x) / 2;
		bullet_position.y = position.y;

		bullet->set_position(bullet_position.x, bullet_position.y);
		bullet->set_velocity((is_facing_right ? velocity_sun.x : -velocity_sun.x), velocity_sun.y);
		

		bullet->set_collide_target(id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);

		bullet->set_callback([&]() {mp += 35;});

		bullet_list.push_back(bullet);

	}
	void on_attack_ex() {
		is_attack_ex = true;
		is_sun_text_visible = true;

		animation_sun_text.reset();
		is_facing_right ? animation_attack_ex_right.reset() : animation_attack_ex_left.reset();

		bullet* bullet = new sun_bullet_ex();
		Player* target_player = (id == PlayerID::P1 ? player_2 : player_1);


		Vector2 bullet_position, bullet_velocity;  // 声明子弹位置和速度向量

		// 获取子弹和目标玩家的尺寸
		const Vector2& bullet_size = bullet->get_size();
		const Vector2& target_size = target_player->get_size();

		// 获取目标玩家的位置
		const Vector2& target_position = target_player->get_postion();

		// 设置子弹的初始位置
		bullet_position.x = target_position.x + (target_size.x - bullet_size.x) / 2;
		bullet_position.y = -size.y;

		// 设置子弹的速度向量
		bullet_velocity.x = 0;
		bullet_velocity.y = speed_sun_ex;
		// 设置子弹位置和速度
		bullet->set_position(bullet_position.x, bullet_position.y);
		bullet->set_velocity(bullet_velocity.x, bullet_velocity.y);

		// 根据ID设置碰撞目标
		bullet->set_collide_target(id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);

		// 设置子弹击中回调函数（增加50点MP值）
		bullet->set_callback([&]() { mp += 50; });

		// 将子弹加入子弹列表
		bullet_list.push_back(bullet);

		mciSendString(_T("play sun_text from 0"), NULL, 0, NULL);
	}
private:
	const float speed_sun_ex = 0.15f;
	const Vector2 velocity_sun = { 0.25,-0.5f };
	Animation animation_sun_text;    //头顶文本
	bool is_sun_text_visible = false;
private:
	Timer timer_attack_ex;     //特殊攻击状态定时器
	Timer timer_spwan_pea_ex;  //特殊子弹发射定时器

};

