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

	m_action = new ActionMng(this);

	{
		ActData data;
		data.actID = ACTID::RUN;
		data.dir = DIR::LEFT;
		data.move = { -playerSpeed ,0 };
		data.state = INPUT_STATE::ON;
		data.colOffset = { Vec2(-24,35) , Vec2(-24,-65) };
		m_action->AddAct("左移動", data);
	}

	{
		ActData data;
		data.actID = ACTID::RUN;
		data.dir = DIR::RIGHT;
		data.move = { playerSpeed ,0 };
		data.state = INPUT_STATE::ON;
		data.colOffset = { Vec2(24,35) , Vec2(24,-65) };
		m_action->AddAct("右移動", data);
	}

	// ｱﾆﾒｰｼｮﾝの登録
	lpAnimMng.AnimCacheInit("player", "idle", 4, 0.3f);
	lpAnimMng.AnimCacheInit("player", "run", 10, 0.1f);
	lpAnimMng.AnimCacheInit("player", "jump", 6, 0.1f);

	// 最初は待ち状態のｱﾆﾒｰｼｮﾝ
	lpAnimMng.ActAnim(this,"player","idle", true);

	this->scheduleUpdate();

	return true;
}

// 情報更新
void Player::update(float dt)
{
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

	m_action->ActRun();
	m_input->PressingUpdate();
}