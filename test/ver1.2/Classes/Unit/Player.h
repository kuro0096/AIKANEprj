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
	ACT_ID getActID() { return m_actID; };	// ｱｸｼｮﾝのIDを取得
private:
	bool Init();							// 変数やｱﾆﾒｰｼｮﾝの初期化
	
	cocos2d::AnimationCache* m_animSave;	// ｱﾆﾒｰｼｮﾝのﾃﾞｰﾀ保存用変数
	input* m_input;							// ｷｰの入力情報
	ActionMng* m_actionMng;					// ｱｸｼｮﾝ管理用変数
	ACT_ID m_actID;							// ﾌﾟﾚｲﾔｰが行っているｱｸｼｮﾝのID

	bool m_jumpFlag;						// ｼﾞｬﾝﾌﾟ用ﾌﾗｸﾞ
	bool m_reverse;							// ｱﾆﾒｰｼｮﾝを反転するかしないか

	CREATE_FUNC(Player);
};