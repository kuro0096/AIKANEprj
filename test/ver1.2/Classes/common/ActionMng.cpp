#pragma execution_character_set("utf-8")
#include "ActionMng.h"
#include "common/AnimMng.h"
#include "CollisionCheck.h"
#include "CheckKey.h"
#include "MoveLR.h"
#include "MoveJump.h"
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
	if (actName == "左移動" || actName == "右移動")
	{
		m_actData.emplace(actName,std::move(data));
		m_actData[actName].checkModule.emplace_back(CheckKey());
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].runAct = MoveLR();
	}
	if (actName == "ジャンプ開始")
	{
		m_actData.emplace(actName, std::move(data));
		m_actData[actName].checkModule.emplace_back(CheckKey());
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].runAct = MoveJump();
	}
	if (actName == "落下中")
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
				m_actID = data.second.actID;
			}
		}
		cnt = 0;
	}
}

void ActionMng::AnimUpdata(ACTID id, std::string move)
{
	if (id == ACTID::RUN)
	{
		lpAnimMng.ActAnim(m_sprite, "player", "run", true);
		m_sprite->runAction(FlipX::create(move == "左移動"? true:false));
	}
	if (id == ACTID::JUMP)
	{
		lpAnimMng.ActAnim(m_sprite, "player", "jump", false);
	}
}
