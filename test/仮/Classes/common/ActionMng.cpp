#pragma execution_character_set("utf-8")
#include "ActionMng.h"
#include "MoveLR.h"
#include "CollisionCheck.h"

Vec2 visibleSize = Director::getInstance()->getVisibleSize();

ActionMng::ActionMng()
{
}

ActionMng::~ActionMng()
{
}

// �ړ�����(���W,�̾�č��W1,�̾�č��W2,�ړ���)
void ActionMng::moveCtrl(Sprite* sp, Vec2 offset1, Vec2 offset2, Vec2 speed)
{
	//// �ړ�����
	//if (pos + speed + limit <= 0 || pos + speed + limit >= visibleSize)
	//{
	//	sp->setPosition(sp->getPosition() + speed + limit);
	//}
	// ���ݍ��W�Ƶ̾�č��W����CollisionCheck�ɓn��
	/*if (!CollisionCheck(sp->getPosition() + speed, offset1, offset2))
	{
		sp->setPosition(sp->getPosition() + speed);
	}*/
}

void ActionMng::AddAct(std::string actName,ActData& data)
{ 
	if (actName == "���ړ�" || actName == "�E�ړ�")
	{
		m_actData.try_emplace(actName,std::move(data));
		m_actData[actName].act.emplace_back(CollisionCheck());
		m_actData[actName].runAct = MoveLR();
	}
}

void ActionMng::ActRun(Sprite & sprite,std::string actName)
{
	m_actData[actName].runAct(sprite, m_actData[actName]);
}
