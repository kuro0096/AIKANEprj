#include "main.h"
#include "stage.h"
#include "player.h"

// �萔

// ��`
int mapData[15][48] = {
{ 8, 3, 3, 3, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 3, 3, 3, 8 },
{ 8, 1, 1, 1, 2, 1,  1, 1, 1, 1, 1, 3,  3, 1, 1, 2, 1, 1,  1, 1, 3, 3, 1, 1,  1, 1, 1, 3, 3, 1,  1, 1, 1, 1, 1, 3,  3, 3, 1, 2, 1, 1,  1, 1, 1, 1, 1, 8 },
{ 8, 1, 1, 1, 1, 1,  1, 1, 2,10,10, 1,  1, 1, 1,10,10, 1,  1, 1, 2, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 2, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 2, 1, 1, 8 },
{ 8, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 2,  1, 1, 1, 1, 1, 1,  1, 1, 8,11,12, 8 },
{ 8, 1, 1, 1,11,11,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  2, 1, 1, 1, 1, 2,  1, 1, 1, 1, 1, 8,  8, 8, 1, 1, 1, 8 },

{ 8, 1, 1, 2, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 2, 1,  1, 1, 1, 8, 8, 8,  8, 1, 1, 1, 1, 1,  1, 1, 1, 8, 8, 1,  1, 1, 1, 1, 2, 8 },
{ 8, 1, 1, 1, 1, 1,  1, 1, 1, 2, 1, 1,  1, 1, 1, 1, 2, 1,  1, 8, 8, 8, 8, 8,  1, 1, 1, 1, 1, 1,  1, 1, 1, 2, 1, 1,  1, 1, 1, 1, 2, 1,  1, 1, 1, 1, 1, 8 },
{ 8,10, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 8, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 8, 8,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 8 },
{ 8,10,10, 1, 1, 2,  1, 1, 1, 1, 8, 8,  8, 1, 1, 1, 1, 1,  1, 8, 1, 1, 1, 1,  1, 1, 1, 1, 1, 2,  1, 1, 1, 1, 8, 8,  1, 1, 1, 1, 1, 1,  1, 2, 1, 1, 1, 8 },
{ 8, 1, 1, 1, 1, 1,  1, 1, 8, 8, 8, 1,  8, 8, 1, 1, 1, 1,  8, 8, 1, 1, 1,11, 12, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 2, 1, 1, 1, 1,  1, 1, 1, 1, 1, 8 },

{ 8, 1, 2, 1, 1, 1, 10,10, 1, 1, 1, 1,  1, 1, 1, 1, 2, 1,  1, 1, 1, 1, 1, 1,  1, 1, 2, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 2, 1,  1, 1, 1, 1, 1, 8 },
{ 8, 1, 1, 1, 1, 1,  1, 2, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 2, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1,12,11, 1, 1, 1,  1, 1, 1, 9, 1, 1,  1, 1, 2, 1, 1, 8 },
{ 8, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 8, 8,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1, 9, 1, 1,  1, 1, 1, 1, 1, 8 },
{ 8, 8, 8, 8, 8, 8,  8, 8, 8, 8, 8, 8,  8, 8, 8, 8, 8, 8,  8, 8, 8, 8, 8, 8,  8, 8, 8, 8, 8, 8,  8, 8, 8, 8, 8, 8,  8, 8, 8, 8, 8, 8,  8, 8, 8, 8, 8, 8 },
{ 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 0,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 0 },
};

// �ϐ�
int mapImg[14];

// �v���g�^�C�v�錾

// �摜�ǂݍ���
void StageSysInit()
{
	LoadDivGraph("image/bg.png", 13, 13, 1, 32, 32, mapImg);
}

// �X�e�[�W������
void StageGameInit()
{


}

// �X�e�[�W�`��
void StageDraw()
{
	for (int y = 0; y < MAP_CHIP_Y; y++)
	{
		for (int x = 0; x < MAP_CHIP_X; x++)
		{
			DrawGraph(MAP_CHIP_SIZE_X * x - scrPos.x, MAP_CHIP_SIZE_Y * y, mapImg[mapData[y][x]], true);
			/*DrawLine(x * 32, 0, x * 32, SCREEN_SIZE_Y, GetColor(0, 255, 255));
			DrawLine(0, y * 32, SCREEN_SIZE_X, y * 32,GetColor(0, 255, 255));
			DrawLine(MAP_CHIP_SIZE_X, 0, MAP_CHIP_SIZE_X, SCREEN_SIZE_Y, GetColor(255, 0, 255));
			DrawLine(SCREEN_SIZE_X - MAP_CHIP_SIZE_X, 0, SCREEN_SIZE_X - MAP_CHIP_SIZE_X, SCREEN_SIZE_Y, GetColor(255, 0, 255));*/
		}
	}
}

// pos����index��
XY MapPosToIndex(XY pos)
{
	XY mapIndex;
	mapIndex = { pos.x / MAP_CHIP_SIZE_X, pos.y / MAP_CHIP_SIZE_Y };

	return mapIndex;
}

// index����pos��
XY MapIndexToPos(XY index)
{
	XY mapPos;

	mapPos = { index.x * MAP_CHIP_SIZE_X, index.y * MAP_CHIP_SIZE_Y };

	return mapPos;
}

// ��ڲ԰�X�e�[�W����
bool IsPass(XY pos)
{
	bool ret = true;
	int mapNo;
	XY mapIndex;

	mapIndex = MapPosToIndex(pos);
	mapNo = mapData[mapIndex.y][mapIndex.x];

	switch (mapNo) {
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
		ret = false;
		break;
	}
	return ret;
}

/*
XY MovedIndexPos(XY pos, MOVE_DIR dir)
{
	XY mapIndex;
	mapIndex = MapPosToIndex(pos);
}
*/



