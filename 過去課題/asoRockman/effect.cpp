#include <math.h>
#include "main.h"
#include "player.h"
#include "shot.h"
#include "effect.h"

// ��`
int shot1EffImg[6];
int shot2EffImg[6];

int p1TobichirImg[6];	// p1�G�t�F�N�g
int p2TobichirImg[6];	// p2�G�t�F�N�g

// �G�t�F�N�g������
TOBICHIRI Effect[EFFECT_MAX];
TOBICHIRI Dead[TOBICHIRI_MAX]; // ��юU��p�[�c������ 
float tobichiriAcc; // �p�[�c�̉����x 
bool tobichiriEffFlag;
float angle;  // �v�Z�p 

// �G�t�F�N�g�Ɣ�юU��̏�����
void EffectSysInit(void)
{
	LoadDivGraph("image/effect_yellow.png", 6, 6, 1, 16, 16, shot1EffImg);
	LoadDivGraph("image/effect_magenta.png", 6, 6, 1, 16, 16, shot2EffImg);
	LoadDivGraph("image/tobichiri.png", 6, 6, 1, 16, 16, p1TobichirImg);
	LoadDivGraph("image/effect_red.png", 6, 6, 1, 16, 16, p2TobichirImg);
}

// ========== �G�t�F�N�g ========== 
// �G�t�F�N�g������
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

// �G�t�F�N�g�l�X�V
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

// �G�t�F�N�g����
void EffectCtr(void)
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (Effect[i].visible)
		{
			// �S�p�[�c�ړ�����
			Effect[i].pos.x += Effect[i].mov.x;
			Effect[i].pos.y += Effect[i].mov.y;
			// �G�t�F�N�g��life�����炷
			Effect[i].life--;

			// �G�t�F�N�g��life��0��菬�����Ȃ�����
			if (Effect[i].life <= 0)
			{
				// �G�t�F�N�g������
				Effect[i].visible = false;
			}
		}
	}
}

// �G�t�F�N�g�`��
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

// ========== ��юU�� ========== 

// ��юU�菉����
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

// ��юU��l�X�V
void SetTobichiri(XY pos, TYPE ptype)
{
	angle = 0.0f; // �p�x��0�x�ɐݒ� 
	tobichiriAcc = 0; // �p�[�c�̉����x�������� 

	for (int i = 0; i < TOBICHIRI_MAX; i++)
	{
		Dead[i].charaType = ptype;
		Dead[i].no = GetRand(5); // �召�̉摜������тɐݒ�(0�`5) 
		Dead[i].angle = angle; // �p�x�����߂�(0 �x���� 3�x�����炷)
		Dead[i].speed = GetRand(16) + 1;  // 1�`16 ���炢�Őݒ� 
		Dead[i].pos.x = pos.x; // ��ڲ԰�̍��WX 
		Dead[i].pos.y = pos.y; // ��ڲ԰�̍��WY 
		// �p�x�����Ɉړ��ʂ�ݒ�(angle ���g��) 
		Dead[i].mov.x = cos((PI / 180)*angle) * Dead[i].speed;
		Dead[i].mov.y = sin((PI / 180)*angle) * Dead[i].speed;
		angle += 3.0f;  // 3�x����](����Dead[i].angle �Ɏg�p����)  
		Dead[i].visible = true;   // ��юU�蒆�ɐݒ� 
	}
	tobichiriEffFlag = true;
}

// ��юU�蓮��
void TobichiriCtr(void)
{
	// �S�p�[�c�ړ�����(�����t��) 
	for (int i = 0; i < TOBICHIRI_MAX; i++)
	{
		Dead[i].pos.x += Dead[i].mov.x;
		Dead[i].pos.y += Dead[i].mov.y;
		// �ړ��ʂ͏��������������Ă���  
		Dead[i].speed -= 0.1f;
		// �������ā��ɏd�͂��������̂ňړ��ʂ��Čv�Z���� 
		Dead[i].mov.x = cos((PI / 180)*Dead[i].angle) * Dead[i].speed;
		Dead[i].mov.y = sin((PI / 180)*Dead[i].angle) * Dead[i].speed + tobichiriAcc;
	}
	// �������������ɏd�͂������Ă����ׂ̏��� 
	tobichiriAcc += 0.3f;
	int cnt = 0;
	// �S�����������`�F�b�N 
	for (int i = 0; i < TOBICHIRI_MAX; i++)
	{
		if (Dead[i].pos.y > SCREEN_SIZE_Y)
		{
			cnt++;
		}
	}
	// ��юU��I��  
	if (cnt >= TOBICHIRI_MAX)
	{	
		tobichiriEffFlag = false;

		for (int i = 0; i < TOBICHIRI_MAX; i++)
		{
			Dead[i].visible = false;
		}
	}
}

// ��юU�蓮��
void TobichiriDraw(void)
{
	// �S�p�[�c�`�揈��(��Ұ��݂ɂ���߰̻��ޕύX) 
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


