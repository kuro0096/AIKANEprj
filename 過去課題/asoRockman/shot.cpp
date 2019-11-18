#include "DxLib.h"
#include <math.h>
#include "main.h"
#include "shot.h"
#include "player.h"
#include "Stage.h"
#include "keycheck.h"
#include "effect.h"

// 定数
#define SHOT_LIFE_MAX 150
#define SHOT_SIZE_X 16
#define SHOT_SIZE_Y 16

// 変数
CHARACTER shot[SHOT_MAX];
int sGageImg;
int shotImg;
int shotImg2;

// プロトタイプ宣言

// 画像読み込み
void ShotSysInit()
{
	sGageImg = LoadGraph("image/sgage.png");
	shotImg = LoadGraph("image/shot1.png");
	shotImg2 = LoadGraph("image/shot2.png");
}

// 初期化
void ShotGameInit()
{
	for (int i = 0; i < SHOT_MAX; i++)
	{
		shot[i].pos = { 0,0 };
		shot[i].dir = DIR_DOWN;
		shot[i].visible = false;
		shot[i].size = { SHOT_SIZE_X, SHOT_SIZE_Y };
		shot[i].sizeOffset = { shot[i].size.x / 2,shot[i].size.y / 2 };
		shot[i].lifeMax = SHOT_LIFE_MAX;
		shot[i].life = 0;
		shot[i].moveSpeed = 10;
	}
}

// ｼｮｯﾄが発射出来るならもう１度初期化
void Shoot(XY pPos, MOVE_DIR pDir , TYPE pType)
{
	if ((!shot[0].visible)&&(pType == PLAYER1))
	{
		shot[0].pos.x = pPos.x;
		shot[0].pos.y = pPos.y;
		shot[0].dir = pDir;
		shot[0].visible = true;
		shot[0].life = shot[0].lifeMax;
		shot[0].charaType = pType;
	}
	if ((!shot[1].visible) && (pType == PLAYER2))
	{
		shot[1].pos.x = pPos.x;
		shot[1].pos.y = pPos.y;
		shot[1].dir = pDir;
		shot[1].visible = true;
		shot[1].life = shot[1].lifeMax;
		shot[1].charaType = pType;
	}
}

// ｼｮｯﾄ動作
void ShotCtr()
{
	for (int i = 0; i < SHOT_MAX; i++)
	{
		if (shot[i].visible)
		{
			shot[i].life -= 3;
			switch (shot[i].dir)
			{
			case DIR_RIGHT:
				shot[i].pos.x += shot[i].moveSpeed;
				break;
			case DIR_LEFT:
				shot[i].pos.x -= shot[i].moveSpeed;
				break;
			}

			if ((!IsPass(shot[i].pos))||(shot[i].life == 0))
			{
				shot[i].visible = false;
				SetBlockEffect(shot[i].pos, shot[i].charaType);
				shot[i].life = 0;
			}
		}
	}
}

// ｼｮｯﾄ描画
void ShotDraw()
{
	DrawRotaGraph(65, 92, 0.5, 0,sGageImg, true, false);
	DrawRotaGraph(700, 92, 0.5, 0, sGageImg, true, false);
	for (int i = 0; i < SHOT_MAX; i++)
	{
		if ((shot[i].visible)&&(shot[i].charaType == PLAYER1))
		{
			DrawGraph(shot[i].pos.x - scrPos.x, shot[i].pos.y, shotImg, true);
		}
		if ((shot[i].visible) && (shot[i].charaType == PLAYER2))
		{
			DrawGraph(shot[i].pos.x - scrPos.x, shot[i].pos.y, shotImg2, true);
		}
	}
	DrawBox(44, 100, 194, 120, GetColor(0, 0, 0), true);
	DrawBox(44, 100, 194 - abs(shot[0].life), 120, GetColor(0, 0, 255), true);
	DrawBox(44, 100, 194, 120, GetColor(255, 0, 0), false);

	DrawBox(SCREEN_SIZE_X - 200, 100, SCREEN_SIZE_X - 50, 120, GetColor(0, 0, 0), true);
	DrawBox(SCREEN_SIZE_X - 200, 100, SCREEN_SIZE_X - 50 - abs(shot[1].life), 120, GetColor(255, 255, 0), true);
	DrawBox(SCREEN_SIZE_X - 200, 100, SCREEN_SIZE_X - 50, 120, GetColor(255, 0, 0), false);
}

// ｼｮｯﾄが発射されているか
bool ShotFlag()
{
	for (int i = 0; i < SHOT_MAX; i++)
	{
		return shot[i].visible;
	}
}

// ｼｮｯﾄデータ
CHARACTER GetShot(int index)
{
	return shot[index];
}

// ｼｮｯﾄ消去
void ShotDelete(int index)
{
	shot[index].visible = false;
	shot[index].life = 0;
}