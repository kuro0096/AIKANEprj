#include "MoveJump.h"
#include "Gravity.h"
#include "Unit/Player.h"

// ｼﾞｬﾝﾌﾟ開始時用関数
bool MoveJump::operator()(cocos2d::Sprite & sprite, ActData & data)
{
	((Player&)sprite).setActID(ACT_ID::JUMP);
	((Player&)sprite).setJumpCnt(0);
	return true;
}
