#pragma once
#include "input.h"

struct inputKey : public input
{
	void Init(Node* node)override; // ���̓��͏�񏉊����֐�(�֘A�t����Node�������Ƃ��Ă��炤)
	INPUT_TYPE GetType(void)override { return INPUT_TYPE::KEY; }	// �ǂ̎�ނ̓��͏��
};

