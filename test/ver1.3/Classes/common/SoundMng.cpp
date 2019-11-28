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

bool SoundMng::SERecord(const char* name)
{
	m_bank = CkBank::newBank("/test/MyGame/Resources/Sounds/soundeffects.ckb", kCkPathType_FileSystem);
	return true;
}

void SoundMng::SoundStreaming(const char* execution, const SOUND_TYPE type)
{
	if (type == SOUND_TYPE::SE)
	{
		m_sound = CkSound::newBankSound(m_bank, execution);
		m_sound->play();
	}
}
