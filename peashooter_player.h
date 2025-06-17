#pragma once
#include"Player.h"
#include"Animation.h"
#include"pea_bullet.h"
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

//extern std::vector<bullet*> bullet_list; // 子弹列表
class peashooter_player : public Player
{
public:
	peashooter_player() {
		animation_idle_left.set_atlas(&atlas_peashooter_idle_left);
		animation_idle_right.set_atlas(&atlas_peashooter_idle_right);
		animation_run_left.set_atlas(&atlas_peashooter_run_left);
		animation_run_right.set_atlas(&atlas_peashooter_run_right);
		animation_attack_ex_left.set_atlas(&atlas_peashooter_attack_ex_left);
		animation_attack_ex_right.set_atlas(&atlas_peashooter_attack_ex_right);

		animation_idle_left.set_interval(75);
		animation_idle_right.set_interval(75);
		animation_run_left.set_interval(75);
		animation_run_right.set_interval(75);
		animation_attack_ex_left.set_interval(75);
		animation_attack_ex_right.set_interval(75);
		size.x = 96, size.y = 96;
		//初始化定时器
		timer_attack_ex.set_wait_time(attack_ex_duration);
		timer_attack_ex.set_one_shot(true);
		timer_attack_ex.set_callback([&]() {
			is_attack_ex = false;
			});

		timer_spwan_pea_ex.set_wait_time(100);
		timer_spwan_pea_ex.set_callback([&]() {
			spawn_pea_bullet(speed_pea_ex); // 每100毫秒发射一次特殊子弹
			});
		attack_cd = 100;
	}
	~peashooter_player() = default;

	void on_update(int delta) {
		Player::on_update(delta); // 调用基类的更新方法
		
		if (is_attack_ex) {
			main_camera.shake(5, 100);
			timer_attack_ex.on_update(delta); // 更新特殊攻击定时器
			timer_spwan_pea_ex.on_update(delta); // 更新特殊攻击定时器
		}
	}

	void on_draw(const Camera& camera) {
		Player::on_draw(camera); // 调用基类的绘制方法
	}

	void on_input(const ExMessage& msg) {
		Player::on_input(msg);
	}

	void spawn_pea_bullet(float speed) {
		bullet* bullet = new pea_bullet();

		Vector2  bullet_position, bullet_velocity;
		const Vector2& bullet_size = bullet->get_size();
		bullet_position.x = is_facing_right
			? position.x +size.x - bullet_size.x/2
			: position.x + bullet_size.x / 2;
		bullet_position.y = position.y /*+ size.y / 2*/;
		bullet_velocity.x = is_facing_right ? speed : -speed;
		bullet_velocity.y = 0;

		bullet->set_position(bullet_position.x, bullet_position.y);
		bullet->set_velocity(bullet_velocity.x, bullet_velocity.y);

		bullet->set_collide_target(id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);

		bullet->set_callback([&]() {mp += 25; });

		bullet_list.push_back(bullet);
	}
	void on_attack() {
		spawn_pea_bullet(speed_pea);

		switch (rand() % 2) {
		case 0:
			mciSendString(_T("play pea_shoot_1 from 0"), NULL, 0, NULL);
			break;
		case 1:
			mciSendString(_T("play pea_shoot_2 from 0"), NULL, 0, NULL);
		}
	}
	void on_attack_ex() {
		is_attack_ex = true;
		timer_attack_ex.restart(); // 重置特殊攻击定时器

		is_facing_right ? animation_attack_ex_right.reset() : animation_attack_ex_left.reset(); // 重置特殊攻击动画
		mciSendString(_T("play pea_shoot_ex from 0"), NULL, 0, NULL); // 播放特殊攻击音效

	}
private:
	const float speed_pea = 0.75f;
	const float speed_pea_ex = 1.5f;        // 豌豆射手子弹速度
	const int attack_ex_duration = 2500;    //特殊攻击状态持续时间(ms)
private:
	Timer timer_attack_ex;     //特殊攻击状态定时器
	Timer timer_spwan_pea_ex;  //特殊子弹发射定时器

}
;
