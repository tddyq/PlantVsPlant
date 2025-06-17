#pragma once
#include <wtypes.h>
#include <graphics.h>
extern void putimage_alpha(int x, int y, IMAGE* img);   //播放动画
class status_bar
{
public:
	status_bar() = default;
	~status_bar() = default;

	void set_position(int x, int y) {
		position.x = x;
		position.y = y;
	}
	void set_avatar(IMAGE* img) {
		img_avatar = img;
	}
	void set_hp(int hp) {
		this->hp = hp;
	}
	void set_mp(int mp) {
		this->mp = mp;
	}
	void on_draw() {
		// 绘制透明头像
		putimage_alpha(position.x, position.y, img_avatar);

		// 设置深灰色填充颜色（用于阴影效果）
		setfillcolor(RGB(5, 5, 5));

		// 绘制两个深灰色圆角矩形（作为进度条的阴影）
		solidroundrect(position.x + 100, position.y + 10,
			position.x + 100 + width + 3 * 2,
			position.y + 36, 8, 8);

		solidroundrect(position.x + 100, position.y + 45,
			position.x + 100 + width + 3 * 2,
			position.y + 71, 8, 8);

		// 设置褐色填充颜色（用于进度条背景）
		setfillcolor(RGB(67, 47, 47));

		// 绘制两个褐色圆角矩形（实际进度条）
		solidroundrect(position.x + 100, position.y + 10,
			position.x + 100 + width + 3,
			position.y + 33, 8, 8);

		solidroundrect(position.x + 100, position.y + 45,
			position.x + 100 + width + 3,
			position.y + 68, 8, 8);

		float hp_bar_width = width * max(0, hp) / 100.0f; // 计算生命值进度条宽度
		float mp_bar_width = width * max(0, mp) / 100.0f; // 计算魔法值进度条宽度
		setfillcolor(RGB(197, 61, 67));
		solidroundrect(position.x + 100, position.y + 10, 
			position.x + 100 + (int)hp_bar_width + 3, position.y + 33, 8, 8);
		setfillcolor(RGB(83,131,195));
		solidroundrect(position.x + 100, position.y + 45,
			position.x + 100 + (int)mp_bar_width + 3, position.y + 66, 8, 8);


	}
private:
	const int width = 275; //进度条宽度
private:
	int hp = 0;      //需要显示的生命值
	int mp = 0;      //需要显示的魔法值
	POINT position = { 0 }; //状态栏位置
	IMAGE* img_avatar = nullptr; //头像图片
};

