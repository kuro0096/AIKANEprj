#pragma once
#include <cocos2d.h>
#include "ActionMng.h"

struct MoveLR
{
	bool operator()(cocos2d::Sprite& sprite,ActData& data)
	{
		sprite.setPosition(sprite.getPosition() + data.move);
		return true;
	};
};

