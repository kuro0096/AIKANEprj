#include "CheckKey.h"
#include "Unit/Player.h"

// ·°‚Ì“ü—Íî•ñ‚ğ”»’è‚·‚é‚½‚ß‚ÌŠÖ”
bool CheckKey::operator()(cocos2d::Sprite & sprite, ActData & data)
{
	inputMap input;
	input[data.dir] = data.state;
	// “ü—Í‚³‚ê‚½·°î•ñ‚ÆActData‚É“o˜^‚³‚ê‚Ä‚¢‚é·°î•ñ‚ª“¯‚¶‚¾‚Á‚½‚çtrue‚ğ•Ô‚·
	if (((Player&)sprite).getInput()->GetState(data.dir) == input[data.dir])
	{
		return true;
	}
	else
	{
		return false;
	}
}