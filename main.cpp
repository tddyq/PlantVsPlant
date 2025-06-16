#include"heads.h"

// 主菜单与选角界面
IMAGE img_menu_background;                // 主菜单背景图片
IMAGE img_VS;                             // VS 艺术字图片
IMAGE img_1P;                             // 1P 文本图片
IMAGE img_2P;                             // 2P 文本图片
IMAGE img_1P_desc;                        // 1P 键位描述图片
IMAGE img_2P_desc;                        // 2P 键位描述图片

// 墓碑与选角界面元素
IMAGE img_gravestone_left;                // 朝向左的墓碑图片
IMAGE img_gravestone_right;               // 朝向右的墓碑图片
IMAGE img_selector_tip;                   // 选角界面提示信息文本图片
IMAGE img_selector_background;            // 选角界面背景图

// 游戏场景元素图片资源定义
IMAGE img_sky;            // 天空图片
IMAGE img_hills;          // 山脉图片
IMAGE img_platform_large; // 大型平台图片
IMAGE img_platform_small; // 小型平台图片

// 玩家光标指示图片
IMAGE img_1P_cursor;      // 1P 指示光标图片
IMAGE img_2P_cursor;      // 2P 指示光标图片

// 玩家选择按钮图片（1P/2P）
IMAGE img_1P_selector_btn_idle_left;      // 1P 向左选择按钮默认状态图片
IMAGE img_1P_selector_btn_idle_right;     // 1P 向右选择按钮默认状态图片
IMAGE img_1P_selector_btn_down_left;      // 1P 向左选择按钮按下状态图片
IMAGE img_1P_selector_btn_down_right;     // 1P 向右选择按钮按下状态图片
IMAGE img_2P_selector_btn_idle_left;      // 2P 向左选择按钮默认状态图片
IMAGE img_2P_selector_btn_idle_right;     // 2P 向右选择按钮默认状态图片
IMAGE img_2P_selector_btn_down_left;      // 2P 向左选择按钮按下状态图片
IMAGE img_2P_selector_btn_down_right;     // 2P 向右选择按钮按下状态图片

// 角色选角背景
IMAGE img_peashooter_selector_background_left;   // 选角界面朝向左的豌豆射手背景图片
IMAGE img_peashooter_selector_background_right;  // 选角界面朝向右的豌豆射手背景图片
IMAGE img_sunflower_selector_background_left;   // 选角界面朝向左的龙日葵背景图片
IMAGE img_sunflower_selector_background_right;  // 选角界面朝向右的龙日葵背景图片

// 豌豆射手系列动画图集
Atlas atlas_peashooter_idle_left;         // 豌豆射手朝向左的默认动画图集
Atlas atlas_peashooter_idle_right;        // 豌豆射手朝向右的默认动画图集
Atlas atlas_peashooter_run_left;          // 豌豆射手朝向左的奔跑动画图集
Atlas atlas_peashooter_run_right;         // 豌豆射手朝向右的奔跑动画图集
Atlas atlas_peashooter_attack_ex_left;    // 豌豆射手朝向左的特殊攻击动画图集
Atlas atlas_peashooter_attack_ex_right;   // 豌豆射手朝向右的特殊攻击动画图集
Atlas atlas_peashooter_die_left;          // 豌豆射手朝向左的死亡动画图集
Atlas atlas_peashooter_die_right;         // 豌豆射手朝向右的死亡动画图集

// 龙日葵系列动画图集
Atlas atlas_sunflower_idle_left;          // 龙日葵朝向左的默认动画图集
Atlas atlas_sunflower_idle_right;         // 龙日葵朝向右的默认动画图集
Atlas atlas_sunflower_run_left;           // 龙日葵朝向左的奔跑动画图集
Atlas atlas_sunflower_run_right;          // 龙日葵朝向右的奔跑动画图集
Atlas atlas_sunflower_attack_ex_left;     // 龙日葵朝向左的特殊攻击动画图集
Atlas atlas_sunflower_attack_ex_right;    // 龙日葵朝向右的特殊攻击动画图集
Atlas atlas_sunflower_die_left;           // 龙日葵朝向左的死亡动画图集
Atlas atlas_sunflower_die_right;          // 龙日葵朝向右的死亡动画图集

// 游戏元素资源
IMAGE img_pea;                            // 豌豆图片
Atlas atlas_pea_break;                    // 豌豆破碎动画图集
Atlas atlas_sun;                          // 日光动画图集
Atlas atlas_sun_explode;                  // 日光爆炸动画图集
Atlas atlas_sun_ex;                       // 特殊日光动画图集
Atlas atlas_sun_ex_explode;               // 特殊日光爆炸动画图集
Atlas atlas_sun_text;                     // “日”文本动画图集

// 特效动画
Atlas atlas_run_effect;                   // 奔跑特效动画图集
Atlas atlas_jump_effect;                  // 跳跃特效动画图集
Atlas atlas_land_effect;                  // 落地特效动画图集

// 胜负界面
IMAGE img_1P_winnner;                     // 1P获胜文本图片
IMAGE img_2P_winnner;                     // 2P获胜文本图片
IMAGE img_winnner_bar;                    // 获胜玩家文本背景图片

// 角色头像
IMAGE img_avatar_peashooter;              // 豌豆射手头像图片
IMAGE img_avatar_sunflower;               // 龙日葵头像图片

// 场景管理
Scene* menu_scene = nullptr;              // 主菜单场景指针
Scene* game_scene = nullptr;              // 游戏场景指针
Scene* selector_scene = nullptr;          // 选角场景指针
SceneManager scene_manager;               // 场景管理器对象
Camera main_camera;                       // 主摄像机对象

std::vector<Platform> platform_list; // 平台列表
std::vector<bullet*> bullet_list; // 子弹列表

Player* player_1; // 玩家1
Player* player_2; // 玩家2
bool is_debug = false;
int main() {
    ExMessage msg;
    const int FPS = 60;

    initgraph(1280, 720);
    
    settextstyle(28, 0, _T("IPix"));
	setbkmode(TRANSPARENT);


    load_game_resources();
    BeginBatchDraw();

    menu_scene = new MenuScene();
    game_scene = new GameScene();
    selector_scene = new SelectorScene();
    scene_manager.set_current_sence(menu_scene);

    

    while (true)
    {
        DWORD frame_start_time = GetTickCount();
        while (peekmessage(&msg)) 
        {
            scene_manager.on_input(msg);
        }

        static DWORD last_tick_time = GetTickCount();
        DWORD current_tick_time = GetTickCount();
        DWORD delta_tick = current_tick_time - last_tick_time;
        scene_manager.on_update(delta_tick);
        last_tick_time = current_tick_time;

        cleardevice();  
        scene_manager.on_draw(main_camera);
        FlushBatchDraw();

        DWORD frame_end_time = GetTickCount();
        DWORD frame_delta_time = frame_end_time - frame_start_time;
        if (frame_delta_time < 1000 / FPS)
            Sleep(1000 / FPS - frame_delta_time);


        
    }
    EndBatchDraw();
}