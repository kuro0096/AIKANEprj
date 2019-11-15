#pragma execution_character_set("utf-8")
#include "ActionMng.h"
#include "MoveLR.h"
#include "CollisionCheck.h"
#include "CheckKey.h"

Vec2 visibleSize = Director::getInstance()->getVisibleSize();

ActionMng::ActionMng(cocos2d::Sprite* sp) : m_sprite(sp)
{
}

ActionMng::~ActionMng()
{
}

void ActionMng::AddAct(std::string actName,ActData& data)
{ 
	if (actName == "Left" || actName == "Right")
	{
		m_actData.emplace(actName,std::move(data));
		m_actData[actName].checkList.emplace_back(CheckKey());
		m_actData[actName].checkList.emplace_back(CollisionCheck());
		m_actData[actName].runAct = MoveLR();
	}
	if (actName == "ƒWƒƒƒ“ƒv’†")
	{
		
	}
	if (actName == "—Ž‰º’†")
	{

	}
}

void ActionMng::ActRun()
{
	for (auto data : m_actData)
	{
		for (auto check : data.second.checkList)
		{
			if (check(*m_sprite, data.second) && m_actData[data.first].runAct != nullptr)
			{
				m_actData[data.first].runAct(*m_sprite, m_actData[data.first]);
			}
		}
	}
}
