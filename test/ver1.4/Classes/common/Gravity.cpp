#include "Gravity.h"
#include "Unit/Player.h"

// 重力処理用関数
bool Gravity::operator()(cocos2d::Sprite & sprite, ActData & data)
{
	((Player&)sprite).setActID(ACT_ID::FALL);
	sprite.setPositionY(sprite.getPositionY() + (data.move.y * framePerSecond));
	return true;
}