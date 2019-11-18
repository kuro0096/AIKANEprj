#pragma once
#pragma execution_character_set("utf-8")
#include <array>
#include <cocos2d.h>
#include <input/input.h>
#include "common/ActionMng.h"

class Player : public cocos2d::Sprite
{
public:
	static Player* createPlayer();	
	Player();
	~Player();
	void update(float dt);					// 情報更新
	input* getInput() { return m_input; };	// ｲﾝﾌﾟｯﾄの情報を取得
private:
	bool Init();							// 変数やｱﾆﾒｰｼｮﾝの初期化
	
	cocos2d::AnimationCache* m_animSave;	// ｱﾆﾒｰｼｮﾝのﾃﾞｰﾀ保存用変数

	input* m_input;							// ｷｰの入力情報
	
	bool m_jumpFlag;						// ｼﾞｬﾝﾌﾟ用ﾌﾗｸﾞ
	cocos2d::Vec2 m_speed[static_cast<size_t>(DIR::MAX)];	// 移動速度
	std::map<DIR, std::pair<cocos2d::Vec2, cocos2d::Vec2>> m_offset;

	ActionMng* m_action;

	CREATE_FUNC(Player);
};