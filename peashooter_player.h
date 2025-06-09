#pragma once
#include"Player.h"
#include<iostream>
// 豌豆射手系列动画图集
extern Atlas atlas_peashooter_idle_left;         // 豌豆射手朝向左的默认动画图集
extern Atlas atlas_peashooter_idle_right;        // 豌豆射手朝向右的默认动画图集
extern Atlas atlas_peashooter_run_left;          // 豌豆射手朝向左的奔跑动画图集
extern Atlas atlas_peashooter_run_right;         // 豌豆射手朝向右的奔跑动画图集
extern Atlas atlas_peashooter_attack_ex_left;    // 豌豆射手朝向左的特殊攻击动画图集
extern Atlas atlas_peashooter_attack_ex_right;   // 豌豆射手朝向右的特殊攻击动画图集
extern Atlas atlas_peashooter_die_left;          // 豌豆射手朝向左的死亡动画图集
extern Atlas atlas_peashooter_die_right;         // 豌豆射手朝向右的死亡动画图集
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
		Player::on_update(delta); // 调用基类的更新方法
		std::cout << "豌豆射手正在更新" << std::endl;
	}

	void on_draw(const Camera& camera) {
		Player::on_draw(camera); // 调用基类的绘制方法
	}

	void on_input(const ExMessage& msg) {
		Player::on_input(msg);
	}
}
;
