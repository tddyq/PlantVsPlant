#pragma once
#include<functional>

class Timer {
public:
	Timer() = default;
	~Timer() = default;
	/*
	* @brief 重置计时器持续时间与触发状态
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
			//循环触发或单次未触发过
			if ((!one_shot || (one_shot && !shotted)) && callback) {
				callback();
			}
			shotted = true;
			pass_time = 0;
		}
	}
private:
	int pass_time = 0;                           //经过时间
	int wait_time = 0;                           //等待时间
	bool paused = false;                         //是否暂停
	bool shotted = false;                        //是否已触发
	bool one_shot = false;                       //单次触发
	std::function<void()> callback = nullptr;    //触发回调
};




