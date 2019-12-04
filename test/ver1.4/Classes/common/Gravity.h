#pragma once
#include <cocos2d.h>
#include "ActionMng.h"

constexpr float framePerSecond = 0.5f;

struct Gravity
{
	// d—Íˆ——pŠÖ”
	bool operator()(cocos2d::Sprite& sprite, ActData& data);
};
