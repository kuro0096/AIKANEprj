#pragma once
#include "cocos2d.h"
#include "ActionMng.h"

struct CheckList
{
	bool operator()(cocos2d::Sprite& sprite, ActData& data);	// ﾘｽﾄをﾁｪｯｸして動いていいかを確認するための関数
};