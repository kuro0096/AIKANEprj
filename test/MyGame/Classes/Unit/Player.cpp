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
	// 初期座標
	this->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + this->getContentSize().height + 20));

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	m_input = new(inputKey);
#else
	m_input = new(inputTouch);
#endif
	// 入力情報の登録
	m_input->Init(this);
	
	Init();
}

Player::~Player()
{
}

// 変数やｱﾆﾒｰｼｮﾝの初期化
bool Player::Init()
{
	// 変数初期化
	m_jumpFlag = false;

	m_bustOffset = { 24 , 35 };
	m_legOffset = { 24 , 65 };
	m_speed = { 3,3 };

	// ｱﾆﾒｰｼｮﾝの登録
	lpAnimMng.AnimCacheInit("player", "idle", 4, 0.3f);
	lpAnimMng.AnimCacheInit("player", "run", 10, 0.1f);
	lpAnimMng.AnimCacheInit("player", "jump", 6, 0.1f);

	// 最初は待ち状態のｱﾆﾒｰｼｮﾝ
	lpAnimMng.ActAnim(this, "idle", true);

	this->scheduleUpdate();

	return true;
}

// 情報更新
void Player::update(float dt)
{
	CollisionCheck collision = CollisionCheck();

	// 移動処理
	// 向いてる方向によって処理を変える
	// 左
	if (m_input->GetDir(static_cast<size_t>(DIR::LEFT)) == true)
	{
		// 移動制限
		if (this->getPositionX() - m_bustOffset.x - m_speed.x <= 0)
		{
			this->setPositionX(0 + m_bustOffset.x + -m_speed.x);
		}
		// 左上と左下の情報をCollisionCheckに渡す
		else if (!collision(this, Vec2(-m_bustOffset.x, m_bustOffset.y), Vec2(-m_legOffset.x, -m_legOffset.y), Vec2(-m_speed.x, 0)))
		{
			this->setPositionX(this->getPositionX() - m_speed.x);
		}
	}
	// 右
	if (m_input->GetDir(static_cast<size_t>(DIR::RIGHT)) == true)
	{
		// 右上と右下の情報をCollisionCheckに渡す
		if (!collision(this, Vec2(m_bustOffset.x, m_bustOffset.y), Vec2(m_legOffset.x, -m_legOffset.y), Vec2(m_speed.x, 0)))
		{
			this->setPositionX(this->getPositionX() + m_speed.x);
		}
	}
	// 上
	if (m_input->GetDir(static_cast<size_t>(DIR::UP)) == true)
	{
		// 左上と右上の情報をCollisionCheckに渡す
		if (!collision(this, Vec2(-m_legOffset.x, m_bustOffset.y), Vec2(m_legOffset.x, m_bustOffset.y), Vec2(0, m_speed.y)))
		{
			this->setPositionY(this->getPositionY() + m_speed.y);
		}
	}
	// 重力
	// 移動制限
	if (this->getPositionY() - m_legOffset.y - m_speed.y <= 0)
	{
		this->setPositionY(0 + m_legOffset.y + m_speed.y);
	}
	// 左下と右下の情報をCollisionCheckに渡す
	else if (!collision(this, Vec2(-m_legOffset.x, -m_legOffset.y), Vec2(m_legOffset.x, -m_legOffset.y), Vec2(0, -1)))
	{
		this->setPositionY(this->getPositionY() - 1);
	}

	auto animRun = [&](DIR state1,DIR state2,bool reverse)
	{
		if ((m_input->GetState(state1) == INPUT_STATE::ON_MON)
		|| (m_input->GetState(state1) == INPUT_STATE::ON) && (m_input->GetState(state2) == INPUT_STATE::OFF_MON))
		{
			lpAnimMng.ActAnim(this, "run", true);
			this->runAction(FlipX::create(reverse));
		}
		if (m_input->GetState(state1) == INPUT_STATE::OFF_MON && m_input->GetState(state2) == INPUT_STATE::OFF)
		{
			lpAnimMng.ActAnim(this, "idle", true);
			this->runAction(FlipX::create(reverse));
		}
	};

	animRun(DIR::LEFT,DIR::RIGHT,true);
	animRun(DIR::RIGHT,DIR::LEFT,false);

	m_input->update();
}