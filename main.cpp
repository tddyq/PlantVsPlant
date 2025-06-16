#include"heads.h"

// ���˵���ѡ�ǽ���
IMAGE img_menu_background;                // ���˵�����ͼƬ
IMAGE img_VS;                             // VS ������ͼƬ
IMAGE img_1P;                             // 1P �ı�ͼƬ
IMAGE img_2P;                             // 2P �ı�ͼƬ
IMAGE img_1P_desc;                        // 1P ��λ����ͼƬ
IMAGE img_2P_desc;                        // 2P ��λ����ͼƬ

// Ĺ����ѡ�ǽ���Ԫ��
IMAGE img_gravestone_left;                // �������Ĺ��ͼƬ
IMAGE img_gravestone_right;               // �����ҵ�Ĺ��ͼƬ
IMAGE img_selector_tip;                   // ѡ�ǽ�����ʾ��Ϣ�ı�ͼƬ
IMAGE img_selector_background;            // ѡ�ǽ��汳��ͼ

// ��Ϸ����Ԫ��ͼƬ��Դ����
IMAGE img_sky;            // ���ͼƬ
IMAGE img_hills;          // ɽ��ͼƬ
IMAGE img_platform_large; // ����ƽ̨ͼƬ
IMAGE img_platform_small; // С��ƽ̨ͼƬ

// ��ҹ��ָʾͼƬ
IMAGE img_1P_cursor;      // 1P ָʾ���ͼƬ
IMAGE img_2P_cursor;      // 2P ָʾ���ͼƬ

// ���ѡ��ťͼƬ��1P/2P��
IMAGE img_1P_selector_btn_idle_left;      // 1P ����ѡ��ťĬ��״̬ͼƬ
IMAGE img_1P_selector_btn_idle_right;     // 1P ����ѡ��ťĬ��״̬ͼƬ
IMAGE img_1P_selector_btn_down_left;      // 1P ����ѡ��ť����״̬ͼƬ
IMAGE img_1P_selector_btn_down_right;     // 1P ����ѡ��ť����״̬ͼƬ
IMAGE img_2P_selector_btn_idle_left;      // 2P ����ѡ��ťĬ��״̬ͼƬ
IMAGE img_2P_selector_btn_idle_right;     // 2P ����ѡ��ťĬ��״̬ͼƬ
IMAGE img_2P_selector_btn_down_left;      // 2P ����ѡ��ť����״̬ͼƬ
IMAGE img_2P_selector_btn_down_right;     // 2P ����ѡ��ť����״̬ͼƬ

// ��ɫѡ�Ǳ���
IMAGE img_peashooter_selector_background_left;   // ѡ�ǽ��泯������㶹���ֱ���ͼƬ
IMAGE img_peashooter_selector_background_right;  // ѡ�ǽ��泯���ҵ��㶹���ֱ���ͼƬ
IMAGE img_sunflower_selector_background_left;   // ѡ�ǽ��泯��������տ�����ͼƬ
IMAGE img_sunflower_selector_background_right;  // ѡ�ǽ��泯���ҵ����տ�����ͼƬ

// �㶹����ϵ�ж���ͼ��
Atlas atlas_peashooter_idle_left;         // �㶹���ֳ������Ĭ�϶���ͼ��
Atlas atlas_peashooter_idle_right;        // �㶹���ֳ����ҵ�Ĭ�϶���ͼ��
Atlas atlas_peashooter_run_left;          // �㶹���ֳ�����ı��ܶ���ͼ��
Atlas atlas_peashooter_run_right;         // �㶹���ֳ����ҵı��ܶ���ͼ��
Atlas atlas_peashooter_attack_ex_left;    // �㶹���ֳ���������⹥������ͼ��
Atlas atlas_peashooter_attack_ex_right;   // �㶹���ֳ����ҵ����⹥������ͼ��
Atlas atlas_peashooter_die_left;          // �㶹���ֳ��������������ͼ��
Atlas atlas_peashooter_die_right;         // �㶹���ֳ����ҵ���������ͼ��

// ���տ�ϵ�ж���ͼ��
Atlas atlas_sunflower_idle_left;          // ���տ��������Ĭ�϶���ͼ��
Atlas atlas_sunflower_idle_right;         // ���տ������ҵ�Ĭ�϶���ͼ��
Atlas atlas_sunflower_run_left;           // ���տ�������ı��ܶ���ͼ��
Atlas atlas_sunflower_run_right;          // ���տ������ҵı��ܶ���ͼ��
Atlas atlas_sunflower_attack_ex_left;     // ���տ�����������⹥������ͼ��
Atlas atlas_sunflower_attack_ex_right;    // ���տ������ҵ����⹥������ͼ��
Atlas atlas_sunflower_die_left;           // ���տ����������������ͼ��
Atlas atlas_sunflower_die_right;          // ���տ������ҵ���������ͼ��

// ��ϷԪ����Դ
IMAGE img_pea;                            // �㶹ͼƬ
Atlas atlas_pea_break;                    // �㶹���鶯��ͼ��
Atlas atlas_sun;                          // �չ⶯��ͼ��
Atlas atlas_sun_explode;                  // �չⱬը����ͼ��
Atlas atlas_sun_ex;                       // �����չ⶯��ͼ��
Atlas atlas_sun_ex_explode;               // �����չⱬը����ͼ��
Atlas atlas_sun_text;                     // ���ա��ı�����ͼ��

// ��Ч����
Atlas atlas_run_effect;                   // ������Ч����ͼ��
Atlas atlas_jump_effect;                  // ��Ծ��Ч����ͼ��
Atlas atlas_land_effect;                  // �����Ч����ͼ��

// ʤ������
IMAGE img_1P_winnner;                     // 1P��ʤ�ı�ͼƬ
IMAGE img_2P_winnner;                     // 2P��ʤ�ı�ͼƬ
IMAGE img_winnner_bar;                    // ��ʤ����ı�����ͼƬ

// ��ɫͷ��
IMAGE img_avatar_peashooter;              // �㶹����ͷ��ͼƬ
IMAGE img_avatar_sunflower;               // ���տ�ͷ��ͼƬ

// ��������
Scene* menu_scene = nullptr;              // ���˵�����ָ��
Scene* game_scene = nullptr;              // ��Ϸ����ָ��
Scene* selector_scene = nullptr;          // ѡ�ǳ���ָ��
SceneManager scene_manager;               // ��������������
Camera main_camera;                       // �����������

std::vector<Platform> platform_list; // ƽ̨�б�
std::vector<bullet*> bullet_list; // �ӵ��б�

Player* player_1; // ���1
Player* player_2; // ���2
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