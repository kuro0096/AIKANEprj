// #pragma once

// �萔
#define MAP_CHIP_X 48
#define MAP_CHIP_Y 15

#define MAP_CHIP_SIZE_X 32
#define MAP_CHIP_SIZE_Y 32

// �v���g�^�C�v�錾
void StageSysInit(void);
void StageGameInit(void);
void StageDraw(void);
XY MapPosToIndex(XY);
XY MapIndexToPos(XY index);
bool IsPass(XY);
