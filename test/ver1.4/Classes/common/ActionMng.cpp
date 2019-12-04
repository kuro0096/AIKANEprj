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

// ｱｸｼｮﾝﾃﾞｰﾀの追加
void ActionMng::AddAct(std::string actName,ActData& data)
{ 
	// 名前によって登録するものを変える
	// 待機状態
	if (actName == "Idle")
	{
		m_actData.emplace(actName, std::move(data));
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].checkModule.emplace_back(CheckList());
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].runAct = IdleState();
	}
	// 左移動 || 右移動
	if (actName == "Left" || actName == "Right")
	{
		m_actData.emplace(actName,std::move(data));
		m_actData[actName].checkModule.emplace_back(CheckList());
		m_actData[actName].checkModule.emplace_back(CheckKey());
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].runAct = MoveLR();
	}
	// ｼﾞｬﾝﾌﾟ開始時
	if (actName == "Jump")
	{
		m_actData.emplace(actName, std::move(data));
		m_actData[actName].checkModule.emplace_back(CheckList());
		m_actData[actName].checkModule.emplace_back(CheckKey());
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].runAct = MoveJump();
	}
	// ｼﾞｬﾝﾌﾟ中
	if (actName == "Jumping")
	{
		m_actData.emplace(actName, std::move(data));
		m_actData[actName].checkModule.emplace_back(CheckList());
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].runAct = MoveJumping();
	}
	// 落下
	if (actName == "Fall")
	{
		m_actData.emplace(actName, std::move(data));
		m_actData[actName].checkModule.emplace_back(CheckList());
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].runAct = Gravity();
	}
}

// ｱｸｼｮﾝﾃﾞｰﾀを処理する関数
void ActionMng::ActRun()
{
	// ﾁｪｯｸﾓｼﾞｭｰﾙの中身を確認
	auto CheckModule = [&](std::pair<std::string, ActData> data)
	{
		for (auto check : data.second.checkModule)
		{
			// 実行不可だったらfalse
			if (!check(*m_sprite, data.second))
			{
				return false;
			}
		}
		// 実行可能だったらtrueを返す
		return true;
	};

	for (auto data : m_actData)
	{
		// ﾁｪｯｸﾓｼﾞｭｰﾙを確認
		if (CheckModule(data))
		{
			m_actID = data.second.actID;
			m_actDir = data.second.dir;
			// 実行するｱｸｼｮﾝ情報が入っていたらｱｸｼｮﾝを実行
			if(data.second.runAct != nullptr)
			{ 
				data.second.runAct(*m_sprite, data.second);
			}
		}
	}
}
