#include"heads.h"
//翻转图片
void flip_image(IMAGE* src, IMAGE* dst) {
	int w = src->getwidth();
	int h = src->getheight();
	Resize(dst, w, h);
	DWORD* src_buffer = GetImageBuffer(src);
	DWORD* dst_buffer = GetImageBuffer(dst);
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int idx_src = y * w + x;
			int idx_dst = y * w + (w - x - 1);
			dst_buffer[idx_dst] = src_buffer[idx_src];
		}
	}
}
//翻转图集
void flip_atlas(Atlas& src, Atlas& dst) {
	dst.clear();
	for (int i = 0; i < src.get_size(); i++) {
		IMAGE img_flpipped;
		flip_image(src.get_image(i), &img_flpipped);
		dst.add_image(img_flpipped);
	}
}
//加载带透明度的图片
void putimage_alpha(int x, int y, IMAGE* img) {
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });

}
void putimage_alpha(const Camera& camera, int x, int y, IMAGE* img) {
	int w = img->getwidth();
	int h = img->getheight();
	const Vector2& pos_camera = camera.get_position();
	AlphaBlend(GetImageHDC(GetWorkingImage()), x - pos_camera.x, y - pos_camera.y , w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
void putimage_alpha(int dst_x, int dst_y, int width, int height, IMAGE* img, int src_x, int src_y) {
	int w = width > 0 ? width : img->getheight();
	int h = height > 0 ? height : img->getheight();
	AlphaBlend(GetImageHDC(NULL), dst_x, dst_y, w, h,
		GetImageHDC(img), src_x, src_y, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
//加载图片
void load_game_resources() {
	//============================ 字体加载 ============================//
	AddFontResourceEx(_T("resources/IPix.ttf"), FR_PRIVATE, NULL);  // 加载像素字体用于游戏UI

	//============================ 基础图片加载 ============================//
	// 主菜单与界面元素
	loadimage(&img_menu_background, _T("resources/menu_background.png"));  // 菜单背景图 1280x720
	loadimage(&img_VS, _T("resources/VS.png"));                           // VS对战标志图 300x120
	loadimage(&img_1P, _T("resources/1P.png"));                          // 1P标识图 100x40
	loadimage(&img_2P, _T("resources/2P.png"));                          // 2P标识图 100x40
	loadimage(&img_1P_desc, _T("resources/1P_desc.png"));                // 1P键位说明图 400x200
	loadimage(&img_2P_desc, _T("resources/2P_desc.png"));                // 2P键位说明图 400x200

	// 场景元素
	loadimage(&img_sky, _T("resources/sky.png"));                        // 天空渐变背景图 1280x720
	loadimage(&img_hills, _T("resources/hills.png"));                    // 山丘前景图 1280x200
	loadimage(&img_platform_large, _T("resources/platform_large.png"));  // 大平台图 320x40
	loadimage(&img_platform_small, _T("resources/platform_small.png"));  // 小平台图 160x40

	// 界面组件
	loadimage(&img_gravestone_right, _T("resources/gravestone.png"));    // 右侧墓碑图 80x120
	flip_image(&img_gravestone_right, &img_gravestone_left);             // 生成左侧镜像墓碑
	loadimage(&img_selector_tip, _T("resources/selector_tip.png"));      // 选角提示图 600x80
	loadimage(&img_selector_background, _T("resources/selector_background.png")); // 选角背景图 1280x720

	// 玩家选择按钮（通过镜像生成左右版本）
	loadimage(&img_1P_selector_btn_idle_right, _T("resources/1P_selector_btn_idle.png")); // 1P右侧常态按钮 200x60
	flip_image(&img_1P_selector_btn_idle_right, &img_1P_selector_btn_idle_left);
	loadimage(&img_1P_selector_btn_down_right, _T("resources/1P_selector_btn_down.png")); // 1P右侧按下状态
	flip_image(&img_1P_selector_btn_down_right, &img_1P_selector_btn_down_left);

	loadimage(&img_2P_selector_btn_idle_right, _T("resources/2P_selector_btn_idle.png")); // 2P右侧常态按钮
	flip_image(&img_2P_selector_btn_idle_right, &img_2P_selector_btn_idle_left);
	loadimage(&img_2P_selector_btn_down_right, _T("resources/2P_selector_btn_down.png"));
	flip_image(&img_2P_selector_btn_down_right, &img_2P_selector_btn_down_left);

	// 角色选角背景
	loadimage(&img_peashooter_selector_background_right, _T("resources/peashooter_selector_background.png")); // 豌豆射手右侧背景 600x400
	flip_image(&img_peashooter_selector_background_right, &img_peashooter_selector_background_left);
	loadimage(&img_sunflower_selector_background_right, _T("resources/sunflower_selector_background.png"));   // 向日葵右侧背景
	flip_image(&img_sunflower_selector_background_right, &img_sunflower_selector_background_left);

	//============================ 动画图集加载 ============================//
	// 豌豆射手动画（帧数根据实际文件调整）
	atlas_peashooter_idle_right.load_from_file(_T("resources/peashooter_idle_%d.png"), 9);  // 右侧闲置动画（9帧）
	flip_atlas(atlas_peashooter_idle_right, atlas_peashooter_idle_left);
	atlas_peashooter_run_right.load_from_file(_T("resources/peashooter_run_%d.png"), 5);    // 右侧奔跑动画
	flip_atlas(atlas_peashooter_run_right, atlas_peashooter_run_left);
	atlas_peashooter_attack_ex_right.load_from_file(_T("resources/peashooter_attack_ex_%d.png"), 3); // 特殊攻击
	flip_atlas(atlas_peashooter_attack_ex_right, atlas_peashooter_attack_ex_left);
	atlas_peashooter_die_right.load_from_file(_T("resources/peashooter_die_%d.png"), 4);    // 死亡动画
	flip_atlas(atlas_peashooter_die_right, atlas_peashooter_die_left);

	// 向日葵动画
	atlas_sunflower_idle_right.load_from_file(_T("resources/sunflower_idle_%d.png"), 8);     // 右侧闲置动画
	flip_atlas(atlas_sunflower_idle_right, atlas_sunflower_idle_left);
	atlas_sunflower_run_right.load_from_file(_T("resources/sunflower_run_%d.png"), 5);
	flip_atlas(atlas_sunflower_run_right, atlas_sunflower_run_left);
	atlas_sunflower_attack_ex_right.load_from_file(_T("resources/sunflower_attack_ex_%d.png"), 9);
	flip_atlas(atlas_sunflower_attack_ex_right, atlas_sunflower_attack_ex_left);
	atlas_sunflower_die_right.load_from_file(_T("resources/sunflower_die_%d.png"), 2);
	flip_atlas(atlas_sunflower_die_right, atlas_sunflower_die_left);

	//============================ 游戏元素 ============================//
	// 投射物与特效
	loadimage(&img_pea, _T("resources/pea.png"));                          // 豌豆基础图 32x32
	atlas_pea_break.load_from_file(_T("resources/pea_break_%d.png"), 3);   // 豌豆破裂动画（3帧）

	// 日光系统
	atlas_sun.load_from_file(_T("resources/sun_%d.png"), 5);              // 日光浮动动画
	atlas_sun_explode.load_from_file(_T("resources/sun_explode_%d.png"), 5);// 日光爆炸
	atlas_sun_ex.load_from_file(_T("resources/sun_ex_%d.png"), 5);         // 特殊日光
	atlas_sun_ex_explode.load_from_file(_T("resources/sun_ex_explode_%d.png"), 5);
	atlas_sun_text.load_from_file(_T("resources/sun_text_%d.png"), 6);      // "日"文字动画

	// 运动特效
	atlas_run_effect.load_from_file(_T("resources/run_effect_%d.png"), 4);  // 奔跑灰尘特效
	atlas_jump_effect.load_from_file(_T("resources/jump_effect_%d.png"), 5);// 跳跃特效
	atlas_land_effect.load_from_file(_T("resources/land_effect_%d.png"), 2);// 落地冲击波

	// 胜负界面
	loadimage(&img_1P_winnner, _T("resources/1P_winner.png"));            // 1P胜利横幅 600x200 
	loadimage(&img_2P_winnner, _T("resources/2P_winner.png"));
	loadimage(&img_winnner_bar, _T("resources/winnner_bar.png"));        // 胜利条背景 800x80

	// 角色头像
	loadimage(&img_avatar_peashooter, _T("resources/avatar_peashooter.png")); // 128x128
	loadimage(&img_avatar_sunflower, _T("resources/avatar_sunflower.png"));

	//============================ 音频资源 ============================//
	// 背景音乐
	mciSendString(_T("open resources/bgm_game.mp3 alias bgm_game"), NULL, 0, NULL);  // 游戏BGM
	mciSendString(_T("open resources/bgm_menu.mp3 alias bgm_menu"), NULL, 0, NULL);  // 菜单BGM

	// 音效系统
	mciSendString(_T("open resources/pea_break_1.mp3 alias pea_break_1"), NULL, 0, NULL); // 豌豆破裂音效
	mciSendString(_T("open resources/pea_break_2.mp3 alias pea_break_2"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_break_3.mp3 alias pea_break_3"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_shoot_1.mp3 alias pea_shoot_1"), NULL, 0, NULL); // 发射音效
	mciSendString(_T("open resources/pea_shoot_2.mp3 alias pea_shoot_2"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_shoot_ex.mp3 alias pea_shoot_ex"), NULL, 0, NULL);// 特殊射击

	// 系统音效
	mciSendString(_T("open resources/sun_explode.mp3 alias sun_explode"), NULL, 0, NULL);// 日光爆炸
	mciSendString(_T("open resources/sun_explode_ex.mp3 alias sun_explode_ex"), NULL, 0, NULL);
	mciSendString(_T("open resources/ui_confirm.wav alias ui_confirm"), NULL, 0, NULL); // 确认音
	mciSendString(_T("open resources/ui_switch.wav alias ui_switch"), NULL, 0, NULL);   // 切换音
	mciSendString(_T("open resources/ui_win.wav alias ui_win"), NULL, 0, NULL);        // 胜利音效

}