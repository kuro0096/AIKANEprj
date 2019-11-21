#include "CheckList.h"
#include "Unit/Player.h"

// ﾘｽﾄをﾁｪｯｸして動いていいかを確認するための関数
bool CheckList::operator()(cocos2d::Sprite & sprite, ActData & data)
{
	for (auto white : data.whiteList)
	{
		if (((Player&)sprite).getActID() == white)
		{
			return true;
		}
	}
	for (auto black : data.blackList)
	{
		if (((Player&)sprite).getActID() == black)
		{
			return false;
		}
	}
	if (data.blackList.size() <= 0)
	{
		return true;
	}
	return true;
}
