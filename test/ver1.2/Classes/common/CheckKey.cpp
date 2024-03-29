#include "CheckKey.h"
#include "Unit/Player.h"

// ｷｰの入力情報を判定するための関数
bool CheckKey::operator()(cocos2d::Sprite & sprite, ActData & data)
{
	inputMap input;
	input[data.dir] = data.state;
	// 入力されたｷｰ情報とActDataに登録されているｷｰ情報が同じだったらtrueを返す
	if (((Player&)sprite).getInput()->GetState(data.dir) == input[data.dir])
	{
		return true;
	}
	else
	{
		return false;
	}
}