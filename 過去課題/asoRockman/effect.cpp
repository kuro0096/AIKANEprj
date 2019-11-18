#include <math.h>
#include "main.h"
#include "player.h"
#include "shot.h"
#include "effect.h"

// 定義
int shot1EffImg[6];
int shot2EffImg[6];

int p1TobichirImg[6];	// p1エフェクト
int p2TobichirImg[6];	// p2エフェクト

// エフェクト初期化
TOBICHIRI Effect[EFFECT_MAX];
TOBICHIRI Dead[TOBICHIRI_MAX]; // 飛び散りパーツを準備 
float tobichiriAcc; // パーツの加速度 
bool tobichiriEffFlag;
float angle;  // 計算用 

// エフェクトと飛び散りの初期化
void EffectSysInit(void)
{
	LoadDivGraph("image/effect_yellow.png", 6, 6, 1, 16, 16, shot1EffImg);
	LoadDivGraph("image/effect_magenta.png", 6, 6, 1, 16, 16, shot2EffImg);
	LoadDivGraph("image/tobichiri.png", 6, 6, 1, 16, 16, p1TobichirImg);
	LoadDivGraph("image/effect_red.png", 6, 6, 1, 16, 16, p2TobichirImg);
}

// ========== エフェクト ========== 
// エフェクト初期化
void EffectInit(void)
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		Effect[i].no = 1;
		Effect[i].speed = 8;
		Effect[i].pos.x = 0;
		Effect[i].pos.y = 0;
		Effect[i].mov.x = 0;
		Effect[i].mov.y = 0;
		Effect[i].size = { 16,16 };
		Effect[i].sizeOffset = { Effect[i].size.x / 2 , Effect[i].size.y / 2 };
		Effect[i].lifeMax = 10;
		Effect[i].life = Effect[i].lifeMax;
		Effect[i].charaType = PROTO;
		Effect[i].visible = false;
	}
}

// エフェクト値更新
void SetBlockEffect(XY pos, TYPE color) 
{
	int effCnt = 0;
	int angleE = 0;

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (!Effect[i].visible)
		{
			effCnt++;

			Effect[i].no = GetRand(EFFECT_IMAGE_MAX - 1);
			Effect[i].speed = GetRand(8) + 1;
			Effect[i].pos.x = pos.x;
			Effect[i].pos.y = pos.y;
			Effect[i].mov.x = cos((PI / 180)*angleE) * (int)Effect[i].speed;
			Effect[i].mov.y = sin((PI / 180)*angleE) * (int)Effect[i].speed;
			Effect[i].life = Effect[i].lifeMax;
			Effect[i].charaType = color;
			angleE += 30.0f;
			Effect[i].visible = true;
			if (effCnt > 12) { break; }
		}
	}
}

// エフェクト動作
void EffectCtr(void)
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (Effect[i].visible)
		{
			// 全パーツ移動処理
			Effect[i].pos.x += Effect[i].mov.x;
			Effect[i].pos.y += Effect[i].mov.y;
			// エフェクトのlifeを減らす
			Effect[i].life--;

			// エフェクトのlifeが0より小さくなったら
			if (Effect[i].life <= 0)
			{
				// エフェクトを消す
				Effect[i].visible = false;
			}
		}
	}
}

// エフェクト描画
void EffectDraw(void)
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{ 
		if(Effect[i].visible)
		{
			if (Effect[i].charaType == PLAYER1)
			{
				DrawGraph(Effect[i].pos.x - Effect[i].sizeOffset.x - scrPos.x, Effect[i].pos.y - Effect[i].sizeOffset.y, shot1EffImg[Effect[i].no % 6], true);
				Effect[i].no++;
			}
			if (Effect[i].charaType == PLAYER2)
			{
				DrawGraph(Effect[i].pos.x - Effect[i].sizeOffset.x - scrPos.x, Effect[i].pos.y - Effect[i].sizeOffset.y, shot2EffImg[Effect[i].no % 6], true);
				Effect[i].no++;
			}
		}
	}
}

// ========== 飛び散り ========== 

// 飛び散り初期化
void TobichiriInit(void)
{
	for (int i = 0; i < TOBICHIRI_MAX; i++)
	{
		Dead[i].charaType = PROTO;
		Dead[i].no = 0;
		Dead[i].angle = 0;
		Dead[i].speed = 0;
		Dead[i].pos.x = 0;
		Dead[i].pos.y = 0;
 		Dead[i].mov.x = 0;
		Dead[i].mov.y = 0;
		Dead[i].visible = false;
		angle = 0;
	}
	tobichiriEffFlag = false;
}

// 飛び散り値更新
void SetTobichiri(XY pos, TYPE ptype)
{
	angle = 0.0f; // 角度を0度に設定 
	tobichiriAcc = 0; // パーツの加速度を初期化 

	for (int i = 0; i < TOBICHIRI_MAX; i++)
	{
		Dead[i].charaType = ptype;
		Dead[i].no = GetRand(5); // 大小の画像をﾗﾝﾀﾞﾑに設定(0～5) 
		Dead[i].angle = angle; // 角度を決める(0 度から 3度ずつずらす)
		Dead[i].speed = GetRand(16) + 1;  // 1～16 ぐらいで設定 
		Dead[i].pos.x = pos.x; // ﾌﾟﾚｲﾔｰの座標X 
		Dead[i].pos.y = pos.y; // ﾌﾟﾚｲﾔｰの座標Y 
		// 角度を元に移動量を設定(angle を使う) 
		Dead[i].mov.x = cos((PI / 180)*angle) * Dead[i].speed;
		Dead[i].mov.y = sin((PI / 180)*angle) * Dead[i].speed;
		angle += 3.0f;  // 3度ずつ回転(次のDead[i].angle に使用する)  
		Dead[i].visible = true;   // 飛び散り中に設定 
	}
	tobichiriEffFlag = true;
}

// 飛び散り動作
void TobichiriCtr(void)
{
	// 全パーツ移動処理(加速付き) 
	for (int i = 0; i < TOBICHIRI_MAX; i++)
	{
		Dead[i].pos.x += Dead[i].mov.x;
		Dead[i].pos.y += Dead[i].mov.y;
		// 移動量は少しずつ減速させていく  
		Dead[i].speed -= 0.1f;
		// 減速して↓に重力をかけたので移動量を再計算する 
		Dead[i].mov.x = cos((PI / 180)*Dead[i].angle) * Dead[i].speed;
		Dead[i].mov.y = sin((PI / 180)*Dead[i].angle) * Dead[i].speed + tobichiriAcc;
	}
	// 少しずつ↓方向に重力をかけていく為の処理 
	tobichiriAcc += 0.3f;
	int cnt = 0;
	// 全部消えたかチェック 
	for (int i = 0; i < TOBICHIRI_MAX; i++)
	{
		if (Dead[i].pos.y > SCREEN_SIZE_Y)
		{
			cnt++;
		}
	}
	// 飛び散り終了  
	if (cnt >= TOBICHIRI_MAX)
	{	
		tobichiriEffFlag = false;

		for (int i = 0; i < TOBICHIRI_MAX; i++)
		{
			Dead[i].visible = false;
		}
	}
}

// 飛び散り動作
void TobichiriDraw(void)
{
	// 全パーツ描画処理(ｱﾆﾒｰｼｮﾝによるﾊﾟｰﾂのｻｲｽﾞ変更) 
	for (int i = 0; i < TOBICHIRI_MAX; i++)
	{
		if (tobichiriEffFlag)
		{
			if (Dead[i].charaType == PLAYER1)
			{
				DrawGraph(Dead[i].pos.x - 8 - scrPos.x, Dead[i].pos.y - 8, p1TobichirImg[Dead[i].no % 6], true);
				Dead[i].no++;
			}
			if (Dead[i].charaType == PLAYER2)
			{
				DrawGraph(Dead[i].pos.x - 8 - scrPos.x, Dead[i].pos.y - 8, p2TobichirImg[Dead[i].no % 6], true);
				Dead[i].no++;
			}
		}
	}
}

bool TobichiriFlag(void)
{
	return tobichiriEffFlag;
}


