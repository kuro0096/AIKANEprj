#include "SoundMng.h"

SoundMng* SoundMng::s_instance = nullptr; // ±ÄÞÚ½‚Ì‰Šú‰»

SoundMng::SoundMng()
{
}

SoundMng::~SoundMng()
{
	m_sound->destroy();
	m_bank->destroy();
}

// »³ÝÄÞî•ñ“o˜^—pŠÖ”
bool SoundMng::SERecord(const char* name)
{
	m_bank = CkBank::newBank("/test/MyGame/Resources/Sounds/soundeffects.ckb", kCkPathType_FileSystem);
	return true;
}

// »³ÝÄÞ‚ðÄ¶‚·‚é‚½‚ß‚ÌŠÖ”(»³ÝÄÞ‚Ì–¼‘O,BGM‚©SE‚©)
void SoundMng::SoundStreaming(const char* name, const SOUND_TYPE type)
{
	if (type == SOUND_TYPE::SE)
	{
		m_sound = CkSound::newBankSound(m_bank, name);
		m_sound->play();
	}
	if (type == SOUND_TYPE::BGM)
	{
		m_sound = CkSound::newStreamSound("/test/MyGame/Resources/Sounds/test.cks", kCkPathType_FileSystem);
		m_sound->play();
	}
}

// »³ÝÄÞ‚ðŽ~‚ß‚é‚½‚ß‚ÌŠÖ”
void SoundMng::StopStreaming()
{
	m_sound->stop();
}


