#pragma once
#include <cocos2d.h>
#include "ActionMng.h"

struct MoveLR
{
	// ¶‰EˆÚ“®—pŠÖ”
	bool operator()(cocos2d::Sprite& sprite,ActData& data)
	{
		sprite.setPositionX(sprite.getPositionX() + data.move.x);
		return true;
	};
};

