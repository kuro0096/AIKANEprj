// #pragma once

#define EFFECT_MAX 100  
#define EFFECT_IMAGE_MAX 6
#define TOBICHIRI_MAX 300   

// ----- ��юU��p 
typedef struct {  
	XY pos;   // �߰� 1�̍��W 
	XY mov;   // �߰� 1�̈ړ���  
	float speed;  // �߰� 1�̽�߰��  
	float angle;  // �߰� 1�̈ړ����� 
	int no;    // �߰̻���(��Ұ��ݗp) 
	int life;
	int lifeMax;
	XY size;
	XY sizeOffset;
	TYPE charaType;
	bool visible;
}TOBICHIRI;

void EffectSysInit(void);
void EffectInit(void);
void EffectCtr(void);
void EffectDraw(void);
void SetBlockEffect(XY pos, TYPE color);

void TobichiriInit(void);
void SetTobichiri(XY pos, TYPE ptype);
void TobichiriCtr(void);
void TobichiriDraw(void);
bool TobichiriFlag(void);
