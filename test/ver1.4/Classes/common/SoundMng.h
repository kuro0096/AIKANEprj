#pragma once
#include <cocos2d.h>
#include "ck/bank.h"
#include "ck/ck.h"
#include "ck/config.h"
#include "ck/sound.h"
#include "jni.h"

// ����ނ̎��
enum class SOUND_TYPE
{
	SE,		// ����޴̪��
	BGM		// �ޯ���׳���Э��ޯ�
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
	// ����ޏ��o�^�p�֐�
	bool SERecord(const char* name);
	// ����ނ��Đ����邽�߂̊֐�(����ނ̖��O,BGM��SE��)
	void SoundStreaming(const char* name, const SOUND_TYPE type);
	// ����ނ��~�߂邽�߂̊֐�
	void StopStreaming();
	~SoundMng();
private:
	SoundMng();
	static SoundMng* s_instance;	// SoundMng�Ųݽ�ݽ����ϐ�

	CkBank* m_bank;					// SE����۰�ނ��邽�߂̕ϐ�
	CkSound* m_sound;				// ����ނ��Đ����邽�߂̕ϐ�	
};

