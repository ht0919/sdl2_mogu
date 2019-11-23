/****************************************/
/* mogu_enemy.c : モグラ叩き（敵の管理）*/
/* 【記述内容】    ※（複数匹対応）		*/
/*  ・敵の初期化処理                    */
/*  ・敵の表示処理                      */
/*  ・敵の終了処理                      */
/*  ・敵の中央表示                      */
/****************************************/
#include "mogu.h"
#include <time.h>

extern int	timer_cnt;	// タイマカウンタ(from mogu_judg.c)
//int	timer_cnt = GAME_TIME;	// タイマカウンタ

struct char_data e_dat[MOGU_NUM];	// 敵画像管理用変数（複数匹対応）

extern SDL_Window* window;

/******************/
/* 敵の初期化処理 */
/******************/
void e_init(void) {

	int	i;

	for (i=0; i<MOGU_NUM; i++) {
		// 敵画像の読み込み
		e_dat[i].img = SDL_LoadBMP("mogura.bmp");
		// 白を透過色にする
		//SDL_SetColorKey(e_dat[i].img, SDL_SRCCOLORKEY, SDL_MapRGB(e_dat[i].img->format, 255, 255, 255));
		SDL_SetColorKey(e_dat[i].img, SDL_TRUE, SDL_MapRGB(e_dat[i].img->format, 255, 255, 255));
		//e_dat[i].img = SDL_DisplayFormat(e_dat[i].img);
		e_dat[i].img = SDL_ConvertSurfaceFormat(e_dat[i].img, SDL_GetWindowPixelFormat(window), 0);
		// 敵画像の矩形情報を設定
		e_dat[i].rect.x = 0;			// 敵の画像の取り出し位置（横）
		e_dat[i].rect.y = 0;			// 敵の画像の取り出し位置（縦）
		e_dat[i].rect.w = CHIP_SIZE;	// 敵の画像のサイズ（横幅）
		e_dat[i].rect.h = CHIP_SIZE;	// 敵の画像のサイズ（高さ）

		// 最初に出現する座標の設定
		srand((unsigned int)time(NULL));// 乱数の種を生成
		e_dat[i].scrn.x = CHIP_SIZE * (rand() % MAP_X);
		e_dat[i].scrn.y = CHIP_SIZE * (rand() % MAP_Y);
		e_dat[i].cp = (rand() % P_NUM);	// チップパターンの初期化（複数匹対応）
		e_dat[i].dspcnt = 0;			// 表示切り替えカウンタの初期化
		e_dat[i].speed = SPEED;			// 表示切り替え速度の設定
	}
}

/****************/
/* 敵の移動処理 */
/****************/
void e_move(void) {

	int	i;

	for (i=0; i<MOGU_NUM; i++) {
		// もし当たっていたら画像を差し替える
		if (e_dat[i].hitflg == E_HIT) {
			e_dat[i].rect.x = CHIP_SIZE * P_NUM;
		} else {
			e_dat[i].rect.x = CHIP_SIZE * e_dat[i].cp;
		}
		//SDL_BlitSurface(e_dat[i].img, &e_dat[i].rect, SDL_GetVideoSurface(), &e_dat[i].scrn);
		SDL_BlitSurface(e_dat[i].img, &e_dat[i].rect, SDL_GetWindowSurface(window), &e_dat[i].scrn);

		// 指定回数のフレームを表示したらチップパターンを更新
		if (++e_dat[i].dspcnt >= e_dat[i].speed) {
			e_dat[i].dspcnt = 0;		// 表示カウンタのリセット
			e_dat[i].hitflg = E_SAFE;	// 当たり判定フラグのリセット
			if (++e_dat[i].cp == P_NUM) {
				// チップパターンのリセット
				e_dat[i].cp=0;
				// 出現する座標の更新（ランダム）
				e_dat[i].scrn.x = CHIP_SIZE * (rand() % MAP_X);
				e_dat[i].scrn.y = CHIP_SIZE * (rand() % MAP_Y);
			}
		}

		// 残り時間に応じて切替速度を高速にする
		if (timer_cnt==45 && e_dat[i].speed==60) e_dat[i].speed=50;
		if (timer_cnt==30 && e_dat[i].speed==50) e_dat[i].speed=40;
	}
}

/****************/
/* 敵の終了処理 */
/****************/
void e_fin(void){

	int	i;

	for (i=0; i<MOGU_NUM; i++) {
		SDL_FreeSurface(e_dat[i].img);	// 敵画像領域の解放
	}
}

/****************/
/* 敵の中央表示 */
/****************/
void e_center(void) {

	// 表示切り替え速度の設定(60固定)
	e_dat[0].speed = SPEED;//※修正(06/18)

	// 出現する座標の設定(画面の中央)
	e_dat[0].scrn.x = (DSP_X - CHIP_SIZE)/2;
	e_dat[0].scrn.y = (DSP_Y - CHIP_SIZE)/2;

	// もし当たっていたら画像を差し替える
	if (e_dat[0].hitflg == E_HIT) {
		e_dat[0].rect.x = CHIP_SIZE * P_NUM;
	} else {
		e_dat[0].rect.x = CHIP_SIZE * e_dat[0].cp;
	}
	//SDL_BlitSurface(e_dat[0].img, &e_dat[0].rect, SDL_GetVideoSurface(), &e_dat[0].scrn);
	SDL_BlitSurface(e_dat[0].img, &e_dat[0].rect, SDL_GetWindowSurface(window), &e_dat[0].scrn);

	// 指定回数のフレームを表示したらチップパターンを更新
	if (++e_dat[0].dspcnt >= e_dat[0].speed) {
		e_dat[0].dspcnt = 0;		// 表示カウンタのリセット
		e_dat[0].hitflg = E_SAFE;	// 当たり判定フラグのリセット
		if (++e_dat[0].cp == P_NUM) {
			// チップパターンのリセット
			e_dat[0].cp=0;
		}
	}
}