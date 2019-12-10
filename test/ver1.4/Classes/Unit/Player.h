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
	// 情報更新
	void update(float dt);
	// ｲﾝﾌﾟｯﾄの情報を取得
	input* getInput() { return m_input; };
	// ｱｸｼｮﾝのIDを取得
	ACT_ID getActID() { return m_actID; };
	// ｱｸｼｮﾝのIDを設定
	void setActID(ACT_ID actID) { m_actID = actID; };
	// ｼﾞｬﾝﾌﾟの時間を設定
	void setJumpCnt(int cnt) { m_jumpCnt = cnt; };
	// ｼﾞｬﾝﾌﾟの経過時間を渡す
	int getJumpCnt() { return m_jumpCnt; };	
private:
	// 変数やｱﾆﾒｰｼｮﾝの初期化
	bool Init();
	
	cocos2d::AnimationCache* m_animSave;	// ｱﾆﾒｰｼｮﾝのﾃﾞｰﾀ保存用変数
	input* m_input;							// ｷｰの入力情報
	ActionMng* m_actionMng;					// ｱｸｼｮﾝ管理用変数
	ACT_ID m_actID;							// ﾌﾟﾚｲﾔｰが行っているｱｸｼｮﾝのID

	int m_jumpCnt;							// ｼﾞｬﾝﾌﾟの秒数
	float m_jumpSpeed;						// ｼﾞｬﾝﾌﾟの移動量
	bool m_reverse;							// 画像反転用のFlag

	CREATE_FUNC(Player);
};