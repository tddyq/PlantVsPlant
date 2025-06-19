#pragma once
#include"Player.h"
#include<iostream>
#include<vector>
#include"Scene.h"
#include"Platform.h"
#include"bullet.h"
#include"status_bar.h"
// 游戏场景元素图片资源定义
extern IMAGE img_sky;                                                         // 天空图片
extern IMAGE img_hills;                                                       // 山脉图片
extern IMAGE img_platform_large;                                              // 大型平台图片
extern IMAGE img_platform_small;                                              // 小型平台图片
// 胜负界面
extern IMAGE img_1P_winnner;                     // 1P获胜文本图片
extern IMAGE img_2P_winnner;                     // 2P获胜文本图片
extern IMAGE img_winnner_bar;                    // 获胜玩家文本背景图片

extern SceneManager scene_manager;                                            // 场景管理器对象
extern std::vector<Platform> platform_list;                                   // 平台列表
extern std::vector<bullet*> bullet_list;                                      // 子弹列表

extern Player* player_1;                                                      // 玩家1
extern Player* player_2;                                                      // 玩家2
extern IMAGE* img_player_1_avatar;                                            // 玩家1头像
extern IMAGE* img_player_2_avatar;                                            // 玩家2头像

extern Camera main_camera;                                                    // 主摄像机对象

extern void putimage_alpha(const Camera& camera, int x, int y, IMAGE* img);   //播放动画
class GameScene : public Scene
{
public:
	GameScene() = default;
	~GameScene() = default;

	void on_enter() {
		is_game_over = false;
		is_slide_out_started = false; 

		// 设置胜利进度条初始位置
		pos_img_winner_bar.x = -img_winnner_bar.getwidth();
		pos_img_winner_bar.y = (getheight() - img_winnner_bar.getheight()) / 2;

		// 计算胜利进度条目标位置
		pos_x_img_winner_bar_dst = (getwidth() - img_winnner_bar.getwidth()) / 2;

		// 设置胜利文本初始位置
		pos_img_winner_text.x = pos_img_winner_bar.x;
		pos_img_winner_text.y = (getheight() - img_1P_winnner.getheight()) / 2;

		// 计算胜利文本目标位置
		pos_x_img_winner_text_dst = (getwidth() - img_1P_winnner.getwidth()) / 2;

		status_bar_p1.set_avatar(img_player_1_avatar); // 设置玩家1头像
		status_bar_p2.set_avatar(img_player_2_avatar); // 设置玩家2头像

		status_bar_p1.set_position(235, 625);
		status_bar_p2.set_position(675, 625);
		
		timer_winner_slide_in.restart();
		timer_winner_slide_in.set_wait_time(2500);
		timer_winner_slide_in.set_one_shot(true);
		timer_winner_slide_in.set_callback([&]() {
			is_slide_out_started = true; // 开始滑出结算界面
			});
		
		timer_winner_slide_out.restart();
		timer_winner_slide_out.set_wait_time(1000);
		timer_winner_slide_out.set_one_shot(true);
		timer_winner_slide_out.set_callback([&]() {
			scene_manager.switch_to(SceneManager::SceneType::Menu);
			});

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

		mciSendString(_T("play bgm_game repeat from 0"), NULL, 0, NULL); // 播放游戏背景音乐
	}
	void on_update(int delta) {
		player_1->on_update(delta);
		player_2->on_update(delta);

		main_camera.on_update(delta);                                // 更新摄像机状态

		bullet_list.erase(std::remove_if(
			bullet_list.begin(), bullet_list.end(),
			[](const bullet* bullet) {
				bool deletable = bullet->check_can_remove();
				if (deletable) {
					delete bullet;                                   // 删除子弹对象
				}
				return deletable;                                    // 返回是否可以删除

			}),
			bullet_list.end());

		const Vector2& position_player_1 = player_1->get_position();
		const Vector2& position_player_2 = player_2->get_position();
		if (position_player_1.y >= getheight()) {
			player_1->set_hp(0);                                        // 玩家1掉出屏幕，设置生命值为0
		}
		if (position_player_2.y >= getheight()) {
			player_2->set_hp(0);                                        // 玩家1掉出屏幕，设置生命值为0
		}
		if (player_1->get_hp() <= 0 || player_2->get_hp() <= 0) {
			
			if (!is_game_over) {
				mciSendString(_T("stop bgm_game"), NULL, 0, NULL);      // 停止背景音乐
				mciSendString(_T("play ui_win from 0"), NULL, 0, NULL); // 播放胜利音效
			}
			is_game_over = true;
		}

		status_bar_p1.set_hp(player_1->get_hp());
		status_bar_p1.set_mp(player_1->get_mp());
		status_bar_p2.set_hp(player_2->get_hp());
		status_bar_p2.set_mp(player_2->get_mp());
		for (bullet* bullet : bullet_list) {
			bullet->on_update(delta);
		}

		if (is_game_over) {
			pos_img_winner_bar.x += (int)(speed_winner_bar * delta);
			pos_img_winner_text.x += (int)(speed_winner_text * delta);
			if (!is_slide_out_started) {
				timer_winner_slide_in.on_update(delta); // 更新结算动效滑入定时器
				if (pos_img_winner_bar.x > pos_x_img_winner_bar_dst) {
					pos_img_winner_bar.x = pos_x_img_winner_bar_dst;
				}
				if (pos_img_winner_text.x > pos_x_img_winner_text_dst) {
					pos_img_winner_text.x = pos_x_img_winner_text_dst;
				}
			}
			else {
				timer_winner_slide_out.on_update(delta); // 更新结算动效滑出定时器
			}
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

		if (is_game_over) {
			putimage_alpha(pos_img_winner_bar.x, pos_img_winner_bar.y, &img_winnner_bar); // 绘制结算动效背景
			putimage_alpha(pos_img_winner_text.x,pos_img_winner_text.y,
				player_1->get_hp() > 0 ? &img_1P_winnner : &img_2P_winnner);              // 绘制结算动效文本
		}
		else {
			status_bar_p1.on_draw();
			status_bar_p2.on_draw();
		}
		

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
		delete player_1; // 删除玩家1对象
		player_1 = nullptr;
		delete player_2;
		player_2 = nullptr;

		is_debug = false;

		bullet_list.clear(); // 清空子弹列表
		main_camera.reset(); // 重置摄像机状态
	}
private:
	const float speed_winner_bar = 3.0f;  //结算动效背景滑入速度
	const float speed_winner_text = 1.5f; //结算动效文本滑入速度
private:
	POINT pos_img_sky = { 0 };         // 天空图片位置
	POINT pos_img_hills = { 0 };       // 山脉图片位置

	status_bar status_bar_p1;
	status_bar status_bar_p2;

	bool is_game_over = false;         // 游戏是否结束

	POINT pos_img_winner_bar = { 0 };            //结算动效背景位置
	POINT pos_img_winner_text = { 0 };           //结算动效文本位置
	int pos_x_img_winner_bar_dst = 0;            //结算动效背景移动的目标位置
	int pos_x_img_winner_text_dst = 0;           //结算动效文本移动的目标位置
	Timer timer_winner_slide_in;                 //结算动效滑入定时器
	Timer timer_winner_slide_out;                //结算动效滑出定时器
	bool is_slide_out_started = false;           //结算动效是否开始滑出
};

