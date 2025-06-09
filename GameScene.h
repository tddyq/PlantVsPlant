#pragma once
#include"Player.h"
#include<iostream>
#include<vector>
#include"Scene.h"
#include"Platform.h"
// ��Ϸ����Ԫ��ͼƬ��Դ����
extern IMAGE img_sky;            // ���ͼƬ
extern IMAGE img_hills;          // ɽ��ͼƬ
extern IMAGE img_platform_large; // ����ƽ̨ͼƬ
extern IMAGE img_platform_small; // С��ƽ̨ͼƬ

extern SceneManager scene_manager;               // ��������������
extern std::vector<Platform> platform_list; // ƽ̨�б�
extern Player* player_1; // ���1
extern Player* player_2; // ���2

extern void putimage_alpha(const Camera& camera, int x, int y, IMAGE* img);   //���Ŷ���
class GameScene : public Scene
{
public:
	GameScene() = default;
	~GameScene() = default;

	void on_enter() {
		
		/*
		Ϊ��ֹ����ʱ���ֺڱ�,���ͼƬ���ڴ��ڳߴ�
		����õ���ֵʹ��ͼƬ�ڴ�������ص��԰�����������
		*/
		pos_img_sky.x = (getwidth() - img_sky.getwidth()) / 2;   // �������ͼƬλ��
		pos_img_sky.y = (getheight() - img_sky.getheight()) / 2; // �������ͼƬλ��

		pos_img_hills.x = (getwidth() - img_hills.getwidth()) / 2; // ����ɽ��ͼƬλ��
		pos_img_hills.y = (getheight() - img_hills.getheight()) / 2; // ����ɽ��ͼƬλ��

		platform_list.resize(4);

		Platform& large_platform = platform_list[0];
		large_platform.img = &img_platform_large; // ���ô���ƽ̨ͼƬ
		large_platform.render_pos.x = 122;
		large_platform.render_pos.y = 455;
		large_platform.shape.left = (float)large_platform.render_pos.x + 30;
		large_platform.shape.right = (float)large_platform.render_pos.x + img_platform_large.getwidth() - 30;
		large_platform.shape.y = (float)large_platform.render_pos.y + 60;

		// ���õ�һ��С��ƽ̨
		Platform& small_platform_1 = platform_list[1];
		small_platform_1.img = &img_platform_small;
		small_platform_1.render_pos.x = 175;
		small_platform_1.render_pos.y = 360;
		small_platform_1.shape.left = (float)small_platform_1.render_pos.x + 40;
		small_platform_1.shape.right = (float)small_platform_1.render_pos.x + img_platform_small.getwidth() - 40;
		small_platform_1.shape.y = (float)small_platform_1.render_pos.y + img_platform_small.getheight() / 2;

		// ���õڶ���С��ƽ̨
		Platform& small_platform_2 = platform_list[2];
		small_platform_2.img = &img_platform_small;
		small_platform_2.render_pos.x = 855;
		small_platform_2.render_pos.y = 360;
		small_platform_2.shape.left = (float)small_platform_2.render_pos.x + 40;
		small_platform_2.shape.right = (float)small_platform_2.render_pos.x + img_platform_small.getwidth() - 40;
		small_platform_2.shape.y = (float)small_platform_2.render_pos.y + img_platform_small.getheight() / 2;

		// ���õ�����Сƽ̨
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
	}
	void on_draw(const Camera& camera) {
		putimage_alpha(camera, pos_img_sky.x, pos_img_sky.y, &img_sky);
		putimage_alpha(camera, pos_img_hills.x, pos_img_hills.y, &img_hills);
		for (Platform& platform : platform_list) {
			platform.on_draw(camera);
		}
		if (is_debug) {
			settextcolor(RGB(255, 0, 0));
			outtextxy(15, 15, _T("�ѿ�������ģʽ,��Q�ر�"));
		}
		player_1->on_draw(camera);
		player_2->on_draw(camera);
	}
	void on_input(const ExMessage& msg) {
		player_1->on_input(msg);
		player_2->on_input(msg);
		switch (msg.message) {
		case WM_KEYUP:
		if (msg.vkcode == 0x51) {
			is_debug = !is_debug; // �л�����ģʽ
			break;
		}
		default:
		    break;
		}
	}
	void on_exit() {
		
	}
private:
	POINT pos_img_sky = { 0 };         // ���ͼƬλ��
	POINT pos_img_hills = { 0 };       // ɽ��ͼƬλ��
};

