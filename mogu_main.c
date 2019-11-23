/******************************************/
/* mogu_main.c : モグラ叩き（メイン処理） */
/* 【記述内容】                           */
/*  ・メイン関数                          */
/*  ・ゲームのメインループ                */
/*  ・ゲームの初期化処理                  */
/*  ・ゲームの終了処理                    */
/*  ・ゲームの開始画面                    */
/*  ・ゲームの終了画面                    */
/*  ・ゲームメッセージ表示                */
/******************************************/
#include "mogu.h"
#include <stdio.h>
#include <unistd.h>

#define DUMMYWAIT 1.0*10000 // メインループの時間調整(μs)

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;

/**************/
/* メイン関数 */
/**************/
int main(int argc, char *argv[]){

	int ret=0;

	game_init();		// ゲームの初期化
	ret=game_start();	//ゲームの開始画面
	if (ret!=GAME_EXIT) {
		while(1) {

			ret=game_loop();	// ゲームのメインループ
			if (ret==GAME_EXIT) break;//※元に戻す

			if (ret==GAME_END) {
				ret=game_end();	//ゲームの終了画面
				if (ret==GAME_EXIT) break;
			}
		}
	}
	game_fin();		// ゲームの終了処理
	return 0;
}

/************************/
/* ゲームのメインループ */
/************************/
int game_loop(void){

	int ret=0;

	s_bgm_on();	// BGMの再生開始
	j_init();	// 判定処理の初期化
	while (1) {		// ゲームのメインループ	

		b_dsp();	// 背景画像の描画
		e_move();	// 敵の移動処理

		ret = j_event();	// イベント処理（タイマーと当たり判定）
		if ( ret==GAME_EXIT || ret==GAME_END ) break;

		t_score();	// スコア表示
		SDL_UpdateWindowSurface(window);// スクリーン更新

		usleep(DUMMYWAIT); // ダミーループ
	}
	s_bgm_off();// BGMの再生停止

	return ret;
}

/**********************/
/* ゲームの初期化処理 */
/**********************/
void game_init(void){

	// SDLの初期化
	SDL_Init(SDL_INIT_VIDEO);
	// ウィンドウ表示
	//SDL_SetVideoMode(DSP_X, DSP_Y, 32, SDL_SWSURFACE);
	window = SDL_CreateWindow( "Mogu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_SWSURFACE );

	b_init();	// 背景の初期化
	e_init();	// 敵の初期化
	t_init();	// 文字の初期化
	s_init();	// 音の初期化処理
}

/********************/
/* ゲームの終了処理 */
/********************/
void game_fin(void){

	s_fin();	// 音の終了処理
	t_fin();	// 文字の終了処理
	e_fin();	// 敵の終了処理
	b_fin();	// 背景の終了処理

	SDL_Quit();	// SDLの終了
}

/********************/
/* ゲームの開始画面 */
/********************/
int game_start(void){
	return game_dispmsg(GAME_PLAY);
}

/********************/
/* ゲームの終了画面 */
/********************/
int game_end(void){
	return game_dispmsg(GAME_END);
}

/************************/
/* ゲームメッセージ表示 */
/************************/
int game_dispmsg(int mode){

	SDL_Event ev;
	int	ret=0;

	do {	// マウスイベントキューのクリア
		SDL_PollEvent(&ev);
	} while (ev.type==SDL_MOUSEBUTTONDOWN || ev.type==SDL_MOUSEBUTTONUP);

	while (1) {

		b_dsp();			// 背景画像の描画

		if (mode==GAME_PLAY)	t_startmsg();	// スタートメッセージの表示
		else					t_endmsg();		// エンドメッセージの表示

		e_center();			// モグラのセンター表示（アニメーション）
		ret = j_mouse2();	// マウスイベント処理2（複数匹対応）

		if ( ret==GAME_EXIT || ret==E_HIT ) break;

		SDL_UpdateWindowSurface(window);// スクリーン更新

		usleep(DUMMYWAIT); // ダミーループ
	}
	return ret;
}