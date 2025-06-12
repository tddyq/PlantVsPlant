#pragma once
#include"Player.h"
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
class sunflower_player :  public Player
{
public:
	sunflower_player() {
		animation_idle_left.set_atlas(&atlas_sunflower_idle_left);
		animation_idle_right.set_atlas(&atlas_sunflower_idle_right);
		animation_run_left.set_atlas(&atlas_sunflower_run_left);
		animation_run_right.set_atlas(&atlas_sunflower_run_right);

		animation_idle_left.set_interval(75);
		animation_idle_right.set_interval(75);
		animation_run_left.set_interval(75);
		animation_run_right.set_interval(75);

		size.x = 96, size.y = 96;
	}
	~sunflower_player() = default;

	void on_update(int delta) {
		Player::on_update(delta); // ���û���ĸ��·���
		std::cout << "���տ����ڸ���" << std::endl;
	}

	void on_draw(const Camera& camera) {
		Player::on_draw(camera); // ���û���Ļ��Ʒ���
	}

	void on_input(const ExMessage& msg) {
		// ����������߼�
		Player::on_input(msg);
	}
};

