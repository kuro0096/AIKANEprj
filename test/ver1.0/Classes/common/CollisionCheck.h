#pragma once
#include "cocos2d.h"

USING_NS_CC;

struct CollisionCheck
{
	bool operator()(Sprite* sprite, Vec2 rect1, Vec2 rect2, Vec2 move);	// 当たり判定用関数(spriteの情報,1つ目のｵﾌｾｯﾄ座標,2つ目のｵﾌｾｯﾄ座標,移動量)
};