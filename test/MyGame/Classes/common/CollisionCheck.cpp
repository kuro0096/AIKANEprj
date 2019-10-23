#include "CollisionCheck.h"

bool CollisionCheck::operator()(Sprite * sprite, Vec2 rect1, Vec2 rect2, Vec2 move)
{
	auto director = Director::getInstance();
	auto map = (TMXTiledMap*)director->getRunningScene()->getChildByName("BG_BACK")->getChildByName("map");

	auto layer = map->getLayer("collision");

	auto vec = (sprite->getPosition() + rect1 + move) / layer->getMapTileSize().width; // posに移動量とオフセットを足す
	vec.y = layer->getLayerSize().height - vec.y;
	auto vec2 = (sprite->getPosition() + rect2 + move) / layer->getMapTileSize().width; // posに移動量とオフセットを足す
	vec2.y = layer->getLayerSize().height - vec2.y;
	Vec2 center = { float((int)vec.x + (int)vec2.x) / 2, float((int)vec.y + (int)vec2.y) / 2 };

	auto datalist = { vec,vec2,Vec2{0,0}, Vec2(layer->getLayerSize()) };
	auto data = std::minmax_element(datalist.begin(), datalist.end());

	if (layer->getTileGIDAt(center) == 0 && layer->getTileGIDAt(vec) == 0 && layer->getTileGIDAt(vec2) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
