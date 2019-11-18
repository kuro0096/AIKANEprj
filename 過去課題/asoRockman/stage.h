// #pragma once

// 定数
#define MAP_CHIP_X 48
#define MAP_CHIP_Y 15

#define MAP_CHIP_SIZE_X 32
#define MAP_CHIP_SIZE_Y 32

// プロトタイプ宣言
void StageSysInit(void);
void StageGameInit(void);
void StageDraw(void);
XY MapPosToIndex(XY);
XY MapIndexToPos(XY index);
bool IsPass(XY);
