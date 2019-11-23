/*******************************************/
/* mogu.h : モグラ叩き（ヘッダーファイル） */
/* 【記述内容】                            */
/*  ・インクルードファイル指定             */
/*  ・定数定義                             */
/*  ・構造体定義                           */
/*  ・関数定義                             */
/*******************************************/

#include <SDL2/SDL.h>
#include <time.h>

#define	DSP_X	640		// ウィンドウの横サイズ
#define	DSP_Y	480		// ウィンドウの縦サイズ
#define	MAP_X	20		// マップデータの横個数
#define	MAP_Y	15		// マップデータの縦個数

#define	CHIP_SIZE	32	// チップのドット数
#define	P_NUM		3	// 各パターンの個数
#define	SPEED		60	// 表示スピード調整用
#define	GAME_TIME	60	// ゲーム時間

#define	GAME_PLAY	11	// ゲーム実行
#define	GAME_RETRY	33	// ゲームリトライ
#define	GAME_END	66	// ゲーム終了
#define	GAME_EXIT	99	// ゲーム中止

#define E_SAFE	0		// 敵の当たり判定（はずれ）
#define E_HIT	1		// 敵の当たり判定（当たり）

#define SE_HIT	1		// 効果音（叩く音）
#define SE_CRY	2		// 効果音（モグラの鳴く音）

#define	MOGU_NUM	5	// モグラの数（複数匹対応）

// 敵画像管理情報
struct char_data {
	SDL_Surface	*img;	// 画像イメージ
	SDL_Rect	rect;	// 矩形情報
	SDL_Rect	scrn;	// 表示位置
	int			  cp;	// チップパターン
	int		  dspcnt;	// 表示カウンタ
	int		   speed;	// 表示切り替え速度
	int		  hitflg;	// 当たりフラグ
};

// メイン処理(mogu_main.c)
void game_init(void);	// ゲーム全体の初期化処理
void game_fin(void);	// ゲーム全体の終了処理
int  game_start(void);	//ゲームの開始画面
int  game_loop(void);	//ゲームのメインループ
int  game_end(void);	//ゲームの終了画面
int  game_dispmsg(int);	//ゲームメッセージ表示

// 背景処理(mogu_back.c)
void b_init(void);		// 背景初期化処理
void b_dsp(void);		// 背景表示処理
void b_fin(void);		// 背景終了処理

// 敵処理(mogu_enemy.c)
void e_init(void);		// 敵の初期化処理
void e_move(void);		// 敵の移動処理
void e_fin(void);		// 敵の終了処理
void e_center(void);	// 敵の中央表示

// 判定処理(mogu_judg.c)
void j_init(void);		// 判定処理の初期化
int  j_event(void);		// マウスイベント処理
int  j_timer(void);		// 経過時間の設定
int  j_mouse(void);		// マウスイベント処理
int	 j_mouse2(void);	// マウスイベント処理（複数匹対応）

// 文字処理(mogu_text.c)
void t_init(void);		// 文字の初期化処理
void t_score(void);		// スコアの表示処理
void t_startmsg(void);	// スタートメッセージの表示
void t_endmsg(void);	// エンドメッセージの表示
void t_fin(void);		// 文字の終了処理

// 音処理(mogu_music.c)
void s_init(void);		// 音の初期化処理
void s_se(int num);		// 音の再生処理（1:叩く音、2:泣き声）
void s_bgm_on(void);	// BGMの再生処理
void s_bgm_off(void);	// BGMの停止処理
void s_fin(void);		// 音の終了処理