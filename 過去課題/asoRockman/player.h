// #pragma once

#define PLAYER_MAX 2

// �v���g�^�C�v�錾
void PlayerSysInit(void);
void PlayerGameInit(void);
void PlayerCtr(void);
void PlayerDraw(void);
bool PlayerhitCheck(XY sPos, XY sSize , TYPE sType);
TYPE GameEnd(void);
CHARACTER GetPlayer1(void);