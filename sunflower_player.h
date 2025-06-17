#pragma once
#include"Player.h"
#include"Animation.h"
#include"sun_bullet.h"
#include"sun_bullet_ex.h"
#include<iostream>
// ���տ�ϵ�ж���ͼ��
extern Atlas atlas_sunflower_idle_left;          // ���տ��������Ĭ�϶���ͼ��
extern Atlas atlas_sunflower_idle_right;         // ���տ������ҵ�Ĭ�϶���ͼ��
extern Atlas atlas_sunflower_run_left;           // ���տ�������ı��ܶ���ͼ��
extern Atlas atlas_sunflower_run_right;          // ���տ������ҵı��ܶ���ͼ��
extern Atlas atlas_sunflower_attack_ex_left;     // ���տ�����������⹥������ͼ��
extern Atlas atlas_sunflower_attack_ex_right;    // ���տ������ҵ����⹥������ͼ��
extern Atlas atlas_sunflower_die_left;           // ���տ����������������ͼ��
extern Atlas atlas_sunflower_die_right;          // ���տ������ҵ���������ͼ��
extern Atlas atlas_sun_text;                     // ���ա��ı�����ͼ��

extern Player* player_1; // ���1
extern Player* player_2; // ���2
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

		// ����������⹥�������Ļص�����
		animation_attack_ex_left.set_callback([&]()
			{
				is_attack_ex = false;          // �������⹥��״̬
				is_sun_text_visible = false;      // ����̫�������ı�
			});

		// �����Ҳ����⹥�������Ļص�����
		animation_attack_ex_right.set_callback([&]()
			{
				is_attack_ex = false;          // �������⹥��״̬
				is_sun_text_visible = false;      // ����̫�������ı�
			});

		size.x = 96, size.y = 96;

		attack_cd = 250;
	}
	~sunflower_player() = default;

	void on_update(int delta) {
		Player::on_update(delta); // ���û���ĸ��·���

	}

	void on_draw(const Camera& camera) {
		Player::on_draw(camera); // ���û���Ļ��Ʒ���

		if (is_sun_text_visible) {
			Vector2 text_position;
			IMAGE* frame = animation_sun_text.get_frame();
			text_position.x = position.x - (size.x - frame->getwidth()) / 2;
			text_position.y = position.y - frame->getheight();
			animation_sun_text.on_draw(camera, (int)text_position.x, (int)text_position.y);
		}
	
	}

	void on_input(const ExMessage& msg) {
		// ����������߼�
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


		Vector2 bullet_position, bullet_velocity;  // �����ӵ�λ�ú��ٶ�����

		// ��ȡ�ӵ���Ŀ����ҵĳߴ�
		const Vector2& bullet_size = bullet->get_size();
		const Vector2& target_size = target_player->get_size();

		// ��ȡĿ����ҵ�λ��
		const Vector2& target_position = target_player->get_postion();

		// �����ӵ��ĳ�ʼλ��
		bullet_position.x = target_position.x + (target_size.x - bullet_size.x) / 2;
		bullet_position.y = -size.y;

		// �����ӵ����ٶ�����
		bullet_velocity.x = 0;
		bullet_velocity.y = speed_sun_ex;
		// �����ӵ�λ�ú��ٶ�
		bullet->set_position(bullet_position.x, bullet_position.y);
		bullet->set_velocity(bullet_velocity.x, bullet_velocity.y);

		// ����ID������ײĿ��
		bullet->set_collide_target(id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);

		// �����ӵ����лص�����������50��MPֵ��
		bullet->set_callback([&]() { mp += 50; });

		// ���ӵ������ӵ��б�
		bullet_list.push_back(bullet);

		mciSendString(_T("play sun_text from 0"), NULL, 0, NULL);
	}
private:
	const float speed_sun_ex = 0.15f;
	const Vector2 velocity_sun = { 0.25,-0.5f };
	Animation animation_sun_text;    //ͷ���ı�
	bool is_sun_text_visible = false;
private:
	Timer timer_attack_ex;     //���⹥��״̬��ʱ��
	Timer timer_spwan_pea_ex;  //�����ӵ����䶨ʱ��

};

