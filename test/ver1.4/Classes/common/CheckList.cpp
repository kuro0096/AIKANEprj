#include "CheckList.h"
#include "Unit/Player.h"

// ؽĂ��������ē����Ă��������m�F���邽�߂̊֐�
bool CheckList::operator()(cocos2d::Sprite & sprite, ActData & data)
{
	// �ް��̒��g�����Ď��s���Ă������̂�������true
	for (auto white : data.whiteList)
	{
		if (((Player&)sprite).getActID() == white)
		{
			return true;
		}
	}
	// �ް��̒��g�����Ď��s���Ă͂����Ȃ����̂�������false
	for (auto black : data.blackList)
	{
		if (((Player&)sprite).getActID() == black)
		{
			return false;
		}
	}
	// ���s���Ă͂����Ȃ����̂��Ȃ�������true��Ԃ�
	if (data.blackList.size() <= 0)
	{
		return true;
	}
	return true;
}
