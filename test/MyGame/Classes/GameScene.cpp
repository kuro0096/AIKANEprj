/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include <string>
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "input/inputKey.h"
#include "input/inputTouch.h"

USING_NS_CC;
#pragma execution_character_set("utf-8")

Scene* GameScene::createScene()
{
	return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameScene::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu,static_cast<int>(Z_ORDER::MAX));
	
	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	//auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	//if (label == nullptr)
	//{
	//	problemLoading("'fonts/Marker Felt.ttf'");
	//}
	//else
	//{
	//	// position the label on the center of the screen
	//	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
	//		origin.y + visibleSize.height - label->getContentSize().height));

	//	// add the label as a child to this layer
	//	this->addChild(label, 1);
	//}

	auto bg_Back = Layer::create();
	bg_Back->setName("BG_BACK");
	auto back = Sprite::create("image/Environment/background.png");
	back->setAnchorPoint(Vec2(0, 0));
	bg_Back->addChild(back,0);

	auto map = TMXTiledMap::create("map/test.tmx");
	map->setName("map");
	auto water = map->getLayer("water");
	bg_Back->addChild(map, 1);
	this->addChild(bg_Back,static_cast<int>(Z_ORDER::BG_BACK));
	water->setGlobalZOrder(static_cast<int>(Z_ORDER::BG_FRONT));

	auto CharLayer = Layer::create();
	auto player = Player::createPlayer();
	CharLayer->addChild(player,0);
	this->addChild(CharLayer, static_cast<int>(Z_ORDER::CHAR));

	auto bg_Front = Layer::create();
	bg_Front->setName("BG_FRONT");
	this->addChild(bg_Front, static_cast<int>(Z_ORDER::BG_FRONT));

	this->scheduleUpdate();

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	m_input = new(inputKey);
#else
	m_input = new(inputTouch);
#endif
	m_input->Init(this);
	return true;
}

void GameScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}

void GameScene::update(float dt)
{

}

