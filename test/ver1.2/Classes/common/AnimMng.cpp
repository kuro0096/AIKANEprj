#include "AnimMng.h"

USING_NS_CC;

AnimMng* AnimMng::s_Instance = nullptr; // ｱﾄﾞﾚｽの初期化

AnimMng::AnimMng()
{
	m_anim = "";
}

AnimMng::~AnimMng()
{
}

// ｱﾆﾒｰｼｮﾝの登録(ﾕﾆｯﾄ名,ｱｸｼｮﾝ名,ｱﾆﾒｰｼｮﾝの枚数,ｱﾆﾒｰｼｮﾝの間隔)
void AnimMng::AnimCacheInit(const std::string unit, const std::string actAnim, int cnt, float delay)
{
	m_animSave = AnimationCache::getInstance();
	auto cache = SpriteFrameCache::getInstance();
	// ｷｬｯｼｭにplistを追加
	cache->addSpriteFramesWithFile(unit+"-plist/"+actAnim+".plist");
	auto anim = Animation::create();
	// ｱﾆﾒｰｼｮﾝにｷｬｯｼｭから画像を取り出す
	for (int i = 1; i <= cnt; i++)
	{
		anim->addSpriteFrame(cache->getSpriteFrameByName(unit+"-"+actAnim+"-"+std::to_string(i)+".png"));
	}
	// ｱﾆﾒｰｼｮﾝの間隔を設定
	anim->setDelayPerUnit(delay);
	// ｱﾆﾒｰｼｮﾝが終わったら1ﾌﾚｰﾑ目に戻す
	anim->setRestoreOriginalFrame(true);
	// AnimationCacheにｱﾆﾒｰｼｮﾝ情報を保存
	m_animSave->addAnimation(anim,unit+"-"+actAnim);
}

// 保存したｱﾆﾒｰｼｮﾝをrunActionする(spriteの情報,保存した名前,repeatするか)
bool AnimMng::ActAnim(Sprite* sprite,const std::string unit,const std::string actAnim,bool repeat)
{
	std::string animName = unit+"-"+actAnim;
	// 前のｱﾆﾒｰｼｮﾝと違ったら
	if (m_anim != animName)
	{
		// まずすべてのｱｸｼｮﾝを止め
		sprite->stopAllActions();
		// 引数のstrと一致するｱﾆﾒｰｼｮﾝをanimateに入れる
		auto animate = Animate::create(m_animSave->getAnimation(animName));
		// repeatがtrueだったらﾘﾋﾟｰﾄするｱﾆﾒｰｼｮﾝ
		if (repeat)
		{
			auto animation =  RepeatForever::create(animate);
			sprite->runAction(animation);
			// animに現在のｱﾆﾒｰｼｮﾝを保存
			m_anim = animName;
		}
		// repeatがfalseだったら1度だけ実行されるｱﾆﾒｰｼｮﾝ
		else
		{
			// 1度実行されたら前のｱﾆﾒｰｼｮﾝに戻すようにする
			auto oldanimate = Repeat::create(Animate::create(m_animSave->getAnimation(m_anim)),-1);
			sprite->runAction(Sequence::create(animate,oldanimate,nullptr));
		}
	}
	return true;
}