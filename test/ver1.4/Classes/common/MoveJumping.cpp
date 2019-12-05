#include "MoveJumping.h"
#include "Gravity.h"
#include "Unit/Player.h"

// ｼﾞｬﾝﾌﾟ中処理用関数
bool MoveJumping::operator()(cocos2d::Sprite & sprite, ActData & data)
{
	if (((Player&)sprite).getJumpCnt() == 30)
	{
		((Player&)sprite).setActID(ACT_ID::FALL);
		return true;
	}
	if (((Player&)sprite).getJumpCnt() > 1)
	{
		((Player&)sprite).setActID(ACT_ID::JUMPING);
	}
	((Player&)sprite).setJumpCnt(((Player&)sprite).getJumpCnt()+1);
	sprite.setPositionY(sprite.getPositionY() + 6.0f);
	return true;
}
