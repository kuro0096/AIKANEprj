#include "Player.h"
#include "_Debug/_DebugConOut.h"
#include "common/AnimMng.h"
#include "common/CollisionCheck.h"
#include "input/inputKey.h"
#include "input/inputTouch.h"

USING_NS_CC;

Player * Player::createPlayer()
{
	return Player::create();
}

Player::Player()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// �������W
	this->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + this->getContentSize().height + 20));

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
	// �ϐ�������
	m_runFlag = { false,false };
	m_jumpFlag = false;

	m_bustOffset = { 30 , 35 };
	m_legOffset = { 10 , 65 };
	m_speed = { 3,3 };

	// ��Ұ��݂̓o�^
	lpAnimMng.AnimCacheInit("player", "idle", 4, 0.3f);
	lpAnimMng.AnimCacheInit("player", "run", 10, 0.1f);
	lpAnimMng.AnimCacheInit("player", "jump", 6, 0.1f);

	// �ŏ��͑҂���Ԃ̱�Ұ���
	lpAnimMng.ActAnim(this, "idle", true);

	this->scheduleUpdate();

	return true;
}

// ���X�V
void Player::update(float dt)
{
	CollisionCheck collision = CollisionCheck();

	// �ړ�����
	// �����Ă�����ɂ���ď�����ς���
	// ��
	if (m_input->GetDir(static_cast<size_t>(DIR::LEFT)) == true)
	{
		m_runFlag.first = true;
		// �ړ�����
		if (this->getPositionX() - m_bustOffset.x - m_speed.x <= 0)
		{
			this->setPositionX(0 + m_bustOffset.x + -m_speed.x);
		}
		// ����ƍ����̏���CollisionCheck�ɓn��
		else if (!collision(this, Vec2(-m_bustOffset.x, m_bustOffset.y), Vec2(-m_legOffset.x, -m_legOffset.y), Vec2(-m_speed.x, 0)))
		{
			this->setPositionX(this->getPositionX() - m_speed.x);
		}
	}
	// �E
	if (m_input->GetDir(static_cast<size_t>(DIR::RIGHT)) == true)
	{
		m_runFlag.second = true;
		// �E��ƉE���̏���CollisionCheck�ɓn��
		if (!collision(this, Vec2(m_bustOffset.x, m_bustOffset.y), Vec2(m_legOffset.x, -m_legOffset.y), Vec2(m_speed.x, 0)))
		{
			this->setPositionX(this->getPositionX() + m_speed.x);
		}
	}
	// ��
	if (m_input->GetDir(static_cast<size_t>(DIR::DOWN)) == true)
	{
		// �ړ�����
		if (this->getPositionY() - m_legOffset.y - m_speed.y <= 0)
		{
			this->setPositionY(0 + m_legOffset.y + m_speed.y);
		}
		// �����ƉE���̏���CollisionCheck�ɓn��
		else if (!collision(this, Vec2(-m_legOffset.x, -m_legOffset.y), Vec2(m_legOffset.x, -m_legOffset.y), Vec2(0, -m_speed.y)))
		{
			this->setPositionY(this->getPositionY() - m_speed.y);
		}
	}
	// ��
	if (m_input->GetDir(static_cast<size_t>(DIR::UP)) == true)
	{
		// ����ƉE��̏���CollisionCheck�ɓn��
		if (!collision(this, Vec2(-m_legOffset.x, m_bustOffset.y), Vec2(m_legOffset.x, m_bustOffset.y), Vec2(0, m_speed.y)))
		{
			this->setPositionY(this->getPositionY() + m_speed.y);
		}
	}
	// �E�ƍ��������ɉ�����Ă����瓮���Ȃ�
	if (m_input->GetDir(static_cast<size_t>(DIR::RIGHT)) == true
		&& m_input->GetDir(static_cast<size_t>(DIR::LEFT)) == true)
	{
		return;
	}

	// �����͂��ꂽ��Ԃ̱�Ұ���
	if (m_runFlag.first)
	{
		lpAnimMng.ActAnim(this, "run", true);
		this->runAction(FlipX::create(true));
	}
	// �����͂��ꂽ��Ԃ�����͂��Ȃ��Ȃ������̱�Ұ���
	if (m_runFlag.first && m_input->GetDir(static_cast<size_t>(DIR::LEFT)) == false)
	{
		lpAnimMng.ActAnim(this, "idle", true);
		this->runAction(FlipX::create(true));
		m_runFlag.first = false;
	}
	// �E���͂��ꂽ��Ԃ̱�Ұ���
	if (m_runFlag.second){
		lpAnimMng.ActAnim(this, "run", true);
		this->runAction(FlipX::create(false));
	}
	// �E���͂��ꂽ��Ԃ�����͂��Ȃ��Ȃ������̱�Ұ���
	if (m_runFlag.second && m_input->GetDir(static_cast<size_t>(DIR::RIGHT)) == false)
	{
		lpAnimMng.ActAnim(this, "idle", true);
		this->runAction(FlipX::create(false));
		m_runFlag.second = false;
	}
}