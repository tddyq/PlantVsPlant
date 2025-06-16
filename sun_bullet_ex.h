#pragma once
#include"bullet.h"
#include"Animation.h"


extern Camera main_camera;                // �����������
extern Atlas atlas_sun_ex;                       // �����չ⶯��ͼ��
extern Atlas atlas_sun_ex_explode;               // �����չⱬը����ͼ��
class sun_bullet_ex:public bullet
{
public:
	sun_bullet_ex() {
		// �������տ���������
		size.x = 288;                  // ������
		size.y = 288;                  // ����߶�

		damage = 20;                   // ����˺�ֵ

		// ���ÿ���״̬��������
		animation_idle.set_atlas(&atlas_sun_ex);          // �󶨿���״̬ͼ��
		animation_idle.set_interval(50);                  // ����֡���ʱ��(ms)
		animation_idle.set_loop(true);                    // ����Ϊѭ������

		// ���ñ�ը״̬��������
		animation_explode.set_atlas(&atlas_sun_ex_explode); // �󶨱�ըͼ��
		animation_explode.set_interval(50);                // ����֡���ʱ��(ms)
		animation_explode.set_loop(false);                 // ���ò�ѭ��
		animation_explode.set_callback([&]() {             // ���ö��������ص�
			can_remove = true;                             // ����������ǿ��Ƴ�
			});

		// ��ȡ����״̬�Ķ���֡
		IMAGE* frame_idle = animation_idle.get_frame();     // ��ȡ����״̬��ǰ֡
		IMAGE* frame_explode = animation_explode.get_frame(); // ��ȡ��ը״̬��ǰ֡

		// ���㱬ը��������Ⱦƫ����
		// ȷ����ը�����ڿ��ж��������Ͼ�����ʾ
		explode_render_offset.x = (frame_idle->getwidth() - frame_explode->getwidth()) / 2.0f;
		explode_render_offset.y = (frame_idle->getheight() - frame_explode->getheight()) / 2.0f;
	}
	~sun_bullet_ex() = default;
	void on_collide() {
		bullet::on_collide();

		main_camera.shake(5, 350);

		mciSendString(_T("play sun_explode from 0"), NULL, 0, NULL);
	}
	bool check_collision() {
		// ��������ײ����
		bool is_collide_x = (max(this->position.x + this->size.x, position.x + size.x)
			- min(this->position.x, position.x) <= this->size.x + size.x);

		bool is_collide_y = (max(this->position.y + this->size.y, position.y + size.y)
			- min(this->position.y, position.y) <= this->size.y + size.y);

		// ��ײ�����ͬʱ����X��Y������ص�
		return is_collide_x && is_collide_y;
	}
	void on_update(int delta) {
		if (valid) {

			position += velocity * (float)delta; // ����λ��
		}
		if (!valid) {
			animation_explode.on_update(delta); // ���±�ը����
		}
		else {
			animation_idle.on_update(delta); // ���¿��ж���
		}

		if (check_if_exceeds_screen()) { // ����Ƿ񳬳���Ļ��Χ
			can_remove = true; // ���ÿ��Ƴ����
		}
	}
	void on_draw(const Camera& camera)const {
		if (valid) {
			animation_idle.on_draw(camera, (int)position.x, (int)position.y);
		}
		else {
			animation_explode.on_draw(camera,
				(int)position.x + (int)explode_render_offset.x,
				(int)position.y + (int)explode_render_offset.y);
		}
	}

private:
	Animation animation_idle;        //�չ�ը��Ĭ�϶���
	Animation animation_explode;     //�չ�ը����ը����


	Vector2 explode_render_offset;   //��ը����ƫ����
};

