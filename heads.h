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
// ���˵���ѡ�ǽ���
extern IMAGE img_menu_background;                // ���˵�����ͼƬ
extern IMAGE img_VS;                             // VS ������ͼƬ
extern IMAGE img_1P;                             // 1P �ı�ͼƬ
extern IMAGE img_2P;                             // 2P �ı�ͼƬ
extern IMAGE img_1P_desc;                        // 1P ��λ����ͼƬ
extern IMAGE img_2P_desc;                        // 2P ��λ����ͼƬ

// Ĺ����ѡ�ǽ���Ԫ��
extern IMAGE img_gravestone_left;                // �������Ĺ��ͼƬ
extern IMAGE img_gravestone_right;               // �����ҵ�Ĺ��ͼƬ
extern IMAGE img_selector_tip;                   // ѡ�ǽ�����ʾ��Ϣ�ı�ͼƬ
extern IMAGE img_selector_background;            // ѡ�ǽ��汳��ͼ

// ��Ϸ����Ԫ��ͼƬ��Դ����
extern IMAGE img_sky;            // ���ͼƬ
extern IMAGE img_hills;          // ɽ��ͼƬ
extern IMAGE img_platform_large; // ����ƽ̨ͼƬ
extern IMAGE img_platform_small; // С��ƽ̨ͼƬ

// ��ҹ��ָʾͼƬ
extern IMAGE img_1P_cursor;      // 1P ָʾ���ͼƬ
extern IMAGE img_2P_cursor;      // 2P ָʾ���ͼƬ

// ���ѡ��ťͼƬ��1P/2P��
extern IMAGE img_1P_selector_btn_idle_left;      // 1P ����ѡ��ťĬ��״̬ͼƬ
extern IMAGE img_1P_selector_btn_idle_right;     // 1P ����ѡ��ťĬ��״̬ͼƬ
extern IMAGE img_1P_selector_btn_down_left;      // 1P ����ѡ��ť����״̬ͼƬ
extern IMAGE img_1P_selector_btn_down_right;     // 1P ����ѡ��ť����״̬ͼƬ
extern IMAGE img_2P_selector_btn_idle_left;      // 2P ����ѡ��ťĬ��״̬ͼƬ
extern IMAGE img_2P_selector_btn_idle_right;     // 2P ����ѡ��ťĬ��״̬ͼƬ
extern IMAGE img_2P_selector_btn_down_left;      // 2P ����ѡ��ť����״̬ͼƬ
extern IMAGE img_2P_selector_btn_down_right;     // 2P ����ѡ��ť����״̬ͼƬ

// ��ɫѡ�Ǳ���
extern IMAGE img_peashooter_selector_background_left;   // ѡ�ǽ��泯������㶹���ֱ���ͼƬ
extern IMAGE img_peashooter_selector_background_right;  // ѡ�ǽ��泯���ҵ��㶹���ֱ���ͼƬ
extern IMAGE img_sunflower_selector_background_left;   // ѡ�ǽ��泯��������տ�����ͼƬ
extern IMAGE img_sunflower_selector_background_right;  // ѡ�ǽ��泯���ҵ����տ�����ͼƬ

// �㶹����ϵ�ж���ͼ��
extern Atlas atlas_peashooter_idle_left;         // �㶹���ֳ������Ĭ�϶���ͼ��
extern Atlas atlas_peashooter_idle_right;        // �㶹���ֳ����ҵ�Ĭ�϶���ͼ��
extern Atlas atlas_peashooter_run_left;          // �㶹���ֳ�����ı��ܶ���ͼ��
extern Atlas atlas_peashooter_run_right;         // �㶹���ֳ����ҵı��ܶ���ͼ��
extern Atlas atlas_peashooter_attack_ex_left;    // �㶹���ֳ���������⹥������ͼ��
extern Atlas atlas_peashooter_attack_ex_right;   // �㶹���ֳ����ҵ����⹥������ͼ��
extern Atlas atlas_peashooter_die_left;          // �㶹���ֳ��������������ͼ��
extern Atlas atlas_peashooter_die_right;         // �㶹���ֳ����ҵ���������ͼ��

// ���տ�ϵ�ж���ͼ��
extern Atlas atlas_sunflower_idle_left;          // ���տ��������Ĭ�϶���ͼ��
extern Atlas atlas_sunflower_idle_right;         // ���տ������ҵ�Ĭ�϶���ͼ��
extern Atlas atlas_sunflower_run_left;           // ���տ�������ı��ܶ���ͼ��
extern Atlas atlas_sunflower_run_right;          // ���տ������ҵı��ܶ���ͼ��
extern Atlas atlas_sunflower_attack_ex_left;     // ���տ�����������⹥������ͼ��
extern Atlas atlas_sunflower_attack_ex_right;    // ���տ������ҵ����⹥������ͼ��
extern Atlas atlas_sunflower_die_left;           // ���տ����������������ͼ��
extern Atlas atlas_sunflower_die_right;          // ���տ������ҵ���������ͼ��

// ��ϷԪ����Դ
extern IMAGE img_pea;                            // �㶹ͼƬ
extern Atlas atlas_pea_break;                    // �㶹���鶯��ͼ��
extern Atlas atlas_sun;                          // �չ⶯��ͼ��
extern Atlas atlas_sun_explode;                  // �չⱬը����ͼ��
extern Atlas atlas_sun_ex;                       // �����չ⶯��ͼ��
extern Atlas atlas_sun_ex_explode;               // �����չⱬը����ͼ��
extern Atlas atlas_sun_text;                     // ���ա��ı�����ͼ��

// ��Ч����
extern Atlas atlas_run_effect;                   // ������Ч����ͼ��
extern Atlas atlas_jump_effect;                  // ��Ծ��Ч����ͼ��
extern Atlas atlas_land_effect;                  // �����Ч����ͼ��

// ʤ������
extern IMAGE img_1P_winnner;                     // 1P��ʤ�ı�ͼƬ
extern IMAGE img_2P_winnner;                     // 2P��ʤ�ı�ͼƬ
extern IMAGE img_winnner_bar;                    // ��ʤ����ı�����ͼƬ

// ��ɫͷ��
extern IMAGE img_avatar_peashooter;              // �㶹����ͷ��ͼƬ
extern IMAGE img_avatar_sunflower;               // ���տ�ͷ��ͼƬ

// ��������
extern Scene* menu_scene;              // ���˵�����ָ��
extern Scene* game_scene;              // ��Ϸ����ָ��
extern Scene* selector_scene;          // ѡ�ǳ���ָ��
extern SceneManager scene_manager;               // ��������������
extern Camera main_camera;                // �����������

extern std::vector<Platform> platform_list; // ƽ̨�б�
extern std::vector<bullet*> bullet_list; // �ӵ��б�
extern Player* player_1; // ���1
extern Player* player_2; // ���2
extern IMAGE* img_player_1_avatar; // ���1ͷ��
extern IMAGE* img_player_2_avatar; // ���2ͷ��
extern bool is_debug;


inline void flip_image(IMAGE* src, IMAGE* dst);
void flip_atlas(Atlas& src, Atlas& dst);
void putimage_alpha(int x, int y, IMAGE* img);   //���Ŷ���
void putimage_alpha(const Camera& camera,int x, int y, IMAGE* img);   //���Ŷ���
void putimage_alpha(int dst_x, int dst_y, int width, int height, IMAGE* img, int src_x, int src_y);
void load_game_resources();
void line(const Camera& camera, int x1, int y1, int x2, int y2);
void sketch_image(IMAGE* src, IMAGE* dst);
