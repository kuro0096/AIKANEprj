#include "inputKey.h"

// ���̓��͏�񏉊����֐�(�֘A�t����Node�������Ƃ��Ă��炤)
void inputKey::Init(Node * node)
{
	auto listener = cocos2d::EventListenerKeyboard::create();

	// ���������ꂽ���ɉ����ꂽ�����̓��͏���true��
	listener->onKeyPressed = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)->bool {
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			m_dirFlag[static_cast<size_t>(DIR::LEFT)] = true;
			m_dir = DIR::LEFT;
		}
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			m_dirFlag[static_cast<size_t>(DIR::RIGHT)] = true;
			m_dir = DIR::RIGHT;
		}
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			m_dirFlag[static_cast<size_t>(DIR::DOWN)] = true;
			m_dir = DIR::DOWN;
		}
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			m_dirFlag[static_cast<size_t>(DIR::UP)] = true;
			m_dir = DIR::UP;
		}
		return true;
	};
	// ���������ꂽ���ɉ����ꂽ�����̓��͏���false��
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