#pragma once
#include <cocos2d.h>
#include <input/input.h>

USING_NS_CC;

enum class ACTID
{
	IDLE,
	RUN,
	JUMP,
	JUMPING,
	FALL,
	FALLING,
	MAX
};

struct ActData;

using actFunc = std::function<bool(cocos2d::Sprite&,ActData&)>;

struct ActData
{
	ACTID actID;
	actFunc runAct;
	std::list<actFunc>checkModule;
	DIR dir;
	cocos2d::Point move;
	INPUT_STATE state;
	std::pair<Vec2,Vec2>colOffset;
};

class ActionMng
{
public:
	ActionMng(cocos2d::Sprite* sp);
	~ActionMng();
	//void update(float dt);		// èÓïÒçXêV

	void AddAct(std::string actName,ActData& data);
	void ActRun();
private:
	std::map<std::string, ActData> m_actData;
	cocos2d::Sprite* m_sprite;
};

