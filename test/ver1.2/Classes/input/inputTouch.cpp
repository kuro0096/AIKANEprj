#include "inputTouch.h"

// ｷｰの入力情報初期化関数(関連付けるNodeを引数としてもらう)
void inputTouch::Init(Node * node)
{
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	// listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(inputTouch::touchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(inputTouch::touchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(inputTouch::touchEnd, this);

	node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
}

// ﾀｯﾁ開始時の処理
bool inputTouch::touchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	// ﾀｯﾁの開始位置を設定
	m_StartPoint = touch->getLocation();
	return true;
}

// ﾀｯﾁ中の処理
bool inputTouch::touchMoved(cocos2d::Touch * touch, cocos2d::Event * event)
{
	auto offset = 5;
	auto location = touch->getLocation();

	// ﾀｯﾁの開始位置からある程度動いていたら方向毎の入力情報をtrueに,反対方向をfalseに
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

// ﾀｯﾁ終了時の処理
bool inputTouch::touchEnd(cocos2d::Touch * touch, cocos2d::Event * event)
{
	// ﾀｯﾁが終了したら全ての入力情報をfalseに
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