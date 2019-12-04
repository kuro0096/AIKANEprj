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
	m_bank = CkBank::newBank("/test/MyGame/Resources/Sounds/soundeffects.ckb", kCkPathType_FileSystem);
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
		m_sound = CkSound::newStreamSound("/test/MyGame/Resources/Sounds/test.cks", kCkPathType_FileSystem);
		m_sound->play();
	}
}

// ｻｳﾝﾄﾞを止めるための関数
void SoundMng::StopStreaming()
{
	m_sound->stop();
}


