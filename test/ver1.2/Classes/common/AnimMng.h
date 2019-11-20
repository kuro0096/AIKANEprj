#pragma once
#include <string>
#include <cocos2d.h>

#define lpAnimMng AnimMng::GetInstance()

class AnimMng
{
public:
	// 動的なｼﾝｸﾞﾙﾄﾝ
	static AnimMng& GetInstance()
	{
		// 1度だけｲﾝｽﾀﾝｽ
		if (s_instance == nullptr)
		{
			s_instance = new AnimMng();
		}
		return (*s_instance);
	}

	void AnimCacheInit(const std::string unit,const std::string actAnim,int cnt,float delay);		// ｱﾆﾒｰｼｮﾝの登録(ﾕﾆｯﾄ名,ｱｸｼｮﾝ名,ｱﾆﾒｰｼｮﾝの枚数,ｱﾆﾒｰｼｮﾝの間隔)
	bool ActAnim(cocos2d::Sprite* sprite,const std::string unit,const std::string str,bool repeat);	// 保存したｱﾆﾒｰｼｮﾝをrunActionする(spriteの情報,保存した名前,repeatするか)
	
	~AnimMng();
private:
	AnimMng();
	static AnimMng* s_instance;				// AnimMngでｲﾝｽﾀﾝｽする変数

	cocos2d::AnimationCache* m_animSave;	// ｱﾆﾒｰｼｮﾝのﾃﾞｰﾀ保存用変数
	std::string m_anim;						// どのｱﾆﾒｰｼｮﾝが実行されているか文字列で保存
};