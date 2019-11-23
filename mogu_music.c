/***************************************/
/* mogu_music.c : モグラ叩き（音関連） */
/* 【記述内容】                        */
/*  ・音の初期化処理     　　          */
/*  ・効果音の再生処理                 */
/*  ・BGMの再生処理                    */
/*  ・BGMの停止処理                    */
/*  ・音の終了処理                     */
/***************************************/
#include "mogu.h"
#include <SDL2/SDL_mixer.h>

// 音関連の管理情報構造体
struct sound_data {
	Mix_Chunk   *se1;	// 効果音用変数（叩く音）
	Mix_Chunk   *se2;	// 効果音用変数（モグラの鳴く音）
	Mix_Music   *bgm;	// BGM用変数
};

struct sound_data s_dat;	// 音関連データ管理用変数

/******************/
/* 音の初期化処理 */
/******************/
void s_init(void) {

	// SDL_mixerの初期化
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,1024);
	// 同時発声数を設定
	Mix_AllocateChannels(16);

	// サウンドファイルの読み込み
	s_dat.se1 = Mix_LoadWAV("se1.wav");	// 効果音ファイル1をロード
	s_dat.se2 = Mix_LoadWAV("se2.wav");	// 効果音ファイル2をロード
	s_dat.bgm = Mix_LoadMUS("bgm1.mid");// BGMファイルをロード
}

/********************/
/* 効果音の再生処理 */
/********************/
void s_se(int s_num) {

	switch(s_num){
		case SE_HIT:	// 効果音（叩く音）
			if (Mix_Playing(1) == 0)
				Mix_PlayChannel( 1,s_dat.se1,0 );
			break;
		case SE_CRY:	// 効果音（モグラの鳴く音）
			if (Mix_Playing(2) == 0)
				Mix_PlayChannel( 2,s_dat.se2,0 );
			break;
		default:
			break;
	}
}

/*****************/
/* BGMの再生処理 */
/*****************/
void s_bgm_on(void) {
	Mix_PlayMusic(s_dat.bgm,-1);// BGMの再生スタート(※無限ループ)
}

/*****************/
/* BGMの停止処理 */
/*****************/
void s_bgm_off(void) {
	Mix_HaltMusic();	// BGMの停止
}

/****************/
/* 音の終了処理 */
/****************/
void s_fin(void) {
	Mix_FreeMusic(s_dat.bgm);	// ロードした曲を開放
	Mix_FreeChunk(s_dat.se2);	// ロードした効果音2を開放
	Mix_FreeChunk(s_dat.se1);	// ロードした効果音1を開放
	Mix_CloseAudio();			// SDL_Mixerクローズ
}