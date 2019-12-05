#pragma once
#include "input.h"

struct inputKey : public input
{
	// ·°‚Ì“ü—Íî•ñ‰Šú‰»ŠÖ”(ŠÖ˜A•t‚¯‚éNode‚ğˆø”‚Æ‚µ‚Ä‚à‚ç‚¤)
	void Init(Node* node)override;
	// ‚Ç‚Ìí—Ş‚Ì“ü—Íî•ñ‚©
	INPUT_TYPE GetType(void)override { return INPUT_TYPE::KEY; }
};