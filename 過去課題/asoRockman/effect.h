// #pragma once

#define EFFECT_MAX 100  
#define EFFECT_IMAGE_MAX 6
#define TOBICHIRI_MAX 300   

// ----- ”ò‚ÑU‚è—p 
typedef struct {  
	XY pos;   // Êß°Â 1ŒÂ‚ÌÀ•W 
	XY mov;   // Êß°Â 1ŒÂ‚ÌˆÚ“®—Ê  
	float speed;  // Êß°Â 1ŒÂ‚Ì½Ëß°ÄŞ  
	float angle;  // Êß°Â 1ŒÂ‚ÌˆÚ“®•ûŒü 
	int no;    // Êß°Â‚Ì»²½Ş(±ÆÒ°¼®İ—p) 
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
