#pragma once
#include "cocos2d.h"
#include "ActionMng.h"

struct CheckList
{
	// ؽĂ��������ē����Ă��������m�F���邽�߂̊֐�
	bool operator()(cocos2d::Sprite& sprite, ActData& data);
};