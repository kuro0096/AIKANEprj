#pragma once
#include "cocos2d.h"
#include "ActionMng.h"

USING_NS_CC;

struct CollisionCheck
{
	// 当たり判定用関数
	bool operator()(cocos2d::Sprite& sprite, ActData& data);
};