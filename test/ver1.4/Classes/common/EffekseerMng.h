#pragma once
#include <cocos2d.h>
#include "Effekseer/Effekseer.h"

enum class EFF_ID
{
	JUMP,
	COR,
	MAX
};

#define lpEffekseerMng EffekseerMng::GetInstance()

class EffekseerMng
{
public:
	// ���I�ȼݸ����
	static EffekseerMng& GetInstance()
	{
		// 1�x�����ݽ�ݽ
		if (s_instance == nullptr)
		{
			s_instance = new EffekseerMng();
		}
		return (*s_instance);
	}
	efk::EffectEmitter* EffekseerInit(const EFF_ID id,const std::string effect, cocos2d::Vec2 pos, int scale);
	bool PlayEffekseer(const EFF_ID id, cocos2d::Vec2 pos);
	
	std::shared_ptr<efk::EffectManager> GetEffMng()
	{
		return  m_effMng;
	};
	~EffekseerMng();
private:
	EffekseerMng();
	static EffekseerMng* s_instance;				// EffekseerCtr�Ųݽ�ݽ����ϐ�
	std::map<EFF_ID, efk::EffectEmitter*>m_emitter;	// �̪�ď����i�[
	std::shared_ptr<efk::EffectManager> m_effMng = nullptr;
};

