#pragma once
#include <cocos2d.h>
#include <input/input.h>

USING_NS_CC;

struct ActData
{
	DIR dir;

};

class ActionMng
{
public:
	ActionMng();
	~ActionMng();

	bool CollisionCheck(Vec2 pos, Vec2 offsetSpot1, Vec2 offsetSpot2);	// �����蔻��p�֐�(sprite�̍��W,1�ڂ̵̾�č��W,2�ڂ̵̾�č��W)
	Vec2 moveCtrl (Vec2 pos,Vec2 offset1,Vec2 offset2,Vec2 speed);		// �ړ������p�֐�(���W�ƈړ��ʂ𑫂����l,�̾�č��W1,�̾�č��W2,�ړ�����)

	void AddAct(const std::string& actName, const ActData& data);

private:
	std::map<std::string, ActData> m_act;
};

