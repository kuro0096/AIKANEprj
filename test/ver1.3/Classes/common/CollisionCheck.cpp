#include "CollisionCheck.h"
#include "_debug/_DebugConOut.h"

// �����蔻��p�֐�
bool CollisionCheck::operator()(cocos2d::Sprite& sprite, ActData& data)
{
	// ڲ԰�̏����擾
	auto director = Director::getInstance();
	auto map = (TMXTiledMap*)director->getRunningScene()->getChildByName("BG_BACK")->getChildByName("map");
	auto layer = map->getLayer("collision");

	// pos�Ɉړ��ʂƃI�t�Z�b�g�𑫂�(�_1)
	auto vec = (sprite.getPosition() + data.colOffset.first + data.move) / layer->getMapTileSize().width;
	vec.y = layer->getLayerSize().height - vec.y;
	// pos�Ɉړ��ʂƃI�t�Z�b�g�𑫂�(�_2)
	auto vec2 = (sprite.getPosition() + data.colOffset.second + data.move) / layer->getMapTileSize().width;
	vec2.y = layer->getLayerSize().height - vec2.y;
	// 1��2�̒��Ԃ̓_
	Vec2 center = { float((int)vec.x + (int)vec2.x) / 2, float((int)vec.y + (int)vec2.y) / 2 };
	// GID�������𐧌�
	auto Restriction = [&](Vec2 pos ,Size size) 
	{
		if (pos.x < size.width && pos.x >= 0 && pos.y < size.height &&  pos.y >= 0)
		{
			return true;
		}
		return false;
	};
	// 3�_�œ����蔻��̏���
	// GID�����������Ă����͈͂�������
	// �_��ڲ԰���������Ă�����false�𓖂����Ă��Ȃ�������true��Ԃ�
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