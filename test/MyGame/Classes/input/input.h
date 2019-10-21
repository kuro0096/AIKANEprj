#pragma once
#pragma execution_character_set("utf-8")

#include "cocos2d.h"

enum class INPUT_TYPE	// ‚Ç‚Ì“ü—Í‚©
{
	KEY,	// ·°
	TOUCH,	// À¯Á
	MAX
};

enum class DIR	// Œü‚¢‚Ä‚¢‚é•ûŒü
{
	LEFT,	// ¶
	RIGHT,	// ‰E
	DOWN,	// ‰º
	UP,		// ã
	MAX
};

enum class COMAND
{
	JUMP,
	SHOT,
	MAX
};

enum class INPUT_STATE // “ü—Íó‘Ô
{
	NOW,	// Œ»İ
	OLD,	// ‘O‚Ìó‘Ô
	MAX
};

struct input : public cocos2d::Node
{
	virtual void Init(Node* node) = 0;
	virtual INPUT_TYPE GetType(void) = 0;
	INPUT_STATE GetState(void) {
		return m_state;			// “ü—Í‚Ìó‘Ô‚ğÁ‚·
	}
	const bool GetDir(const size_t& n) {
		return m_dirFlag[n];	// •ûŒüÌ×¸Ş‚Ìó‘Ô‚ğÁ‚·
	}
protected:
	INPUT_STATE m_state;		// “ü—Íó‘Ô
	bool m_dirFlag[static_cast<size_t>(DIR::MAX)];
};
