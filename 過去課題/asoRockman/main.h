// #pragma once
#include "DxLib.h"

// �萔
#define SCREEN_SIZE_X 768
#define SCREEN_SIZE_Y 480

#define PI 3.141592
#define ACC_G 10	//	�d�͉����x
#define ACC_RUN 0.15	// ��������x
#define ACC_STOP 0.15	// ��~�����x
#define X_MAX 7			// X�����̈ړ��̍ő�l

// ��`
typedef struct {
	float x;
	float y;
} XY_F;

typedef struct {
	int x;
	int y;
} XY;

enum MOVE_DIR {
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LEFT,
	DIR_MAX
};

enum TYPE {
	PROTO,
	PLAYER1,
	PLAYER2
};

typedef struct {
	MOVE_DIR dir;		// �����Ă������
	XY pos;				// �L�����N�^�̈ʒu
	XY size;			// �L�����N�^�摜�̃T�C�Y
	XY sizeOffset;		// �L�����N�^��������̍���ʒu
	XY hitPosS;			// �����蔻��p�̍���
	XY hitPosE;			// �����蔻��p�̉E��
	bool runFlag;		// �L�����N�^�̏��(�����Ă��邩�H)
	bool jumpFlag;		// �L�����N�^�̏��(�W�����v���Ă��邩�H)
	bool shotFlag;		// �L�����N�^�̏��(�e�����Ă��邩�H)
	bool damageFlag;	// �L�����N�^�̏��(�_���[�W�󂯂Ă��邩�H)
	int moveSpeed;		// �L�����N�^�̈ړ���
	int life;			// �L�����N�^�̗̑�
	int lifeMax;		// �L�����N�^�̗͍̑ő�
	int animCnt;		// �L�����N�^�̃A�j���[�V�����p�J�E���^
	int imgLockCnt;     // �L�����N�^�̃C���[�W�Œ�p�J�E���^
	XY_F velocity;		// �ړ����x
	bool visible;
	TYPE charaType;		// �L�����N�^�[�^�C�v
	int invincible;
}CHARACTER;

extern XY scrPos;

// �v���g�^�C�v�錾