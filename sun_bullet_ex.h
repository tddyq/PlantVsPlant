#pragma once
#include"bullet.h"
#include"Animation.h"


extern Camera main_camera;                // 主摄像机对象
extern Atlas atlas_sun_ex;                       // 特殊日光动画图集
extern Atlas atlas_sun_ex_explode;               // 特殊日光爆炸动画图集
class sun_bullet_ex:public bullet
{
public:
	sun_bullet_ex() {
		// 设置向日葵物体属性
		size.x = 288;                  // 物体宽度
		size.y = 288;                  // 物体高度

		damage = 20;                   // 造成伤害值

		// 设置空闲状态动画属性
		animation_idle.set_atlas(&atlas_sun_ex);          // 绑定空闲状态图集
		animation_idle.set_interval(50);                  // 设置帧间隔时间(ms)
		animation_idle.set_loop(true);                    // 设置为循环播放

		// 设置爆炸状态动画属性
		animation_explode.set_atlas(&atlas_sun_ex_explode); // 绑定爆炸图集
		animation_explode.set_interval(50);                // 设置帧间隔时间(ms)
		animation_explode.set_loop(false);                 // 设置不循环
		animation_explode.set_callback([&]() {             // 设置动画结束回调
			can_remove = true;                             // 动画结束标记可移除
			});

		// 获取两种状态的动画帧
		IMAGE* frame_idle = animation_idle.get_frame();     // 获取空闲状态当前帧
		IMAGE* frame_explode = animation_explode.get_frame(); // 获取爆炸状态当前帧

		// 计算爆炸动画的渲染偏移量
		// 确保爆炸动画在空闲动画基础上居中显示
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
		// 检测矩形碰撞函数
		bool is_collide_x = (max(this->position.x + this->size.x, position.x + size.x)
			- min(this->position.x, position.x) <= this->size.x + size.x);

		bool is_collide_y = (max(this->position.y + this->size.y, position.y + size.y)
			- min(this->position.y, position.y) <= this->size.y + size.y);

		// 碰撞结果需同时满足X和Y方向的重叠
		return is_collide_x && is_collide_y;
	}
	void on_update(int delta) {
		if (valid) {

			position += velocity * (float)delta; // 更新位置
		}
		if (!valid) {
			animation_explode.on_update(delta); // 更新爆炸动画
		}
		else {
			animation_idle.on_update(delta); // 更新空闲动画
		}

		if (check_if_exceeds_screen()) { // 检查是否超出屏幕范围
			can_remove = true; // 设置可移除标记
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
	Animation animation_idle;        //日光炸弹默认动画
	Animation animation_explode;     //日光炸弹爆炸动画


	Vector2 explode_render_offset;   //爆炸动画偏移量
};

