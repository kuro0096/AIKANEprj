#pragma once
#include <cocos2d.h>
#include "ActionMng.h"

struct MoveJumping
{
	// �ެ��ߒ������p�֐�
	bool operator()(cocos2d::Sprite& sprite, ActData& data);
};

