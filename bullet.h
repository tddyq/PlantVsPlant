#pragma once
#include"vector2.h"
#include"playerID.h"
#include<graphics.h>
#include<functional>
extern bool is_debug;
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
	void set_position(float x, float y) {
		position.x = x;
		position.y = y;
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
	bool check_can_remove()const {
		return can_remove;
	}
	
	void set_callback(std::function<void()> callback) {
		this->callback = callback;
	}
	virtual void on_collide() {
		if (callback) {
			callback();
		}
	}
	virtual bool check_collision(const Vector2& position, const Vector2& size) {
		bool is_collide_x = (max(this->position.x + this->size.x, position.x + size.x)
			- min(this->position.x, position.x) <= this->size.x + size.x);

		bool is_collide_y = (max(this->position.y + this->size.y, position.y + size.y)
			- min(this->position.y, position.y) <= this->size.y + size.y);

		return is_collide_x && is_collide_y;
	}
	virtual void on_update(int delta){}
	virtual void on_draw(const Camera& camera)const {
		if (is_debug) {
			setfillcolor(RGB(255,255, 255));
			setlinecolor(RGB(255, 255, 255));
			rectangle((int)position.x,(int)position.y,
				(int)(position.x + size.x), (int)(position.y + size.y));
			solidcircle((int)(position.x + size.x / 2), (int)(position.y + size.y / 2), 5);
		}
	}
protected:
	Vector2 size;                   //�ӵ��ߴ�
	Vector2 position;               //�ӵ�λ��
	Vector2 velocity;               //�ӵ��ٶ�	
	int damage = 10;               //�ӵ��˺�
	bool valid = true;              //�ӵ��Ƿ���Ч
	bool can_remove = false;        //�ӵ��Ƿ�����Ƴ�
	std::function<void()> callback; // �ӵ���ײ�ص�����
	PlayerID target_id = PlayerID::P1; // �ӵ�Ŀ�����ID
protected:

	//��Ӧ�ü��봰��λ��������
	bool check_if_exceeds_screen() {
		return (position.x + size.x <= 0 || position.x >= getwidth()
			|| position.y + size.y <= 0 || position.y >= getheight());
	}
};

