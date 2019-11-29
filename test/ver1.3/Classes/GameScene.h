#pragma once
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include <input/input.h>
#include <Unit/Player.h>
#include "Effekseer/Effekseer.h"

enum class Z_ORDER	// spriteの描画順	
{
	BG_BACK = 0,	// 背景の後ろ部分
	CHAR = 10,		// ｷｬﾗｸﾀｰ
	BG_FRONT = 20,	// 背景の前部分(ｷｬﾗｸﾀｰの前)
	MAX = 1000
};

class GameScene : public cocos2d::Scene
{
public:
	~GameScene();
	static cocos2d::Scene* createScene();
	
	virtual bool init();    // 初期化関数

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
private:
	void update(float dt);	// 情報更新

	input* m_input;			// ｷｰの入力情報

	void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};
#endif // __GAME_SCENE_H__