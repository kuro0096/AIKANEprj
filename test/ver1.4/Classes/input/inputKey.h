#pragma once
#include "input.h"

struct inputKey : public input
{
	// ���̓��͏�񏉊����֐�(�֘A�t����Node�������Ƃ��Ă��炤)
	void Init(Node* node)override;
	// �ǂ̎�ނ̓��͏��
	INPUT_TYPE GetType(void)override { return INPUT_TYPE::KEY; }
};