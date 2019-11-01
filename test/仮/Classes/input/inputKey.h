#pragma once
#include "input.h"

struct inputKey : public input
{
	void Init(Node* node)override;	// ｷｰの入力情報初期化関数(関連付けるNodeを引数としてもらう)
	void PressingUpdate()override;	// ｷｰの情報を更新
	INPUT_TYPE GetType(void)override { return INPUT_TYPE::KEY; }	// どの種類の入力情報か
};