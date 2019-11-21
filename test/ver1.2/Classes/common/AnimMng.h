#pragma once
#include <string>
#include <cocos2d.h>
#include "ActionMng.h"

#define lpAnimMng AnimMng::GetInstance()

class AnimMng
{
public:
	// ���I�ȼݸ����
	static AnimMng& GetInstance()
	{
		// 1�x�����ݽ�ݽ
		if (s_instance == nullptr)
		{
			s_instance = new AnimMng();
		}
		return (*s_instance);
	}

	// ��Ұ��݂̓o�^(�ƯĖ�,����ݖ�,��Ұ��݂̖���,��Ұ��݂̊Ԋu)
	void AnimCacheInit(const std::string unit,const std::string actAnim,int cnt,float delay);
	// �ۑ�������Ұ��݂�runAction����(sprite�̏��,�ۑ��������O,repeat���邩)
	bool ActAnim(cocos2d::Sprite* sprite,const std::string unit,const std::string str,bool repeat);
	~AnimMng();
private:
	AnimMng();
	static AnimMng* s_instance;					// AnimMng�Ųݽ�ݽ����ϐ�

	cocos2d::AnimationCache* m_animSave;		// ��Ұ��݂��ް��ۑ��p�ϐ�
	std::string m_anim;							// �ǂ̱�Ұ��݂����s����Ă��邩������ŕۑ�
};