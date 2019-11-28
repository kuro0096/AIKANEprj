#pragma once
#include "input.h"

class inputTouch : public input
{
	void Init(Node* node)override;	// ���̓��͏�񏉊����֐�(�֘A�t����Node�������Ƃ��Ă��炤)
	INPUT_TYPE GetType(void)override { return INPUT_TYPE::TOUCH; }	// �ǂ̎�ނ̓��͏��
	bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);	// ����J�n���̏���
	bool touchMoved(cocos2d::Touch* touch, cocos2d::Event* event);	// ������̏���
	bool touchEnd(cocos2d::Touch* touch, cocos2d::Event* event);	// ����I�����̏���
private:
	cocos2d::Vec2 m_StartPoint;		// ����̊J�n���W
};