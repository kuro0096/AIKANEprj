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
	void update(float dt);								// ���X�V
	input* getInput() { return m_input; };				// ���߯Ă̏����擾
	ACT_ID getActID() { return m_actID; };				// ����݂�ID���擾
	void setActID(ACT_ID actID) { m_actID = actID; };	// ����݂�ID��ݒ�
	void setJumpCnt(int cnt) { m_jumpCnt = cnt; };		// �ެ��߂̎��Ԃ�ݒ�
	int getJumpCnt() { return m_jumpCnt; };				// �ެ��߂̌o�ߎ��Ԃ�n��
private:
	bool Init();							// �ϐ����Ұ��݂̏�����
	
	cocos2d::AnimationCache* m_animSave;	// ��Ұ��݂��ް��ۑ��p�ϐ�
	input* m_input;							// ���̓��͏��
	ActionMng* m_actionMng;					// ����݊Ǘ��p�ϐ�
	ACT_ID m_actID;							// ��ڲ԰���s���Ă��鱸��݂�ID

	int m_jumpCnt;							// �ެ��߂̕b��
	float m_jumpSpeed;						// �ެ��߂̈ړ���

	CREATE_FUNC(Player);
};