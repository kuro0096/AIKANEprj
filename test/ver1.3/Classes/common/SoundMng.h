#pragma once
#include <cocos2d.h>
#include "ck/bank.h"
#include "ck/ck.h"
#include "ck/config.h"
#include "ck/sound.h"

enum class SOUND_TYPE	// ｻｳﾝﾄﾞの種類
{
	SE,
	BGM
};

#define lpSoundMng SoundMng::GetInstance()

class SoundMng
{
public:
	// 動的なｼﾝｸﾞﾙﾄﾝ
	static SoundMng& GetInstance()
	{
		// 1度だけｲﾝｽﾀﾝｽ
		if (s_instance == nullptr)
		{
			s_instance = new SoundMng();
		}
		return (*s_instance);
	}
	bool SERecord(const char* name);			// ｻｳﾝﾄﾞ情報登録用関数
	void SoundStreaming(const char* execution, const SOUND_TYPE type);	// 
	~SoundMng();
private:
	SoundMng();
	static SoundMng* s_instance;					// AnimMngでｲﾝｽﾀﾝｽする変数

	CkBank* m_bank;
	CkSound* m_sound;
};

