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

#pragma execution_character_set("utf-8")

#include <string>
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "input/inputKey.h"
#include "input/inputTouch.h"

USING_NS_CC;

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
// 初期化関数
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
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
	
	// GameSceneの子としてﾚｲﾔｰを作りそこにspriteを子として関連付ける
	// 背景後ろ部分
	auto bg_Back = Layer::create();
	bg_Back->setName("BG_BACK");
	auto backG = Sprite::create("image/Environment/background.png");
	auto backG2 = Sprite::create("image/Environment/background.png");
	backG->setAnchorPoint(Vec2(0, 0));
	backG2->setAnchorPoint(Vec2(0, 0));
	backG2->setPosition(Vec2::ZERO + Vec2(720,0));

	// 中間の画像	
	auto backF = Sprite::create("image/Environment/middleground.png");
	backF->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	bg_Back->addChild(backG,0);
	bg_Back->addChild(backG2,0);
	bg_Back->addChild(backF, 0);

	// ﾏｯﾌﾟと前に表示される水
	auto map = TMXTiledMap::create("map/test.tmx");
	map->setName("map");
	auto water = map->getLayer("water");
	bg_Back->addChild(map, 1);
	this->addChild(bg_Back,static_cast<int>(Z_ORDER::BG_BACK));
	water->setGlobalZOrder(static_cast<int>(Z_ORDER::BG_FRONT));

	// ｷｬﾗｸﾀｰ
	auto charLayer = Layer::create();
	auto player = Player::createPlayer();
	charLayer->addChild(player,0);
	this->addChild(charLayer, static_cast<int>(Z_ORDER::CHAR));

	// 背景の前部分(仮)
	auto bg_Front = Layer::create();
	bg_Front->setName("BG_FRONT");
	this->addChild(bg_Front, static_cast<int>(Z_ORDER::BG_FRONT));

	m_effMng.reset(efk::EffectManager::create(Director::getInstance()->getVisibleSize()));
	auto effect = efk::Effect::create("Effect/Laser01.efk");

	auto emitter = efk::EffectEmitter::create(m_effMng.get());
	emitter->setEffect(effect);
	emitter->setPlayOnEnter(true);

	emitter->setPosition(Vec2(300, 300));
	emitter->setScale(20);
	this->addChild(emitter, static_cast<int>(Z_ORDER::MAX));

	this->scheduleUpdate();

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	m_input = new(inputKey);
#else
	m_input = new(inputTouch);
#endif
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

// 情報更新
void GameScene::update(float dt)
{
	(*m_effMng).update();
}

void GameScene::visit(cocos2d::Renderer * renderer, const cocos2d::Mat4 & parentTransform, uint32_t parentFlags)
{
	(*m_effMng).begin(renderer, _globalZOrder);
	cocos2d::Scene::visit(renderer, parentTransform, parentFlags);
	(*m_effMng).end(renderer, _globalZOrder);
}
