#include "main.h"
#include "keycheck.h"
#include "stage.h"
#include "player.h"
#include "shot.h"
#include "effect.h"

// 変数初期化
typedef enum {
	GMODE_INIT,
	GMODE_TITLE,
	GMODE_MAIN,
	GMODE_OVER
}GMODE;

GMODE  gameMode;

typedef enum {
	BMODE_BATTLE,
	BMODE_COOPERATION
}BMODE;

BMODE battleMode;

int gameCnt;
bool stopFlag;
int fadeCnt;
bool fadeIn;
bool fadeOut;

int titleImg;
int gameOverImg;
int startImg;
int p1WinImg;
int p2WinImg;

TYPE winerType; // 勝ち判定

// プロトタイプ宣言
bool SysInit(void);
void GameInit(void);
void GameTitle(void);
void GameTitleDraw(void);
void GameMain(void);
void GameMainDraw(void);
void GameOver(void);
void GameOverDraw(void);
void HitCheck(void);
bool FadeInScreen(int fadestep);
bool FadeOutScreen(int fadestep);


// ========== WinMain関数
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	if (SysInit() == false)
	{
		DxLib_End();
		return 0;
	}

	// ｹﾞｰﾑﾙｰﾌﾟ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();	// 画面消去

		KeyCheck();

		switch (gameMode)
		{
		case GMODE_INIT:
			GameInit();
			gameMode = GMODE_TITLE;
			break;
		case GMODE_TITLE:
			if (fadeIn)
			{
				if (!FadeInScreen(5)) fadeIn = false;
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					gameMode = GMODE_MAIN;
					fadeOut = false;
					fadeIn = true;
				}
			}
			else
			{
				if (trgKey[START]) fadeOut = true;
			}
			GameTitle();
			break;
		case GMODE_MAIN:
			if (fadeIn)
			{
				if (!FadeInScreen(5)) fadeIn = false;
			}

			if (winerType == PLAYER1)
			{
				fadeOut = true;
				if (fadeOut)
				{
					if (!FadeOutScreen(5))
					{
						gameMode = GMODE_OVER;
						fadeOut = false;
						fadeIn = true;
					}
				}
			}
			if (winerType == PLAYER2)
			{
				fadeOut = true;
				if (fadeOut)
				{
					if (!FadeOutScreen(5))
					{
						gameMode = GMODE_OVER;
						fadeOut = false;
						fadeIn = true;
					}
				}
			}
			GameMain();
			break;
		case GMODE_OVER:
			if (fadeIn)
			{
				if (!FadeInScreen(5))fadeIn = false;
			}
			if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					gameMode = GMODE_TITLE;
					GameInit();
					fadeOut = false;
					fadeIn = true;
				}
			}
			else
			{
				if (trgKey[START]) fadeOut = true;
			}
			GameOver();
			break;
		default: 
			gameMode = GMODE_INIT;
			break;
		}

		ScreenFlip();
	}

	DxLib_End();
	return 0;
}

// ---------------------------------------------------------------------
// ｼｽﾃﾑ処理
bool SysInit(void)
{
	SetWindowText("asorockman");

	// ｼｽﾃﾑ処理
	SetGraphMode(SCREEN_SIZE_X,SCREEN_SIZE_Y,16);
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)
	{
		return false;
	}

	SetDrawScreen(DX_SCREEN_BACK);  // ﾊﾞｯｸに描画

	// 画像読み込み
	titleImg = LoadGraph("image/title.png");
	gameOverImg = LoadGraph("image/gameover.png");
	startImg = LoadGraph("image/hitstartkey.png");
	p1WinImg = LoadGraph("image/p1win.png");
	p2WinImg = LoadGraph("image/p2win.png");

	KeyCheckInit();
	StageSysInit();
	PlayerSysInit();
	ShotSysInit();
	EffectSysInit();

	gameMode = GMODE_INIT;
	battleMode = BMODE_BATTLE;
	return true;
}

// 初期化関数
void GameInit(void)
{
	stopFlag = false;
	fadeCnt = 0;
	fadeIn = false;
	fadeOut = false;
	winerType = PROTO;
	StageGameInit();
	PlayerGameInit();
	ShotGameInit();
	EffectInit();
	TobichiriInit();
}

// ﾀｲﾄﾙ
void GameTitle(void)
{
	GameTitleDraw();
}

// ﾀｲﾄﾙ描画
void GameTitleDraw(void)
{
	DrawGraph(0, 0,titleImg,true);
	DrawGraph(225, SCREEN_SIZE_Y  - 100, startImg, true);
	DrawFormatString(0, 0, GetColor(255, 255, 0), "GameTitle");
}

// ｹﾞｰﾑﾒｲﾝ関数
void GameMain(void)
{
	// PAUSEのON/OFF
	/*
	if (trgKey[STOP] == true) {
		stopFlag++;
		stopFlag = stopFlag % 2;
	}
	*/

	// Pが押されたらPAUSE
	if (trgKey[STOP])
	{
		stopFlag = !stopFlag; 
	}

	if (!stopFlag)
	{
		gameCnt++;	
		PlayerCtr();
		ShotCtr();
		HitCheck();
		EffectCtr();
		bool tobichiriFlag = TobichiriFlag();
		if (TobichiriFlag) { TobichiriCtr(); }
		if (battleMode == BMODE_BATTLE) { winerType = GameEnd(); }
	}
	GameMainDraw();
}

// ｹﾞｰﾑﾒｲﾝ描画関数
void GameMainDraw(void)
{
	StageDraw();
	ShotDraw();
	PlayerDraw();
	EffectDraw();
	TobichiriDraw();

	if (stopFlag)
	{
		DrawFormatString(SCREEN_SIZE_X / 2 - 72, SCREEN_SIZE_Y / 2, GetColor(255, 0, 0), " P  A  U  S  E");
	}
	// DrawFormatString(0, 0, GetColor(255, 0, 0), "GameMain : (%d)",gameCnt);
}

// ｹﾞｰﾑｵｰﾊﾞｰ関数
void GameOver(void)
{
	GameOverDraw();
}

// ｹﾞｰﾑｵｰﾊﾞｰ描画関数
void GameOverDraw(void)
{
	// player1が勝ったら
	if (winerType == PLAYER1)
	{
		DrawGraph(150, 150, p1WinImg, true);
		DrawFormatString(0, 0, GetColor(255, 255, 0), "GameOver : PLAYER1WIN");
	}
	// player2が勝ったら
	else if (winerType == PLAYER2)
	{
		DrawGraph(150, 150, p2WinImg, true);
		DrawFormatString(0, 0, GetColor(255, 255, 0), "GameOver : PLAYER2WIN");
	}
}

// ﾋｯﾄﾁｪｯｸ関数
void HitCheck(void)
{
	for (int i = 0; i < SHOT_MAX; i++)
	{
		CHARACTER shotTemp = GetShot(i);
		if (shotTemp.visible)
		{
			bool ret;
			ret = PlayerhitCheck(shotTemp.pos, shotTemp.size,shotTemp.charaType);
			if (ret)
			{
				ShotDelete(i);
			}
		}
	}
}

// ﾌｪｰﾄﾞｲﾝ
bool FadeInScreen(int fadestep)
{
	fadeCnt += fadestep;
	if (fadeCnt <= 255)
	{
		SetDrawBright(fadeCnt,fadeCnt,fadeCnt);
		return true;
	}

	else
	{
		SetDrawBright(255, 255, 255);
		fadeCnt = 0;
		return false;
	}
}

// ﾌｪｰﾄﾞｱｳﾄ
bool FadeOutScreen(int fadestep)
{
	fadeCnt += fadestep;
	if (fadeCnt <= 255)
	{
		SetDrawBright(255 - fadeCnt, 255 - fadeCnt, 255 - fadeCnt);
	    return true;
	}

	else
	{
		SetDrawBright(0, 0, 0);
		fadeCnt = 0;
		return false;
	}
}