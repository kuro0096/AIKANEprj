#include "MoveJump.h"
#include "Gravity.h"
#include "Unit/Player.h"

// �ެ��ߏ����p�֐�
bool MoveJump::operator()(cocos2d::Sprite & sprite, ActData & data)
{
	((Player&)sprite).setActID(ACT_ID::JUMP);
	((Player&)sprite).setJumpCnt(0);
	return true;
}
