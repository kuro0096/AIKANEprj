#pragma once
#include <cocos2d.h>
#include "ck/bank.h"
#include "ck/ck.h"
#include "ck/config.h"
#include "ck/sound.h"

enum class SOUND_TYPE	// ����ނ̎��
{
	SE,
	BGM
};

#define lpSoundMng SoundMng::GetInstance()

class SoundMng
{
public:
	// ���I�ȼݸ����
	static SoundMng& GetInstance()
	{
		// 1�x�����ݽ�ݽ
		if (s_instance == nullptr)
		{
			s_instance = new SoundMng();
		}
		return (*s_instance);
	}
	bool SERecord(const char* name);			// ����ޏ��o�^�p�֐�
	void SoundStreaming(const char* execution, const SOUND_TYPE type);	// 
	~SoundMng();
private:
	SoundMng();
	static SoundMng* s_instance;					// AnimMng�Ųݽ�ݽ����ϐ�

	CkBank* m_bank;
	CkSound* m_sound;
};

