#pragma once
#include "cocos2d.h"
#include "ActionMng.h"

struct CheckKey
{
	bool operator()(cocos2d::Sprite& sprite, ActData& data);
};

