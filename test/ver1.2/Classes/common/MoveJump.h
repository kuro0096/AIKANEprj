#pragma once
#include <cocos2d.h>
#include "ActionMng.h"

struct MoveJump
{
	bool operator()(cocos2d::Sprite& sprite, ActData& data);	// ｼﾞｬﾝﾌﾟ処理用関数
};

