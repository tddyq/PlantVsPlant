#pragma once
#include <graphics.h>
#include"Vector2.h"
#include"Animation.h"
#include"PlayerID.h"
#include"Platform.h"

extern std::vector<Platform> platform_list; // 平台列表
class Camera;
class Player
{
public:

	Player(){
		current_animation = &animation_idle_right; // 默认朝向右侧的待机动画
	}


	~Player() = default;

	virtual void on_update(int delta) {
		int direction = is_left_key_down - is_right_key_down;

		if (direction != 0) {
			is_facing_right = (direction > 0);
			current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
			float distance = direction * run_velocity * delta; //这一帧中玩家的移动距离
			on_run(distance); // 更新玩家位置
		}
		else {
			current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;	

		}
		current_animation->on_update(delta);
		move_and_collide(delta); // 更新位置和碰撞检测
	}
	virtual void on_draw(const Camera& camera) {
		current_animation->on_draw(camera, position.x, position.y);
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
		position.x += distance;
	}
	virtual void on_jump() {

		if (velocity.y != 0) {
			return;
		}
		velocity.y += jump_velocity;

	}
	void set_position(float x, float y) {
		position.x = x;
		position.y = y;

	}
	void set_id(PlayerID player_id) {
		id = player_id;
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
					velocity.y = 0; // 重置垂直速度

					break;
				}
			}
		}
	}

protected:
	const float run_velocity = 0.55f; // 跑步速度
	const float gravity = 1.6e-3f; // 重力加速度
	const float jump_velocity = -0.85f; // 跳跃初速度
protected:
	Vector2 size;     // 玩家碰撞尺寸大小
	Vector2 position;
	Vector2 velocity; // 速度向量

	Animation animation_idle_left;  // 待机动画（向左）
	Animation animation_idle_right; // 待机动画（向右）
	Animation animation_run_left;   // 向左跑步动画
	Animation animation_run_right;  //向右跑步动画

	Animation* current_animation = nullptr;

	PlayerID id = PlayerID::P1;

	bool is_left_key_down = false;
	bool is_right_key_down = false;

	bool is_facing_right = true;    // 是否面向右侧
};

