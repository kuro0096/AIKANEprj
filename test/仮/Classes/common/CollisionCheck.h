#pragma once
#include "cocos2d.h"

USING_NS_CC;

struct CollisionCheck
{
	bool operator()(Sprite* sprite, Vec2 offsetSpot1, Vec2 offsetSpot2, Vec2 move);	// 当たり判定用関数(spriteの情報,1つ目のｵﾌｾｯﾄ座標,2つ目のｵﾌｾｯﾄ座標,移動量)
};