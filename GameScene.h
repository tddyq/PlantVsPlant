#pragma once
#include"Scene.h"
#include<iostream>
class GameScene : public Scene
{
public:
	GameScene() = default;
	~GameScene() = default;

	void on_enter() {
		std::cout << "进入游戏内场景" << std::endl;
	}
	void on_update(int delta) {
		std::cout << "游戏正在运行..." << std::endl;
	}
	void on_draw() {
		outtextxy(10, 10, _T("游戏内绘图内容"));
	}
	void on_input(const ExMessage& msg) {
		if (msg.message == WM_KEYDOWN) {
			scene_manager.switch_to(SceneManager::SceneType::Menu);
		}
	}
	void on_exit() {
		std::cout << "游戏场景退出" << std::endl;
	}
private:

};

