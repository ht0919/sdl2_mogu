/****************************************/
/* mogu_back.c : モグラ叩き（背景処理） */
/* 【記述内容】                         */
/*  ・背景の初期化処理                  */
/*  ・背景の表示処理                    */
/*  ・背景の終了処理                    */
/****************************************/
#include "mogu.h"

// 背景画像管理情報
struct back_data {
	SDL_Surface	*img;	// 画像イメージ
	SDL_Rect	rect;	// 矩形情報
	SDL_Rect	scrn;	// 表示位置
};

struct back_data b_dat;	// 背景データ管理用変数

int map[MAP_Y][MAP_X]={
		{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
		{12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12,12},
		{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
		{12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12,12},
		{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
		{12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12,12},
		{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
		{12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12,12},
		{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
		{12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12,12},
		{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
		{12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12,12},
		{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
		{12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12, 8,12,12},
		{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
};

extern SDL_Window* window;

/********************/
/* 背景の初期化処理 */
/********************/
void b_init(void){
	// 背景画像の読み込み
	b_dat.img = SDL_LoadBMP("chip02.bmp");
	// 背景画像の矩形情報を設定
	//b_dat.rect.x = 32*3;		// 背景画像の取り出し位置（横）
	//b_dat.rect.y = 32*0;		// 背景画像の取り出し位置（縦）
	//b_dat.rect.w = b_dat.img->w;	// 背景画像のサイズ（横幅）
	//b_dat.rect.h = b_dat.img->h;	// 背景画像のサイズ（高さ）
}

/******************/
/* 背景の表示処理 */
/******************/
void b_dsp(void) {

	int i,j;

	for (i=0; i < MAP_Y; i++) {		// 縦表示のループ
		for (j=0; j < MAP_X; j++) {	// 横表示のループ

			/* マップチップの取り出し位置を設定 */
			b_dat.rect.x = CHIP_SIZE * (map[i][j] % 8);	// マップチップの横の個数で割った剰余
			b_dat.rect.y = CHIP_SIZE * (map[i][j] / 8);	// マップチップの横の個数で割った商
			b_dat.rect.w = CHIP_SIZE;		// マップチップの横のドット数
			b_dat.rect.h = CHIP_SIZE;		// マップチップの縦のドット数


			// 画像の表示位置を設定
			b_dat.scrn.x = j * CHIP_SIZE;
			b_dat.scrn.y = i * CHIP_SIZE;
			// 画像をスクリーンへ複写
			//SDL_BlitSurface(b_dat.img, &b_dat.rect, SDL_GetVideoSurface(), &b_dat.scrn);
			SDL_BlitSurface(b_dat.img, &b_dat.rect, SDL_GetWindowSurface(window), &b_dat.scrn);
		}
	}
}

/******************/
/* 背景の終了処理 */
/******************/
void b_fin(void){
	SDL_FreeSurface(b_dat.img);	// 背景画像領域の解放
}