#pragma once
#include "atlas.h"
#include"Camera.h"
#include"vector2.h"
extern void putimage_alpha(const Camera& camera, int x, int y, IMAGE* img);   //���Ŷ���
class Particle
{
public:
	Particle() = default;
	Particle(const Vector2 position,Atlas* atlas,int lifespan)
		:position(position),atlas(atlas),lifespan(lifespan){}
	~Particle() = default;
	void set_position(const Vector2& pos) {
		position = pos;
	}
	void set_atlas(Atlas* atlas) {
		this->atlas = atlas;
	}
	void set_lifespan(int lifespan) {
		this->lifespan = lifespan;
	}
	bool check_valid()const {
		return valid;
	}
	void on_update(int delta) {
		timer += delta;
		if (timer >= lifespan) {
			timer = 0;
			idx_frame++;
			if (idx_frame >= atlas->get_size()) {
				idx_frame = atlas->get_size() - 1; //���������һ֡
				valid = false;
			}
		}
	}
	void on_draw(const Camera& camera) {
		putimage_alpha(camera, (int)position.x, (int)position.y, atlas->get_image(idx_frame));
	}
private:
	int timer = 0;               //���Ӷ������Ŷ�ʱ��
	int lifespan = 0;            //��֡���Ӷ�������ʱ��
	int idx_frame = 0;           //��ǰ֡����
	Vector2 position;            //����λ��
	bool valid = true;           //�����Ƿ���Ч
	Atlas* atlas = nullptr;      //���Ӷ���ͼ��

	


};

