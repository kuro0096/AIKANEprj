#include "keycheck.h"
#include "main.h"

bool newKey[KEY_MAX];	// �V����
bool trgKey[KEY_MAX];	// �ضް
bool upKey[KEY_MAX];	// �����ꂽ��
bool oldKey[KEY_MAX];	// �Â�

void KeyCheckInit(void)
{
	// ����
	for (int i = 0; i < KEY_MAX; i++){
		newKey[i] = false;
		trgKey[i] = false;
		upKey[i] = false;
		oldKey[i] = false;
	}
}

// �������֐�
void KeyCheck(void)
{
	// ����
	for (int i = 0; i < KEY_MAX; i++) {
		newKey[i] = false;		// �S�������Ă��Ȃ����Ƃɂ���
		trgKey[i] = false;		// �S�������Ă��Ȃ����Ƃɂ���
		upKey[i] = false;		// �S�������Ă��Ȃ����Ƃɂ���
	}
	// new���m�F(���񉟂������ǂ���)
	if (CheckHitKey(KEY_INPUT_W)) newKey[P1_UP] = true;	// ��
	if (CheckHitKey(KEY_INPUT_D)) newKey[P1_RIGHT] = true; // �E
	if (CheckHitKey(KEY_INPUT_S)) newKey[P1_DOWN] = true;  // ��
	if (CheckHitKey(KEY_INPUT_A)) newKey[P1_LEFT] = true;  // ��
	if (CheckHitKey(KEY_INPUT_RETURN)) newKey[P1_SHOT] = true; // �ʏ���
	if (CheckHitKey(KEY_INPUT_V)) newKey[P1_A] = true; // ڰ�ް�p
	if (CheckHitKey(KEY_INPUT_B)) newKey[P1_B] = true; // 3way�p


	if (CheckHitKey(KEY_INPUT_UP)) newKey[P2_UP] = true;
	if (CheckHitKey(KEY_INPUT_RIGHT)) newKey[P2_RIGHT] = true;
	if (CheckHitKey(KEY_INPUT_DOWN)) newKey[P2_DOWN] = true;
	if (CheckHitKey(KEY_INPUT_LEFT)) newKey[P2_LEFT] = true;
	if (CheckHitKey(KEY_INPUT_BACK)) newKey[P2_SHOT] = true;

	// ����
	if (CheckHitKey(KEY_INPUT_SPACE)) newKey[START] = true; // ���ėp
	// �ꎞ��~
	if (CheckHitKey(KEY_INPUT_P)) newKey[STOP] = true;

	// -----trgKey & upKey & oldKey
	for (int i = 0; i < KEY_MAX; i++) {
		trgKey[i] = newKey[i] & ~oldKey[i]; // trgKey
		upKey[i] = ~newKey[i] & oldKey[i];	// upKey
		oldKey[i] = newKey[i];  // oldkey
	}
}