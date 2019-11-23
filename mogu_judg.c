/****************************************/
/* mogu_judg.c : モグラ叩き（判定処理） */
/*  ・判定処理の初期化                  */
/*  ・イベント処理                      */
/*  ・経過時間の設定                    */
/*  ・マウスイベント処理                */
/****************************************/
#include "mogu.h"

extern struct char_data e_dat[MOGU_NUM];	// 敵管理用変数（複数匹対応）

time_t start_time = 0;	// 開始時間
int	mouse_flg = 0;		// マウスリピートフラグ
int	score_cnt = 0;		// スコアカウンタ
int	timer_cnt = 0;		// タイマカウンタ

/********************/
/* 判定処理の初期化 */
/********************/
void j_init(void) {
	score_cnt = 0;			// スコアカウンタの初期化
	timer_cnt = GAME_TIME;	// タイマカウンタの初期化
	start_time = time(NULL);// 開始時刻の取得
}

/****************/
/* イベント処理 */
/****************/
int j_event(void) {

	// 制限時間の判定
	if (j_timer() <= 0) return GAME_END; //ゲーム終了
	// マウスの当たり判定
	return j_mouse();
}

/******************/
/* 経過時間の設定 */
/******************/
int j_timer(void) {

	double current_time;

	current_time = difftime(time(NULL), start_time);// ゲームの経過時刻の計算
	timer_cnt = (int)(GAME_TIME - current_time);
	return timer_cnt;
}

/**********************/
/* マウスイベント処理 */
/**********************/
int j_mouse(void) {

	SDL_Event ev;
	int		ret=0;
	int		x,y;
	Uint8	flg;
	int		i;

	SDL_PollEvent(&ev);	// イベントの取得
	switch(ev.type){	// ×ボタンが押されたらゲーム終了
		case SDL_QUIT:
			ret = GAME_EXIT;
			break;	

		case SDL_MOUSEBUTTONDOWN:

			// マウスの状態を取得
			flg = SDL_GetMouseState( &x, &y );

			for (i=0; i<MOGU_NUM; i++) {
				// マウスリピートフラグがOFFでかつ当たっていなくてかつ左ボタンが押されたか？
				if( (mouse_flg==0) && (e_dat[i].hitflg != E_HIT) && (flg & SDL_BUTTON(1)) ){
					// printf("CLICK！ mx=%d,my=%d\n",x,y);	//デバッグ用表示
					s_se(SE_HIT); // 叩く音を再生
					if( e_dat[i].cp == (P_NUM - 1) ){		// モグラが完全に出た状態か？
						// マウスの座標がモグラの表示範囲内か
						if ((e_dat[i].scrn.x <= x && (e_dat[i].scrn.x+CHIP_SIZE) >= x) &&
							(e_dat[i].scrn.y <= y && (e_dat[i].scrn.y+CHIP_SIZE) >= y)) {
								// printf("HIT！ ex=%d,ey=%d\n",e_dat.scrn.x,e_dat.scrn.y);	//デバッグ用表示
								s_se(SE_CRY); // モグラの鳴く音を再生
								e_dat[i].hitflg = E_HIT;	// ヒットフラグをON
								ret = e_dat[i].hitflg;
								score_cnt++;			// スコアカウンタをインクリメント
								break;
						}
					}
				}
			}
			mouse_flg = 1;	// マウスリピートフラグをON
			break;

		case SDL_MOUSEBUTTONUP:
			mouse_flg = 0;		// マウスリピートフラグをOFF
			break;

		default:
			break;
	}
	return(ret);
}

/*************************************/
/* マウスイベント処理2（複数匹対応） */
/*************************************/
int j_mouse2(void) {

	SDL_Event ev;
	int		ret=0;
	int		x,y;
	Uint8	flg;

	SDL_PollEvent(&ev);	// イベントの取得
	switch(ev.type){	// ×ボタンが押されたらゲーム終了
		case SDL_QUIT:
			ret = GAME_EXIT;
			break;	

		case SDL_MOUSEBUTTONDOWN:

			// マウスの状態を取得
			flg = SDL_GetMouseState( &x, &y );

			// マウスリピートフラグがOFFでかつ当たっていなくてかつ左ボタンが押されたか？
			if( (mouse_flg==0) && (e_dat[0].hitflg != E_HIT) && (flg & SDL_BUTTON(1)) ){
				// printf("CLICK！ mx=%d,my=%d\n",x,y);	//デバッグ用表示
				s_se(SE_HIT); // 叩く音を再生
				if( e_dat[0].cp == (P_NUM - 1) ){		// モグラが完全に出た状態か？
					// マウスの座標がモグラの表示範囲内か
					if ((e_dat[0].scrn.x <= x && (e_dat[0].scrn.x+CHIP_SIZE) >= x) &&
						(e_dat[0].scrn.y <= y && (e_dat[0].scrn.y+CHIP_SIZE) >= y)) {
							// printf("HIT！ ex=%d,ey=%d\n",e_dat.scrn.x,e_dat.scrn.y);	//デバッグ用表示
							s_se(SE_CRY); // モグラの鳴く音を再生
							e_dat[0].hitflg = E_HIT;	// ヒットフラグをON
							score_cnt++;			// スコアカウンタをインクリメント
					}
				}
			}
			mouse_flg = 1;	// マウスリピートフラグをON
			ret = e_dat[0].hitflg;
			break;

		case SDL_MOUSEBUTTONUP:
			mouse_flg = 0;		// マウスリピートフラグをOFF
			break;

		default:
			break;
	}
	return(ret);
}