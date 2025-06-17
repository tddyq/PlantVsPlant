#pragma once
#include <wtypes.h>
#include <graphics.h>
extern void putimage_alpha(int x, int y, IMAGE* img);   //���Ŷ���
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
		// ����͸��ͷ��
		putimage_alpha(position.x, position.y, img_avatar);

		// �������ɫ�����ɫ��������ӰЧ����
		setfillcolor(RGB(5, 5, 5));

		// �����������ɫԲ�Ǿ��Σ���Ϊ����������Ӱ��
		solidroundrect(position.x + 100, position.y + 10,
			position.x + 100 + width + 3 * 2,
			position.y + 36, 8, 8);

		solidroundrect(position.x + 100, position.y + 45,
			position.x + 100 + width + 3 * 2,
			position.y + 71, 8, 8);

		// ���ú�ɫ�����ɫ�����ڽ�����������
		setfillcolor(RGB(67, 47, 47));

		// ����������ɫԲ�Ǿ��Σ�ʵ�ʽ�������
		solidroundrect(position.x + 100, position.y + 10,
			position.x + 100 + width + 3,
			position.y + 33, 8, 8);

		solidroundrect(position.x + 100, position.y + 45,
			position.x + 100 + width + 3,
			position.y + 68, 8, 8);

		float hp_bar_width = width * max(0, hp) / 100.0f; // ��������ֵ���������
		float mp_bar_width = width * max(0, mp) / 100.0f; // ����ħ��ֵ���������
		setfillcolor(RGB(197, 61, 67));
		solidroundrect(position.x + 100, position.y + 10, 
			position.x + 100 + (int)hp_bar_width + 3, position.y + 33, 8, 8);
		setfillcolor(RGB(83,131,195));
		solidroundrect(position.x + 100, position.y + 45,
			position.x + 100 + (int)mp_bar_width + 3, position.y + 66, 8, 8);


	}
private:
	const int width = 275; //���������
private:
	int hp = 0;      //��Ҫ��ʾ������ֵ
	int mp = 0;      //��Ҫ��ʾ��ħ��ֵ
	POINT position = { 0 }; //״̬��λ��
	IMAGE* img_avatar = nullptr; //ͷ��ͼƬ
};

