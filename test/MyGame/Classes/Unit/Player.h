#pragma once
#include <array>
#include <cocos2d.h>
#include <input/input.h>

USING_NS_CC;

enum HALF
{

};

class Player : public cocos2d::Sprite
{
public:
	static Player* createPlayer();
	Player();
	~Player();
	void update(float dt);
	Action* GetAnim(const char* str,bool repeat);
private:
	bool Init();

	AnimationCache* animSave;
	input* m_input;
	
	bool m_runFlag;
	bool m_runFlagL;

	Vec2 m_bust;
	Vec2 m_leg;
	Vec2 m_speed;

	CREATE_FUNC(Player);
};

