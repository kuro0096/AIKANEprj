#pragma once
#include "input.h"

class inputTouch : public input
{
	void Init(Node* node)override;	// ｷｰの入力情報初期化関数(関連付けるNodeを引数としてもらう)
	INPUT_TYPE GetType(void)override { return INPUT_TYPE::TOUCH; }	// どの種類の入力情報か
	bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);	// ﾀｯﾁ開始時の処理
	bool touchMoved(cocos2d::Touch* touch, cocos2d::Event* event);	// ﾀｯﾁ中の処理
	bool touchEnd(cocos2d::Touch* touch, cocos2d::Event* event);	// ﾀｯﾁ終了時の処理
private:
	cocos2d::Vec2 m_StartPoint;		// ﾀｯﾁの開始座標
};