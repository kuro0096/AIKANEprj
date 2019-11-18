#include <math.h>
#include "main.h"
#include "keycheck.h"
#include "player.h"
#include "stage.h"
#include "shot.h"
#include "effect.h"
#include "enemy.h"

// 定数
#define PLAYER_SIZE_X 96
#define PLAYER_SIZE_Y 64

#define PI 3.141592

#define G 9.8 // 重力加速度

#define INIT_VELOCITY 50 // 初速度
#define SECOND_PER_FRAME 0.3

#define Y_MAX 100

// 定義

// 変数
CHARACTER player1;
CHARACTER player2;

int p1StopImg[2];		// p1停止状態の画像
int p1runImg[2][4];		// p1走り状態の画像
int p1jumpImg[2];		// p1ジャンプ中の画像
int p1DamageImg;		// p1ダメージ画像

int p2StopImg[2];		// p2停止状態の画像
int p2runImg[2][4];		// p2走り状態の画像
int p2jumpImg[2];		// p2ジャンプ中の画像
int p2DamageImg;		// p2ダメージ画像

int hpImg;
int lifeImg; // ライフ画像

XY scrPos;

// プロトタイプ宣言

// プレイヤー画像読み込み
void PlayerSysInit()
{
	// player1画像読み込み
	p1StopImg[0] = LoadGraph("image/stop.png");		
	p1StopImg[1] = LoadGraph("image/stop_shot.png");
	LoadDivGraph("image/run.png",4,4,1,96,64, p1runImg[0]);
	LoadDivGraph("image/run_shot.png", 4, 4, 1, 96, 64, p1runImg[1]);
	p1jumpImg[0] = LoadGraph("image/jump.png");
	p1jumpImg[1] = LoadGraph("image/jump_shot.png");
	p1DamageImg = LoadGraph("image/damage.png");

	// player2画像読み込み
	p2StopImg[0] = LoadGraph("image/stop2.png");
	p2StopImg[1] = LoadGraph("image/stop_shot2.png");
	LoadDivGraph("image/run2.png", 4, 4, 1, 96, 64, p2runImg[0]);
	LoadDivGraph("image/run_shot2.png", 4, 4, 1, 96, 64, p2runImg[1]);
	p2jumpImg[0] = LoadGraph("image/jump2.png");
	p2jumpImg[1] = LoadGraph("image/jump_shot2.png");
	p2DamageImg = LoadGraph("image/damage2.png");

	// ライフ画像
	hpImg = LoadGraph("image/hp.png");
	lifeImg = LoadGraph("image/life.png");
}

// プレイヤー初期化
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

// プレイヤー動作
void PlayerCtr()
{
// ==================== プレイヤー1動作 ====================
	XY tmpIndex;
	XY tmpPos;
	// プレイヤー1が生きていたら動作
	if (player1.visible)
	{
		// 右キー(D)が押されたら右に向き左キー(A)が押されたら左に向き走るFlagをtrueにする
		// 押されてなかったら走るFlagをfalseに
		if (player1.damageFlag == false)
		{
			if (newKey[P1_RIGHT])
			{
				player1.dir = DIR_RIGHT;
				player1.runFlag = true;
				player1.velocity.x += ACC_RUN; // ACG_RUNに本当は時間をかける
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

		// ジャンプ処理
		XY movedjumpPos = player1.pos;
		XY movedjumpHitPos = movedjumpPos;
		XY movedjumpHitPos2 = movedjumpPos;
		XY movedjumpHitPos3 = movedjumpPos;
		movedjumpPos.y -= player1.velocity.y * SECOND_PER_FRAME; // 軸方向が逆なので-する

		// 上方向
		if (player1.velocity.y > 0)
		{
			movedjumpHitPos = { movedjumpPos.x ,movedjumpPos.y - player1.hitPosS.y };
			movedjumpHitPos2 = { movedjumpPos.x - player1.hitPosS.x ,movedjumpPos.y - player1.hitPosS.y };
			movedjumpHitPos3 = { movedjumpPos.x + player1.hitPosE.x - 1, movedjumpPos.y - player1.hitPosS.y };
		}

		// 下方向
		if (player1.velocity.y < 0)
		{
			movedjumpHitPos = { movedjumpPos.x ,movedjumpPos.y + player1.hitPosE.y };
			movedjumpHitPos2 = { movedjumpPos.x - player1.hitPosS.x ,  movedjumpPos.y + player1.hitPosE.y };
			movedjumpHitPos3 = { movedjumpPos.x + player1.hitPosE.x - 1 , movedjumpPos.y + player1.hitPosE.y };
		}

		// ブロックにあたってなかったら移動 あたっていたら各種処理
		if ((IsPass(movedjumpHitPos)) && (IsPass(movedjumpHitPos2)) && (IsPass(movedjumpHitPos3)))
		{
			player1.velocity.y -= ACC_G * SECOND_PER_FRAME;
			player1.pos.y = movedjumpPos.y;
		}
		// 上にブロックがあったら
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
		// 下にブロックがあったら
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

		// jumpFLgaがfalseだったら上キー(W)が押されたらjumpFlagをtrueに
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

		// RETURNキーでｼｮｯﾄ発射
		if (player1.damageFlag == false)
		{
			if (trgKey[P1_SHOT])
			{
				player1.shotFlag = true;
				Shoot(player1.pos, player1.dir, player1.charaType);
				player1.imgLockCnt = 30;
			}
		}
		// shotFlagがtrueだったら
		if (player1.shotFlag == true)
		{
			player1.imgLockCnt--;
			if (player1.imgLockCnt <= 0)
			{
				player1.shotFlag = false;
			}
		}

		// 走るFlagがtrueだったら
		player1.animCnt++;
		XY movedPos = player1.pos;
		XY movedHitPos = movedPos;
		XY movedHitPos2 = movedPos;
		XY movedHitPos3 = movedPos;

		// 移動処理
		// 右移動
		if (player1.velocity.x > 0)
		{
			movedPos.x += player1.velocity.x;
			movedHitPos = { movedPos.x + player1.hitPosE.x , movedPos.y };
			movedHitPos2 = { movedPos.x + player1.hitPosE.x, movedPos.y - player1.hitPosS.y };
			movedHitPos3 = { movedPos.x + player1.hitPosE.x, movedPos.y + player1.hitPosE.y - 1 };
		}
		// 左移動
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

		// 壁やブロックじゃなければ移動
		if ((IsPass(movedHitPos)) && (IsPass(movedHitPos2)) && (IsPass(movedHitPos3)))
		{
			player1.pos.x = movedPos.x;
			
		}
		// 壁やブロックなら
		else
		{
			// 右側
			if (player1.velocity.x > 0)
			{
				player1.velocity.x = 0;
				tmpIndex = MapPosToIndex(movedHitPos);
				tmpPos = MapIndexToPos(tmpIndex);
				player1.pos.x = tmpPos.x - player1.hitPosE.x;
			}
			// 左側
			if (player1.velocity.x < 0)
			{
				player1.velocity.x = 0;
				tmpIndex = MapPosToIndex(movedHitPos);
				tmpIndex.x++;
				tmpPos = MapIndexToPos(tmpIndex);
				player1.pos.x = tmpPos.x + player1.hitPosS.x;
			}
		}

		// スクロール
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

		// player1の走るフラグがfalseだったら
		if (!player1.runFlag)
		{
			// 加速度が0より大きかったら
			if (player1.velocity.x > 0)
			{
				player1.velocity.x -= ACC_STOP;
				if (player1.velocity.x <= 0)
				{
					player1.velocity.x = 0;
				}
			}
			// 加速度が0より小さかったら
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
//==================== プレイヤー2動作 ====================
	XY p2tmpIndex;
	XY p2tmpPos;
	// プレイヤー2が生きていたら動作
	if(player2.visible)
	{
		// 右キー(D)が押されたら右に向き左キー(A)が押されたら左に向き走るFlagをtrueにする
		// 押されてなかったら走るFlagをfalseに
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
		// ジャンプ処理
		XY p2Pos = player2.pos;
		XY p2HitPos = p2Pos;
		XY p2HitPos2 = p2Pos;
		XY p2HitPos3 = p2Pos;
		p2Pos.y -= player2.velocity.y * SECOND_PER_FRAME; // 軸方向が逆なので-する

		// 上方向
		if (player2.velocity.y > 0)
		{
			p2HitPos = { p2Pos.x ,  p2Pos.y - player2.hitPosS.y };
			p2HitPos2 = { p2Pos.x - player2.hitPosS.x ,  p2Pos.y - player2.hitPosS.y };
			p2HitPos3 = { p2Pos.x + player2.hitPosE.x - 1 ,  p2Pos.y - player2.hitPosS.y };
		}

		// 下方向
		if (player2.velocity.y < 0)
		{
			p2HitPos = { p2Pos.x ,  p2Pos.y + player2.hitPosE.y };
			p2HitPos2 = { p2Pos.x - player2.hitPosS.x ,  p2Pos.y + player2.hitPosE.y };
			p2HitPos3 = { p2Pos.x + player2.hitPosE.x - 1,  p2Pos.y + player2.hitPosE.y };
		}

		// ブロックにあたってなかったら移動 あたっていたら各種処理
		if ((IsPass(p2HitPos))&& (IsPass(p2HitPos2))&& (IsPass(p2HitPos3)))
		{
			player2.velocity.y -= ACC_G * SECOND_PER_FRAME;
			player2.pos.y = p2Pos.y;
		}
		// 上にブロックがあったら
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
		// 下にブロックがあったら
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

		// jumpFLgaがfalseだったら上キー(W)が押されたらjumpFlagをtrueに
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
		// RETURNキーでｼｮｯﾄ発射
		if (player2.damageFlag == false)
		{
			if (trgKey[P2_SHOT])
			{
				player2.shotFlag = true;
				Shoot(player2.pos, player2.dir, player2.charaType);
				player2.imgLockCnt = 30;
			}
		}
		// shotFlagがtrueだったら
		if (player2.shotFlag == true)
		{
			player2.imgLockCnt--;
			if (player2.imgLockCnt <= 0)
			{
				player2.shotFlag = false;
			}
		}

		// 走るFlagがtrueだったら
		player2.animCnt++;
		XY p2movedPos = player2.pos;
		XY p2movedHitPos = p2movedPos;
		XY p2movedHitPos2 = p2movedPos;
		XY p2movedHitPos3 = p2movedPos;

		// 移動処理
		// 右移動
		if (player2.velocity.x > 0)
		{
			p2movedPos.x += player2.velocity.x;
			p2movedHitPos = { p2movedPos.x + player2.hitPosE.x , p2movedPos.y };
			p2movedHitPos2 = { p2movedPos.x + player2.hitPosE.x, p2movedPos.y - player2.hitPosS.y };
			p2movedHitPos3 = { p2movedPos.x + player2.hitPosE.x, p2movedPos.y + player2.hitPosE.y - 1 };
		}
		// 左移動
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

		// 壁やブロックじゃなければ移動
		if ((IsPass(p2movedHitPos))&& (IsPass(p2movedHitPos2))&& (IsPass(p2movedHitPos3)))
		{
			player2.pos.x = p2movedPos.x;
		}

		// 壁やブロックだったら
		else
		{
			// 右側
			if (player2.velocity.x > 0)
			{
				player2.velocity.x = 0;
				p2tmpIndex = MapPosToIndex(p2movedHitPos);
				p2tmpPos = MapIndexToPos(p2tmpIndex);
				player2.pos.x = p2tmpPos.x - player2.hitPosE.x;
			}
			// 左側
			if (player2.velocity.x < 0)
			{
				player2.velocity.x = 0;
				p2tmpIndex = MapPosToIndex(p2movedHitPos);
				p2tmpIndex.x++;
				p2tmpPos = MapIndexToPos(p2tmpIndex);
				player2.pos.x = p2tmpPos.x + player2.hitPosS.x;
			}
		}

		// ============ スクロール ============
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

		// player2の走るフラグがfalseだったら
		if (!player2.runFlag)
		{
			// 加速度が0より大きかったら
			if (player2.velocity.x > 0)
			{
				player2.velocity.x -= ACC_STOP;
				if (player2.velocity.x <= 0)
				{
					player2.velocity.x = 0;
				}
			}
			// 加速度が0より小さかったら
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

// プレイヤー描画
void PlayerDraw()
{
	// ==================== player1描画 ====================
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
	// player1が生存していたら
	if (player1.life > 0)
	{
		for (int i = 0; i < player1.life; i++)
		{
			DrawRotaGraph(50 + (i* 15), 76, 1.0, PI / 2, lifeImg, true,true);
		}
		// ダメージを受けたら点滅
		if (player1.invincible % 5 == 0)
		{
			// 右を向いていたら
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
			// 左を向いていたら
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
	// player1座標等表示
	/*DrawFormatString(32, 32, 0xFFFFFF, "player1 : (%d , %d)", player1.pos.x, player1.pos.y);
	DrawFormatString(32, 32, GetColor(255, 255, 0), "velocity : (%f , %f)", player1.velocity.x, player1.velocity.y);
	DrawFormatString(32, 48, 0xFFFFFF, "p1life : (%d)", player1.life);
	DrawFormatString(32, 16, 0xFFFFFF, "scrPos : (%d , %d)", scrPos.x,scrPos.y);*/
	// ==================== player2描画 ====================
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
	// player2が生存していたら
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
	// player2座標等表示
	/*DrawFormatString(SCREEN_SIZE_X / 2 + 64, 16, 0xFFFFFF, "player2 : (%d , %d)", player2.pos.x, player2.pos.y);*/
	//DrawFormatString(SCREEN_SIZE_X / 2 + 64, 32, GetColor(255, 255, 0), "p2velocity : (%f , %f)", player2.velocity.x, player2.velocity.y);
	//DrawFormatString(SCREEN_SIZE_X / 2 + 64, 48, 0xFFFFFF, "p2life : (%d)", player2.life);
}

// プレイヤー当たり判定
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

// 誰が勝ったか
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

// プレイヤー情報
CHARACTER GetPlayer1(void) 
{
	return player1;
}

