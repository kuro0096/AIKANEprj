// #pragma once
#define ENEMY_MAX 5

// �v���g�^�C�v�錾
void EnemySysInit(void);
void EnemyGameInit(void);
void EnemyCtr(void);
void EnemyDraw(void);
bool EnemyhitCheck(XY sPos, XY sSize, TYPE sType);
