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

// ｷｰの情報を更新
void input::PressingUpdate()
{
	int cnt = 0;
	for (auto dir : DIR())
	{
		// ｷｰが押された瞬間か離された瞬間だったら更新
		if (m_inputState[dir] == INPUT_STATE::OFF_MON)
		{
			m_inputState[dir] = INPUT_STATE::OFF;
		}
		if (m_inputState[dir] == INPUT_STATE::ON_MON)
		{
			m_inputState[dir] = INPUT_STATE::ON;
		}
		// 全て入力がなかったら無し状態をtrueに
		if (m_inputState[dir] == INPUT_STATE::OFF)
		{
			cnt++;
		}
		if (cnt == static_cast<int>(DIR::MAX))
		{
			m_inputState[DIR::NON] = INPUT_STATE::ON;
		}
	}
}