#pragma once
#include"vector2.h"
#include"playerID.h"
#include<graphics.h>
#include<functional>
class bullet
{
public:
	bullet() = default;
	~bullet() = default;

	int get_damage() {
		return damage;
	}
	void set_damage(int val) {
		damage = val;
	}
	const Vector2& get_position() const {
		return position;
	}
	const Vector2& get_size() const {
		return size;
	}
	void set_velocity(float x, float y) {
		velocity.x = x;
		velocity.y = y;
	}
	const Vector2& get_velocity() const {
		return velocity;
	}
	void set_collide_target(PlayerID id) {
		target_id = id;
	}
	PlayerID get_collide_target() const {
		return target_id;
	}
	void set_vaild(bool val) {
		valid = val;
	}
	bool get_valid() {
		return valid;
	}
	bool check_can_remove() {
		return can_remove;
	}
	
	void set_callback(std::function<void()> callback) {
		callback = callback;
	}
	virtual void on_collide() {
		if (callback) {
			callback();
		}
	}
	virtual bool check_collision(const Vector2& position, const Vector2& size) {
		return this->position.x + this->size.x/2 >= position.x
			&& this->position.x - this->size.x / 2 <= position.x + size.x &&
			this->position.y + this->size.y / 2 >= position.y &&
			this->position.y - this->size.y / 2 <= position.y + size.y;
	}
protected:
	Vector2 size;                   //子弹尺寸
	Vector2 position;               //子弹位置
	Vector2 velocity;               //子弹速度	
	int damage = 10;               //子弹伤害
	bool valid = true;              //子弹是否有效
	bool can_remove = false;        //子弹是否可以移除
	std::function<void()> callback; // 子弹碰撞回调函数
	PlayerID target_id = PlayerID::P1; // 子弹目标玩家ID
protected:

	//不应该加入窗口位置运算吗
	bool check_if_exceeds_screen() {
		return (position.x + size.x <= 0 || position.x >= getwidth()
			|| position.y + size.y <= 0 || position.y >= getheight());
	}
};

