#pragma once
#include"Vector2.h"
#include"Timer.h"
class Camera
{
public:
	Camera() {
		timer_shake.set_one_shot(true);     //����Ϊ���δ���
		timer_shake.set_callback([&]() {    //���������δ����������λ��
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
		timer_shake.on_update(delta); //���¶�����ʱ��

		if (is_shaking) {
			position.x = (-50 + rand() % 100) / 50.0f * shaking_strength;
			position.y = (-50 + rand() % 100) / 50.0f * shaking_strength;
		}
	}

	void shake(float strength, int duration) {
		is_shaking = true;                   //����Ϊ���ڶ���״̬
		shaking_strength = strength;         //���ö�������

		timer_shake.set_wait_time(duration); //���ö�ʱ����������ʱ��
		timer_shake.restart();               //���ö�ʱ����ʱ������ʱ���봥��״̬
	}
private:
	Vector2 position;             //�����λ��
	Timer timer_shake;            //�����������ʱ��
	bool is_shaking = false;      //�Ƿ����ڶ���
	float shaking_strength = 0;   //�������������
};

