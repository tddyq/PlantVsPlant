#pragma once
#pragma comment(lib,"Winmm.lib")
#pragma comment(lib, "MSIMG32.LIB")
#include<graphics.h>
#include<iostream>
#include<functional>

#include"Scene.h"
#include"MenuScene.h"
#include"GameScene.h"
#include"SceneManager.h"
#include"SelectorScene.h"
#include"Platform.h"
#include"Atlas.h"
#include"Player.h"
#include"bullet.h"
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

// 豌豆射手系列动画图集
extern Atlas atlas_peashooter_idle_left;         // 豌豆射手朝向左的默认动画图集
extern Atlas atlas_peashooter_idle_right;        // 豌豆射手朝向右的默认动画图集
extern Atlas atlas_peashooter_run_left;          // 豌豆射手朝向左的奔跑动画图集
extern Atlas atlas_peashooter_run_right;         // 豌豆射手朝向右的奔跑动画图集
extern Atlas atlas_peashooter_attack_ex_left;    // 豌豆射手朝向左的特殊攻击动画图集
extern Atlas atlas_peashooter_attack_ex_right;   // 豌豆射手朝向右的特殊攻击动画图集
extern Atlas atlas_peashooter_die_left;          // 豌豆射手朝向左的死亡动画图集
extern Atlas atlas_peashooter_die_right;         // 豌豆射手朝向右的死亡动画图集

// 龙日葵系列动画图集
extern Atlas atlas_sunflower_idle_left;          // 龙日葵朝向左的默认动画图集
extern Atlas atlas_sunflower_idle_right;         // 龙日葵朝向右的默认动画图集
extern Atlas atlas_sunflower_run_left;           // 龙日葵朝向左的奔跑动画图集
extern Atlas atlas_sunflower_run_right;          // 龙日葵朝向右的奔跑动画图集
extern Atlas atlas_sunflower_attack_ex_left;     // 龙日葵朝向左的特殊攻击动画图集
extern Atlas atlas_sunflower_attack_ex_right;    // 龙日葵朝向右的特殊攻击动画图集
extern Atlas atlas_sunflower_die_left;           // 龙日葵朝向左的死亡动画图集
extern Atlas atlas_sunflower_die_right;          // 龙日葵朝向右的死亡动画图集

// 游戏元素资源
extern IMAGE img_pea;                            // 豌豆图片
extern Atlas atlas_pea_break;                    // 豌豆破碎动画图集
extern Atlas atlas_sun;                          // 日光动画图集
extern Atlas atlas_sun_explode;                  // 日光爆炸动画图集
extern Atlas atlas_sun_ex;                       // 特殊日光动画图集
extern Atlas atlas_sun_ex_explode;               // 特殊日光爆炸动画图集
extern Atlas atlas_sun_text;                     // “日”文本动画图集

// 特效动画
extern Atlas atlas_run_effect;                   // 奔跑特效动画图集
extern Atlas atlas_jump_effect;                  // 跳跃特效动画图集
extern Atlas atlas_land_effect;                  // 落地特效动画图集

// 胜负界面
extern IMAGE img_1P_winnner;                     // 1P获胜文本图片
extern IMAGE img_2P_winnner;                     // 2P获胜文本图片
extern IMAGE img_winnner_bar;                    // 获胜玩家文本背景图片

// 角色头像
extern IMAGE img_avatar_peashooter;              // 豌豆射手头像图片
extern IMAGE img_avatar_sunflower;               // 龙日葵头像图片

// 场景管理
extern Scene* menu_scene;              // 主菜单场景指针
extern Scene* game_scene;              // 游戏场景指针
extern Scene* selector_scene;          // 选角场景指针
extern SceneManager scene_manager;               // 场景管理器对象
extern Camera main_camera;                // 主摄像机对象

extern std::vector<Platform> platform_list; // 平台列表
extern std::vector<bullet*> bullet_list; // 子弹列表
extern Player* player_1; // 玩家1
extern Player* player_2; // 玩家2
extern IMAGE* img_player_1_avatar; // 玩家1头像
extern IMAGE* img_player_2_avatar; // 玩家2头像
extern bool is_debug;


inline void flip_image(IMAGE* src, IMAGE* dst);
void flip_atlas(Atlas& src, Atlas& dst);
void putimage_alpha(int x, int y, IMAGE* img);   //播放动画
void putimage_alpha(const Camera& camera,int x, int y, IMAGE* img);   //播放动画
void putimage_alpha(int dst_x, int dst_y, int width, int height, IMAGE* img, int src_x, int src_y);
void load_game_resources();
void line(const Camera& camera, int x1, int y1, int x2, int y2);
void sketch_image(IMAGE* src, IMAGE* dst);
