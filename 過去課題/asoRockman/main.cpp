#include "main.h"
#include "keycheck.h"
#include "stage.h"
#include "player.h"
#include "shot.h"
#include "effect.h"

// �ϐ�������
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

TYPE winerType; // ��������

// �v���g�^�C�v�錾
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


// ========== WinMain�֐�
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	if (SysInit() == false)
	{
		DxLib_End();
		return 0;
	}

	// �ް�ٰ��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();	// ��ʏ���

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
// ���я���
bool SysInit(void)
{
	SetWindowText("asorockman");

	// ���я���
	SetGraphMode(SCREEN_SIZE_X,SCREEN_SIZE_Y,16);
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)
	{
		return false;
	}

	SetDrawScreen(DX_SCREEN_BACK);  // �ޯ��ɕ`��

	// �摜�ǂݍ���
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

// �������֐�
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

// ����
void GameTitle(void)
{
	GameTitleDraw();
}

// ���ٕ`��
void GameTitleDraw(void)
{
	DrawGraph(0, 0,titleImg,true);
	DrawGraph(225, SCREEN_SIZE_Y  - 100, startImg, true);
	DrawFormatString(0, 0, GetColor(255, 255, 0), "GameTitle");
}

// �ް�Ҳ݊֐�
void GameMain(void)
{
	// PAUSE��ON/OFF
	/*
	if (trgKey[STOP] == true) {
		stopFlag++;
		stopFlag = stopFlag % 2;
	}
	*/

	// P�������ꂽ��PAUSE
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

// �ް�Ҳݕ`��֐�
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

// �ްѵ��ް�֐�
void GameOver(void)
{
	GameOverDraw();
}

// �ްѵ��ް�`��֐�
void GameOverDraw(void)
{
	// player1����������
	if (winerType == PLAYER1)
	{
		DrawGraph(150, 150, p1WinImg, true);
		DrawFormatString(0, 0, GetColor(255, 255, 0), "GameOver : PLAYER1WIN");
	}
	// player2����������
	else if (winerType == PLAYER2)
	{
		DrawGraph(150, 150, p2WinImg, true);
		DrawFormatString(0, 0, GetColor(255, 255, 0), "GameOver : PLAYER2WIN");
	}
}

// ˯������֐�
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

// ̪��޲�
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

// ̪��ޱ��
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