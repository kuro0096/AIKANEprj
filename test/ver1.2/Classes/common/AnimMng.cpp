#include "AnimMng.h"

USING_NS_CC;

AnimMng* AnimMng::s_Instance = nullptr; // ���ڽ�̏�����

AnimMng::AnimMng()
{
	m_anim = "";
}

AnimMng::~AnimMng()
{
}

// ��Ұ��݂̓o�^(�ƯĖ�,����ݖ�,��Ұ��݂̖���,��Ұ��݂̊Ԋu)
void AnimMng::AnimCacheInit(const std::string unit, const std::string actAnim, int cnt, float delay)
{
	m_animSave = AnimationCache::getInstance();
	auto cache = SpriteFrameCache::getInstance();
	// �������plist��ǉ�
	cache->addSpriteFramesWithFile(unit+"-plist/"+actAnim+".plist");
	auto anim = Animation::create();
	// ��Ұ��݂ɷ��������摜�����o��
	for (int i = 1; i <= cnt; i++)
	{
		anim->addSpriteFrame(cache->getSpriteFrameByName(unit+"-"+actAnim+"-"+std::to_string(i)+".png"));
	}
	// ��Ұ��݂̊Ԋu��ݒ�
	anim->setDelayPerUnit(delay);
	// ��Ұ��݂��I�������1�ڰіڂɖ߂�
	anim->setRestoreOriginalFrame(true);
	// AnimationCache�ɱ�Ұ��ݏ���ۑ�
	m_animSave->addAnimation(anim,unit+"-"+actAnim);
}

// �ۑ�������Ұ��݂�runAction����(sprite�̏��,�ۑ��������O,repeat���邩)
bool AnimMng::ActAnim(Sprite* sprite,const std::string unit,const std::string actAnim,bool repeat)
{
	std::string animName = unit+"-"+actAnim;
	// �O�̱�Ұ��݂ƈ������
	if (m_anim != animName)
	{
		// �܂����ׂĂ̱���݂��~��
		sprite->stopAllActions();
		// ������str�ƈ�v�����Ұ��݂�animate�ɓ����
		auto animate = Animate::create(m_animSave->getAnimation(animName));
		// repeat��true����������߰Ă����Ұ���
		if (repeat)
		{
			auto animation =  RepeatForever::create(animate);
			sprite->runAction(animation);
			// anim�Ɍ��݂̱�Ұ��݂�ۑ�
			m_anim = animName;
		}
		//// repeat��false��������1�x�������s������Ұ���
		//else
		//{
		//	// 1�x���s���ꂽ��O�̱�Ұ��݂ɖ߂��悤�ɂ���
		//	auto oldanimate = Repeat::create(Animate::create(animSave->getAnimation(anim)),-1);
		//	sprite->runAction(Sequence::create(animate,oldanimate,nullptr));
		//}
	}
	return true;
}