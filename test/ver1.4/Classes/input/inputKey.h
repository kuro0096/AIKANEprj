#pragma once
#include "input.h"

struct inputKey : public input
{
	// ｷｰの入力情報初期化関数(関連付けるNodeを引数としてもらう)
	void Init(Node* node)override;
	// どの種類の入力情報か
	INPUT_TYPE GetType(void)override { return INPUT_TYPE::KEY; }
};