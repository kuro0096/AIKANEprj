#pragma execution_character_set("utf-8")
#include "CommonInclude.h"

ActionMng::ActionMng(cocos2d::Sprite* sp)
{
	m_sprite = sp;
	m_actID = ACT_ID::IDLE;
}

ActionMng::~ActionMng()
{
}

// ±∏ºÆ›√ﬁ∞¿ÇÃí«â¡
void ActionMng::AddAct(std::string actName,ActData& data)
{ 
	// ñºëOÇ…ÇÊÇ¡Çƒìoò^Ç∑ÇÈÇ‡ÇÃÇïœÇ¶ÇÈ
	if (actName == "Idle")
	{
		m_actData.emplace(actName, std::move(data));
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].checkModule.emplace_back(CheckList());
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].runAct = IdleState();
	}
	if (actName == "Left" || actName == "Right")
	{
		m_actData.emplace(actName,std::move(data));
		m_actData[actName].checkModule.emplace_back(CheckList());
		m_actData[actName].checkModule.emplace_back(CheckKey());
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].runAct = MoveLR();
	}
	if (actName == "Jump")
	{
		m_actData.emplace(actName, std::move(data));
		m_actData[actName].checkModule.emplace_back(CheckList());
		m_actData[actName].checkModule.emplace_back(CheckKey());
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
	}
	if (actName == "Jumping")
	{
		m_actData.emplace(actName, std::move(data));
		m_actData[actName].checkModule.emplace_back(CheckList());
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].runAct = MoveJump();
	}
	if (actName == "Fall")
	{
		m_actData.emplace(actName, std::move(data));
		m_actData[actName].checkModule.emplace_back(CheckList());
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].runAct = Gravity();
	}
}

// ±∏ºÆ›√ﬁ∞¿ÇèàóùÇ∑ÇÈä÷êî
void ActionMng::ActRun()
{
	auto checkModule = [&](std::pair<std::string, ActData> data)
	{
		for (auto check : data.second.checkModule)
		{
			if (!check(*m_sprite, data.second))
			{
				return false;
			}
		}
		return true;
	};

	for (auto data : m_actData)
	{
		if (checkModule(data))
		{
			m_actID = data.second.actID;
			if(data.second.runAct != nullptr)
			{ 
				data.second.runAct(*m_sprite, data.second);
			}
		}
	}
}
