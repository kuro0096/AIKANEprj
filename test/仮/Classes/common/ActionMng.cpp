#include "ActionMng.h"

Vec2 visibleSize = Director::getInstance()->getVisibleSize();

ActionMng::ActionMng()
{
}

ActionMng::~ActionMng()
{
}

// 当たり判定用関数(spriteの座標,1つ目のｵﾌｾｯﾄ座標,2つ目のｵﾌｾｯﾄ座標)
bool ActionMng::CollisionCheck(Vec2 pos, Vec2 offsetSpot1, Vec2 offsetSpot2)
{
	m_act["左移動"];
	// ﾚｲﾔｰの情報を取得
	auto director = Director::getInstance();
	auto map = (TMXTiledMap*)director->getRunningScene()->getChildByName("BG_BACK")->getChildByName("map");
	auto layer = map->getLayer("collision");

	// posに移動量とオフセットを足す(点1)
	auto vec = (pos + offsetSpot1) / layer->getMapTileSize().width;
	vec.y = layer->getLayerSize().height - vec.y;
	// posに移動量とオフセットを足す(点2)
	auto vec2 = (pos + offsetSpot2) / layer->getMapTileSize().width;
	vec2.y = layer->getLayerSize().height - vec2.y;
	// 1と2の中間の点
	Vec2 center = { float((int)vec.x + (int)vec2.x) / 2, float((int)vec.y + (int)vec2.y) / 2 };

	// 3点で当たり判定の処理
	// 点とﾚｲﾔｰが当たっていたらtrueを当たっていなかったらfalseを返す
	if (layer->getTileGIDAt(center) != 0 || layer->getTileGIDAt(vec) != 0 || layer->getTileGIDAt(vec2) != 0)
	{
		return true;
	}
	return false;
}

Vec2 ActionMng::moveCtrl(Vec2 pos, Vec2 offset1, Vec2 offset2,Vec2 speed)
{
	//// 移動制限
	//if (pos + limit < 0 || pos + limit > visibleSize)
	//{
	//	return pos += limit;
	//}
	// 現在座標とｵﾌｾｯﾄ座標情報をCollisionCheckに渡す
	if (!CollisionCheck(pos + speed, offset1, offset2))
	{
		return pos += speed;
	}
	return pos;
}

void ActionMng::AddAct(std::string actName, ActData data)
{
	
}
