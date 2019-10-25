#include "CollisionCheck.h"

// 当たり判定用関数(spriteの情報,1つ目のｵﾌｾｯﾄ座標,2つ目のｵﾌｾｯﾄ座標,移動量)
bool CollisionCheck::operator()(Sprite * sprite, Vec2 rect1, Vec2 rect2, Vec2 move)
{
	// ﾚｲﾔｰの情報を取得
	auto director = Director::getInstance();
	auto map = (TMXTiledMap*)director->getRunningScene()->getChildByName("BG_BACK")->getChildByName("map");
	auto layer = map->getLayer("collision");

	// posに移動量とオフセットを足す(点1)
	auto vec = (sprite->getPosition() + rect1 + move) / layer->getMapTileSize().width;
	vec.y = layer->getLayerSize().height - vec.y;
	// posに移動量とオフセットを足す(点2)
	auto vec2 = (sprite->getPosition() + rect2 + move) / layer->getMapTileSize().width;
	vec2.y = layer->getLayerSize().height - vec2.y;
	// 1と2の中間の点
	Vec2 center = { float((int)vec.x + (int)vec2.x) / 2, float((int)vec.y + (int)vec2.y) / 2 };

	// 3点で当たり判定の処理
	// 点とﾚｲﾔｰが当たっていたらtrueを当たっていなかったらfalseを返す
	if (layer->getTileGIDAt(center) != 0 || layer->getTileGIDAt(vec) != 0 || layer->getTileGIDAt(vec2) != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}