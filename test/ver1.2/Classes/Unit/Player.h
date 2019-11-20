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
	ACT_ID getActID() { return m_actID; };	// ����݂�ID���擾
private:
	bool Init();							// �ϐ����Ұ��݂̏�����
	
	cocos2d::AnimationCache* m_animSave;	// ��Ұ��݂��ް��ۑ��p�ϐ�
	input* m_input;							// ���̓��͏��
	ActionMng* m_actionMng;					// ����݊Ǘ��p�ϐ�
	ACT_ID m_actID;							// ��ڲ԰���s���Ă��鱸��݂�ID

	bool m_jumpFlag;						// �ެ��ߗp�׸�
	bool m_reverse;							// ��Ұ��݂𔽓]���邩���Ȃ���

	CREATE_FUNC(Player);
};