#pragma once
#include <array>
#include <cocos2d.h>
#include <input/input.h>

USING_NS_CC;

class Player : public cocos2d::Sprite
{
public:
	static Player* createPlayer();	
	Player();
	~Player();
	void update(float dt);							// ���X�V
private:
	bool Init();					// �ϐ����Ұ��݂̏�����

	AnimationCache* animSave;       // ��Ұ��݂��ް��ۑ��p�ϐ�
	input* m_input;					// ���̓��͏��
	
	std::pair<bool,bool>m_runFlag;  // �����Ұ��ݗp�׸�(first����,second���E)
	bool m_jumpFlag;				// �ެ��߱�Ұ��ݗp�׸�

	Vec2 m_bustOffset;	// �㔼�g�̓����蔻��p�̾�č��W
	Vec2 m_legOffset;	// �����g�̓����蔻��p�̾�č��W
	Vec2 m_speed;		// �ړ����x

	CREATE_FUNC(Player);
};

