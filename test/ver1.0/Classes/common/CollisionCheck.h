#pragma once
#include "cocos2d.h"

USING_NS_CC;

struct CollisionCheck
{
	bool operator()(Sprite* sprite, Vec2 rect1, Vec2 rect2, Vec2 move);	// �����蔻��p�֐�(sprite�̏��,1�ڂ̵̾�č��W,2�ڂ̵̾�č��W,�ړ���)
};