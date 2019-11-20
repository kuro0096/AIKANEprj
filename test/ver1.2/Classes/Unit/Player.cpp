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
	delete m_actionMng;
	delete m_input;
}

// 変数やｱﾆﾒｰｼｮﾝの初期化
bool Player::Init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// 初期座標
	this->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + this->getContentSize().height + 20));
	// 変数初期化
	m_jumpFlag = false;
	m_reverse = false;
	m_actID = ACT_ID::IDLE;

	// ｱｸｼｮﾝ管理用変数初期化
	m_actionMng = new ActionMng(this);

	// 左移動の情報登録
	{
		ActData data;
		data.actID = ACT_ID::RUN;
		data.dir = DIR::LEFT;
		data.move = { -3 ,0 };
		data.state = INPUT_STATE::ON;
		data.colOffset = { Vec2(-24,35) , Vec2(-24,-65) };
		m_actionMng->AddAct("左移動", data);
	}
	// 右移動の情報登録
	{
		ActData data;
		data.actID = ACT_ID::RUN;
		data.dir = DIR::RIGHT;
		data.move = { 3 ,0 };
		data.state = INPUT_STATE::ON;
		data.colOffset = { Vec2(24,35) , Vec2(24,-65) };
		m_actionMng->AddAct("右移動", data);
	}
	// ｼﾞｬﾝﾌﾟ開始時の登録
	{
		ActData data;
		data.actID = ACT_ID::JUMP;
		data.blackList.emplace_back(ACT_ID::RUN);
		data.blackList.emplace_back(ACT_ID::JUMP);
		data.dir = DIR::UP;
		data.move = { 0 , 0.1f };
		data.state = INPUT_STATE::ON_MON;
		data.colOffset = { Vec2(-24,35) , Vec2(24,35) };
		m_actionMng->AddAct("ジャンプ開始", data);
	}
	// ｼﾞｬﾝﾌﾟ中の情報登録
	{
		ActData data;
		data.actID = ACT_ID::JUMPING;
		data.blackList.emplace_back(ACT_ID::RUN);
		data.blackList.emplace_back(ACT_ID::JUMP);
		data.dir = DIR::UP;
		data.colOffset = { Vec2(-24,35) , Vec2(24,35) };
		m_actionMng->AddAct("ジャンプ中", data);
	}
	// 落下の情報登録
	{
		ActData data;
		data.actID = ACT_ID::FALLING;
		data.blackList.emplace_back(ACT_ID::JUMP);
		data.blackList.emplace_back(ACT_ID::RUN);
		data.dir = DIR::NON;
		data.move = { 0 , -10 };
		data.state = INPUT_STATE::ON;
		data.colOffset = { Vec2(-24,-65) , Vec2(24,-65) };
		m_actionMng->AddAct("落下", data);
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
	m_actionMng->ActRun();
	m_actID = m_actionMng->GetActID();

	// ｷｰが押された瞬間になったらｱﾆﾒｰｼｮﾝ切り替え
	if (m_input->GetState(DIR::LEFT) == INPUT_STATE::ON_MON)
	{
		lpAnimMng.ActAnim(this, "player", "run", true);
		m_reverse = true;
	}
	if (m_input->GetState(DIR::RIGHT) == INPUT_STATE::ON_MON)
	{
		lpAnimMng.ActAnim(this, "player", "run", true);
		m_reverse = false;
	}
	if (m_input->GetState(DIR::UP) == INPUT_STATE::ON_MON)
	{
		lpAnimMng.ActAnim(this, "player", "jump", false);
	}
	if (m_input->GetState(DIR::NON) == INPUT_STATE::ON_MON)
	{
		lpAnimMng.ActAnim(this, "player", "idle", true);
	}
	this->runAction(FlipX::create(m_reverse));

	m_input->PressingUpdate();
}