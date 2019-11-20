#pragma execution_character_set("utf-8")
#include "CommonInclude.h"

ActionMng::ActionMng(cocos2d::Sprite* sp)
{
	m_sprite = sp;
}

ActionMng::~ActionMng()
{
}

// ｱｸｼｮﾝﾃﾞｰﾀの追加
void ActionMng::AddAct(std::string actName,ActData& data)
{ 
	// 名前によって登録するものを変える
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
		m_actData[actName].checkModule.emplace_back(CheckList());
		m_actData[actName].checkModule.emplace_back(CheckKey());
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].runAct = MoveJump();
	}
	if (actName == "落下")
	{
		m_actData.emplace(actName, std::move(data));
		m_actData[actName].checkModule.emplace_back(CheckKey());
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].runAct = Gravity();
	}
}

// ｱｸｼｮﾝﾃﾞｰﾀを処理する関数
void ActionMng::ActRun()
{
	auto checkModule = [&](auto data)
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
			data.second.runAct(*m_sprite, data.second);
			m_actID = data.second.actID;
		}
	}
}
