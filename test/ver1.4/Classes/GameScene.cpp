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
#include "common/SoundMng.h"
#include "common/EffekseerMng.h"
#include "ck/bank.h"
#include "ck/ck.h"
#include "ck/config.h"
#include "ck/sound.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	return GameScene::create();
}

GameScene::~GameScene()
{
	
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
// èâä˙âªä÷êî
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
	
	// GameSceneÇÃéqÇ∆ÇµÇƒ⁄≤‘∞ÇçÏÇËÇªÇ±Ç…spriteÇéqÇ∆ÇµÇƒä÷òAïtÇØÇÈ
	// îwåiå„ÇÎïîï™
	auto bg_Back = Layer::create();
	bg_Back->setName("BG_BACK");
	auto backG = Sprite::create("image/Environment/background.png");
	auto backG2 = Sprite::create("image/Environment/background.png");
	backG->setAnchorPoint(Vec2(0, 0));
	backG2->setAnchorPoint(Vec2(0, 0));
	backG2->setPosition(Vec2::ZERO + Vec2(720,0));

	// íÜä‘ÇÃâÊëú	
	auto backF = Sprite::create("image/Environment/middleground.png");
	backF->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	bg_Back->addChild(backG,0);
	bg_Back->addChild(backG2,0);
	bg_Back->addChild(backF, 0);

	// œØÃﬂÇ∆ëOÇ…ï\é¶Ç≥ÇÍÇÈêÖ
	auto map = TMXTiledMap::create("map/test.tmx");
	map->setName("map");
	auto water = map->getLayer("water");
	bg_Back->addChild(map, 1);
	this->addChild(bg_Back,static_cast<int>(Z_ORDER::BG_BACK));
	water->setGlobalZOrder(static_cast<int>(Z_ORDER::BG_FRONT));

	// ∑¨◊∏¿∞
	auto charLayer = Layer::create();
	auto player = Player::createPlayer();
	charLayer->addChild(player,0);
	this->addChild(charLayer, static_cast<int>(Z_ORDER::CHAR));

	// îwåiÇÃëOïîï™(âº)
	auto bg_Front = Layer::create();
	bg_Front->setName("BG_FRONT");
	this->addChild(bg_Front, static_cast<int>(Z_ORDER::BG_FRONT));

	// SEÇÃìoò^
	lpSoundMng.SERecord("soundeffects");
	// ¥Ã™∏ƒÇÃìoò^
	this->addChild(lpEffekseerMng.EffekseerInit(EFF_ID::JUMP, "Jump", Vec2(300, 300), 20), 1000);
	
	lpSoundMng.SoundStreaming("test", SOUND_TYPE::BGM);

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

// èÓïÒçXêV
void GameScene::update(float dt)
{
	(*lpEffekseerMng.GetEffMng()).update();
}

void GameScene::visit(cocos2d::Renderer * renderer, const cocos2d::Mat4 & parentTransform, uint32_t parentFlags)
{
	(*lpEffekseerMng.GetEffMng()).begin(renderer, _globalZOrder);
	cocos2d::Scene::visit(renderer, parentTransform, parentFlags);
	(*lpEffekseerMng.GetEffMng()).end(renderer, _globalZOrder);
}