#pragma once
#include "cocos2d.h"

enum class INPUT_TYPE	// どの入力か
{
	KEY,	// ｷｰ
	TOUCH,	// ﾀｯﾁ
	MAX
};

enum class INPUT_STATE	// 入力状態
{
	OFF,		// 離されている
	OFF_MON,	// 離された瞬間
	ON,			// 押されている
	ON_MON,		// 押された瞬間
	MAX
};

enum class INPUT__TRG
{
	NOW,
	OLD,
	INPUT,
	MAX
};

enum class DIR			// 向いている方向
{
	NON,	// 入力無し
	LEFT,	// 左
	RIGHT,	// 右
	DOWN,	// 下
	UP,		// 上
	MAX
};

struct input : public cocos2d::Node
{
	input();
	~input();
	virtual void Init(Node* node) = 0;
	void PressingUpdate();			// ｷｰの情報を更新
	virtual INPUT_TYPE GetType(void) = 0;
	INPUT_STATE GetState(const DIR dir) {
		return m_inputState[dir];	// 入力の状態を返す
	}
	const bool GetDir(const size_t& n) {
		return m_dirFlag[n];		// 方向ﾌﾗｸﾞの状態を返す
	}
protected:
	std::map<DIR,INPUT_STATE> m_inputState;			// 入力状態
	bool m_dirFlag[static_cast<size_t>(DIR::MAX)];	// 方向毎の入力情報
};

// 範囲for分用定義
DIR begin(DIR);				// 先頭
DIR end(DIR);				// 終端
DIR operator*(DIR key);		// ﾎﾟｲﾝﾀ
DIR operator++(DIR& key);	// 加算