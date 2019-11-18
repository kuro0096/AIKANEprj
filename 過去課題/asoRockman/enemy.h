// #pragma once
#define ENEMY_MAX 5

// プロトタイプ宣言
void EnemySysInit(void);
void EnemyGameInit(void);
void EnemyCtr(void);
void EnemyDraw(void);
bool EnemyhitCheck(XY sPos, XY sSize, TYPE sType);
