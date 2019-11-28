#include "CollisionCheck.h"
#include "_debug/_DebugConOut.h"

// 当たり判定用関数
bool CollisionCheck::operator()(cocos2d::Sprite& sprite, ActData& data)
{
	// ﾚｲﾔｰの情報を取得
	auto director = Director::getInstance();
	auto map = (TMXTiledMap*)director->getRunningScene()->getChildByName("BG_BACK")->getChildByName("map");
	auto layer = map->getLayer("collision");

	// posに移動量とオフセットを足す(点1)
	auto vec = (sprite.getPosition() + data.colOffset.first + data.move) / layer->getMapTileSize().width;
	vec.y = layer->getLayerSize().height - vec.y;
	// posに移動量とオフセットを足す(点2)
	auto vec2 = (sprite.getPosition() + data.colOffset.second + data.move) / layer->getMapTileSize().width;
	vec2.y = layer->getLayerSize().height - vec2.y;
	// 1と2の中間の点
	Vec2 center = { float((int)vec.x + (int)vec2.x) / 2, float((int)vec.y + (int)vec2.y) / 2 };
	// GIDのﾁｪｯｸを制限
	auto Restriction = [&](Vec2 pos ,Size size) 
	{
		if (pos.x < size.width && pos.x >= 0 && pos.y < size.height &&  pos.y >= 0)
		{
			return true;
		}
		return false;
	};
	// 3点で当たり判定の処理
	// GIDのﾁｪｯｸをしていい範囲だったら
	// 点とﾚｲﾔｰが当たっていたらfalseを当たっていなかったらtrueを返す
	if (Restriction(center,layer->getLayerSize()) && Restriction(vec,layer->getLayerSize()) && Restriction(vec2,layer->getLayerSize()))
	{
		if (layer->getTileGIDAt(center) != 0 || layer->getTileGIDAt(vec) != 0 || layer->getTileGIDAt(vec2) != 0)
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}