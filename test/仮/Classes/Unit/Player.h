#pragma once
#pragma execution_character_set("utf-8")
#include <array>
#include <cocos2d.h>
#include <input/input.h>
#include "common/ActionMng.h"

constexpr float playerSpeed = 3.0f;			// ﾌﾟﾚｲﾔｰの移動量
constexpr float offsetX = 24.0f;			// 左右用のｵﾌｾｯﾄ座標量
constexpr float bustOffsetY = 35.0f;		// 中心より上のｵﾌｾｯﾄ座標量
constexpr float legOffsetY = 65.0f;			// 中心より下のｵﾌｾｯﾄ座標量

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
	
	bool m_jumpFlag;						// ｼﾞｬﾝﾌﾟ用ﾌﾗｸﾞ
	cocos2d::Vec2 m_speed[static_cast<size_t>(DIR::MAX)];	// 移動速度
	std::map<DIR, std::pair<cocos2d::Vec2, cocos2d::Vec2>> m_offset;

	ActionMng* m_action;

	CREATE_FUNC(Player);
};