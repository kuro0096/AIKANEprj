#include "Player.h"
#include "_Debug/_DebugConOut.h"
#include "common/AnimMng.h"
#include "common/ActionMng.h"
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
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// 初期座標
	this->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + this->getContentSize().height + 20));
	// 変数初期化
	m_jumpFlag = false;

	// offset初期化
	// 左上,左下
	m_offset[DIR::LEFT] = { Vec2(-offsetX, bustOffsetY),Vec2(-offsetX,-legOffsetY) };
	// 右上,右下
	m_offset[DIR::RIGHT] = { Vec2(offsetX, bustOffsetY),Vec2(offsetX,-legOffsetY) };
	// 左上,右上
	m_offset[DIR::UP] = { Vec2(-offsetX, bustOffsetY),Vec2(offsetX,bustOffsetY) };
	// 左下,右下
	m_offset[DIR::DOWN] = { Vec2(-offsetX, -legOffsetY),Vec2(offsetX,-legOffsetY) };

	// 移動量初期化
	m_speed[static_cast<size_t>(DIR::LEFT)] = { - playerSpeed ,0 };
	m_speed[static_cast<size_t>(DIR::RIGHT)] = { playerSpeed ,0 };
	m_speed[static_cast<size_t>(DIR::UP)] = { 0 , playerSpeed };
	m_speed[static_cast<size_t>(DIR::DOWN)] = { 0 ,-playerSpeed };

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
	ActionMng* action = new(ActionMng);
	// 現在座標
	Vec2 pos = this->getPosition();
	// 移動処理
	for (auto dir : DIR())
	{
		// 向いてる方向によって渡す値を変える
		if (m_input->GetDir(static_cast<size_t>(dir)) == true)
		{
			auto addPos = action->moveCtrl(pos,m_offset[dir].first,m_offset[dir].second,m_speed[static_cast<size_t>(dir)]);
			this->setPosition(addPos);
		}
	}

	// 重力と下方向の移動制限

	

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