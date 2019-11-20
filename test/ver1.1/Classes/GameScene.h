#pragma once
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include <input/input.h>
#include <Unit/Player.h>

enum class Z_ORDER	// sprite�̕`�揇	
{
	BG_BACK = 0,	// �w�i�̌�땔��
	CHAR = 10,		// ��׸��
	BG_FRONT = 20,	// �w�i�̑O����(��׸���̑O)
	MAX = 1000
};

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();    // �������֐�

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
private:
	void update(float dt);	// ���X�V

	input* m_input;			// ���̓��͏��

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};
#endif // __GAME_SCENE_H__