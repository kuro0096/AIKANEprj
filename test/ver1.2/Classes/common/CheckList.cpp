#include "CheckList.h"
#include "Unit/Player.h"

// ؽĂ��������ē����Ă��������m�F���邽�߂̊֐�
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
