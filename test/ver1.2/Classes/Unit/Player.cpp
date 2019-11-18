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
	// ����݊Ǘ��p
	m_action = new ActionMng(this);

	// ���ړ��̏��o�^
	{
		ActData data;
		data.actID = ACTID::RUN;
		data.dir = DIR::LEFT;
		data.move = { -5 ,0 };
		data.state = INPUT_STATE::ON;
		data.colOffset = { Vec2(-24,35) , Vec2(-24,-65) };
		m_action->AddAct("���ړ�", data);
	}
	// �E�ړ��̏��o�^
	{
		ActData data;
		data.actID = ACTID::RUN;
		data.dir = DIR::RIGHT;
		data.move = { 3 ,0 };
		data.state = INPUT_STATE::ON;
		data.colOffset = { Vec2(24,35) , Vec2(24,-65) };
		m_action->AddAct("�E�ړ�", data);
	}
	// �W�����v���̏��o�^
	{
		ActData data;
		data.actID = ACTID::JUMP;
		data.dir = DIR::UP;
		data.move = { 0 , 10 };
		data.state = INPUT_STATE::ON_MON;
		data.colOffset = { Vec2(-24,35) , Vec2(24,35) };
		m_action->AddAct("�W�����v��", data);
	}
	// �������̏��o�^
	{
		ActData data;
		data.actID = ACTID::FALLING;
		data.dir = DIR::NON;
		data.move = { 0 , -10 };
		data.state = INPUT_STATE::ON;
		data.colOffset = { Vec2(-24,-65) , Vec2(24,-65) };
		m_action->AddAct("������", data);
	}

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
	m_action->ActRun();
	m_input->PressingUpdate();
}