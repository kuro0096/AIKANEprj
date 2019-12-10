#pragma once
#include "cocos2d.h"
#include "ActionMng.h"

struct CheckList
{
	// Ø½Ä‚ğÁª¯¸‚µ‚Ä“®‚¢‚Ä‚¢‚¢‚©‚ğŠm”F‚·‚é‚½‚ß‚ÌŠÖ”
	bool operator()(cocos2d::Sprite& sprite, ActData& data);
};