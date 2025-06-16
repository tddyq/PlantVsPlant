#pragma once
#include"Vector2.h"
#include"Timer.h"
class Camera
{
public:
	Camera() {
		timer_shake.set_one_shot(true);     //设置为单次触发
		timer_shake.set_callback([&]() {    //设置摄像机未抖动并重置位置
			is_shaking = false;
			reset();
			});
	}
	~Camera() = default;

	const Vector2& get_position()const {
		return position;
	}

	void reset() {
		position.x = 0;
		position.y = 0;
	}

	void on_update(int delta) {
		timer_shake.on_update(delta); //更新抖动计时器

		if (is_shaking) {
			position.x = (-50 + rand() % 100) / 50.0f * shaking_strength;
			position.y = (-50 + rand() % 100) / 50.0f * shaking_strength;
		}
	}

	void shake(float strength, int duration) {
		is_shaking = true;                   //设置为正在抖动状态
		shaking_strength = strength;         //设置抖动幅度

		timer_shake.set_wait_time(duration); //设置定时器抖动持续时间
		timer_shake.restart();               //重置定时器计时器持续时间与触发状态
	}
private:
	Vector2 position;             //摄像机位置
	Timer timer_shake;            //摄像机抖动计时器
	bool is_shaking = false;      //是否正在抖动
	float shaking_strength = 0;   //摄相机抖动幅度
};

