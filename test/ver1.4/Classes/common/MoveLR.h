#pragma once
#include <cocos2d.h>
#include "ActionMng.h"
#include "Unit/Player.h"

struct MoveLR
{
	// 左右移動用関数
	bool operator()(cocos2d::Sprite& sprite,ActData& data)
	{
		((Player&)sprite).setActID(ACT_ID::RUN);
		sprite.setPositionX(sprite.getPositionX() + data.move.x);
		return true;
	};
};

