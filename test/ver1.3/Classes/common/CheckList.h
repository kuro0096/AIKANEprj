#pragma once
#include "cocos2d.h"
#include "ActionMng.h"

struct CheckList
{
	bool operator()(cocos2d::Sprite& sprite, ActData& data);	// Ø½Ä‚ğÁª¯¸‚µ‚Ä“®‚¢‚Ä‚¢‚¢‚©‚ğŠm”F‚·‚é‚½‚ß‚ÌŠÖ”
};