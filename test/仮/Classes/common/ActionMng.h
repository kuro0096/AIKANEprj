#pragma once
#include <cocos2d.h>
#include <input/input.h>

USING_NS_CC;

class ActData;

using actFunc = std::function<bool(std::string, ActData&)>;

struct ActData
{
	actFunc runAct;
	std::list<actFunc>act;
	DIR dir;
	INPUT_STATE state;
	COMAND comand;
	cocos2d::Point move;
	std::pair<Vec2, Vec2>colOffset;
};

class ActionMng
{
public:
	ActionMng();
	~ActionMng();

	void moveCtrl(Sprite* sp, Vec2 offset1, Vec2 offset2, Vec2 speed);	// 移動処理(対象,ｵﾌｾｯﾄ座標1,ｵﾌｾｯﾄ座標2,移動量)
	bool CollisionCheck(Vec2 pos, Vec2 offsetSpot1, Vec2 offsetSpot2);	// 当たり判定用関数(spriteの座標,1つ目のｵﾌｾｯﾄ座標,2つ目のｵﾌｾｯﾄ座標)

	void AddAct(std::string actName,ActData& data);

private:
	std::map<std::string, ActData> m_actData;
};

