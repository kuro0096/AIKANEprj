#pragma once
#include "cocos2d.h"
#include "ActionMng.h"

USING_NS_CC;

struct CollisionCheck
{
	// �����蔻��p�֐�
	bool operator()(cocos2d::Sprite& sprite, ActData& data);
};