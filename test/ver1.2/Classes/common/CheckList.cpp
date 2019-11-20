#include "CheckList.h"
#include "Unit/Player.h"

// Ø½Ä‚ğÁª¯¸‚µ‚Ä“®‚¢‚Ä‚¢‚¢‚©‚ğŠm”F‚·‚é‚½‚ß‚ÌŠÖ”
bool CheckList::operator()(cocos2d::Sprite & sprite, ActData & data)
{
	ACT_ID actID;
	actID = ((Player&)sprite).getActID();
	for (auto black : data.blackList)
	{
		if (actID == black)
		{
			return false;
		}
	}
	for (auto white : data.whiteList)
	{
		if (actID == white)
		{
			return true;
		}
	}
	return true;
}
