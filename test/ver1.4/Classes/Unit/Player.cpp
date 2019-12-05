#pragma execution_character_set("utf-8")
#include "Player.h"
#include "_Debug/_DebugConOut.h"
#include "common/AnimMng.h"
#include "common/SoundMng.h"
#include "common/EffekseerMng.h"
#include "input/inputKey.h"
#include "input/inputTouch.h"
#include "ck/bank.h"
#include "ck/ck.h"
#include "ck/config.h"
#include "ck/sound.h"

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
	delete m_actionMng;
	delete m_input;
}

// �ϐ����Ұ��݂̏�����
bool Player::Init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// �������W
	this->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + this->getContentSize().height + 20));
	// �ϐ�������
	m_actID = ACT_ID::IDLE;
	m_jumpSpeed = 5.0f;
	m_reverse = false;

	// ����݊Ǘ��p�ϐ�������
	m_actionMng = new ActionMng(this);

	// ����ݏ��̓o�^
	{
		// �ҋ@��Ԃ̏��o�^
		ActData data;
		data.actID = ACT_ID::IDLE;
		data.dir = DIR::NON;
		data.blackList.emplace_back(ACT_ID::FALL);
		data.blackList.emplace_back(ACT_ID::RUN);
		data.blackList.emplace_back(ACT_ID::JUMP);
		data.blackList.emplace_back(ACT_ID::JUMPING);
		data.state = INPUT_STATE::ON;
		data.colOffset = { Vec2(-24,-65) , Vec2(24,-65) };
		m_actionMng->AddAct("Idle", data);
	}
	{
		// ���ړ��̏��o�^
		ActData data;
		data.actID = ACT_ID::RUN;
		data.dir = DIR::LEFT;
		data.blackList.emplace_back(ACT_ID::JUMPING);
		data.move = { -3 ,0 };
		data.state = INPUT_STATE::ON;
		data.colOffset = { Vec2(-24,35) , Vec2(-24,-65) };
		m_actionMng->AddAct("Left", data);
	}
	{
		// �E�ړ��̏��o�^
		ActData data;
		data.actID = ACT_ID::RUN;
		data.dir = DIR::RIGHT;
		data.blackList.emplace_back(ACT_ID::JUMPING);
		data.move = { 3 ,0 };
		data.state = INPUT_STATE::ON;
		data.colOffset = { Vec2(24,35) , Vec2(24,-65) };
		m_actionMng->AddAct("Right", data);
	}
	{
		// �ެ��ߊJ�n���̓o�^
		ActData data;
		data.actID = ACT_ID::JUMP;
		data.dir = DIR::UP;
		data.blackList.emplace_back(ACT_ID::JUMPING);
		data.blackList.emplace_back(ACT_ID::FALL);
		data.state = INPUT_STATE::ON_MON;
		data.colOffset = { Vec2(-24,35) , Vec2(24,35) };
		m_actionMng->AddAct("Jump", data);
	}
	{
		// �ެ��ߒ��̏��o�^
		ActData data;
		data.actID = ACT_ID::JUMPING;
		data.dir = DIR::UP;
		data.blackList.emplace_back(ACT_ID::IDLE);
		data.blackList.emplace_back(ACT_ID::RUN);
		data.blackList.emplace_back(ACT_ID::FALL);
		data.whiteList.emplace_back(ACT_ID::JUMP);
		data.move = { 0 , 10.0f };
		data.colOffset = { Vec2(-24,30) , Vec2(24,30) };
		m_actionMng->AddAct("Jumping", data);
	}
	{
		// �����̏��o�^
		ActData data;
		data.actID = ACT_ID::FALL;
		data.blackList.emplace_back(ACT_ID::JUMP);
		data.blackList.emplace_back(ACT_ID::JUMPING);
		data.move = { 0 , -10 };
		data.colOffset = { Vec2(-24,-65) , Vec2(24,-65) };
		m_actionMng->AddAct("Fall", data);
	}

	// ��Ұ��݂̓o�^
	lpAnimMng.AnimCacheInit("player", "idle", 4, 0.3f);
	lpAnimMng.AnimCacheInit("player", "run", 10, 0.1f);
	lpAnimMng.AnimCacheInit("player", "jump", 6, 0.1f);
	lpAnimMng.AnimCacheInit("player","stand", 3, 0.2f);

	// �ŏ��͑҂���Ԃ̱�Ұ���
	lpAnimMng.ActAnim(this,"player","idle", true);

	this->scheduleUpdate();

	return true;
}

// ���X�V
void Player::update(float dt)
{
	m_actionMng->ActRun();

	TRACE("-%d\n", static_cast<int>(m_actID));

	// ����݂̏�Ԃɂ���ı�Ұ��ݐ؂�ւ�
	if (m_actID == ACT_ID::IDLE)
	{
		lpAnimMng.ActAnim(this, "player", "idle", true);
	}
	if (m_actID == ACT_ID::FALL)
	{
		lpAnimMng.ActAnim(this, "player", "stand", true);
	}
	if (m_actID == ACT_ID::RUN)
	{
		lpAnimMng.ActAnim(this, "player", "run", true);
		m_reverse = m_actionMng->GetActDir() == DIR::LEFT ? true : false;
		this->runAction(FlipX::create(m_reverse));
	}
	if (m_actID == ACT_ID::JUMP)
	{
		lpAnimMng.ActAnim(this, "player", "jump", false);
		lpSoundMng.SoundStreaming("jump", SOUND_TYPE::SE);
		lpEffekseerMng.PlayEffekseer(EFF_ID::JUMP, this->getPosition() - Vec2{ 0,65 });
	}

	m_input->PressingUpdate();
}