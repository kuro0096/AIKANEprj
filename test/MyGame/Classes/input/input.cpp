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

// 先頭
DIR begin(DIR)
{
	return DIR::NON;
}

// 終端
DIR end(DIR)
{
	return DIR::MAX;
}

// ﾎﾟｲﾝﾀ
DIR operator*(DIR key)
{
	return key;
}

// 加算
DIR operator++(DIR& key)
{
	return key = DIR(std::underlying_type<DIR>::type(key) + 1);
}