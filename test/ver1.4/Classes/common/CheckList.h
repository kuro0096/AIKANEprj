#pragma once
#include "cocos2d.h"
#include "ActionMng.h"

struct CheckList
{
	// ﾘｽﾄをﾁｪｯｸして動いていいかを確認するための関数
	bool operator()(cocos2d::Sprite& sprite, ActData& data);
};