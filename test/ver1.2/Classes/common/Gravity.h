#pragma once
#include <cocos2d.h>
#include "ActionMng.h"

constexpr float framePerSecond = 0.5f;

struct Gravity
{
	bool operator()(cocos2d::Sprite& sprite, ActData& data)
	{
		sprite.setPositionY(sprite.getPositionY() + (data.move.y * framePerSecond));
		return true;
	};
};
