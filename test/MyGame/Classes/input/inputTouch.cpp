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
	auto offset = 10;
	auto location = touch->getLocation();

	// ﾀｯﾁの開始位置からある程度動いていたら方向毎の入力情報をtrueに,反対方向をfalseに
	if (location.x < m_StartPoint.x - offset)
	{
		m_dirFlag[static_cast<size_t>(DIR::LEFT)] = true;
		m_dirFlag[static_cast<size_t>(DIR::RIGHT)] = false;
	}
	if (location.x > m_StartPoint.x + offset)
	{
		m_dirFlag[static_cast<size_t>(DIR::RIGHT)] = true;
		m_dirFlag[static_cast<size_t>(DIR::LEFT)] = false;
	}
	if (location.y < m_StartPoint.y - offset)
	{
		m_dirFlag[static_cast<size_t>(DIR::DOWN)] = true;
		m_dirFlag[static_cast<size_t>(DIR::UP)] = false;
	}
	if (location.y > m_StartPoint.y + offset)
	{
		m_dirFlag[static_cast<size_t>(DIR::UP)] = true;
		m_dirFlag[static_cast<size_t>(DIR::DOWN)] = false;
	}
	return true;
}

// ﾀｯﾁ終了時の処理
bool inputTouch::touchEnd(cocos2d::Touch * touch, cocos2d::Event * event)
{
	// ﾀｯﾁが終了したら全ての入力情報をfalseに
	for (int n = 0; n < static_cast<size_t>(DIR::MAX); n++)
	{
		m_dirFlag[n] = false;
	}
	return true;
}
