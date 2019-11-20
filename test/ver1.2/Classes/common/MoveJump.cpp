#include "MoveJump.h"

// ｼﾞｬﾝﾌﾟ処理用関数
bool MoveJump::operator()(cocos2d::Sprite & sprite, ActData & data)
{
	if (data.move.y < 1.0f)
	{
		sprite.setPositionY(sprite.getPositionY() + data.move.y);
		data.move.y += 0.1f;
	}
	data.move.y = 0.0f;
	return true;
}
