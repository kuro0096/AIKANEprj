#pragma once
#include "input.h"

class inputTouch : public input
{
	// ｷｰの入力情報初期化関数(関連付けるNodeを引数としてもらう)
	void Init(Node* node)override;
	// どの種類の入力情報か
	INPUT_TYPE GetType(void)override { return INPUT_TYPE::TOUCH; }
	// ﾀｯﾁ開始時の処理
	bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	// ﾀｯﾁ中の処理
	bool touchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	// ﾀｯﾁ終了時の処理
	bool touchEnd(cocos2d::Touch* touch, cocos2d::Event* event);
private:
	cocos2d::Vec2 m_StartPoint;		// ﾀｯﾁの開始座標
};