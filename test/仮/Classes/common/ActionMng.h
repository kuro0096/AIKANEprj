#pragma once
#include <cocos2d.h>
#include <input/input.h>

USING_NS_CC;

class ActData;

using actFunc = std::function<bool(std::string, ActData&)>;

struct ActData
{
	actFunc runAct;
	std::list<actFunc>act;
	DIR dir;
	INPUT_STATE state;
	COMAND comand;
	cocos2d::Point move;
	std::pair<Vec2, Vec2>colOffset;
};

class ActionMng
{
public:
	ActionMng();
	~ActionMng();

	void moveCtrl(Sprite* sp, Vec2 offset1, Vec2 offset2, Vec2 speed);	// �ړ�����(�Ώ�,�̾�č��W1,�̾�č��W2,�ړ���)
	bool CollisionCheck(Vec2 pos, Vec2 offsetSpot1, Vec2 offsetSpot2);	// �����蔻��p�֐�(sprite�̍��W,1�ڂ̵̾�č��W,2�ڂ̵̾�č��W)

	void AddAct(std::string actName,ActData& data);

private:
	std::map<std::string, ActData> m_actData;
};

