#include <type_traits>
#include "input.h"

input::input()
{
	for (auto dir : DIR())
	{
		m_inputState[dir] = INPUT_STATE::OFF;
	}
}

input::~input()
{
}

// �擪
DIR begin(DIR)
{
	return DIR::NON;
}

// �I�[
DIR end(DIR)
{
	return DIR::MAX;
}

// �߲��
DIR operator*(DIR key)
{
	return key;
}

// ���Z
DIR operator++(DIR& key)
{
	return key = DIR(std::underlying_type<DIR>::type(key) + 1);
}

// ���̏����X�V
void input::PressingUpdate()
{
	for (auto dir : DIR())
	{
		if (m_inputState[dir] == INPUT_STATE::OFF_MON)
		{
			m_inputState[dir] = INPUT_STATE::OFF;
		}
		if (m_inputState[dir] == INPUT_STATE::ON_MON)
		{
			m_inputState[dir] = INPUT_STATE::ON;
		}
	}
}