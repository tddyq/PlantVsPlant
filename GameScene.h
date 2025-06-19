#pragma once
#include"Player.h"
#include<iostream>
#include<vector>
#include"Scene.h"
#include"Platform.h"
#include"bullet.h"
#include"status_bar.h"
// 游戏场景元素图片资源定义
extern IMAGE img_sky;            // 天空图片
extern IMAGE img_hills;          // 山脉图片
extern IMAGE img_platform_large; // 大型平台图片
extern IMAGE img_platform_small; // 小型平台图片

extern SceneManager scene_manager;               // 场景管理器对象
extern std::vector<Platform> platform_list; // 平台列表
extern std::vector<bullet*> bullet_list; // 子弹列表

extern Player* player_1; // 玩家1
extern Player* player_2; // 玩家2
extern IMAGE* img_player_1_avatar; // 玩家1头像
extern IMAGE* img_player_2_avatar; // 玩家2头像

extern Camera main_camera;                // 主摄像机对象

extern void putimage_alpha(const Camera& camera, int x, int y, IMAGE* img);   //播放动画
class GameScene : public Scene
{
public:
	GameScene() = default;
	~GameScene() = default;

	void on_enter() {
		status_bar_p1.set_avatar(img_player_1_avatar); // 设置玩家1头像
		status_bar_p2.set_avatar(img_player_2_avatar); // 设置玩家2头像

		status_bar_p1.set_position(235, 625);
		status_bar_p2.set_position(675, 625);
		
		/*
		为防止抖动时出现黑边,天空图片大于窗口尺寸
		相减得到负值使得图片在窗口外加载得以包裹整个窗口
		*/
		pos_img_sky.x = (getwidth() - img_sky.getwidth()) / 2;   // 计算天空图片位置
		pos_img_sky.y = (getheight() - img_sky.getheight()) / 2; // 计算天空图片位置

		pos_img_hills.x = (getwidth() - img_hills.getwidth()) / 2; // 计算山脉图片位置
		pos_img_hills.y = (getheight() - img_hills.getheight()) / 2; // 计算山脉图片位置

		platform_list.resize(4);

		Platform& large_platform = platform_list[0];
		large_platform.img = &img_platform_large; // 设置大型平台图片
		large_platform.render_pos.x = 122;
		large_platform.render_pos.y = 455;
		large_platform.shape.left = (float)large_platform.render_pos.x + 30;
		large_platform.shape.right = (float)large_platform.render_pos.x + img_platform_large.getwidth() - 30;
		large_platform.shape.y = (float)large_platform.render_pos.y + 60;

		// 设置第一个小型平台
		Platform& small_platform_1 = platform_list[1];
		small_platform_1.img = &img_platform_small;
		small_platform_1.render_pos.x = 175;
		small_platform_1.render_pos.y = 360;
		small_platform_1.shape.left = (float)small_platform_1.render_pos.x + 40;
		small_platform_1.shape.right = (float)small_platform_1.render_pos.x + img_platform_small.getwidth() - 40;
		small_platform_1.shape.y = (float)small_platform_1.render_pos.y + img_platform_small.getheight() / 2;

		// 设置第二个小型平台
		Platform& small_platform_2 = platform_list[2];
		small_platform_2.img = &img_platform_small;
		small_platform_2.render_pos.x = 855;
		small_platform_2.render_pos.y = 360;
		small_platform_2.shape.left = (float)small_platform_2.render_pos.x + 40;
		small_platform_2.shape.right = (float)small_platform_2.render_pos.x + img_platform_small.getwidth() - 40;
		small_platform_2.shape.y = (float)small_platform_2.render_pos.y + img_platform_small.getheight() / 2;

		// 设置第三个小平台
		Platform& small_platform_3 = platform_list[3];
		small_platform_3.img = &img_platform_small;
		small_platform_3.render_pos.x = 515;
		small_platform_3.render_pos.y = 225;
		small_platform_3.shape.left = (float)small_platform_3.render_pos.x + 40;
		small_platform_3.shape.right = (float)small_platform_3.render_pos.x + img_platform_small.getwidth() - 40;
		small_platform_3.shape.y = (float)small_platform_3.render_pos.y + img_platform_small.getheight() / 2;

		player_1->set_position(200, 50);
		player_2->set_position(975, 50);
	}
	void on_update(int delta) {
		player_1->on_update(delta);
		player_2->on_update(delta);

		main_camera.on_update(delta); // 更新摄像机状态

		bullet_list.erase(std::remove_if(
			bullet_list.begin(), bullet_list.end(),
			[](const bullet* bullet) {
				bool deletable = bullet->check_can_remove();
				if (deletable) {
					delete bullet; // 删除子弹对象
				}
				return deletable; // 返回是否可以删除

			}),
			bullet_list.end());

		const Vector2& position_player_1 = player_1->get_position();
		const Vector2& position_player_2 = player_2->get_position();
		if (position_player_1.y >= getheight()) {
			player_1->set_hp(0); // 玩家1掉出屏幕，设置生命值为0
		}
		if (position_player_2.y >= getheight()) {
			player_2->set_hp(0); // 玩家1掉出屏幕，设置生命值为0
		}
		if (player_1->get_hp() <= 0 || player_2->get_hp() <= 0) {
			MessageBox(GetHWnd(), _T("游戏结束"), _T("测试"), MB_OK);
			exit(0);
		}

		status_bar_p1.set_hp(player_1->get_hp());
		status_bar_p1.set_mp(player_1->get_mp());
		status_bar_p2.set_hp(player_2->get_hp());
		status_bar_p2.set_mp(player_2->get_mp());
		for (bullet* bullet : bullet_list) {
			bullet->on_update(delta);
		}
	}
	void on_draw(const Camera& camera) {
		putimage_alpha(camera, pos_img_sky.x, pos_img_sky.y, &img_sky);
		putimage_alpha(camera, pos_img_hills.x, pos_img_hills.y, &img_hills);
		for (Platform& platform : platform_list) {
			platform.on_draw(camera);
		}
		if (is_debug) {
			settextcolor(RGB(255, 0, 0));
			outtextxy(15, 15, _T("已开启调试模式,按Q关闭"));
		}
		player_1->on_draw(camera);
		player_2->on_draw(camera);

		status_bar_p1.on_draw();
		status_bar_p2.on_draw();

		for (bullet* bullet : bullet_list) {
			bullet->on_draw(camera);
		}
	}
	void on_input(const ExMessage& msg) {
		player_1->on_input(msg);
		player_2->on_input(msg);
		switch (msg.message) {
		case WM_KEYUP:
		if (msg.vkcode == 0x51) {
			is_debug = !is_debug; // 切换调试模式
			break;
		}
		default:
		    break;
		}
	}
	void on_exit() {
		
	}
private:
	POINT pos_img_sky = { 0 };         // 天空图片位置
	POINT pos_img_hills = { 0 };       // 山脉图片位置

	status_bar status_bar_p1;
	status_bar status_bar_p2;
};

