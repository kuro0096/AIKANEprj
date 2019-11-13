#pragma once
#include "cocos2d.h"

enum class INPUT_TYPE	// �ǂ̓��͂�
{
	KEY,	// ��
	TOUCH,	// ���
	MAX
};

enum class INPUT_STATE	// ���͏��
{
	OFF,		// ������Ă���
	OFF_MON,	// �����ꂽ�u��
	ON,			// ������Ă���
	ON_MON,		// �����ꂽ�u��
	MAX
};

enum class INPUT__TRG
{
	NOW,
	OLD,
	INPUT,
	MAX
};

enum class DIR			// �����Ă������
{
	NON,	// ���͖���
	LEFT,	// ��
	RIGHT,	// �E
	DOWN,	// ��
	UP,		// ��
	MAX
};

struct input : public cocos2d::Node
{
	input();
	~input();
	virtual void Init(Node* node) = 0;
	void PressingUpdate();			// ���̏����X�V
	virtual INPUT_TYPE GetType(void) = 0;
	INPUT_STATE GetState(const DIR dir) {
		return m_inputState[dir];	// ���͂̏�Ԃ�Ԃ�
	}
	const bool GetDir(const size_t& n) {
		return m_dirFlag[n];		// �����׸ނ̏�Ԃ�Ԃ�
	}
protected:
	std::map<DIR,INPUT_STATE> m_inputState;			// ���͏��
	bool m_dirFlag[static_cast<size_t>(DIR::MAX)];	// �������̓��͏��
};

// �͈�for���p��`
DIR begin(DIR);				// �擪
DIR end(DIR);				// �I�[
DIR operator*(DIR key);		// �߲��
DIR operator++(DIR& key);	// ���Z