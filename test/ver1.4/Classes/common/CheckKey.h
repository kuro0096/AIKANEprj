#pragma once
#include "cocos2d.h"
#include "ActionMng.h"

struct CheckKey
{
	// ���̓��͏��𔻒肷�邽�߂̊֐�
	bool operator()(cocos2d::Sprite& sprite, ActData& data);
};

