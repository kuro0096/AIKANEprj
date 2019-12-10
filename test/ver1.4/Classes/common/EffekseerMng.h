#pragma once
#include <cocos2d.h>
#include "Effekseer/Effekseer.h"

// ´Ìª¸Ä‚ÌID
enum class EFF_ID
{
	JUMP,	// ¼Ş¬İÌß	
	MAX
};

#define lpEffekseerMng EffekseerMng::GetInstance()

class EffekseerMng
{
public:
	// “®“I‚È¼İ¸ŞÙÄİ
	static EffekseerMng& GetInstance()
	{
		// 1“x‚¾‚¯²İ½Àİ½
		if (s_instance == nullptr)
		{
			s_instance = new EffekseerMng();
		}
		return (*s_instance);
	}
	// ´Ìª¸Äî•ñ‰Šú‰»ŠÖ”
	efk::EffectEmitter* EffekseerInit(const EFF_ID id,const std::string effect, cocos2d::Vec2 pos, int scale);
	// “o˜^‚µ‚½´Ìª¸Ä‚ğÄ¶
	bool PlayEffekseer(const EFF_ID id, cocos2d::Vec2 pos);
	
	// ´Ìª¸ÄÏÈ°¼Ş¬‚ÌÎß²İÀ‚ğæ“¾
	std::shared_ptr<efk::EffectManager> GetEffMng()
	{
		return  m_effMng;
	};
	~EffekseerMng();
private:
	EffekseerMng();
	static EffekseerMng* s_instance;				// EffekseerCtr‚Å²İ½Àİ½‚·‚é•Ï”
	std::map<EFF_ID, efk::EffectEmitter*>m_emitter;	// ´Ìª¸Äî•ñ‚ğŠi”[
	std::shared_ptr<efk::EffectManager> m_effMng = nullptr;
};

