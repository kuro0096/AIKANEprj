#include "CollisionCheck.h"
#include "_debug/_DebugConOut.h"

// 当たり判定用関数(spriteの情報,1つ目のｵﾌｾｯﾄ座標,2つ目のｵﾌｾｯﾄ座標,移動量)
bool CollisionCheck::operator()(cocos2d::Sprite& sprite, ActData& data)
{
	// ﾚｲﾔｰの情報を取得
	auto director = Director::getInstance();
	auto map = (TMXTiledMap*)director->getRunningScene()->getChildByName("BG_BACK")->getChildByName("map");
	auto layer = map->getLayer("collision");

	auto Clamp = [](Vec2 num, Vec2 size) {
		return std::min(std::max(num, Vec2{ 0,0 }),size );
	};
	// posに移動量とオフセットを足す(点1)
	auto vec = (sprite.getPosition() + data.colOffset.first + data.move) / layer->getMapTileSize().width;
	vec.y = layer->getLayerSize().height - vec.y;
	vec = Clamp(vec, layer->getLayerSize() - Size{ 1,1 });
	// posに移動量とオフセットを足す(点2)
	auto vec2 = (sprite.getPosition() + data.colOffset.second + data.move) / layer->getMapTileSize().width;
	vec2.y = layer->getLayerSize().height - vec2.y;
	vec2 = Clamp(vec2, layer->getLayerSize() - Size{ 1,1 });
	// 1と2の中間の点
	Vec2 center = { float((int)vec.x + (int)vec2.x) / 2, float((int)vec.y + (int)vec2.y) / 2 };
	center = Clamp(center, layer->getLayerSize() - Size{ 1,1 });
	// 3点で当たり判定の処理
	// 点とﾚｲﾔｰが当たっていたらfalseを当たっていなかったらtrueを返す
	if (layer->getTileGIDAt(center) != 0 || layer->getTileGIDAt(vec) != 0 || layer->getTileGIDAt(vec2) != 0)
	{
		return false;
	}
	return true;
}