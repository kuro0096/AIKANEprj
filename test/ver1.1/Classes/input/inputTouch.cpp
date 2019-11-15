#include "inputTouch.h"

// ���̓��͏�񏉊����֐�(�֘A�t����Node�������Ƃ��Ă��炤)
void inputTouch::Init(Node * node)
{
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	// listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(inputTouch::touchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(inputTouch::touchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(inputTouch::touchEnd, this);

	node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
}

// ����J�n���̏���
bool inputTouch::touchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	// ����̊J�n�ʒu��ݒ�
	m_StartPoint = touch->getLocation();
	return true;
}

// ������̏���
bool inputTouch::touchMoved(cocos2d::Touch * touch, cocos2d::Event * event)
{
	auto offset = 5;
	auto location = touch->getLocation();

	// ����̊J�n�ʒu���炠����x�����Ă�����������̓��͏���true��,���Ε�����false��
	if (location.x < m_StartPoint.x - offset)
	{
		m_inputState[DIR::LEFT] = INPUT_STATE::ON_MON;
		m_inputState[DIR::RIGHT] = INPUT_STATE::OFF_MON;
	}
	if (location.x > m_StartPoint.x + offset)
	{
		m_inputState[DIR::RIGHT] = INPUT_STATE::ON_MON;
		m_inputState[DIR::LEFT] = INPUT_STATE::OFF_MON;
	}
	if (location.y < m_StartPoint.y - offset)
	{
		m_inputState[DIR::DOWN] = INPUT_STATE::ON_MON;
		m_inputState[DIR::UP] = INPUT_STATE::OFF_MON;
	}
	if (location.y > m_StartPoint.y + offset)
	{
		m_inputState[DIR::UP] = INPUT_STATE::ON_MON;
		m_inputState[DIR::DOWN] = INPUT_STATE::OFF_MON;
	}
	return true;
}

// ����I�����̏���
bool inputTouch::touchEnd(cocos2d::Touch * touch, cocos2d::Event * event)
{
	// ������I��������S�Ă̓��͏���false��
	for (auto dir : DIR())
	{
		if (m_inputState[dir] == INPUT_STATE::OFF_MON)
		{
			m_inputState[dir] = INPUT_STATE::OFF;
		}
		if (m_inputState[dir] == INPUT_STATE::ON || m_inputState[dir] == INPUT_STATE::ON_MON)
		{
			m_inputState[dir] = INPUT_STATE::OFF_MON;
		}
	}
	return true;
}