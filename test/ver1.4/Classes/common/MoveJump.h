#pragma once
#include <cocos2d.h>
#include "ActionMng.h"

struct MoveJump
{
	// �ެ��ߊJ�n���p�֐�
	bool operator()(cocos2d::Sprite& sprite, ActData& data);
};

