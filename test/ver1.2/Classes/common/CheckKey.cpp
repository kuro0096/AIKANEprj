#include "CheckKey.h"
#include "Unit/Player.h"

// ·°‚Ì“ü—Íî•ñ‚ğ”»’è‚·‚é‚½‚ß‚ÌŠÖ”
bool CheckKey::operator()(cocos2d::Sprite & sprite, ActData & data)
{
	inputMap input;
	input[data.dir] = data.state;
	if (((Player&)sprite).getInput()->GetState(data.dir) == input[data.dir])
	{
		return true;
	}
	else
	{
		return false;
	}
}