#pragma once
#include<functional>

class Timer {
public:
	Timer() = default;
	~Timer() = default;
	/*
	* @brief ���ü�ʱ������ʱ���봥��״̬
	*/
	void restart() {
		pass_time = 0;;
		shotted = false;
	}

	void set_wait_time(int val) {
		wait_time = val;
	}

	void set_one_shot(bool flag) {
		one_shot = flag;
	}

	void set_callback(std::function<void()> cb) {
		this->callback = cb;
	}

	void pause() {
		paused = true;
	}

	void resume() {
		paused = false;
	}
	void on_update(int delta) {
		if (paused) {
			return;
		}
		pass_time += delta;
		if (pass_time >= wait_time) {
			//ѭ�������򵥴�δ������
			if ((!one_shot || (one_shot && !shotted)) && callback) {
				callback();
			}
			shotted = true;
			pass_time = 0;
		}
	}
private:
	int pass_time = 0;                           //����ʱ��
	int wait_time = 0;                           //�ȴ�ʱ��
	bool paused = false;                         //�Ƿ���ͣ
	bool shotted = false;                        //�Ƿ��Ѵ���
	bool one_shot = false;                       //���δ���
	std::function<void()> callback = nullptr;    //�����ص�
};




