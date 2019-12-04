#include "CheckKey.h"
#include "Unit/Player.h"

// ���̓��͏��𔻒肷�邽�߂̊֐�
bool CheckKey::operator()(cocos2d::Sprite & sprite, ActData & data)
{
	inputMap input;
	input[data.dir] = data.state;
	// ���͂��ꂽ������ActData�ɓo�^����Ă��鷰��񂪓�����������true��Ԃ�
	if (((Player&)sprite).getInput()->GetState(data.dir) == input[data.dir])
	{
		return true;
	}
	else
	{
		return false;
	}
}