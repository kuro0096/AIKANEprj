#pragma once
#include "cocos2d.h"
#include "ActionMng.h"

USING_NS_CC;

struct CollisionCheck
{
	bool operator()(cocos2d::Sprite& sprite, ActData& data);	// 当たり判定用関数
};