//#pragma once

enum KEY_MODE {
	P1_UP,
	P1_RIGHT,
	P1_DOWN,
	P1_LEFT,
	P1_SHOT,
	P1_A,
	P1_B,
	P1_C,

	P2_UP,
	P2_RIGHT,
	P2_DOWN,
	P2_LEFT,
	P2_SHOT,
	P2_A,
	P2_B,

	START,
	STOP,

	KEY_MAX
};

// ｸﾞﾛｰﾊﾞﾙ変数
extern bool newKey[KEY_MAX]; // newｷｰ(今回ﾌﾚｰﾑのｷｰ入力状況)
extern bool trgKey[KEY_MAX]; // trgｷｰ
extern bool upKey[KEY_MAX];  // upｷｰ
extern bool oldKey[KEY_MAX]; // oldｷｰ

// ---------- ﾌﾟﾛﾄﾀｲﾌﾟ宣言 

// keycheck.cpp 
void KeyCheckInit(void); 
void KeyCheck(void); // ｷｰ入力状態のﾁｪｯｸ