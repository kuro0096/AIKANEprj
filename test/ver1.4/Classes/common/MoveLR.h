#pragma once
#include <cocos2d.h>
#include "ActionMng.h"
#include "Unit/Player.h"

struct MoveLR
{
	// ¶‰EˆÚ“®—pŠÖ”
	bool operator()(cocos2d::Sprite& sprite,ActData& data)
	{
		// —‰ºˆÈŠO‚¾‚Á‚½‚ç‘–‚èó‘Ô‚É
		if (((Player&)sprite).getActID() != ACT_ID::FALL)
		{
			((Player&)sprite).setActID(ACT_ID::RUN);
		}
		sprite.setPositionX(sprite.getPositionX() + data.move.x);
		return true;
	};
};

