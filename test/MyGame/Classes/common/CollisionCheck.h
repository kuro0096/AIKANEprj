#pragma once
#include "cocos2d.h"

USING_NS_CC;

struct CollisionCheck
{
	bool operator()(Sprite* sprite, Vec2 rect1, Vec2 rect2, Vec2 move);
};