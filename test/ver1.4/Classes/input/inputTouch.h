#pragma once
#include "input.h"

class inputTouch : public input
{
	// ���̓��͏�񏉊����֐�(�֘A�t����Node�������Ƃ��Ă��炤)
	void Init(Node* node)override;
	// �ǂ̎�ނ̓��͏��
	INPUT_TYPE GetType(void)override { return INPUT_TYPE::TOUCH; }
	// ����J�n���̏���
	bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	// ������̏���
	bool touchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	// ����I�����̏���
	bool touchEnd(cocos2d::Touch* touch, cocos2d::Event* event);
private:
	cocos2d::Vec2 m_StartPoint;		// ����̊J�n���W
};