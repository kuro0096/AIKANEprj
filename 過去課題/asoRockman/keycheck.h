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

// ¸ŞÛ°ÊŞÙ•Ï”
extern bool newKey[KEY_MAX]; // new·°(¡‰ñÌÚ°Ñ‚Ì·°“ü—Íó‹µ)
extern bool trgKey[KEY_MAX]; // trg·°
extern bool upKey[KEY_MAX];  // up·°
extern bool oldKey[KEY_MAX]; // old·°

// ---------- ÌßÛÄÀ²ÌßéŒ¾ 

// keycheck.cpp 
void KeyCheckInit(void); 
void KeyCheck(void); // ·°“ü—Íó‘Ô‚ÌÁª¯¸