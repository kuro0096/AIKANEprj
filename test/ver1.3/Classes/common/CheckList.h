#pragma once
#include "cocos2d.h"
#include "ActionMng.h"

struct CheckList
{
	bool operator()(cocos2d::Sprite& sprite, ActData& data);	// ؽĂ��������ē����Ă��������m�F���邽�߂̊֐�
};