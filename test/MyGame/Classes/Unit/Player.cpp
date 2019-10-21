#include "Player.h"
#include "input/inputKey.h"
#include "input/inputTouch.h"

Player * Player::createPlayer()
{
	return Player::create();
}

Player::Player()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// 初期座標
	this->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + this->getContentSize().height));

	m_runFlag = false;
	m_runFlagL = false;

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
	auto director = Director::getInstance();
	auto map = (TMXTiledMap*)director->getRunningScene()->getChildByName("BG_BACK")->getChildByName("map");

	auto data = map->getLayer("stage");

	auto vec = this->getPosition() / data->getMapTileSize().width; // posに移動量とオフセットを足す
	vec.y = director->getVisibleSize().height - vec.y;
	auto x = this->getPositionX() / data->getMapTileSize().width;
	auto y = (director->getVisibleSize().height - (this->getPositionY() - 73)) / data->getMapTileSize().height;

	// 移動処理
	if (x < data->getLayerSize().width && x > 0)
	{
		if ((data->getTileGIDAt(Vec2(x, y - 1)) * data->getMapTileSize().width < this->getPositionX()))
		{
			if (m_input->GetDir(static_cast<size_t>(DIR::LEFT)) == true)
			{
				this->setPositionX(this->getPositionX() - 3);
			}
		}
		/*if ((data->getTileGIDAt(Vec2(x, y - 1)) * data->getMapTileSize().width > this->getPositionX()))
		{
			if (m_input->GetDir(static_cast<size_t>(DIR::RIGHT)) == true)
			{
				this->setPositionX(this->getPositionX() + 3);
			}
		}*/
	}
	if (y > 0 && y < data->getLayerSize().height)
	{
		if (data->getTileGIDAt(Vec2(x, y)) == 0 && m_input->GetDir(static_cast<size_t>(DIR::UP)) != true)
		{
			this->setPositionY(this->getPositionY() - 3);
		}
	}
	
	if (m_input->GetDir(static_cast<size_t>(DIR::RIGHT)) == true)
	{
		this->setPositionX(this->getPositionX() + 3);
	}
	if (m_input->GetDir(static_cast<size_t>(DIR::UP)) == true)
	{
		this->setPositionY(this->getPositionY() + 3);
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
