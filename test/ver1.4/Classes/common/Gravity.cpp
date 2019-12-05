#include "Gravity.h"
#include "Unit/Player.h"

// d—Íˆ——pŠÖ”
bool Gravity::operator()(cocos2d::Sprite & sprite, ActData & data)
{
	((Player&)sprite).setActID(ACT_ID::FALL);
	sprite.setPositionY(sprite.getPositionY() + (data.move.y * framePerSecond));
	return true;
}