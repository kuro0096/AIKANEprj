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
	std::list<actFunc>act;
	DIR dir;
	cocos2d::Point move;
	INPUT_STATE state;
	std::pair<Vec2,Vec2>colOffset;
};

class ActionMng
{
public:
	ActionMng();
	~ActionMng();


	void moveCtrl(Sprite* sp, Vec2 offset1, Vec2 offset2, Vec2 speed);	// �ړ�����(�Ώ�,�̾�č��W1,�̾�č��W2,�ړ���)

	void AddAct(std::string actName,ActData& data);
	void ActRun(Sprite & sprite, std::string actName);
private:
	std::map<std::string, ActData> m_actData;
};

