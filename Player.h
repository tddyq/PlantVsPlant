#pragma once
#include <graphics.h>
#include"Vector2.h"
#include"Animation.h"
#include"PlayerID.h"
class Camera;
class Player
{
public:

	Player(){
		current_animation = &animation_idle_right; // Ĭ�ϳ����Ҳ�Ĵ�������
	}


	~Player() = default;

	virtual void on_update(int delta) {
		int direction = is_left_key_down - is_right_key_down;

		if (direction != 0) {
			is_facing_right = (direction > 0);
			current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
		}
		else {
			current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;	

		}
		current_animation->on_update(delta);
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
				case 0x41:
					is_left_key_down = true;
					break;
					//'D'
				case 0x44:
					is_right_key_down = true;
					break;
				default:
					break;
				}
				break;
			case PlayerID::P2:
				switch (msg.vkcode) {
					//'��'
				case VK_LEFT:
					is_left_key_down = true;
					break;
					//'��'
				case VK_RIGHT:
					is_right_key_down = true;
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
				case 0x41:
					is_left_key_down = false;
					break;
					//'D'
				case 0x44:
					is_right_key_down = false;
					break;
				default:
					break;
				}
				
				break;
			case PlayerID::P2:
				switch (msg.vkcode) {
					//'��'
				case VK_LEFT:
					is_left_key_down = false;
					break;
					//'��'
				case VK_RIGHT:
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
	void set_position(float x, float y) {
		position.x = x;
		position.y = y;

	}
	void set_id(PlayerID player_id) {
		id = player_id;
	}
protected:
	Vector2 position;

	Animation animation_idle_left;  // ��������������
	Animation animation_idle_right; // �������������ң�
	Animation animation_run_left;   // �����ܲ�����
	Animation animation_run_right;  //�����ܲ�����

	Animation* current_animation = nullptr;

	PlayerID id = PlayerID::P1;

	bool is_left_key_down = false;
	bool is_right_key_down = false;

	bool is_facing_right = true;    // �Ƿ������Ҳ�
};

