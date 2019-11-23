/****************************************/
/* mogu_text.c : モグラ叩き（文字表示） */
/* 【記述内容】                         */
/*  ・文字の初期化処理     　　         */
/*  ・スコアの表示処理                  */
/*  ・スタートメッセージ表示            */
/*  ・エンドメッセージ表示              */
/*  ・文字の表示処理                    */
/*  ・文字の終了処理                    */
/****************************************/
#include "mogu.h"
#include <SDL2/SDL_ttf.h>

#define FONTFILE	"AGENCYB.TTF"
#define FONTSIZE	28

TTF_Font* font;

extern int	score_cnt;	// スコアカウンタ(from mogu_judg.c)
extern int	timer_cnt;	// タイマカウンタ

void t_dsp(int x, int y, char *str, SDL_Color color);	// 文字表示(Private)

extern SDL_Window* window;

/********************/
/* 文字の初期化処理 */
/********************/
void t_init(void){
	TTF_Init();									// SDL_ttfの初期化
	font = TTF_OpenFont(FONTFILE,FONTSIZE);		// フォントデータの読み込み
}

/******************/
/* スコア表示処理 */
/******************/
void t_score(void) {
	char strbuf[32];
	SDL_Color color = {0xff, 0xff, 0x00};	// RGB(黄色)
	snprintf(strbuf, sizeof(strbuf),"HIT:%d  TIME:%d",score_cnt,timer_cnt);	// 整数を文字列に変換
	t_dsp(20,0,strbuf,color);
}

/**************************/
/* スタートメッセージ表示 */
/**************************/
void t_startmsg(void) {
	char strbuf[32];
	SDL_Color color = {0xff, 0x00, 0x00};	// RGB(赤)
	snprintf(strbuf, sizeof(strbuf),"CLICK MOLE, GAME START");
	t_dsp(14,12,strbuf,color);
}

/**************************/
/* エンドメッセージ表示 */
/**************************/
void t_endmsg(void) {
	char strbuf[32];
	SDL_Color color = {0xff, 0xff, 0x00};	// RGB(黄色)

	snprintf(strbuf, sizeof(strbuf),"YOUR SCORE : %d",score_cnt);
	t_dsp(14,10,strbuf,color);

	snprintf(strbuf, sizeof(strbuf),"CLICK MOLE, GAME RESTART");
	t_dsp(14,13,strbuf,color);
}

/******************/
/* 文字の表示処理 */
/******************/
void t_dsp(int x, int y, char *str, SDL_Color color) {

	SDL_Surface* image;
	SDL_Rect rect, scr_rect;

	// 文字列の画像を作成
	image = TTF_RenderUTF8_Blended(font, str, color);
	// 文字の画像情報を設定
	rect.x = 0;			// 文字画像の取り出し位置（横）
	rect.y = 0;			// 文字画像の取り出し位置（縦）
	rect.w = image->w;	// 文字画像のサイズ（横幅）
	rect.h = image->h;	// 文字画像のサイズ（高さ）
	// 文字の表示位置を設定
	scr_rect.x = x * (FONTSIZE/2);
	scr_rect.y = y * (FONTSIZE/2);
	scr_rect.w = image->w;
	scr_rect.h = image->h;
	// 文字をスクリーンへ複写
	//SDL_BlitSurface(image, &rect, SDL_GetVideoSurface(), &scr_rect);
	SDL_BlitSurface(image, &rect, SDL_GetWindowSurface(window), &scr_rect);
	SDL_FreeSurface(image);	// サーフェスエリアの解放
}

/******************/
/* 文字の終了処理 */
/******************/
void t_fin(void){
	TTF_CloseFont(font);	// フォントエリアの解放
	TTF_Quit();				// SDL_ttfの終了
}