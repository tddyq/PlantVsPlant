#pragma once
#include"Scene.h"
#include"MenuScene.h"
// 主菜单与选角界面
extern IMAGE img_menu_background;                // 主菜单背景图片
extern IMAGE img_VS;                             // VS 艺术字图片
extern IMAGE img_1P;                             // 1P 文本图片
extern IMAGE img_2P;                             // 2P 文本图片
extern IMAGE img_1P_desc;                        // 1P 键位描述图片
extern IMAGE img_2P_desc;                        // 2P 键位描述图片

// 墓碑与选角界面元素
extern IMAGE img_gravestone_left;                // 朝向左的墓碑图片
extern IMAGE img_gravestone_right;               // 朝向右的墓碑图片
extern IMAGE img_selector_tip;                   // 选角界面提示信息文本图片
extern IMAGE img_selector_background;            // 选角界面背景图

// 游戏场景元素图片资源定义
extern IMAGE img_sky;            // 天空图片
extern IMAGE img_hills;          // 山脉图片
extern IMAGE img_platform_large; // 大型平台图片
extern IMAGE img_platform_small; // 小型平台图片

// 玩家光标指示图片
extern IMAGE img_1P_cursor;      // 1P 指示光标图片
extern IMAGE img_2P_cursor;      // 2P 指示光标图片

// 玩家选择按钮图片（1P/2P）
extern IMAGE img_1P_selector_btn_idle_left;      // 1P 向左选择按钮默认状态图片
extern IMAGE img_1P_selector_btn_idle_right;     // 1P 向右选择按钮默认状态图片
extern IMAGE img_1P_selector_btn_down_left;      // 1P 向左选择按钮按下状态图片
extern IMAGE img_1P_selector_btn_down_right;     // 1P 向右选择按钮按下状态图片
extern IMAGE img_2P_selector_btn_idle_left;      // 2P 向左选择按钮默认状态图片
extern IMAGE img_2P_selector_btn_idle_right;     // 2P 向右选择按钮默认状态图片
extern IMAGE img_2P_selector_btn_down_left;      // 2P 向左选择按钮按下状态图片
extern IMAGE img_2P_selector_btn_down_right;     // 2P 向右选择按钮按下状态图片

// 角色选角背景
extern IMAGE img_peashooter_selector_background_left;   // 选角界面朝向左的豌豆射手背景图片
extern IMAGE img_peashooter_selector_background_right;  // 选角界面朝向右的豌豆射手背景图片
extern IMAGE img_sunflower_selector_background_left;   // 选角界面朝向左的龙日葵背景图片
extern IMAGE img_sunflower_selector_background_right;  // 选角界面朝向右的龙日葵背景图片

extern SceneManager scene_manager;               // 场景管理器对象
extern Atlas atlas_sunflower_idle_right;         // 龙日葵朝向右的默认动画图集
extern Atlas atlas_peashooter_idle_right;        // 豌豆射手朝向右的默认动画图集

class SelectorScene : public Scene 
{
public:
	SelectorScene() = default;
	~SelectorScene() = default;

	void on_enter() {
		animation_peashooter.set_atlas(&atlas_peashooter_idle_right);
		animation_sunflower.set_atlas(&atlas_sunflower_idle_right);
		animation_peashooter.set_interval(100);
		animation_sunflower.set_interval(100);

		static const int OFFSET_X = 50; // 偏移量

		// VS 标志位置
		pos_img_VS.x = (getwidth() - img_VS.getwidth()) / 2;
		pos_img_VS.y = (getheight() - img_VS.getheight()) / 2;

		// 选择提示位置
		pos_img_tip.x = (getwidth() - img_selector_tip.getwidth()) / 2;
		pos_img_tip.y = getheight() - 125;

		// 玩家标识位置
		pos_img_1P.x = (getwidth() / 2 - img_1P.getwidth()) / 2 - OFFSET_X;
		pos_img_1P.y = 35;
		pos_img_2P.x = getwidth() / 2 + (getwidth() / 2 - img_2P.getwidth()) / 2 + OFFSET_X;
		pos_img_2P.y = pos_img_1P.y;

		// 玩家描述位置
		pos_img_1P_desc.x = (getwidth() / 2 - img_1P_desc.getwidth()) / 2 - OFFSET_X;
		pos_img_1P_desc.y = getheight() - 150;
		pos_img_2P_desc.x = getwidth() / 2 + (getwidth() / 2 - img_2P_desc.getwidth()) / 2 + OFFSET_X;
		pos_img_2P_desc.y = pos_img_1P_desc.y;

		// 墓碑位置
		pos_img_1P_gravestone.x = (getwidth() / 2 - img_gravestone_right.getwidth()) / 2 - OFFSET_X;
		pos_img_1P_gravestone.y = pos_img_1P.y + img_1P.getheight() + 35;
		pos_img_2P_gravestone.x = getwidth() / 2 + (getwidth() / 2 - img_gravestone_left.getwidth()) / 2 + OFFSET_X;
		pos_img_2P_gravestone.y = pos_img_1P_gravestone.y;

		// 动画位置
		pos_animation_1P.x = (getwidth() / 2 - atlas_peashooter_idle_right.get_image(0)->getwidth()) / 2 - OFFSET_X;
		pos_animation_1P.y = pos_img_1P_gravestone.y + 80;
		pos_animation_2P.x = getwidth() / 2 + (getwidth() / 2 - atlas_peashooter_idle_right.get_image(0)->getwidth()) / 2 + OFFSET_X;
		pos_animation_2P.y = pos_animation_1P.y;

		// 玩家名字位置
		pos_img_1P_name.y = pos_animation_1P.y + 155;
		pos_img_2P_name.y = pos_img_1P_name.y;

		// 选择器按钮位置
		pos_1P_selector_btn_left.x = pos_img_1P_gravestone.x - img_1P_selector_btn_idle_left.getwidth();
		pos_1P_selector_btn_left.y = pos_img_1P_gravestone.y + (img_gravestone_right.getheight() - img_1P_selector_btn_idle_left.getheight()) / 2;
		pos_1P_selector_btn_right.x = pos_img_1P_gravestone.x + img_gravestone_right.getwidth();

		// 2P 选择器按钮位置 (修正后的版本)
		pos_2P_selector_btn_left.x = pos_img_2P_gravestone.x - img_2P_selector_btn_idle_left.getwidth();
		pos_2P_selector_btn_left.y = pos_img_2P_gravestone.y + (img_gravestone_left.getheight() - img_2P_selector_btn_idle_left.getheight()) / 2;
		pos_2P_selector_btn_right.x = pos_img_2P_gravestone.x + img_gravestone_left.getwidth();
		pos_2P_selector_btn_right.y = pos_2P_selector_btn_left.y;
	}
	void on_update(int delta) {}
	void on_draw(const Camera& camera) {
		// 绘制选择界面背景（全屏覆盖）
		putimage(0, 0, &img_selector_background);

		// 绘制VS标志（居中）
		putimage_alpha(pos_img_VS.x, pos_img_VS.y, &img_VS);

		// 绘制玩家标识（1P在左，2P在右）
		putimage_alpha(pos_img_1P.x, pos_img_1P.y, &img_1P);
		putimage_alpha(pos_img_2P.x, pos_img_2P.y, &img_2P);

		// 绘制玩家墓碑（1P右侧墓碑，2P左侧墓碑）
		putimage_alpha(pos_img_1P_gravestone.x, pos_img_1P_gravestone.y, &img_gravestone_right);
		putimage_alpha(pos_img_2P_gravestone.x, pos_img_2P_gravestone.y, &img_gravestone_left);

		// 绘制玩家控制说明（屏幕底部）
		putimage_alpha(pos_img_1P_desc.x, pos_img_1P_desc.y, &img_1P_desc);
		putimage_alpha(pos_img_2P_desc.x, pos_img_2P_desc.y, &img_2P_desc);

		// 绘制选择提示（屏幕底部居中）
		putimage_alpha(pos_img_tip.x, pos_img_tip.y, &img_selector_tip);
	}
	void on_input(const ExMessage& msg) {}
	void on_exit() {}
private:
	POINT pos_img_VS = { 0 };               // VS 艺术字图片位置
	POINT pos_img_tip = { 0 };              // 提示信息文本图片位置
	POINT pos_img_1P = { 0 };               // 1P 文本图片位置
	POINT pos_img_2P = { 0 };               // 2P 文本图片位置
	POINT pos_img_1P_desc = { 0 };          // 1P 键位描述图片位置
	POINT pos_img_2P_desc = { 0 };          // 2P 键位描述图片位置
	POINT pos_img_1P_name = { 0 };          // 1P 角色姓名文本位置
	POINT pos_img_2P_name = { 0 };          // 2P 角色姓名文本位置
	POINT pos_animation_1P = { 0 };         // 1P 角色动画位置
	POINT pos_animation_2P = { 0 };         // 2P 角色动画位置
	POINT pos_img_1P_gravestone = { 0 };    // 1P 墓碑图片位置
	POINT pos_img_2P_gravestone = { 0 };    // 2P 墓碑图片位置
	POINT pos_1P_selector_btn_left = { 0 }; // 1P 向左切换按钮位置
	POINT pos_1P_selector_btn_right = { 0 };// 1P 向右切换按钮位置
	POINT pos_2P_selector_btn_left = { 0 }; // 2P 向左切换按钮位置
	POINT pos_2P_selector_btn_right = { 0 };// 2P 向右切换按钮位置

	Animation animation_peashooter;          // 豌豆射手动画 
	Animation animation_sunflower;           // 向日葵动画
};

