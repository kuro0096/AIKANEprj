#include "Gravity.h"
#include "Unit/Player.h"

// �d�͏����p�֐�
bool Gravity::operator()(cocos2d::Sprite & sprite, ActData & data)
{
	((Player&)sprite).setActID(ACT_ID::FALL);
	sprite.setPositionY(sprite.getPositionY() + (data.move.y * framePerSecond));
	return true;
}