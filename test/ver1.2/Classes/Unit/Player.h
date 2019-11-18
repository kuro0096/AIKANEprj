#pragma once
#pragma execution_character_set("utf-8")
#include <array>
#include <cocos2d.h>
#include <input/input.h>
#include "common/ActionMng.h"

class Player : public cocos2d::Sprite
{
public:
	static Player* createPlayer();	
	Player();
	~Player();
	void update(float dt);					// ���X�V
	input* getInput() { return m_input; };	// ���߯Ă̏����擾
private:
	bool Init();							// �ϐ����Ұ��݂̏�����
	
	cocos2d::AnimationCache* m_animSave;	// ��Ұ��݂��ް��ۑ��p�ϐ�

	input* m_input;							// ���̓��͏��
	
	bool m_jumpFlag;						// �ެ��ߗp�׸�
	cocos2d::Vec2 m_speed[static_cast<size_t>(DIR::MAX)];	// �ړ����x
	std::map<DIR, std::pair<cocos2d::Vec2, cocos2d::Vec2>> m_offset;

	ActionMng* m_action;

	CREATE_FUNC(Player);
};