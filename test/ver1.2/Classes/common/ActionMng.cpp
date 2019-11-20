#pragma execution_character_set("utf-8")
#include "CommonInclude.h"

ActionMng::ActionMng(cocos2d::Sprite* sp)
{
	m_sprite = sp;
}

ActionMng::~ActionMng()
{
}

// ������ް��̒ǉ�
void ActionMng::AddAct(std::string actName,ActData& data)
{ 
	// ���O�ɂ���ēo�^������̂�ς���
	if (actName == "���ړ�" || actName == "�E�ړ�")
	{
		m_actData.emplace(actName,std::move(data));
		m_actData[actName].checkModule.emplace_back(CheckKey());
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].runAct = MoveLR();
	}
	if (actName == "�W�����v�J�n")
	{
		m_actData.emplace(actName, std::move(data));
		m_actData[actName].checkModule.emplace_back(CheckList());
		m_actData[actName].checkModule.emplace_back(CheckKey());
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].runAct = MoveJump();
	}
	if (actName == "����")
	{
		m_actData.emplace(actName, std::move(data));
		m_actData[actName].checkModule.emplace_back(CheckKey());
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].runAct = Gravity();
	}
}

// ������ް�����������֐�
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
