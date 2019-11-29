#include "EffekseerMng.h"

EffekseerMng* EffekseerMng::s_instance = nullptr; // ±ÄÞÚ½‚Ì‰Šú‰»

EffekseerMng::EffekseerMng()
{
}

EffekseerMng::~EffekseerMng()
{
}

void EffekseerMng::EffekseerInit(const EFF_ID id, const std::string effect)
{
	m_effMng.reset(efk::EffectManager::create(cocos2d::Director::getInstance()->getVisibleSize()));
	m_eff[static_cast<int>(id)] = efk::Effect::create("Effect/"+effect+".efk");
}

efk::EffectEmitter* EffekseerMng::PlayEffect(const EFF_ID id, cocos2d::Vec2 pos, int scale)
{
	m_effMng.reset(efk::EffectManager::create(cocos2d::Director::getInstance()->getVisibleSize()));
	auto emitter = efk::EffectEmitter::create(m_effMng.get());

	emitter->setEffect(m_eff[static_cast<int>(id)]);
	emitter->setPlayOnEnter(true);
	emitter->setPosition(pos);
	emitter->setScale(scale);

	return emitter;
}
