#include "inputKey.h"

// ｷｰの入力情報初期化関数(関連付けるNodeを引数としてもらう)
void inputKey::Init(Node * node)
{
	auto listener = cocos2d::EventListenerKeyboard::create();

	// ｷｰが押された時に押されたｷｰ毎の入力情報をtrueに
	listener->onKeyPressed = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)->bool {
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			m_dirFlag[static_cast<size_t>(DIR::LEFT)] = true;
			m_inputState[DIR::LEFT] = INPUT_STATE::ON_MON;
		}
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			m_dirFlag[static_cast<size_t>(DIR::RIGHT)] = true;
			m_inputState[DIR::RIGHT] = INPUT_STATE::ON_MON;
		}
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			m_dirFlag[static_cast<size_t>(DIR::DOWN)] = true;
			m_inputState[DIR::DOWN] = INPUT_STATE::ON_MON;
		}
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			m_dirFlag[static_cast<size_t>(DIR::UP)] = true;
			m_inputState[DIR::UP] = INPUT_STATE::ON_MON;
		}
		return true;
	};
	// ｷｰが離された時に押されたｷｰ毎の入力情報をfalseに
	listener->onKeyReleased = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)->bool {
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			m_dirFlag[static_cast<size_t>(DIR::LEFT)] = false;
			m_inputState[DIR::LEFT] = INPUT_STATE::OFF_MON;
		}
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			m_dirFlag[static_cast<size_t>(DIR::RIGHT)] = false;
			m_inputState[DIR::RIGHT] = INPUT_STATE::OFF_MON;
		}
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			m_dirFlag[static_cast<size_t>(DIR::DOWN)] = false;
			m_inputState[DIR::DOWN] = INPUT_STATE::OFF_MON;
		}
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			m_dirFlag[static_cast<size_t>(DIR::UP)] = false;
			m_inputState[DIR::UP] = INPUT_STATE::OFF_MON;
		}
		return true;
	};
	node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
}

// ｷｰの情報を更新
void inputKey::PressingUpdate()
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