#pragma once
#include <cocos2d.h>
#include "ActionMng.h"

struct MoveJump
{
	// ｼﾞｬﾝﾌﾟ開始時用関数
	bool operator()(cocos2d::Sprite& sprite, ActData& data);
};

