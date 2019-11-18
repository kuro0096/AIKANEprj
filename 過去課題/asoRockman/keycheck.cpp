#include "keycheck.h"
#include "main.h"

bool newKey[KEY_MAX];	// 新しい
bool trgKey[KEY_MAX];	// ﾄﾘｶﾞｰ
bool upKey[KEY_MAX];	// 離されたか
bool oldKey[KEY_MAX];	// 古い

void KeyCheckInit(void)
{
	// 準備
	for (int i = 0; i < KEY_MAX; i++){
		newKey[i] = false;
		trgKey[i] = false;
		upKey[i] = false;
		oldKey[i] = false;
	}
}

// ｷｰﾁｪｯｸ関数
void KeyCheck(void)
{
	// 準備
	for (int i = 0; i < KEY_MAX; i++) {
		newKey[i] = false;		// 全部押していないことにする
		trgKey[i] = false;		// 全部押していないことにする
		upKey[i] = false;		// 全部押していないことにする
	}
	// newｷｰ確認(今回押したかどうか)
	if (CheckHitKey(KEY_INPUT_W)) newKey[P1_UP] = true;	// 上
	if (CheckHitKey(KEY_INPUT_D)) newKey[P1_RIGHT] = true; // 右
	if (CheckHitKey(KEY_INPUT_S)) newKey[P1_DOWN] = true;  // 下
	if (CheckHitKey(KEY_INPUT_A)) newKey[P1_LEFT] = true;  // 左
	if (CheckHitKey(KEY_INPUT_RETURN)) newKey[P1_SHOT] = true; // 通常ｼｮｯﾄ
	if (CheckHitKey(KEY_INPUT_V)) newKey[P1_A] = true; // ﾚｰｻﾞｰ用
	if (CheckHitKey(KEY_INPUT_B)) newKey[P1_B] = true; // 3way用


	if (CheckHitKey(KEY_INPUT_UP)) newKey[P2_UP] = true;
	if (CheckHitKey(KEY_INPUT_RIGHT)) newKey[P2_RIGHT] = true;
	if (CheckHitKey(KEY_INPUT_DOWN)) newKey[P2_DOWN] = true;
	if (CheckHitKey(KEY_INPUT_LEFT)) newKey[P2_LEFT] = true;
	if (CheckHitKey(KEY_INPUT_BACK)) newKey[P2_SHOT] = true;

	// ｽﾀｰﾄ
	if (CheckHitKey(KEY_INPUT_SPACE)) newKey[START] = true; // ｽﾀｰﾄ用
	// 一時停止
	if (CheckHitKey(KEY_INPUT_P)) newKey[STOP] = true;

	// -----trgKey & upKey & oldKey
	for (int i = 0; i < KEY_MAX; i++) {
		trgKey[i] = newKey[i] & ~oldKey[i]; // trgKey
		upKey[i] = ~newKey[i] & oldKey[i];	// upKey
		oldKey[i] = newKey[i];  // oldkey
	}
}