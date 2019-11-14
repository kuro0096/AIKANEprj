#pragma execution_character_set("utf-8")
#include "Player.h"
#include "_Debug/_DebugConOut.h"
#include "common/AnimMng.h"
#include "input/inputKey.h"
#include "input/inputTouch.h"

USING_NS_CC;

Player * Player::createPlayer()
{
	return Player::create();
}

Player::Player()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	m_input = new(inputKey);
#else
	m_input = new(inputTouch);
#endif
	// ���͏��̓o�^
	m_input->Init(this);
	Init();
}

Player::~Player()
{
}

// �ϐ����Ұ��݂̏�����
bool Player::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// �������W
	this->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + this->getContentSize().height + 20));
	// �ϐ�������
	m_jumpFlag = false;

	// offset������
	// ����,����
	m_offset[DIR::LEFT] = { Vec2(-offsetX, bustOffsetY),Vec2(-offsetX,-legOffsetY) };
	// �E��,�E��
	m_offset[DIR::RIGHT] = { Vec2(offsetX, bustOffsetY),Vec2(offsetX,-legOffsetY) };
	// ����,�E��
	m_offset[DIR::UP] = { Vec2(-offsetX, bustOffsetY),Vec2(offsetX,bustOffsetY) };
	// ����,�E��
	m_offset[DIR::DOWN] = { Vec2(-offsetX, -legOffsetY),Vec2(offsetX,-legOffsetY) };

	// �ړ��ʏ�����
	m_speed[static_cast<size_t>(DIR::LEFT)] = { - playerSpeed ,0 };
	m_speed[static_cast<size_t>(DIR::RIGHT)] = { playerSpeed ,0 };
	m_speed[static_cast<size_t>(DIR::UP)] = { 0 ,playerSpeed };
	m_speed[static_cast<size_t>(DIR::DOWN)] = { 0 ,-playerSpeed };

	m_action = new(ActionMng);

	ActData data;
	data.actID = ACTID::RUN;
	data.dir = DIR::LEFT;
	data.move = { -2 ,0 };
	data.state = INPUT_STATE::ON;
	data.colOffset = { Vec2(-24,35) , Vec2(-24,-65) };
	m_action->AddAct("���ړ�", data);

	// ��Ұ��݂̓o�^
	lpAnimMng.AnimCacheInit("player", "idle", 4, 0.3f);
	lpAnimMng.AnimCacheInit("player", "run", 10, 0.1f);
	lpAnimMng.AnimCacheInit("player", "jump", 6, 0.1f);

	// �ŏ��͑҂���Ԃ̱�Ұ���
	lpAnimMng.ActAnim(this,"player","idle", true);

	this->scheduleUpdate();

	return true;
}

// ���X�V
void Player::update(float dt)
{
	//// �ړ�����
	//for (auto dir : DIR())
	//{
	//	// �����Ă�����ɂ���ēn���l��ς���
	//	if (m_input->GetState(dir) == INPUT_STATE::ON)
	//	{
	//		m_action->moveCtrl(this,m_offset[dir].first,m_offset[dir].second,m_speed[static_cast<size_t>(dir)]);
	//	}
	//}
	//// �d�͂Ɖ������̈ړ�����

	auto animRun = [&](DIR state1,DIR state2,bool reverse)
	{
		if ((m_input->GetState(state1) == INPUT_STATE::ON_MON)
		|| (m_input->GetState(state1) == INPUT_STATE::ON) && (m_input->GetState(state2) == INPUT_STATE::OFF_MON))
		{
			lpAnimMng.ActAnim(this,"player","run", true);
			this->runAction(FlipX::create(reverse));
		}
		if (m_input->GetState(state1) == INPUT_STATE::OFF_MON && m_input->GetState(state2) == INPUT_STATE::OFF)
		{
			lpAnimMng.ActAnim(this,"player","idle", true);
			this->runAction(FlipX::create(reverse));
		}
	};

	animRun(DIR::LEFT,DIR::RIGHT,true);
	animRun(DIR::RIGHT,DIR::LEFT,false);

	if (m_input->GetState(DIR::LEFT) == INPUT_STATE::ON)
	{
		m_action->ActRun(*this, "���ړ�");
	}
	m_input->PressingUpdate();
}