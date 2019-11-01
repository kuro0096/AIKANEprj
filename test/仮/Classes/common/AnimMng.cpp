#include "AnimMng.h"

USING_NS_CC;

AnimMng* AnimMng::s_Instance = nullptr; // ±ÄŞÚ½‚Ì‰Šú‰»

AnimMng::AnimMng()
{
	m_anim = "";
}

AnimMng::~AnimMng()
{
}

// ±ÆÒ°¼®İ‚Ì“o˜^(ÕÆ¯Ä–¼,±¸¼®İ–¼,±ÆÒ°¼®İ‚Ì–‡”,±ÆÒ°¼®İ‚ÌŠÔŠu)
void AnimMng::AnimCacheInit(const std::string unit, const std::string actAnim, int cnt, float delay)
{
	m_animSave = AnimationCache::getInstance();
	auto cache = SpriteFrameCache::getInstance();
	// ·¬¯¼­‚Éplist‚ğ’Ç‰Á
	cache->addSpriteFramesWithFile(unit+"-plist/"+actAnim+".plist");
	auto anim = Animation::create();
	// ±ÆÒ°¼®İ‚É·¬¯¼­‚©‚ç‰æ‘œ‚ğæ‚èo‚·
	for (int i = 1; i <= cnt; i++)
	{
		anim->addSpriteFrame(cache->getSpriteFrameByName(unit+"-"+actAnim+"-"+std::to_string(i)+".png"));
	}
	// ±ÆÒ°¼®İ‚ÌŠÔŠu‚ğİ’è
	anim->setDelayPerUnit(delay);
	// ±ÆÒ°¼®İ‚ªI‚í‚Á‚½‚ç1ÌÚ°Ñ–Ú‚É–ß‚·
	anim->setRestoreOriginalFrame(true);
	// AnimationCache‚É±ÆÒ°¼®İî•ñ‚ğ•Û‘¶
	m_animSave->addAnimation(anim,unit+"-"+actAnim);
}

// •Û‘¶‚µ‚½±ÆÒ°¼®İ‚ğrunAction‚·‚é(sprite‚Ìî•ñ,•Û‘¶‚µ‚½–¼‘O,repeat‚·‚é‚©)
bool AnimMng::ActAnim(Sprite* sprite,const std::string unit,const std::string actAnim,bool repeat)
{
	std::string animName = unit+"-"+actAnim;
	// ‘O‚Ì±ÆÒ°¼®İ‚Æˆá‚Á‚½‚ç
	if (m_anim != animName)
	{
		// ‚Ü‚¸‚·‚×‚Ä‚Ì±¸¼®İ‚ğ~‚ß
		sprite->stopAllActions();
		// ˆø”‚Ìstr‚Æˆê’v‚·‚é±ÆÒ°¼®İ‚ğanimate‚É“ü‚ê‚é
		auto animate = Animate::create(m_animSave->getAnimation(animName));
		// repeat‚ªtrue‚¾‚Á‚½‚çØËß°Ä‚·‚é±ÆÒ°¼®İ
		if (repeat)
		{
			auto animation =  RepeatForever::create(animate);
			sprite->runAction(animation);
			// anim‚ÉŒ»İ‚Ì±ÆÒ°¼®İ‚ğ•Û‘¶
			m_anim = animName;
		}
		//// repeat‚ªfalse‚¾‚Á‚½‚ç1“x‚¾‚¯Às‚³‚ê‚é±ÆÒ°¼®İ
		//else
		//{
		//	// 1“xÀs‚³‚ê‚½‚ç‘O‚Ì±ÆÒ°¼®İ‚É–ß‚·‚æ‚¤‚É‚·‚é
		//	auto oldanimate = Repeat::create(Animate::create(animSave->getAnimation(anim)),-1);
		//	sprite->runAction(Sequence::create(animate,oldanimate,nullptr));
		//}
	}
	return true;
}