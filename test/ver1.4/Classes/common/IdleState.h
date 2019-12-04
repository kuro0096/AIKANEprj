#pragma once
#include <cocos2d.h>
#include "ActionMng.h"
#include "Unit/Player.h"

struct IdleState
{
	bool operator()(cocos2d::Sprite& sprite, ActData& data)
	{
		((Player&)sprite).setActID(ACT_ID::IDLE);
		return true;
	};
};