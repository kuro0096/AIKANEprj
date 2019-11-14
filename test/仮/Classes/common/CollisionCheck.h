#pragma once
#include "cocos2d.h"
#include "ActionMng.h"

USING_NS_CC;

struct CollisionCheck
{
	bool operator()(cocos2d::Sprite& sprite, ActData& data);	// “–‚½‚è”»’è—pŠÖ”(sprite‚Ìî•ñ,1‚Â–Ú‚ÌµÌ¾¯ÄÀ•W,2‚Â–Ú‚ÌµÌ¾¯ÄÀ•W,ˆÚ“®—Ê)
};