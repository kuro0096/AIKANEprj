#pragma once
#include "input.h"

struct inputKey : public input
{
	void Init(Node* node)override; // ·°‚Ì“ü—Íî•ñ‰Šú‰»ŠÖ”(ŠÖ˜A•t‚¯‚éNode‚ğˆø”‚Æ‚µ‚Ä‚à‚ç‚¤)
	INPUT_TYPE GetType(void)override { return INPUT_TYPE::KEY; }	// ‚Ç‚Ìí—Ş‚Ì“ü—Íî•ñ‚©
};

