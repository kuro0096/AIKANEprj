#include "EffekseerMng.h"

EffekseerMng* EffekseerMng::s_instance = nullptr; // ±ÄÞÚ½‚Ì‰Šú‰»

EffekseerMng::EffekseerMng()
{
}

EffekseerMng::~EffekseerMng()
{
}

efk::EffectEmitter* EffekseerMng::EffekseerInit(const EFF_ID id, const std::string effect, cocos2d::Vec2 pos, int scale)
{
	m_effMng.reset(efk::EffectManager::create(cocos2d::Director::getInstance()->getVisibleSize()));
	auto effName = efk::Effect::create("Effect/" + effect + ".efk");

	m_emitter.emplace(id,efk::EffectEmitter::create(m_effMng.get()));

	m_emitter[id]->setEffect(effName);
	m_emitter[id]->setPlayOnEnter(false);
	m_emitter[id]->setRemoveOnStop(false);
	m_emitter[id]->setPosition(pos);
	m_emitter[id]->setScale(scale);

	return m_emitter[id];
}

bool EffekseerMng::PlayEffekseer(const EFF_ID id, cocos2d::Vec2 pos)
{
	if (m_emitter[id] != nullptr)
	{
		m_emitter[id]->play();
		m_emitter[id]->setPosition(pos);
		return true;

	}
	return false;
}