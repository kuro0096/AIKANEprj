#pragma execution_character_set("utf-8")
#include "ActionMng.h"
#include "CollisionCheck.h"
#include "CheckKey.h"
#include "MoveLR.h"
#include "Gravity.h"

Vec2 visibleSize = Director::getInstance()->getVisibleSize();

ActionMng::ActionMng(cocos2d::Sprite* sp) : m_sprite(sp)
{
}

ActionMng::~ActionMng()
{
}

void ActionMng::AddAct(std::string actName,ActData& data)
{ 
	if (actName == "ç∂à⁄ìÆ" || actName == "âEà⁄ìÆ")
	{
		m_actData.emplace(actName,std::move(data));
		m_actData[actName].checkModule.emplace_back(CheckKey());
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].runAct = MoveLR();
	}
	if (actName == "ÉWÉÉÉìÉvíÜ")
	{
		/*m_actData.emplace(actName, std::move(data));
		m_actData[actName].checkModule.emplace_back(CheckKey());
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].runAct = MoveLR();*/
	}
	if (actName == "óéâ∫íÜ")
	{
		m_actData.emplace(actName, std::move(data));
		m_actData[actName].checkModule.emplace_back(CheckKey());
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].runAct = Gravity();
	}
}

void ActionMng::ActRun()
{
	int cnt = 0;
	for (auto data : m_actData)
	{
		for (auto check : data.second.checkModule)
		{
			if (check(*m_sprite, data.second) && data.second.runAct != nullptr)
			{
				cnt++;
			}
			if (data.second.checkModule.size() == cnt)
			{
				data.second.runAct(*m_sprite, data.second);
			}
		}
		cnt = 0;
	}
}
