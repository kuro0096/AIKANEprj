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
	if (actName == "左移動" || actName == "右移動")
	{
		m_actData.insert(std::make_pair(actName,std::move(data)));
		m_actData[actName].act.emplace_back(CollisionCheck());
		m_actData[actName].act.emplace_back(CheckKey());
		m_actData[actName].runAct = MoveLR();
	}
}

void ActionMng::ActRun()
{
	for (auto data : m_actData)
	{
		for (auto check : data.second.act)
		{
			if (check(*m_sprite, data.second))
			{
				m_actData[data.first].runAct(*m_sprite, m_actData[data.first]);
			}
			else
			{
				break;
			}
		}
	}
}
