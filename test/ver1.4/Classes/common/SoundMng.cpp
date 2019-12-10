#include "SoundMng.h"

SoundMng* SoundMng::s_instance = nullptr; // ｱﾄﾞﾚｽの初期化

SoundMng::SoundMng()
{
}

SoundMng::~SoundMng()
{
	m_sound->destroy();
	m_bank->destroy();
}

// ｻｳﾝﾄﾞ情報登録用関数
bool SoundMng::SERecord(const char* name)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	m_bank = CkBank::newBank("Sounds/soundeffects.ckb", kCkPathType_FileSystem);
#else
	m_bank = CkBank::newBank("Sounds/soundeffects.ckb");
#endif
	return true;
}

// ｻｳﾝﾄﾞを再生するための関数(ｻｳﾝﾄﾞの名前,BGMかSEか)
void SoundMng::SoundStreaming(const char* name, const SOUND_TYPE type)
{
	if (type == SOUND_TYPE::SE)
	{
		m_sound = CkSound::newBankSound(m_bank, name);
		m_sound->play();
	}
	if (type == SOUND_TYPE::BGM)
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		m_sound = CkSound::newStreamSound("Sounds/test.cks", kCkPathType_FileSystem);
#else
		m_sound = CkSound::newStreamSound("Sounds/test.cks");
#endif
		m_sound->play();
	}
}

// ｻｳﾝﾄﾞを止めるための関数
void SoundMng::StopStreaming()
{
	m_sound->stop();
}


