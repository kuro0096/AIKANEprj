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
	// ���X�V
	void update(float dt);
	// ���߯Ă̏����擾
	input* getInput() { return m_input; };
	// ����݂�ID���擾
	ACT_ID getActID() { return m_actID; };
	// ����݂�ID��ݒ�
	void setActID(ACT_ID actID) { m_actID = actID; };
	// �ެ��߂̎��Ԃ�ݒ�
	void setJumpCnt(int cnt) { m_jumpCnt = cnt; };
	// �ެ��߂̌o�ߎ��Ԃ�n��
	int getJumpCnt() { return m_jumpCnt; };	
private:
	// �ϐ����Ұ��݂̏�����
	bool Init();
	
	cocos2d::AnimationCache* m_animSave;	// ��Ұ��݂��ް��ۑ��p�ϐ�
	input* m_input;							// ���̓��͏��
	ActionMng* m_actionMng;					// ����݊Ǘ��p�ϐ�
	ACT_ID m_actID;							// ��ڲ԰���s���Ă��鱸��݂�ID

	int m_jumpCnt;							// �ެ��߂̕b��
	float m_jumpSpeed;						// �ެ��߂̈ړ���
	bool m_reverse;							// �摜���]�p��Flag

	CREATE_FUNC(Player);
};