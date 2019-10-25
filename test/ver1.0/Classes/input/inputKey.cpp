#include "inputKey.h"

// 럭궻볺쀍륃뺪룊딖돸듫릶(듫쁀븊궚귡Node귩덙릶궴궢궲귖귞궎)
void inputKey::Init(Node * node)
{
	auto listener = cocos2d::EventListenerKeyboard::create();

	// 럭궕돓궠귢궫렄궸돓궠귢궫럭뻽궻볺쀍륃뺪귩true궸
	listener->onKeyPressed = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)->bool {
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			m_dirFlag[static_cast<size_t>(DIR::LEFT)] = true;
		}
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			m_dirFlag[static_cast<size_t>(DIR::RIGHT)] = true;
		}
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			m_dirFlag[static_cast<size_t>(DIR::DOWN)] = true;
		}
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			m_dirFlag[static_cast<size_t>(DIR::UP)] = true;
		}
		return true;
	};
	// 럭궕뿣궠귢궫렄궸돓궠귢궫럭뻽궻볺쀍륃뺪귩false궸
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