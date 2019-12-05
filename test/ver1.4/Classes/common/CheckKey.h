#pragma once
#include "cocos2d.h"
#include "ActionMng.h"

struct CheckKey
{
	// ·°‚Ì“ü—Íî•ñ‚ğ”»’è‚·‚é‚½‚ß‚ÌŠÖ”
	bool operator()(cocos2d::Sprite& sprite, ActData& data);
};

