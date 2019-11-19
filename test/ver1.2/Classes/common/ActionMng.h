#pragma once
#include <cocos2d.h>
#include <input/input.h>

USING_NS_CC;

enum class ACTID	// ����݂�ID
{
	IDLE,		// �ҋ@��
	RUN,		// ���s��
	JUMP,		// �ެ��ߊJ�n
	JUMPING,	// �ެ��ߒ�
	FALL,		// �����J�n
	FALLING,	// ������
	MAX
};

struct ActData;

using actFunc = std::function<bool(cocos2d::Sprite&,ActData&)>;

struct ActData	// ����݊i�[�p�\����
{
	ACTID actID;	
	std::list<ACTID>whiteList;		// ���삵�Ă�������݂��i�[����ؽ�
	std::list<ACTID>blackList;		// ���삵�Ă͂����Ȃ�����݂��i�[����ؽ�
	std::list<actFunc>checkModule;	// Ӽޭ�ق��i�[����ؽ�
	actFunc runAct;					// ���ۂɓ��삷�鱸���
	DIR dir;						// �����̏��
	cocos2d::Point move;			// �ړ���
	INPUT_STATE state;				// ���̓��͏��
	std::pair<Vec2,Vec2>colOffset;	// �����蔻��p�̾�č��W
};

class ActionMng
{
public:
	ActionMng(cocos2d::Sprite* sp);
	~ActionMng();
	
	void AddAct(std::string actName,ActData& data);	// ������ް��̒ǉ�
	void ActRun();									// ������ް�����������֐�
	void AnimUpdata(ACTID id,std::string move);		// ��Ұ��݂̱����ް�
	ACTID GetActID() { return m_actID; };
private:
	std::map<std::string, ActData> m_actData;		// ����݃f�[�^
	cocos2d::Sprite* m_sprite;						// ����݂�������ײĂ̏��
	ACTID m_actID;
};

