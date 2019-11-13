#pragma once
#include "cocos2d.h"

USING_NS_CC;

struct CollisionCheck
{
	bool operator()(Sprite* sprite, Vec2 offsetSpot1, Vec2 offsetSpot2, Vec2 move);	// “–‚½‚è”»’è—pŠÖ”(sprite‚Ìî•ñ,1‚Â–Ú‚ÌµÌ¾¯ÄÀ•W,2‚Â–Ú‚ÌµÌ¾¯ÄÀ•W,ˆÚ“®—Ê)
};