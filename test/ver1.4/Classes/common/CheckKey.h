#pragma once
#include "cocos2d.h"
#include "ActionMng.h"

struct CheckKey
{
	// ｷｰの入力情報を判定するための関数
	bool operator()(cocos2d::Sprite& sprite, ActData& data);
};

