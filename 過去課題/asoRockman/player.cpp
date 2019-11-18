#include <math.h>
#include "main.h"
#include "keycheck.h"
#include "player.h"
#include "stage.h"
#include "shot.h"
#include "effect.h"
#include "enemy.h"

// �萔
#define PLAYER_SIZE_X 96
#define PLAYER_SIZE_Y 64

#define PI 3.141592

#define G 9.8 // �d�͉����x

#define INIT_VELOCITY 50 // �����x
#define SECOND_PER_FRAME 0.3

#define Y_MAX 100

// ��`

// �ϐ�
CHARACTER player1;
CHARACTER player2;

int p1StopImg[2];		// p1��~��Ԃ̉摜
int p1runImg[2][4];		// p1�����Ԃ̉摜
int p1jumpImg[2];		// p1�W�����v���̉摜
int p1DamageImg;		// p1�_���[�W�摜

int p2StopImg[2];		// p2��~��Ԃ̉摜
int p2runImg[2][4];		// p2�����Ԃ̉摜
int p2jumpImg[2];		// p2�W�����v���̉摜
int p2DamageImg;		// p2�_���[�W�摜

int hpImg;
int lifeImg; // ���C�t�摜

XY scrPos;

// �v���g�^�C�v�錾

// �v���C���[�摜�ǂݍ���
void PlayerSysInit()
{
	// player1�摜�ǂݍ���
	p1StopImg[0] = LoadGraph("image/stop.png");		
	p1StopImg[1] = LoadGraph("image/stop_shot.png");
	LoadDivGraph("image/run.png",4,4,1,96,64, p1runImg[0]);
	LoadDivGraph("image/run_shot.png", 4, 4, 1, 96, 64, p1runImg[1]);
	p1jumpImg[0] = LoadGraph("image/jump.png");
	p1jumpImg[1] = LoadGraph("image/jump_shot.png");
	p1DamageImg = LoadGraph("image/damage.png");

	// player2�摜�ǂݍ���
	p2StopImg[0] = LoadGraph("image/stop2.png");
	p2StopImg[1] = LoadGraph("image/stop_shot2.png");
	LoadDivGraph("image/run2.png", 4, 4, 1, 96, 64, p2runImg[0]);
	LoadDivGraph("image/run_shot2.png", 4, 4, 1, 96, 64, p2runImg[1]);
	p2jumpImg[0] = LoadGraph("image/jump2.png");
	p2jumpImg[1] = LoadGraph("image/jump_shot2.png");
	p2DamageImg = LoadGraph("image/damage2.png");

	// ���C�t�摜
	hpImg = LoadGraph("image/hp.png");
	lifeImg = LoadGraph("image/life.png");
}

// �v���C���[������
void PlayerGameInit()
{	
	player1.visible = true;
	player1.lifeMax = 5;
	player1.life = player1.lifeMax;
	player1.dir = DIR_RIGHT;
	player1.pos = { MAP_CHIP_SIZE_X * 2, SCREEN_SIZE_Y - 96 };
	player1.size = { PLAYER_SIZE_X, PLAYER_SIZE_Y };
	player1.sizeOffset = { player1.size.x / 2, player1.size.y / 2 };
	player1.moveSpeed = 5;
	player1.runFlag = false;
	player1.jumpFlag = false;
	player1.shotFlag = false;
	player1.damageFlag = false;
	player1.velocity = { 0,0 };
	player1.hitPosS = { 20 , 16 };
	player1.hitPosE = { 20 , 32 };
	player1.charaType = PLAYER1;
	player1.imgLockCnt = 30;
	player1.invincible = 0;

	player2.visible = true;
	player2.lifeMax = 5;
	player2.life = player2.lifeMax;
	player2.dir = DIR_LEFT;
	player2.pos = { MAP_CHIP_SIZE_X * 20, SCREEN_SIZE_Y - 96 };
	player2.size = { PLAYER_SIZE_X, PLAYER_SIZE_Y };
	player2.sizeOffset = { player1.size.x / 2, player1.size.y / 2 };
	player2.moveSpeed = 5;
	player2.runFlag = false;
	player2.jumpFlag = false;
	player2.shotFlag = false;
	player2.damageFlag = false;
	player2.velocity = { 0,0 };
	player2.hitPosS = { 20 , 16 };
	player2.hitPosE = { 20 , 32 };
	player2.charaType = PLAYER2;
	player2.imgLockCnt = 30;
	player2.invincible = 0;

	scrPos = { 0,0 };
}

// �v���C���[����
void PlayerCtr()
{
// ==================== �v���C���[1���� ====================
	XY tmpIndex;
	XY tmpPos;
	// �v���C���[1�������Ă����瓮��
	if (player1.visible)
	{
		// �E�L�[(D)�������ꂽ��E�Ɍ������L�[(A)�������ꂽ�獶�Ɍ�������Flag��true�ɂ���
		// ������ĂȂ������瑖��Flag��false��
		if (player1.damageFlag == false)
		{
			if (newKey[P1_RIGHT])
			{
				player1.dir = DIR_RIGHT;
				player1.runFlag = true;
				player1.velocity.x += ACC_RUN; // ACG_RUN�ɖ{���͎��Ԃ�������
				if (player1.velocity.x > X_MAX)player1.velocity.x = X_MAX;
			}
			else if (newKey[P1_LEFT])
			{
				player1.dir = DIR_LEFT;
				player1.runFlag = true;
				player1.velocity.x -= ACC_RUN;
				if (player1.velocity.x < -X_MAX)player1.velocity.x = -X_MAX;
			}
			else
			{
				player1.runFlag = false;
			}
		}

		// �W�����v����
		XY movedjumpPos = player1.pos;
		XY movedjumpHitPos = movedjumpPos;
		XY movedjumpHitPos2 = movedjumpPos;
		XY movedjumpHitPos3 = movedjumpPos;
		movedjumpPos.y -= player1.velocity.y * SECOND_PER_FRAME; // ���������t�Ȃ̂�-����

		// �����
		if (player1.velocity.y > 0)
		{
			movedjumpHitPos = { movedjumpPos.x ,movedjumpPos.y - player1.hitPosS.y };
			movedjumpHitPos2 = { movedjumpPos.x - player1.hitPosS.x ,movedjumpPos.y - player1.hitPosS.y };
			movedjumpHitPos3 = { movedjumpPos.x + player1.hitPosE.x - 1, movedjumpPos.y - player1.hitPosS.y };
		}

		// ������
		if (player1.velocity.y < 0)
		{
			movedjumpHitPos = { movedjumpPos.x ,movedjumpPos.y + player1.hitPosE.y };
			movedjumpHitPos2 = { movedjumpPos.x - player1.hitPosS.x ,  movedjumpPos.y + player1.hitPosE.y };
			movedjumpHitPos3 = { movedjumpPos.x + player1.hitPosE.x - 1 , movedjumpPos.y + player1.hitPosE.y };
		}

		// �u���b�N�ɂ������ĂȂ�������ړ� �������Ă�����e�폈��
		if ((IsPass(movedjumpHitPos)) && (IsPass(movedjumpHitPos2)) && (IsPass(movedjumpHitPos3)))
		{
			player1.velocity.y -= ACC_G * SECOND_PER_FRAME;
			player1.pos.y = movedjumpPos.y;
		}
		// ��Ƀu���b�N����������
		else if (player1.velocity.y > 0)
		{
			tmpIndex = MapPosToIndex(movedjumpHitPos);
			// movedjumpHitPos.y / 32
			tmpIndex.y++;
			tmpPos = MapIndexToPos(tmpIndex);
			// (movedjumpHitPos.y / 32) * 32
			player1.pos.y = tmpPos.y + player1.hitPosS.y;
			player1.velocity.y *= -1;
		}
		// ���Ƀu���b�N����������
		else if (player1.velocity.y < 0)
		{
			tmpIndex = MapPosToIndex(movedjumpHitPos);
			// movedjumpHitPos.y / 32
			tmpPos = MapIndexToPos(tmpIndex);
			// (movedjumpHitPos.y / 32) * 32
			player1.pos.y = tmpPos.y - player1.hitPosE.y;
			player1.velocity.y = 0;
			player1.jumpFlag = false;
		}

		// jumpFLga��false���������L�[(W)�������ꂽ��jumpFlag��true��
		if (player1.damageFlag == false)
		{
			if (!player1.jumpFlag)
			{
				if (trgKey[P1_UP])
				{
					player1.jumpFlag = true;
					player1.velocity.y = INIT_VELOCITY;
				}
			}
		}

		// RETURN�L�[�ż��Ĕ���
		if (player1.damageFlag == false)
		{
			if (trgKey[P1_SHOT])
			{
				player1.shotFlag = true;
				Shoot(player1.pos, player1.dir, player1.charaType);
				player1.imgLockCnt = 30;
			}
		}
		// shotFlag��true��������
		if (player1.shotFlag == true)
		{
			player1.imgLockCnt--;
			if (player1.imgLockCnt <= 0)
			{
				player1.shotFlag = false;
			}
		}

		// ����Flag��true��������
		player1.animCnt++;
		XY movedPos = player1.pos;
		XY movedHitPos = movedPos;
		XY movedHitPos2 = movedPos;
		XY movedHitPos3 = movedPos;

		// �ړ�����
		// �E�ړ�
		if (player1.velocity.x > 0)
		{
			movedPos.x += player1.velocity.x;
			movedHitPos = { movedPos.x + player1.hitPosE.x , movedPos.y };
			movedHitPos2 = { movedPos.x + player1.hitPosE.x, movedPos.y - player1.hitPosS.y };
			movedHitPos3 = { movedPos.x + player1.hitPosE.x, movedPos.y + player1.hitPosE.y - 1 };
		}
		// ���ړ�
		if (player1.velocity.x < 0)
		{
			movedPos.x += player1.velocity.x;
			movedHitPos = { movedPos.x - player1.hitPosS.x , movedPos.y };
			movedHitPos2 = { movedPos.x - player1.hitPosS.x , movedPos.y - player1.hitPosS.y };
			movedHitPos3 = { movedPos.x - player1.hitPosS.x , movedPos.y + player1.hitPosE.y - 1 };
		}

		XY p1oldPos;
		p1oldPos.x = player1.pos.x;
	
		if (abs(movedPos.x - player2.pos.x) > SCREEN_SIZE_X - 64)
		{
			if (movedPos.x < player2.pos.x)
			{
				movedPos.x = player2.pos.x - (SCREEN_SIZE_X - 64);
			}
			else
			{
				movedPos.x = player2.pos.x + (SCREEN_SIZE_X - 64);
			}
		}

		// �ǂ�u���b�N����Ȃ���Έړ�
		if ((IsPass(movedHitPos)) && (IsPass(movedHitPos2)) && (IsPass(movedHitPos3)))
		{
			player1.pos.x = movedPos.x;
			
		}
		// �ǂ�u���b�N�Ȃ�
		else
		{
			// �E��
			if (player1.velocity.x > 0)
			{
				player1.velocity.x = 0;
				tmpIndex = MapPosToIndex(movedHitPos);
				tmpPos = MapIndexToPos(tmpIndex);
				player1.pos.x = tmpPos.x - player1.hitPosE.x;
			}
			// ����
			if (player1.velocity.x < 0)
			{
				player1.velocity.x = 0;
				tmpIndex = MapPosToIndex(movedHitPos);
				tmpIndex.x++;
				tmpPos = MapIndexToPos(tmpIndex);
				player1.pos.x = tmpPos.x + player1.hitPosS.x;
			}
		}

		// �X�N���[��
		if (player2.pos.x - scrPos.x == SCREEN_SIZE_X / 4)
		{
			scrPos.x += (movedPos.x - p1oldPos.x);
		}

		if (player1.pos.x - scrPos.x < 32)
		{
			scrPos.x = player1.pos.x - 32;
		}
		if (player1.pos.x - scrPos.x > SCREEN_SIZE_X - 32)
		{
			scrPos.x = player1.pos.x - SCREEN_SIZE_X + 32;
		}

		if (scrPos.x <= 0)
		{
			scrPos.x = 0;
		}
		if (scrPos.x >= MAP_CHIP_SIZE_X * MAP_CHIP_X - SCREEN_SIZE_X)
		{
			scrPos.x = MAP_CHIP_SIZE_X * MAP_CHIP_X - SCREEN_SIZE_X;
		}

		// player1�̑���t���O��false��������
		if (!player1.runFlag)
		{
			// �����x��0���傫��������
			if (player1.velocity.x > 0)
			{
				player1.velocity.x -= ACC_STOP;
				if (player1.velocity.x <= 0)
				{
					player1.velocity.x = 0;
				}
			}
			// �����x��0��菬����������
			else if (player1.velocity.x < 0)
			{
				player1.velocity.x += ACC_STOP;
				if (player1.velocity.x >= 0)
				{
					player1.velocity.x = 0;
				}
			}
		}
	}
//==================== �v���C���[2���� ====================
	XY p2tmpIndex;
	XY p2tmpPos;
	// �v���C���[2�������Ă����瓮��
	if(player2.visible)
	{
		// �E�L�[(D)�������ꂽ��E�Ɍ������L�[(A)�������ꂽ�獶�Ɍ�������Flag��true�ɂ���
		// ������ĂȂ������瑖��Flag��false��
		if (player2.damageFlag == false)
		{
			if (newKey[P2_RIGHT])
			{
				player2.dir = DIR_RIGHT;
				player2.runFlag = true;
				player2.velocity.x += ACC_RUN;
				if (player2.velocity.x > X_MAX)player2.velocity.x = X_MAX;
			}
			else if (newKey[P2_LEFT])
			{
				player2.dir = DIR_LEFT;
				player2.runFlag = true;
				player2.velocity.x -= ACC_RUN;
				if (player2.velocity.x < -X_MAX)player2.velocity.x = -X_MAX;
			}
			else
			{
				player2.runFlag = false;
			}
		}
		// �W�����v����
		XY p2Pos = player2.pos;
		XY p2HitPos = p2Pos;
		XY p2HitPos2 = p2Pos;
		XY p2HitPos3 = p2Pos;
		p2Pos.y -= player2.velocity.y * SECOND_PER_FRAME; // ���������t�Ȃ̂�-����

		// �����
		if (player2.velocity.y > 0)
		{
			p2HitPos = { p2Pos.x ,  p2Pos.y - player2.hitPosS.y };
			p2HitPos2 = { p2Pos.x - player2.hitPosS.x ,  p2Pos.y - player2.hitPosS.y };
			p2HitPos3 = { p2Pos.x + player2.hitPosE.x - 1 ,  p2Pos.y - player2.hitPosS.y };
		}

		// ������
		if (player2.velocity.y < 0)
		{
			p2HitPos = { p2Pos.x ,  p2Pos.y + player2.hitPosE.y };
			p2HitPos2 = { p2Pos.x - player2.hitPosS.x ,  p2Pos.y + player2.hitPosE.y };
			p2HitPos3 = { p2Pos.x + player2.hitPosE.x - 1,  p2Pos.y + player2.hitPosE.y };
		}

		// �u���b�N�ɂ������ĂȂ�������ړ� �������Ă�����e�폈��
		if ((IsPass(p2HitPos))&& (IsPass(p2HitPos2))&& (IsPass(p2HitPos3)))
		{
			player2.velocity.y -= ACC_G * SECOND_PER_FRAME;
			player2.pos.y = p2Pos.y;
		}
		// ��Ƀu���b�N����������
		else if (player2.velocity.y > 0)
		{
			p2tmpIndex = MapPosToIndex(p2HitPos);
			// movedjumpHitPos.y / 32
			p2tmpIndex.y++;
			p2tmpPos = MapIndexToPos(p2tmpIndex);
			// (movedjumpHitPos.y / 32) * 32
			player2.pos.y = p2tmpPos.y + player2.hitPosS.y;
			player2.velocity.y *= -1;
		}
		// ���Ƀu���b�N����������
		else if (player2.velocity.y < 0)
		{
			p2tmpIndex = MapPosToIndex(p2HitPos);
			// movedjumpHitPos.y / 32
			p2tmpPos = MapIndexToPos(p2tmpIndex);
			// (movedjumpHitPos.y / 32) * 32
			player2.pos.y = p2tmpPos.y - player2.hitPosE.y;
			player2.velocity.y = 0;
			player2.jumpFlag = false;
		}

		// jumpFLga��false���������L�[(W)�������ꂽ��jumpFlag��true��
		if (player2.damageFlag == false)
		{
			if (!player2.jumpFlag)
			{
				if (trgKey[P2_UP])
				{
					player2.jumpFlag = true;
					player2.velocity.y = INIT_VELOCITY;
				}
			}
		}
		// RETURN�L�[�ż��Ĕ���
		if (player2.damageFlag == false)
		{
			if (trgKey[P2_SHOT])
			{
				player2.shotFlag = true;
				Shoot(player2.pos, player2.dir, player2.charaType);
				player2.imgLockCnt = 30;
			}
		}
		// shotFlag��true��������
		if (player2.shotFlag == true)
		{
			player2.imgLockCnt--;
			if (player2.imgLockCnt <= 0)
			{
				player2.shotFlag = false;
			}
		}

		// ����Flag��true��������
		player2.animCnt++;
		XY p2movedPos = player2.pos;
		XY p2movedHitPos = p2movedPos;
		XY p2movedHitPos2 = p2movedPos;
		XY p2movedHitPos3 = p2movedPos;

		// �ړ�����
		// �E�ړ�
		if (player2.velocity.x > 0)
		{
			p2movedPos.x += player2.velocity.x;
			p2movedHitPos = { p2movedPos.x + player2.hitPosE.x , p2movedPos.y };
			p2movedHitPos2 = { p2movedPos.x + player2.hitPosE.x, p2movedPos.y - player2.hitPosS.y };
			p2movedHitPos3 = { p2movedPos.x + player2.hitPosE.x, p2movedPos.y + player2.hitPosE.y - 1 };
		}
		// ���ړ�
		if (player2.velocity.x < 0)
		{
			p2movedPos.x += player2.velocity.x;
			p2movedHitPos = { p2movedPos.x - player2.hitPosS.x , p2movedPos.y };
			p2movedHitPos2 = { p2movedPos.x - player2.hitPosS.x, p2movedPos.y - player2.hitPosS.y };
			p2movedHitPos3 = { p2movedPos.x - player2.hitPosS.x, p2movedPos.y + player2.hitPosE.y - 1};
		}

		XY p2oldPos;
		p2oldPos.x = player2.pos.x;

		if (abs(p2movedPos.x - player1.pos.x) > SCREEN_SIZE_X - 64)
		{
			if (p2movedPos.x < player1.pos.x)
			{
				p2movedPos.x = player1.pos.x - (SCREEN_SIZE_X - 64);
			}
			else
			{
				p2movedPos.x = player1.pos.x + (SCREEN_SIZE_X - 64);
			}
		}

		// �ǂ�u���b�N����Ȃ���Έړ�
		if ((IsPass(p2movedHitPos))&& (IsPass(p2movedHitPos2))&& (IsPass(p2movedHitPos3)))
		{
			player2.pos.x = p2movedPos.x;
		}

		// �ǂ�u���b�N��������
		else
		{
			// �E��
			if (player2.velocity.x > 0)
			{
				player2.velocity.x = 0;
				p2tmpIndex = MapPosToIndex(p2movedHitPos);
				p2tmpPos = MapIndexToPos(p2tmpIndex);
				player2.pos.x = p2tmpPos.x - player2.hitPosE.x;
			}
			// ����
			if (player2.velocity.x < 0)
			{
				player2.velocity.x = 0;
				p2tmpIndex = MapPosToIndex(p2movedHitPos);
				p2tmpIndex.x++;
				p2tmpPos = MapIndexToPos(p2tmpIndex);
				player2.pos.x = p2tmpPos.x + player2.hitPosS.x;
			}
		}

		// ============ �X�N���[�� ============
		if (player1.pos.x - scrPos.x == SCREEN_SIZE_X / 4)
		{
			scrPos.x += (p2movedPos.x - p2oldPos.x);
		}

		if (player2.pos.x - scrPos.x < 32)
		{
			scrPos.x = player2.pos.x - 32;
		}
		if (player2.pos.x - scrPos.x > SCREEN_SIZE_X - 32)
		{
			scrPos.x = player2.pos.x - SCREEN_SIZE_X + 32;
		}

		if (scrPos.x <= 0)
		{
			scrPos.x = 0;
		}
		if (scrPos.x >= MAP_CHIP_SIZE_X * MAP_CHIP_X - SCREEN_SIZE_X)
		{
			scrPos.x = MAP_CHIP_SIZE_X * MAP_CHIP_X - SCREEN_SIZE_X;
		}

		// player2�̑���t���O��false��������
		if (!player2.runFlag)
		{
			// �����x��0���傫��������
			if (player2.velocity.x > 0)
			{
				player2.velocity.x -= ACC_STOP;
				if (player2.velocity.x <= 0)
				{
					player2.velocity.x = 0;
				}
			}
			// �����x��0��菬����������
			if (player2.velocity.x < 0)
			{
				player2.velocity.x += ACC_STOP;
				if (player2.velocity.x >= 0)
				{
					player2.velocity.x = 0;
				}
			}
		}
	}
}

// �v���C���[�`��
void PlayerDraw()
{
	// ==================== player1�`�� ====================
	int p1shotStatus = player1.shotFlag;
	int img = p1StopImg[p1shotStatus];
	if (player1.runFlag) img = p1runImg[p1shotStatus][player1.animCnt / 10 % 4];
	if (player1.jumpFlag) img = p1jumpImg[p1shotStatus];
	if (player1.damageFlag) img = p1DamageImg;
	XY p1Pos = { player1.pos.x - player1.sizeOffset.x - scrPos.x, player1.pos.y - player1.sizeOffset.y };

	if (player1.damageFlag == true)
	{
		player1.imgLockCnt--;
		if (player1.imgLockCnt <= 0)
		{
			player1.damageFlag = false;
		}
	}
	if (player1.invincible > 0)
	{
		player1.invincible--;
	}
	DrawRotaGraph(55, 60, 0.5, 0, hpImg, true, false);
	// player1���������Ă�����
	if (player1.life > 0)
	{
		for (int i = 0; i < player1.life; i++)
		{
			DrawRotaGraph(50 + (i* 15), 76, 1.0, PI / 2, lifeImg, true,true);
		}
		// �_���[�W���󂯂���_��
		if (player1.invincible % 5 == 0)
		{
			// �E�������Ă�����
			if (player1.dir == DIR_RIGHT)
			{
				if (player1.jumpFlag)
				{
					DrawGraph(p1Pos.x, p1Pos.y, img, true);
				}
				else if (player1.runFlag == false)
				{
					DrawGraph(p1Pos.x, p1Pos.y, img, true);
				}
				else if (player1.runFlag)
				{
					DrawGraph(p1Pos.x, p1Pos.y, img, true);
				}
			}
			// ���������Ă�����
			else if (player1.dir == DIR_LEFT)
			{
				if (player1.jumpFlag)
				{
					DrawTurnGraph(p1Pos.x, p1Pos.y, img, true);
				}
				else if (player1.runFlag == false)
				{
					DrawTurnGraph(p1Pos.x, p1Pos.y, img, true);
				}
				else if (player1.runFlag)
				{
					DrawTurnGraph(p1Pos.x, p1Pos.y, img, true);
				}
			}
		}
		/*DrawBox(p1Pos.x, p1Pos.y, player1.pos.x + player1.sizeOffset.x, player1.pos.y + player1.sizeOffset.y, GetColor(255, 0, 0), false);
		DrawBox(player1.pos.x + player1.hitPosE.x, player1.pos.y - player1.hitPosS.y, player1.pos.x - player2.hitPosS.x, player1.pos.y + player1.hitPosE.y, GetColor(0, 255, 0), false);*/
	}
	// player1���W���\��
	/*DrawFormatString(32, 32, 0xFFFFFF, "player1 : (%d , %d)", player1.pos.x, player1.pos.y);
	DrawFormatString(32, 32, GetColor(255, 255, 0), "velocity : (%f , %f)", player1.velocity.x, player1.velocity.y);
	DrawFormatString(32, 48, 0xFFFFFF, "p1life : (%d)", player1.life);
	DrawFormatString(32, 16, 0xFFFFFF, "scrPos : (%d , %d)", scrPos.x,scrPos.y);*/
	// ==================== player2�`�� ====================
	int p2shotStatus = player2.shotFlag;
	int img2 = p2StopImg[p2shotStatus];
	if (player2.runFlag) img2 = p2runImg[p2shotStatus][player2.animCnt / 10 % 4];
	if (player2.jumpFlag) img2 = p2jumpImg[p2shotStatus];
	if (player2.damageFlag) img2 = p2DamageImg;
	XY p2Pos = { player2.pos.x - player2.sizeOffset.x - scrPos.x ,player2.pos.y - player2.sizeOffset.y };

	if (player2.damageFlag == true)
	{
		player2.imgLockCnt--;
		if (player2.imgLockCnt <= 0)
		{
			player2.damageFlag = false;
		}
	}
	if (player2.invincible > 0)
	{
		player2.invincible--;
	}
	DrawRotaGraph(710, 60, 0.5, 0, hpImg, true, false);
	// player2���������Ă�����
	if (player2.life > 0)
	{
		for (int i = 0; i < player2.life; i++)
		{
			DrawRotaGraph(SCREEN_SIZE_X - 116 + (i * 15), 76, 1.0, PI / 2, lifeImg, true, true);
		}
		if (player2.invincible % 5 == 0)
		{
			if (player2.dir == DIR_RIGHT)
			{
				if (player2.jumpFlag)
				{
					DrawGraph(p2Pos.x, p2Pos.y, img2, true);
				}
				else if (player2.runFlag == false)
				{
					DrawGraph(p2Pos.x, p2Pos.y, img2, true);
				}
				else if (player2.runFlag)
				{
					DrawGraph(p2Pos.x, p2Pos.y, img2, true);
				}
			}
			else if (player2.dir == DIR_LEFT)
			{
				if (player2.jumpFlag)
				{
					DrawTurnGraph(p2Pos.x, p2Pos.y, img2, true);
				}
				else if (player2.runFlag == false)
				{
					DrawTurnGraph(p2Pos.x, p2Pos.y, img2, true);
				}
				else if (player2.runFlag)
				{
					DrawTurnGraph(p2Pos.x, p2Pos.y, img2, true);
				}
			}
		}
		/*DrawBox(p2Pos.x, p2Pos.y, player2.pos.x + player2.sizeOffset.x, player2.pos.y + player2.sizeOffset.y, GetColor(255, 255, 0), false);
		DrawBox(player2.pos.x + player2.hitPosE.x, player2.pos.y - player2.hitPosS.y, player2.pos.x - player2.hitPosS.x, player2.pos.y + player2.hitPosE.y, GetColor(255, 0, 0), false);*/
	}
	// player2���W���\��
	/*DrawFormatString(SCREEN_SIZE_X / 2 + 64, 16, 0xFFFFFF, "player2 : (%d , %d)", player2.pos.x, player2.pos.y);*/
	//DrawFormatString(SCREEN_SIZE_X / 2 + 64, 32, GetColor(255, 255, 0), "p2velocity : (%f , %f)", player2.velocity.x, player2.velocity.y);
	//DrawFormatString(SCREEN_SIZE_X / 2 + 64, 48, 0xFFFFFF, "p2life : (%d)", player2.life);
}

// �v���C���[�����蔻��
bool PlayerhitCheck(XY sPos, XY sSize ,TYPE sType)
{
	if ((player1.visible) && (player1.damageFlag == false) && (sType == PLAYER2) && (player1.invincible == 0)
		&& (player1.pos.x + player1.hitPosE.x >= sPos.x - sSize.x / 2)
		&& (player1.pos.x - player1.hitPosS.x <= sPos.x + sSize.x / 2)
		&& (player1.pos.y + player1.hitPosE.y >= sPos.y - sSize.y / 2)
		&& (player1.pos.y - player1.hitPosS.y <= sPos.y + sSize.y / 2))
	{
		player1.damageFlag = true;
		player1.imgLockCnt = 30;
		player1.invincible = 120;
		player1.life--;
		if (player1.life <= 0)
		{
			SetTobichiri(player1.pos, player1.charaType);
			player1.visible = false;
		}
		return true;
	}

	if ((player2.visible) && (player2.damageFlag == false) && (sType == PLAYER1)&&(player2.invincible == 0)
		&& (player2.pos.x + player2.hitPosE.x >= sPos.x - sSize.x / 2)
		&& (player2.pos.x - player2.hitPosS.x <= sPos.x + sSize.x / 2)
		&& (player2.pos.y + player2.hitPosE.y >= sPos.y - sSize.y / 2)
		&& (player2.pos.y - player2.hitPosS.y <= sPos.y + sSize.y / 2))
	{
		player2.damageFlag = true;
		player2.imgLockCnt = 30;
		player2.invincible = 120;
		player2.life--;	
		if (player2.life <= 0)
		{
			SetTobichiri(player2.pos,player2.charaType);
			player2.visible = false;
		}
		return true;
	}
	return false;
}

// �N����������
TYPE GameEnd(void) 
{
	TYPE winType = PROTO;
	bool tobichiriFlag = TobichiriFlag();
	if ((player1.visible == false)&&(tobichiriFlag == false))
	{
		winType = PLAYER2;
		return winType;
	}
	else if ((player2.visible == false) && (tobichiriFlag == false))
	{
		winType = PLAYER1;
		return winType;
	}
	return winType;
}

// �v���C���[���
CHARACTER GetPlayer1(void) 
{
	return player1;
}

