// #pragma once

#define SHOT_MAX 2

// �v���g�^�C�v�錾
void ShotSysInit(void);
void ShotGameInit(void);
void ShotCtr(void);
void ShotDraw(void);
void Shoot(XY pPos,MOVE_DIR pDir , TYPE pType);
bool ShotFlag(void);
CHARACTER GetShot(int index);
void ShotDelete(int index);




