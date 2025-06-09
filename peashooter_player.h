#pragma once
#include"Player.h"
#include<iostream>
// �㶹����ϵ�ж���ͼ��
extern Atlas atlas_peashooter_idle_left;         // �㶹���ֳ������Ĭ�϶���ͼ��
extern Atlas atlas_peashooter_idle_right;        // �㶹���ֳ����ҵ�Ĭ�϶���ͼ��
extern Atlas atlas_peashooter_run_left;          // �㶹���ֳ�����ı��ܶ���ͼ��
extern Atlas atlas_peashooter_run_right;         // �㶹���ֳ����ҵı��ܶ���ͼ��
extern Atlas atlas_peashooter_attack_ex_left;    // �㶹���ֳ���������⹥������ͼ��
extern Atlas atlas_peashooter_attack_ex_right;   // �㶹���ֳ����ҵ����⹥������ͼ��
extern Atlas atlas_peashooter_die_left;          // �㶹���ֳ��������������ͼ��
extern Atlas atlas_peashooter_die_right;         // �㶹���ֳ����ҵ���������ͼ��
class peashooter_player : public Player
{
public:
	peashooter_player() {
		animation_idle_left.set_atlas(&atlas_peashooter_idle_left);
		animation_idle_right.set_atlas(&atlas_peashooter_idle_right);
		animation_run_left.set_atlas(&atlas_peashooter_run_left);
		animation_run_right.set_atlas(&atlas_peashooter_run_right);

		animation_idle_left.set_interval(75);
		animation_idle_right.set_interval(75);
		animation_run_left.set_interval(75);
		animation_run_right.set_interval(75);
	}
	~peashooter_player() = default;

	void on_update(int delta) {
		Player::on_update(delta); // ���û���ĸ��·���
		std::cout << "�㶹�������ڸ���" << std::endl;
	}

	void on_draw(const Camera& camera) {
		Player::on_draw(camera); // ���û���Ļ��Ʒ���
	}

	void on_input(const ExMessage& msg) {
		Player::on_input(msg);
	}
}
;
