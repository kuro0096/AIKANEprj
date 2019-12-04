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

// ������ް��̒ǉ�
void ActionMng::AddAct(std::string actName,ActData& data)
{ 
	// ���O�ɂ���ēo�^������̂�ς���
	// �ҋ@���
	if (actName == "Idle")
	{
		m_actData.emplace(actName, std::move(data));
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].checkModule.emplace_back(CheckList());
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].runAct = IdleState();
	}
	// ���ړ� || �E�ړ�
	if (actName == "Left" || actName == "Right")
	{
		m_actData.emplace(actName,std::move(data));
		m_actData[actName].checkModule.emplace_back(CheckList());
		m_actData[actName].checkModule.emplace_back(CheckKey());
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].runAct = MoveLR();
	}
	// �ެ��ߊJ�n��
	if (actName == "Jump")
	{
		m_actData.emplace(actName, std::move(data));
		m_actData[actName].checkModule.emplace_back(CheckList());
		m_actData[actName].checkModule.emplace_back(CheckKey());
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].runAct = MoveJump();
	}
	// �ެ��ߒ�
	if (actName == "Jumping")
	{
		m_actData.emplace(actName, std::move(data));
		m_actData[actName].checkModule.emplace_back(CheckList());
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].runAct = MoveJumping();
	}
	// ����
	if (actName == "Fall")
	{
		m_actData.emplace(actName, std::move(data));
		m_actData[actName].checkModule.emplace_back(CheckList());
		m_actData[actName].checkModule.emplace_back(CollisionCheck());
		m_actData[actName].runAct = Gravity();
	}
}

// ������ް�����������֐�
void ActionMng::ActRun()
{
	// ����Ӽޭ�ق̒��g���m�F
	auto CheckModule = [&](std::pair<std::string, ActData> data)
	{
		for (auto check : data.second.checkModule)
		{
			// ���s�s��������false
			if (!check(*m_sprite, data.second))
			{
				return false;
			}
		}
		// ���s�\��������true��Ԃ�
		return true;
	};

	for (auto data : m_actData)
	{
		// ����Ӽޭ�ق��m�F
		if (CheckModule(data))
		{
			m_actID = data.second.actID;
			m_actDir = data.second.dir;
			// ���s���鱸��ݏ�񂪓����Ă����籸��݂����s
			if(data.second.runAct != nullptr)
			{ 
				data.second.runAct(*m_sprite, data.second);
			}
		}
	}
}
