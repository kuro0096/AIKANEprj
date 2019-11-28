#pragma once
#include <cocos2d.h>
#include "ck/bank.h"
#include "ck/ck.h"
#include "ck/config.h"
#include "ck/sound.h"

enum class SOUND_TYPE	// »³İÄŞ‚Ìí—Ş
{
	SE,
	BGM
};

#define lpSoundMng SoundMng::GetInstance()

class SoundMng
{
public:
	// “®“I‚È¼İ¸ŞÙÄİ
	static SoundMng& GetInstance()
	{
		// 1“x‚¾‚¯²İ½Àİ½
		if (s_instance == nullptr)
		{
			s_instance = new SoundMng();
		}
		return (*s_instance);
	}
	bool SERecord(const char* name);			// »³İÄŞî•ñ“o˜^—pŠÖ”
	void SoundStreaming(const char* execution, const SOUND_TYPE type);	// 
	~SoundMng();
private:
	SoundMng();
	static SoundMng* s_instance;					// AnimMng‚Å²İ½Àİ½‚·‚é•Ï”

	CkBank* m_bank;
	CkSound* m_sound;
};

