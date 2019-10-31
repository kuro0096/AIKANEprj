#include "ActionMng.h"

Vec2 visibleSize = Director::getInstance()->getVisibleSize();

ActionMng::ActionMng()
{
}

ActionMng::~ActionMng()
{
}

// �����蔻��p�֐�(sprite�̍��W,1�ڂ̵̾�č��W,2�ڂ̵̾�č��W)
bool ActionMng::CollisionCheck(Vec2 pos, Vec2 offsetSpot1, Vec2 offsetSpot2)
{
	m_act["���ړ�"];
	// ڲ԰�̏����擾
	auto director = Director::getInstance();
	auto map = (TMXTiledMap*)director->getRunningScene()->getChildByName("BG_BACK")->getChildByName("map");
	auto layer = map->getLayer("collision");

	// pos�Ɉړ��ʂƃI�t�Z�b�g�𑫂�(�_1)
	auto vec = (pos + offsetSpot1) / layer->getMapTileSize().width;
	vec.y = layer->getLayerSize().height - vec.y;
	// pos�Ɉړ��ʂƃI�t�Z�b�g�𑫂�(�_2)
	auto vec2 = (pos + offsetSpot2) / layer->getMapTileSize().width;
	vec2.y = layer->getLayerSize().height - vec2.y;
	// 1��2�̒��Ԃ̓_
	Vec2 center = { float((int)vec.x + (int)vec2.x) / 2, float((int)vec.y + (int)vec2.y) / 2 };

	// 3�_�œ����蔻��̏���
	// �_��ڲ԰���������Ă�����true�𓖂����Ă��Ȃ�������false��Ԃ�
	if (layer->getTileGIDAt(center) != 0 || layer->getTileGIDAt(vec) != 0 || layer->getTileGIDAt(vec2) != 0)
	{
		return true;
	}
	return false;
}

Vec2 ActionMng::moveCtrl(Vec2 pos, Vec2 offset1, Vec2 offset2,Vec2 speed)
{
	//// �ړ�����
	//if (pos + limit < 0 || pos + limit > visibleSize)
	//{
	//	return pos += limit;
	//}
	// ���ݍ��W�Ƶ̾�č��W����CollisionCheck�ɓn��
	if (!CollisionCheck(pos + speed, offset1, offset2))
	{
		return pos += speed;
	}
	return pos;
}

void ActionMng::AddAct(std::string actName, ActData data)
{
	
}
