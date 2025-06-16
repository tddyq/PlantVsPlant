#pragma once
#include <graphics.h>
#include"Vector2.h"
#include"Animation.h"
#include"PlayerID.h"
#include"Platform.h"

extern std::vector<Platform> platform_list; // ƽ̨�б�
class Camera;
class Player
{
public:

	Player(){
		current_animation = &animation_idle_right; // Ĭ�ϳ����Ҳ�Ĵ�������

		timer_attack_cd.set_wait_time(attack_cd);
		timer_attack_cd.set_one_shot(true);
		timer_attack_cd.set_callback([&]() {
			can_attack = true; // ������ȴ������������
			});
	}


	~Player() = default;

	virtual void on_update(int delta) {
		int direction = is_left_key_down - is_right_key_down;

		if (direction != 0) {
			is_facing_right = (direction > 0);
			current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
			float distance = direction * run_velocity * delta; //��һ֡����ҵ��ƶ�����
			on_run(distance); // �������λ��
		}
		else {
			current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;	

		}
		if (current_animation == NULL) {
			std::cout << "current_animation is NULL" << std::endl;
		}
		current_animation->on_update(delta);
		move_and_collide(delta); // ����λ�ú���ײ���

		timer_attack_cd.on_update(delta); // ���¹�����ȴ��ʱ��
	}
	virtual void on_draw(const Camera& camera) {
		current_animation->on_draw(camera, position.x, position.y);
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
				case 0x47:
					if (mp >= 100) {
						on_attack_ex();
						mp = 0;
					}
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
				case VK_OEM_2:
					if (mp >= 100) {
						on_attack_ex();
						mp = 0;
					}
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
	}
	virtual void on_jump() {
		
		if (velocity.y != 0 || is_attack_ex) {
			return;
		}
		velocity.y += jump_velocity;

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

	// ��ȡλ�����꺯�� (ע��ƴд)
	const Vector2& get_postion() const
	{
		return position;
	}

	// ��ȡ����ߴ纯��
	const Vector2& get_size() const
	{
		return size;
	}
protected:
	void move_and_collide(int delta) {
		velocity.y += gravity * delta;
		position += velocity * (float)delta;

		if (velocity.y > 0) {
			for (const Platform& platform : platform_list) {
				const Platform::CollisionShape& shape = platform.shape;
				bool is_collide_x = (max(position.x + size.x, shape.right) - min(position.x, shape.left)
					<= size.x + (shape.right - shape.left));
				bool is_collide_y = (shape.y >= position.y && shape.y <= position.y + size.y);
				if (is_collide_x && is_collide_y) {
					position.y = shape.y - size.y;
					velocity.y = 0; // ���ô�ֱ�ٶ�

					break;
				}
			}
		}
	}

protected:
	const float run_velocity = 0.55f; // �ܲ��ٶ�
	const float gravity = 1.6e-3f; // �������ٶ�
	const float jump_velocity = -0.85f; // ��Ծ���ٶ�
protected:
	Vector2 size;     // �����ײ�ߴ��С
	Vector2 position;
	Vector2 velocity; // �ٶ�����

	Animation animation_idle_left;  // ��������������
	Animation animation_idle_right; // �������������ң�
	Animation animation_run_left;   // �����ܲ�����
	Animation animation_run_right;  //�����ܲ�����
	Animation animation_attack_ex_left;  // ����������⹥������
	Animation animation_attack_ex_right; // �����ҵ����⹥������

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
};

