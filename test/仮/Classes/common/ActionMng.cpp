#pragma execution_character_set("utf-8")
#include "ActionMng.h"

Vec2 visibleSize = Director::getInstance()->getVisibleSize();

ActionMng::ActionMng()
{
}

ActionMng::~ActionMng()
{
}

// �ړ�����(���W,�̾�č��W1,�̾�č��W2,�ړ���)
void ActionMng::moveCtrl(Sprite* sp, Vec2 offset1, Vec2 offset2, Vec2 speed)
{
	//// �ړ�����
	//if (pos + speed + limit <= 0 || pos + speed + limit >= visibleSize)
	//{
	//	sp->setPosition(sp->getPosition() + speed + limit);
	//}
	// ���ݍ��W�Ƶ̾�č��W����CollisionCheck�ɓn��
	if (!CollisionCheck(sp->getPosition() + speed, offset1, offset2))
	{
		sp->setPosition(sp->getPosition() + speed);
	}
}

// �����蔻��p�֐�(sprite�̍��W,1�ڂ̵̾�č��W,2�ڂ̵̾�č��W)
bool ActionMng::CollisionCheck(Vec2 pos, Vec2 offsetSpot1, Vec2 offsetSpot2)
{
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

void ActionMng::AddAct(std::string actName,ActData& data)
{
	if (actName == "���ړ�" || actName == "�E�ړ�")
	{
		m_actData.try_emplace(actName,std::move(data));
		// m_actData[actName].runAct = ;
	}
}
