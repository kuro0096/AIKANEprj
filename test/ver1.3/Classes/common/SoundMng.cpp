#include "SoundMng.h"

SoundMng* SoundMng::s_instance = nullptr; // ���ڽ�̏�����

SoundMng::SoundMng()
{
}

SoundMng::~SoundMng()
{
	m_sound->destroy();
	m_bank->destroy();
}

// ����ޏ��o�^�p�֐�
bool SoundMng::SERecord(const char* name)
{
	m_bank = CkBank::newBank("/test/MyGame/Resources/Sounds/soundeffects.ckb", kCkPathType_FileSystem);
	return true;
}

// ����ނ��Đ����邽�߂̊֐�(����ނ̖��O,BGM��SE��)
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

// ����ނ��~�߂邽�߂̊֐�
void SoundMng::StopStreaming()
{
	m_sound->stop();
}


