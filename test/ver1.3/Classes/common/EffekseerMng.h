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
	// 動的なｼﾝｸﾞﾙﾄﾝ
	static EffekseerMng& GetInstance()
	{
		// 1度だけｲﾝｽﾀﾝｽ
		if (s_instance == nullptr)
		{
			s_instance = new EffekseerMng();
		}
		return (*s_instance);
	}
	void EffekseerInit(const EFF_ID id,const std::string effect);
	efk::EffectEmitter* PlayEffect(const EFF_ID id,cocos2d::Vec2 pos,int scale);
	std::shared_ptr<efk::EffectManager> GetEffMng()
	{
		return  m_effMng;
	};
	~EffekseerMng();
private:
	EffekseerMng();
	static EffekseerMng* s_instance;	// EffekseerCtrでｲﾝｽﾀﾝｽする変数
	std::shared_ptr<efk::EffectManager> m_effMng = nullptr;
	efk::Effect* m_eff[static_cast<int>(EFF_ID::MAX)];
};

