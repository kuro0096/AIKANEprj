#include "inputKey.h"

void inputKey::Init(Node * node)
{
	auto listener = cocos2d::EventListenerKeyboard::create();

	listener->onKeyPressed = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)->bool {
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			m_state = INPUT_STATE::NOW;
			m_dirFlag[static_cast<size_t>(DIR::LEFT)] = true;
		}
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			m_state = INPUT_STATE::NOW;
			m_dirFlag[static_cast<size_t>(DIR::RIGHT)] = true;
		}
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			m_state = INPUT_STATE::NOW;
			m_dirFlag[static_cast<size_t>(DIR::DOWN)] = true;
		}
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			m_state= INPUT_STATE::NOW;
			m_dirFlag[static_cast<size_t>(DIR::UP)] = true;
		}
		return true;
	};
	listener->onKeyReleased = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)->bool {
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			m_dirFlag[static_cast<size_t>(DIR::LEFT)] = false;
		}
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			m_dirFlag[static_cast<size_t>(DIR::RIGHT)] = false;
		}
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			m_dirFlag[static_cast<size_t>(DIR::DOWN)] = false;
		}
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			m_dirFlag[static_cast<size_t>(DIR::UP)] = false;
		}
		return true;
	};
	node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
}

