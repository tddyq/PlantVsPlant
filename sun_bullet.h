#pragma once
#include"bullet.h"
#include"Animation.h"
extern Atlas atlas_sun;                          // 日光动画图集
extern Atlas atlas_sun_explode;                  // 日光爆炸动画图集
extern Camera main_camera;                // 主摄像机对象
class sun_bullet:public bullet
{
public:
	sun_bullet() {
		size.x = 96, size.y = 96;

		damage = 20;

		animation_idle.set_atlas(&atlas_sun);
		animation_idle.set_interval(50);

		animation_explode.set_atlas(&atlas_sun_explode);
		animation_explode.set_interval(50);
		animation_explode.set_loop(false);
		animation_explode.set_callback([&]() {can_remove = true; });

		IMAGE* frame_idle = animation_idle.get_frame();
		IMAGE* frame_explode = animation_explode.get_frame();
		explode_render_offset.x = frame_explode->getwidth() / 2.0f - frame_idle->getwidth() / 2.0f;		
		explode_render_offset.y = frame_explode->getheight() / 2.0f - frame_idle->getheight() / 2.0f;

	}
	~sun_bullet() = default;
	void on_collide() {
		bullet::on_collide();
		
		main_camera.shake(5, 250);

		mciSendString(_T("play sun_explode from 0"), NULL, 0, NULL);
	}
	void on_update(int delta) {
		if (valid) {
			velocity.y += grivate * delta;
			position.y += velocity.y * (float)delta;
			position.x += velocity.x * (float)delta;
		}
		if (!valid) {
			animation_explode.on_update(delta);

		}
		else {
			animation_idle.on_update(delta);
		}

		if (check_if_exceeds_screen()) {
			can_remove = true;
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
	const float grivate = 1e-3f;
private:
	Animation animation_idle;        //日光炸弹默认动画
	Animation animation_explode;     //日光炸弹爆炸动画
	Vector2 explode_render_offset;   //爆炸动画偏移量
};

