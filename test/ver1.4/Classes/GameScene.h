#pragma once
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include <input/input.h>
#include <Unit/Player.h>
#include "Effekseer/Effekseer.h"

enum class Z_ORDER	// sprite‚Ì•`‰æ‡	
{
	BG_BACK = 0,	// ”wŒi‚ÌŒã‚ë•”•ª
	CHAR = 10,		// ·¬×¸À°
	BG_FRONT = 20,	// ”wŒi‚Ì‘O•”•ª(·¬×¸À°‚Ì‘O)
	MAX = 1000
};

class GameScene : public cocos2d::Scene
{
public:
	~GameScene();
	static cocos2d::Scene* createScene();
	
	// ‰Šú‰»ŠÖ”
	virtual bool init(); 

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
private:
	// î•ñXV
	void update(float dt);

	// ·°‚Ì“ü—Íî•ñ
	input* m_input;	

	void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};
#endif // __GAME_SCENE_H__