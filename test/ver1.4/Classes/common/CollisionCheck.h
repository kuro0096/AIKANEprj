#pragma once
#include "cocos2d.h"
#include "ActionMng.h"

USING_NS_CC;

struct CollisionCheck
{
	// “–‚½‚è”»’è—pŠÖ”
	bool operator()(cocos2d::Sprite& sprite, ActData& data);
};