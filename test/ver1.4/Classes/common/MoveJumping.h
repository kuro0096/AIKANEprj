#pragma once
#include <cocos2d.h>
#include "ActionMng.h"

struct MoveJumping
{
	// ｼﾞｬﾝﾌﾟ中処理用関数
	bool operator()(cocos2d::Sprite& sprite, ActData& data);
};

