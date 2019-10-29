#pragma once
#include "cocos2d.h"

enum class INPUT_TYPE	// ‚Ç‚Ì“ü—Í‚©
{
	KEY,	// ·°
	TOUCH,	// À¯Á
	MAX
};

enum class DIR			// Œü‚¢‚Ä‚¢‚é•ûŒü
{
	LEFT,	// ¶
	RIGHT,	// ‰E
	DOWN,	// ‰º
	UP,		// ã
	MAX
};

enum class INPUT_STATE	// “ü—Íó‘Ô
{
	ON,			// ‰Ÿ‚³‚ê‚Ä‚¢‚é
	ON_MON,		// ‰Ÿ‚³‚ê‚½uŠÔ
	OFF,		// —£‚³‚ê‚Ä‚¢‚é
	OFF_MON,	// —£‚³‚ê‚½uŠÔ
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
		return m_inputState;	// “ü—Í‚Ìó‘Ô‚ğÁ‚·
	}
	const bool GetDir(const size_t& n) {
		return m_dirFlag[n];	// •ûŒüÌ×¸Ş‚Ìó‘Ô‚ğÁ‚·
	}
	const DIR GetDir(){
		return m_dir;
	}
protected:
	INPUT_STATE m_inputState;						// “ü—Íó‘Ô
	bool m_dirFlag[static_cast<size_t>(DIR::MAX)];	// •ûŒü–ˆ‚Ì“ü—Íî•ñ
	DIR m_dir;
};