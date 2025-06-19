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
extern Atlas atlas_run_effect;                   // ������Ч����ͼ��
extern Atlas atlas_jump_effect;                  // ��Ծ��Ч����ͼ��
extern Atlas atlas_land_effect;                  // �����Ч����ͼ��
extern std::vector<Platform> platform_list; // ƽ̨�б�
extern std::vector<bullet*> bullet_list; // �ӵ��б�
extern bool is_debug;
class Camera;
class Player
{
public:

	Player(){
		current_animation = &animation_idle_right; // Ĭ�ϳ����Ҳ�Ĵ�������

		// ��Ծ��Ч��������
		animation_jump_effect .set_atlas(&atlas_jump_effect);
		animation_jump_effect.set_interval(25);
		animation_jump_effect.set_loop(false);
		animation_jump_effect.set_callback([&]()
			{
				is_jump_effect_visible = false;
			});

		// �����Ч��������
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
			can_attack = true; // ������ȴ������������
			});

		// �����޵�״̬��ʱ��
		timer_invulnerable.set_wait_time(750);         // ����750����ĵȴ�ʱ��
		timer_invulnerable.set_one_shot(true);         // ����Ϊ���δ���ģʽ
		timer_invulnerable.set_callback([&]()          // ���ö�ʱ��������Ļص�����
			{
				is_invulnerable = false;                   // ȡ���޵�״̬
			});

		// �����޵�״̬��˸Ч����ʱ��
		timer_invulnerable_blink.set_wait_time(75);    // ����75����ĵȴ�ʱ��
		timer_invulnerable_blink.set_callback([&]()    // ���ö�ʱ���ص�����
			{
				// �л�����֡��ʾ״̬��ʵ����˸Ч����
				is_showing_sketch_frame = !is_showing_sketch_frame;
			});

		// �����ܲ���Ч���ɶ�ʱ��
		timer_run_effect_generation.set_wait_time(75);  // ����75������
		timer_run_effect_generation.set_callback([&]()  // ���ûص�����(���ò���)
			{
				Vector2 particle_position;                   // ����λ������
				IMAGE* frame = atlas_run_effect.get_image(0); // ��ȡ�ܲ���Ч��һ֡
				// �������Ӿ���λ��
				particle_position.x = position.x + (size.x - frame->getwidth()) / 2;
				particle_position.y = position.y + size.y - frame->getheight();
				// ���������Ӳ���ӵ��б�(��������45֡)
				particle_list.emplace_back(particle_position, &atlas_run_effect, 45);
			});

		// ����������Ч���ɶ�ʱ��
		timer_die_effect_generation.set_wait_time(35);   // ���ø��̵�35������
		timer_die_effect_generation.set_callback([&]()   // ���ûص�����
			{
				Vector2 particle_position;                   // ����λ������
				IMAGE* frame = atlas_run_effect.get_image(0); // ��ȡͬһͼ���ĵ�һ֡
				// ʹ����ͬ�ľ����㷨����λ��
				particle_position.x = position.x + (size.x - frame->getwidth()) / 2;
				particle_position.y = position.y + size.y - frame->getheight();
				// ����������(��������150֡)
				particle_list.emplace_back(particle_position, &atlas_run_effect, 150);
			});
	}


	~Player() = default;

	virtual void on_update(int delta) {
		int direction = is_left_key_down - is_right_key_down;

		if (direction != 0) {
			if (!is_attack_ex) { // �������ִ�����⹥�����������ƶ�
				is_facing_right = (direction > 0);
			}
			
			current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
			float distance = direction * run_velocity * delta; //��һ֡����ҵ��ƶ�����
			on_run(distance); // �������λ��
		}
		else {
			current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;	
			timer_run_effect_generation.pause(); // ��ͣ�ܲ���Ч���ɼ�ʱ��
		}
		if (is_attack_ex) {
			current_animation = is_facing_right ? &animation_attack_ex_right : &animation_attack_ex_left;
		}
		if (current_animation == NULL) {
			std::cout << "current_animation is NULL" << std::endl;
		}
		current_animation->on_update(delta);
		animation_jump_effect.on_update(delta);        // ������Ծ��Ч����
		animation_land_effect.on_update(delta);        // ���������Ч����

		timer_attack_cd.on_update(delta);              // ���¹�����ȴ��ʱ��
		timer_invulnerable.on_update(delta);           // �����޵�״̬��ʱ��
		timer_invulnerable_blink.on_update(delta);     // �����޵�״̬��˸��ʱ��
		timer_run_effect_generation.on_update(delta);  // �����ܲ���Ч���ɼ�ʱ��
		if (hp <= 0) {
			timer_die_effect_generation.on_update(delta); // ����������Ч���ɼ�ʱ��
		}
		//ɾ�������б���ʧЧ�����Ӳ���ʣ�µ����Ӹ���
		particle_list.erase(std::remove_if(
			particle_list.begin(), particle_list.end(),
			[](const Particle& particle) {
				return !particle.check_valid(); // ɾ����Ч������
			}
		),
			particle_list.end()
		);
		for (Particle& particle : particle_list) {
			particle.on_update(delta); // ����ÿ������
		}

		if (is_showing_sketch_frame) {
			sketch_image(current_animation->get_frame(), &img_sketch);
		}

		move_and_collide(delta); // ����λ�ú���ײ���
	}
	virtual void on_draw(const Camera& camera) {
		if (is_jump_effect_visible) { // �����Ծ��Ч�ɼ����������Ծ��Ч
			animation_jump_effect.on_draw(camera, jump_effect_position.x, jump_effect_position.y);
		}
		if (is_land_effect_visible) {
			animation_land_effect.on_draw(camera, land_effect_position.x, land_effect_position.y);
		}

		for (Particle& particle : particle_list) {
			particle.on_draw(camera); // ����ÿ������
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
		//��һ���жϰ���״̬
		//�ڶ����ж����ID
		//�������жϰ�������
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
						timer_attack_cd.restart(); // ���ù�����ȴ��ʱ��
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
					//'��'
				case VK_RIGHT:
					is_left_key_down = true;
					break;
					//'��'
				case VK_LEFT:
					is_right_key_down = true;
					break;
					//'��'
				case VK_UP:
					on_jump();
					break;
				case VK_OEM_PERIOD:
					if (can_attack) {
						on_attack();
						can_attack = false;
						timer_attack_cd.restart(); // ���ù�����ȴ��ʱ��
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
					//'��'
				case VK_RIGHT:
					is_left_key_down = false;
					break;
					//'��'
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
		animation_jump_effect.reset(); // ������Ծ��Ч����
		IMAGE* effect_frame = animation_jump_effect.get_frame();
		jump_effect_position.x = position.x + (size.x - effect_frame->getwidth()) / 2; // ������Ծ��Чλ��
		jump_effect_position.y = position.y + size.y - effect_frame->getheight();      // ��Ծ��Чλ������ҽ���
	
	}
	virtual void on_land() {
		is_land_effect_visible = true;
		animation_land_effect.reset(); // ������Ծ��Ч����
		IMAGE* effect_frame = animation_land_effect.get_frame();
		land_effect_position.x = position.x + (size.x - effect_frame->getwidth()) / 2; // ������Ծ��Чλ��
		land_effect_position.y = position.y + size.y - effect_frame->getheight();      // ��Ծ��Чλ������ҽ���
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
		float last_velocity = velocity.y; // ������һ֡�Ĵ�ֱ�ٶ�

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
					float last_tick_foot_pos_y = position.y + size.y - delta_pos_y; // ��һ֡�Ų�λ��
					if (last_tick_foot_pos_y <= shape.y) {
						position.y = shape.y - size.y;
						velocity.y = 0; // ���ô�ֱ�ٶ�

						if (last_velocity != 0) {
							on_land(); // ��������¼�
						}

						break;
					}
					
				}
			}
		}
		if (!is_invulnerable) {
			for (bullet* bullet : bullet_list) {
				if (!bullet->get_valid() || bullet->get_collide_target() != id) {
					continue;   // ����ӵ���Ч�����ڵ�ǰ��ң�������
				}
				if (bullet->check_collision(position, size)) {
					make_invulnerable(); // �����޵�״̬
					bullet->on_collide(); // �����ӵ���ײ
					bullet->set_vaild(false); // �����ӵ�Ϊ��Ч״̬
					hp -= bullet->get_damage(); // �����������ֵ
				}
			}
		}
		
	}
	void make_invulnerable() {
		is_invulnerable = true; // �����޵�״̬
		timer_invulnerable.restart(); // �����޵�״̬��ʱ��
		timer_invulnerable_blink.restart(); // �����޵�״̬��˸��ʱ��
	}
protected:
	const float run_velocity = 0.55f; // �ܲ��ٶ�
	const float gravity = 1.6e-3f; // �������ٶ�
	const float jump_velocity = -0.85f; // ��Ծ���ٶ�
protected:
	Vector2 size;     // �����ײ�ߴ��С
	Vector2 position;
	Vector2 velocity; // �ٶ�����

	Animation animation_idle_left;             // ��������������
	Animation animation_idle_right;            // �������������ң�
	Animation animation_run_left;              // �����ܲ�����
	Animation animation_run_right;             //�����ܲ�����
	Animation animation_attack_ex_left;        // ����������⹥������
	Animation animation_attack_ex_right;       // �����ҵ����⹥������
	Animation animation_jump_effect;           // ��Ծ��Ч����
	Animation animation_land_effect;           // �����Ч����

	bool is_jump_effect_visible;
	bool is_land_effect_visible;
	             
	Vector2 jump_effect_position;              // ��Ծ��Чλ��
	Vector2 land_effect_position;              // �����Чλ��
	             
	Animation* current_animation = nullptr;

	PlayerID id = PlayerID::P1;

	bool is_left_key_down = false;
	bool is_right_key_down = false;

	bool is_facing_right = true;    // �Ƿ������Ҳ�

	int attack_cd = 500; // ������ȴʱ�䣨���룩
	bool can_attack = true;
	Timer timer_attack_cd;
	
	bool is_attack_ex = false; // �Ƿ�ʹ�����⹥��

	int mp = 0;
	int hp = 100;

	IMAGE img_sketch; // ��ӰͼƬ
	bool is_invulnerable = false;           // �Ƿ����޵�״̬
	bool is_showing_sketch_frame = false;   //��ǰ֡�Ƿ���ʾ��Ӱ
	Timer timer_invulnerable;               // �޵�״̬��ʱ��
	Timer timer_invulnerable_blink;         // �޵�״̬��˸��ʱ��

	std::vector<Particle> particle_list;    // �����б�������Ч

	Timer timer_run_effect_generation;      // �ܲ���Ч���ɼ�ʱ��
	Timer timer_die_effect_generation;      // ������Ч���ɼ�ʱ��
};

