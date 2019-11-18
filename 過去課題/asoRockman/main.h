// #pragma once
#include "DxLib.h"

// 定数
#define SCREEN_SIZE_X 768
#define SCREEN_SIZE_Y 480

#define PI 3.141592
#define ACC_G 10	//	重力加速度
#define ACC_RUN 0.15	// 走る加速度
#define ACC_STOP 0.15	// 停止加速度
#define X_MAX 7			// X方向の移動の最大値

// 定義
typedef struct {
	float x;
	float y;
} XY_F;

typedef struct {
	int x;
	int y;
} XY;

enum MOVE_DIR {
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LEFT,
	DIR_MAX
};

enum TYPE {
	PROTO,
	PLAYER1,
	PLAYER2
};

typedef struct {
	MOVE_DIR dir;		// 向いている方向
	XY pos;				// キャラクタの位置
	XY size;			// キャラクタ画像のサイズ
	XY sizeOffset;		// キャラクタ中央からの左上位置
	XY hitPosS;			// 当たり判定用の左上
	XY hitPosE;			// 当たり判定用の右下
	bool runFlag;		// キャラクタの状態(走っているか？)
	bool jumpFlag;		// キャラクタの状態(ジャンプしているか？)
	bool shotFlag;		// キャラクタの状態(弾撃っているか？)
	bool damageFlag;	// キャラクタの状態(ダメージ受けているか？)
	int moveSpeed;		// キャラクタの移動量
	int life;			// キャラクタの体力
	int lifeMax;		// キャラクタの体力最大
	int animCnt;		// キャラクタのアニメーション用カウンタ
	int imgLockCnt;     // キャラクタのイメージ固定用カウンタ
	XY_F velocity;		// 移動速度
	bool visible;
	TYPE charaType;		// キャラクタータイプ
	int invincible;
}CHARACTER;

extern XY scrPos;

// プロトタイプ宣言