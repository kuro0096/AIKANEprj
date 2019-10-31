#pragma once
#include <cocos2d.h>
#include <input/input.h>

USING_NS_CC;

struct ActData
{
	DIR dir;

};

class ActionMng
{
public:
	ActionMng();
	~ActionMng();

	bool CollisionCheck(Vec2 pos, Vec2 offsetSpot1, Vec2 offsetSpot2);	// 当たり判定用関数(spriteの座標,1つ目のｵﾌｾｯﾄ座標,2つ目のｵﾌｾｯﾄ座標)
	Vec2 moveCtrl (Vec2 pos,Vec2 offset1,Vec2 offset2,Vec2 speed);		// 移動処理用関数(座標と移動量を足した値,ｵﾌｾｯﾄ座標1,ｵﾌｾｯﾄ座標2,移動制限)

	void AddAct(const std::string& actName, const ActData& data);

private:
	std::map<std::string, ActData> m_act;
};

