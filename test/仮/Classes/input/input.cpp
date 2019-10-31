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