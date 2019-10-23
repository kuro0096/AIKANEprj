#include <algorithm>
#include "Player.h"
#include "_Debug/_DebugConOut.h"
#include "input/inputKey.h"
#include "input/inputTouch.h"
#include "common//CollisionCheck.h"

Player * Player::createPlayer()
{
	return Player::create();
}

Player::Player()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// ‰ŠúÀ•W
	this->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + this->getContentSize().height));

	m_runFlag = false;
	m_runFlagL = false;

	m_bust = { 30 , 35 };
	m_leg = { 10 , 65 };
	m_speed = { 3,3 };

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

void Player::update(float dt)
{
	CollisionCheck collision = CollisionCheck();

	// ˆÚ“®ˆ—
	// Œü‚¢‚Ä‚é•ûŒü‚É‚æ‚Á‚Äˆ—‚ð•Ï‚¦‚é
	if (m_input->GetDir(static_cast<size_t>(DIR::LEFT)) == true)
	{
		if (this->getPositionX() - m_bust.x - m_speed.x <= 0)
		{
			this->setPositionX(0 + m_bust.x + -m_speed.x);
		}
		else
		{
			// ¶ã‚Æ¶‰º‚Ìî•ñ‚ðCollisionCheck‚É“n‚·
			if (collision(this, Vec2(-m_bust.x, m_bust.y), Vec2(-m_leg.x, -m_leg.y), Vec2(-m_speed.x, 0)))
			{
				this->setPositionX(this->getPositionX() - m_speed.x);
			}
		}
	}
	if (m_input->GetDir(static_cast<size_t>(DIR::RIGHT)) == true)
	{
		// ‰Eã‚Æ‰E‰º‚Ìî•ñ‚ðCollisionCheck‚É“n‚·
		if (collision(this, Vec2(m_bust.x, m_bust.y), Vec2(m_leg.x, -m_leg.y), Vec2(m_speed.x, 0)))
		{
			this->setPositionX(this->getPositionX() + m_speed.x);
		}
	}
	if (m_input->GetDir(static_cast<size_t>(DIR::UP)) == true)
	{
		// ¶ã‚Æ‰Eã‚Ìî•ñ‚ðCollisionCheck‚É“n‚·
		if (collision(this, Vec2(-m_leg.x, m_bust.y), Vec2(m_leg.x, m_bust.y), Vec2(0, m_speed.y)))
		{
			this->setPositionY(this->getPositionY() + m_speed.y);
		}
	}
	if (m_input->GetDir(static_cast<size_t>(DIR::DOWN)) == true)
	{
		if (this->getPositionY() - m_leg.y - m_speed.y <= 0)
		{
			this->setPositionY(0 + m_leg.y + m_speed.y);
		}
		else
		{
			// ¶‰º‚Æ‰E‰º‚Ìî•ñ‚ðCollisionCheck‚É“n‚·
			if (collision(this, Vec2(-m_leg.x, -m_leg.y), Vec2(m_leg.x, -m_leg.y), Vec2(0, -m_speed.y)))
			{
				this->setPositionY(this->getPositionY() - m_speed.y);
			}
		}
	}
	if (m_input->GetDir(static_cast<size_t>(DIR::RIGHT)) == true
		&& m_input->GetDir(static_cast<size_t>(DIR::LEFT)) == true)
	{
		return;
	}

	if (!m_runFlag && m_input->GetDir(static_cast<size_t>(DIR::RIGHT)) == true)
	{
		this->runAction(GetAnim("run",true));
		this->runAction(FlipX::create(false));
		m_runFlag = true;
		m_runFlagL = false;
	}
	if (!m_runFlagL && m_input->GetDir(static_cast<size_t>(DIR::LEFT)) == true)
	{
		this->runAction(GetAnim("run", true));
		this->runAction(FlipX::create(true));
		m_runFlagL = true;
		m_runFlag = false;
	}
	if (m_runFlag && m_input->GetDir(static_cast<size_t>(DIR::RIGHT)) == false)
	{
		this->runAction(GetAnim("idle", true));
		this->runAction(FlipX::create(false));
		m_runFlag = false;
	}
	if (m_runFlagL && m_input->GetDir(static_cast<size_t>(DIR::LEFT)) == false)
	{
		this->runAction(GetAnim("idle", true));
		this->runAction(FlipX::create(true));
		m_runFlagL = false;
	}
}

Action * Player::GetAnim(const char* str,bool repeat)
{
	this->stopAllActions();
	auto animate = Animate::create(animSave->getAnimation(str));
	if (repeat)
	{
		auto anim = RepeatForever::create(animate);
		return anim;
	}
	else
	{
		return animate;
	}
}

bool Player::Init()
{
	animSave = AnimationCache::getInstance();
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("plist/idle.plist");
	auto anim = Animation::create();
	for (int i = 1; i <= 4; i++)
	{
		anim->addSpriteFrame(cache->getSpriteFrameByName("player-idle-" + std::to_string(i) + ".png"));
	}
	anim->setDelayPerUnit(0.3f);
	anim->setRestoreOriginalFrame(true);
	animSave->addAnimation(anim, "idle");

	cache->addSpriteFramesWithFile("plist/run.plist");
	anim = Animation::create();
	for (int i = 1; i <= 10; i++)
	{
		anim->addSpriteFrame(cache->getSpriteFrameByName("player-run-" + std::to_string(i) + ".png"));
	}
	anim->setDelayPerUnit(0.1f);
	anim->setRestoreOriginalFrame(true);
	animSave->addAnimation(anim, "run");

	cache->addSpriteFramesWithFile("plist/jump.plist");
	anim = Animation::create();
	for (int i = 1; i <= 6; i++)
	{
		anim->addSpriteFrame(cache->getSpriteFrameByName("player-jump-" + std::to_string(i) + ".png"));
	}
	anim->setDelayPerUnit(0.1f);
	anim->setRestoreOriginalFrame(true);
	animSave->addAnimation(anim, "jump");

	this->runAction(GetAnim("idle",true));

	this->scheduleUpdate();

	return true;
}