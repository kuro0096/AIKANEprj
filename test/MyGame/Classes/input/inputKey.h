#pragma once
#include "input.h"

struct inputKey : public input
{
	void Init(Node* node)override;
	INPUT_TYPE GetType(void)override { return INPUT_TYPE::KEY; }
};

