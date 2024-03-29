#pragma once
#include <cocos2d.h>
#include "ck/bank.h"
#include "ck/ck.h"
#include "ck/config.h"
#include "ck/sound.h"
#include "jni.h"

// ｻｳﾝﾄﾞの種類
enum class SOUND_TYPE
{
	SE,		// ｻｳﾝﾄﾞｴﾌｪｸﾄ
	BGM		// ﾊﾞｯｸｸﾞﾗｳﾝﾄﾞﾐｭｰｼﾞｯｸ
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
	// ｻｳﾝﾄﾞ情報登録用関数
	bool SERecord(const char* name);
	// ｻｳﾝﾄﾞを再生するための関数(ｻｳﾝﾄﾞの名前,BGMかSEか)
	void SoundStreaming(const char* name, const SOUND_TYPE type);
	// ｻｳﾝﾄﾞを止めるための関数
	void StopStreaming();
	~SoundMng();
private:
	SoundMng();
	static SoundMng* s_instance;	// SoundMngでｲﾝｽﾀﾝｽする変数

	CkBank* m_bank;					// SE情報をﾛｰﾄﾞするための変数
	CkSound* m_sound;				// ｻｳﾝﾄﾞを再生するための変数	
};

