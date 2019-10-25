#pragma once
#include "cocos2d.h"

enum class INPUT_TYPE	// どの入力か
{
	KEY,	// ｷｰ
	TOUCH,	// ﾀｯﾁ
	MAX
};

enum class DIR			// 向いている方向
{
	LEFT,	// 左
	RIGHT,	// 右
	DOWN,	// 下
	UP,		// 上
	MAX
};

enum class INPUT_STATE	// 入力状態
{
	NOW,	// 現在
	OLD,	// 前の状態
	MAX
};

enum class COMAND
{
	JUMP,
	SHOT,
	MAX
};

struct input : public cocos2d::Node
{
	virtual void Init(Node* node) = 0;
	virtual INPUT_TYPE GetType(void) = 0;
	INPUT_STATE GetState(void) {
		return m_inputState;	// 入力の状態を消す
	}
	const bool GetDir(const size_t& n) {
		return m_dirFlag[n];	// 方向ﾌﾗｸﾞの状態を消す
	}
protected:
	INPUT_STATE m_inputState;						// 入力状態
	bool m_dirFlag[static_cast<size_t>(DIR::MAX)];	// 方向毎の入力情報
};