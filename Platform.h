#pragma once
#include"Camera.h"
#include <graphics.h>
extern void putimage_alpha(const Camera& camera, int x, int y, IMAGE* img);   //播放动画
extern void line(const Camera& camera, int x1, int y1, int x2, int y2); // 绘制线段
extern bool is_debug;

class Platform
{
public:
	Platform() = default;
	~Platform() = default;

	void on_draw(const Camera& camera)const {
		putimage_alpha(camera, render_pos.x, render_pos.y,img);

		if (is_debug) {
			setcolor(RGB(255, 0, 0));
			line(camera, (int)shape.left, (int)shape.y, (int)shape.right, (int)shape.y);
		}
	}
public:
	struct CollisionShape {
		float y;
		float left, right;
	};
public:
	CollisionShape shape;  // 碰撞形状
	IMAGE* img = nullptr;
	POINT render_pos = { 0 };
};

