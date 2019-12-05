#pragma once
#include <cocos2d.h>
#include "ck/bank.h"
#include "ck/ck.h"
#include "ck/config.h"
#include "ck/sound.h"
#include "jni.h"

// »³İÄŞ‚Ìí—Ş
enum class SOUND_TYPE
{
	SE,		// »³İÄŞ´Ìª¸Ä
	BGM		// ÊŞ¯¸¸Ş×³İÄŞĞ­°¼Ş¯¸
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
	// »³İÄŞî•ñ“o˜^—pŠÖ”
	bool SERecord(const char* name);
	// »³İÄŞ‚ğÄ¶‚·‚é‚½‚ß‚ÌŠÖ”(»³İÄŞ‚Ì–¼‘O,BGM‚©SE‚©)
	void SoundStreaming(const char* name, const SOUND_TYPE type);
	// »³İÄŞ‚ğ~‚ß‚é‚½‚ß‚ÌŠÖ”
	void StopStreaming();
	~SoundMng();
private:
	SoundMng();
	static SoundMng* s_instance;	// SoundMng‚Å²İ½Àİ½‚·‚é•Ï”

	CkBank* m_bank;					// SEî•ñ‚ğÛ°ÄŞ‚·‚é‚½‚ß‚Ì•Ï”
	CkSound* m_sound;				// »³İÄŞ‚ğÄ¶‚·‚é‚½‚ß‚Ì•Ï”	
};

