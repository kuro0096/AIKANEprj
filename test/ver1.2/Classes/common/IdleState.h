#pragma once
#include <cocos2d.h>
#include "ActionMng.h"

struct IdleState
{
	bool operator()(cocos2d::Sprite& sprite, ActData& data)
	{
		return true;
	};
};