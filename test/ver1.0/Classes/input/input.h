#pragma once
#include "cocos2d.h"

enum class INPUT_TYPE	// �ǂ̓��͂�
{
	KEY,	// ��
	TOUCH,	// ���
	MAX
};

enum class DIR			// �����Ă������
{
	LEFT,	// ��
	RIGHT,	// �E
	DOWN,	// ��
	UP,		// ��
	MAX
};

enum class INPUT_STATE	// ���͏��
{
	NOW,	// ����
	OLD,	// �O�̏��
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
		return m_inputState;	// ���͂̏�Ԃ�����
	}
	const bool GetDir(const size_t& n) {
		return m_dirFlag[n];	// �����׸ނ̏�Ԃ�����
	}
protected:
	INPUT_STATE m_inputState;						// ���͏��
	bool m_dirFlag[static_cast<size_t>(DIR::MAX)];	// �������̓��͏��
};