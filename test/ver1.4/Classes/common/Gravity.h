#pragma once
#include <cocos2d.h>
#include "ActionMng.h"

constexpr float framePerSecond = 0.5f;

struct Gravity
{
	// 重力処理用関数
	bool operator()(cocos2d::Sprite& sprite, ActData& data);
};
