#include <algorithm>
#include "Player.h"
#include "_Debug/_DebugConOut.h"
#include "input/inputKey.h"
#include "input/inputTouch.h"
#include "common/CollisionCheck.h"
#include "common/AnimMng.h"

Player * Player::createPlayer()
{
	return Player::create();
}

Player::Player()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// ‰ŠúÀ•W
	this->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + this->getContentSize().height + 20));

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	m_input = new(inputKey);
#else
	m_input = new(inputTouch);
#endif
	m_input->Init(this);
	
	Init();
}

Player::~Player()
{
}

// î•ñXV
void Player::update(float dt)
{
	CollisionCheck collision = CollisionCheck();

	// ˆÚ“®ˆ—
	// Œü‚¢‚Ä‚é•ûŒü‚É‚æ‚Á‚Äˆ—‚ð•Ï‚¦‚é
	// ¶
	if (m_input->GetDir(static_cast<size_t>(DIR::LEFT)) == true)
	{
		lpAnimMng.ActAnim(this, "run", true);
		this->runAction(FlipX::create(true));
		m_runFlag.first = true;
		if (this->getPositionX() - m_bustOffset.x - m_speed.x <= 0)
		{
			this->setPositionX(0 + m_bustOffset.x + -m_speed.x);
		}
		else
		{
			// ¶ã‚Æ¶‰º‚Ìî•ñ‚ðCollisionCheck‚É“n‚·
			if (collision(this, Vec2(-m_bustOffset.x, m_bustOffset.y), Vec2(-m_legOffset.x, -m_legOffset.y), Vec2(-m_speed.x, 0)))
			{
				this->setPositionX(this->getPositionX() - m_speed.x);
			}
		}
	}
	// ‰E
	if (m_input->GetDir(static_cast<size_t>(DIR::RIGHT)) == true)
	{
		lpAnimMng.ActAnim(this, "run", true);
		this->runAction(FlipX::create(false));
		m_runFlag.second = true;
		// ‰Eã‚Æ‰E‰º‚Ìî•ñ‚ðCollisionCheck‚É“n‚·
		if (collision(this, Vec2(m_bustOffset.x, m_bustOffset.y), Vec2(m_legOffset.x, -m_legOffset.y), Vec2(m_speed.x, 0)))
		{
			this->setPositionX(this->getPositionX() + m_speed.x);
		}
	}
	// ã
	if (m_input->GetDir(static_cast<size_t>(DIR::UP)) == true)
	{
		// ¶ã‚Æ‰Eã‚Ìî•ñ‚ðCollisionCheck‚É“n‚·
		if (collision(this, Vec2(-m_legOffset.x, m_bustOffset.y), Vec2(m_legOffset.x, m_bustOffset.y), Vec2(0, m_speed.y)))
		{
			this->setPositionY(this->getPositionY() + m_speed.y);
		}
	}
	// ‰º
	if (m_input->GetDir(static_cast<size_t>(DIR::DOWN)) == true)
	{
		if (this->getPositionY() - m_legOffset.y - m_speed.y <= 0)
		{
			this->setPositionY(0 + m_legOffset.y + m_speed.y);
		}
		else
		{
			// ¶‰º‚Æ‰E‰º‚Ìî•ñ‚ðCollisionCheck‚É“n‚·
			if (collision(this, Vec2(-m_legOffset.x, -m_legOffset.y), Vec2(m_legOffset.x, -m_legOffset.y), Vec2(0, -m_speed.y)))
			{
				this->setPositionY(this->getPositionY() - m_speed.y);
			}
		}
	}
	// ‰E‚Æ¶‚ª“¯Žž‚É‰Ÿ‚³‚ê‚Ä‚¢‚½‚ç“®‚©‚È‚¢
	if (m_input->GetDir(static_cast<size_t>(DIR::RIGHT)) == true
		&& m_input->GetDir(static_cast<size_t>(DIR::LEFT)) == true)
	{
		return;
	}

	// ¶“ü—Í‚³‚ê‚½ó‘Ô‚©‚ç“ü—Í‚ª‚È‚­‚È‚Á‚½Žž‚Ì±ÆÒ°¼®Ý
	if (m_runFlag.first && m_input->GetDir(static_cast<size_t>(DIR::LEFT)) == false)
	{
		lpAnimMng.ActAnim(this, "idle", true);
		this->runAction(FlipX::create(true));
		m_runFlag.first = false;
	}
	// ‰E“ü—Í‚³‚ê‚½ó‘Ô‚©‚ç“ü—Í‚ª‚È‚­‚È‚Á‚½Žž‚Ì±ÆÒ°¼®Ý
	if (m_runFlag.second && m_input->GetDir(static_cast<size_t>(DIR::RIGHT)) == false)
	{
		lpAnimMng.ActAnim(this, "idle", true);
		this->runAction(FlipX::create(false));
		m_runFlag.second = false;
	}
}

// •Ï”‚â±ÆÒ°¼®Ý‚Ì‰Šú‰»
bool Player::Init()
{
	// •Ï”‰Šú‰»
	m_runFlag = { false,false };
	m_jumpFlag = false;

	m_bustOffset = { 30 , 35 };
	m_legOffset = { 10 , 65 };
	m_speed = { 3,3 };

	// ±ÆÒ°¼®Ý‚Ì“o˜^
	lpAnimMng.AnimCacheInit("player", "idle", 4, 0.3f);
	lpAnimMng.AnimCacheInit("player", "run", 10, 0.1f);
	lpAnimMng.AnimCacheInit("player", "jump", 6, 0.1f);

	// Å‰‚Í‘Ò‚¿ó‘Ô‚Ì±ÆÒ°¼®Ý
	lpAnimMng.ActAnim(this,"idle",true);

	this->scheduleUpdate();

	return true;
}