#include "inputTouch.h"

void inputTouch::Init(Node * node)
{
	auto listener = cocos2d::EventListenerTouchOneByOne::create();

	// listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(inputTouch::touchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(inputTouch::touchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(inputTouch::touchEnd, this);

	node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
}

bool inputTouch::touchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	m_StartPoint = touch->getLocation();
	return true;
}

bool inputTouch::touchMoved(cocos2d::Touch * touch, cocos2d::Event * event)
{
	auto offset = 10;
	auto location = touch->getLocation();

	if (location.x < m_StartPoint.x - offset)
	{
		m_state = INPUT_STATE::NOW;
		m_dirFlag[static_cast<size_t>(DIR::LEFT)] = true;
		m_dirFlag[static_cast<size_t>(DIR::RIGHT)] = false;
	}
	if (location.x > m_StartPoint.x + offset)
	{
		m_state = INPUT_STATE::NOW;
		m_dirFlag[static_cast<size_t>(DIR::RIGHT)] = true;
		m_dirFlag[static_cast<size_t>(DIR::LEFT)] = false;
	}
	if (location.y < m_StartPoint.y - offset)
	{
		m_state = INPUT_STATE::NOW;
		m_dirFlag[static_cast<size_t>(DIR::DOWN)] = true;
		m_dirFlag[static_cast<size_t>(DIR::UP)] = false;
	}
	if (location.y > m_StartPoint.y + offset)
	{
		m_state = INPUT_STATE::NOW;
		m_dirFlag[static_cast<size_t>(DIR::UP)] = true;
		m_dirFlag[static_cast<size_t>(DIR::DOWN)] = false;
	}
	return true;
}

bool inputTouch::touchEnd(cocos2d::Touch * touch, cocos2d::Event * event)
{
	for (int n = 0; n < static_cast<size_t>(DIR::MAX); n++)
	{
		m_dirFlag[n] = false;
	}
	m_state = INPUT_STATE::OLD;
	return true;
}
