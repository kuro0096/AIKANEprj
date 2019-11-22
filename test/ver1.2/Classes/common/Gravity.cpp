#include "Gravity.h"
#include "Unit/Player.h"

bool Gravity::operator()(cocos2d::Sprite & sprite, ActData & data)
{
	bool checkflag = true;
	for (auto check : data.checkModule)
	{
		if (!check(sprite, data))
		{
			checkflag = false;
			((Player&)sprite).setActID(ACT_ID::IDLE);
		}
	}
	if(checkflag)
	{
		sprite.setPositionY(sprite.getPositionY() + (data.move.y * framePerSecond));
	}
	return true;
}