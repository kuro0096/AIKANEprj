#pragma once
#pragma execution_character_set("utf-8")
#include <array>
#include <cocos2d.h>
#include <input/input.h>

using LamudaAct = bool(*)(cocos2d::Sprite& sprite);


class Player : public cocos2d::Sprite
{
public:
	static Player* createPlayer();	
	Player();
	~Player();
	void update(float dt);					// 情報更新
private:
	bool Init();							// 変数やｱﾆﾒｰｼｮﾝの初期化
	
	cocos2d::AnimationCache* m_animSave;	// ｱﾆﾒｰｼｮﾝのﾃﾞｰﾀ保存用変数

	input* m_input;							// ｷｰの入力情報
	
	
	std::pair<bool,bool>m_runFlag;			// 走るｱﾆﾒｰｼｮﾝ用ﾌﾗｸﾞ<firstが左,secondが右>
	bool m_jumpFlag;						// ｼﾞｬﾝﾌﾟｱﾆﾒｰｼｮﾝ用ﾌﾗｸﾞ

	cocos2d::Vec2 m_bustOffset;				// 上半身の当たり判定用ｵﾌｾｯﾄ座標
	cocos2d::Vec2 m_legOffset;				// 下半身の当たり判定用ｵﾌｾｯﾄ座標
	cocos2d::Vec2 m_speed;					// 移動速度

	CREATE_FUNC(Player);
};