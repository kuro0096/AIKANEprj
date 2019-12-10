#pragma once
#include <cocos2d.h>
#include <input/input.h>

USING_NS_CC;

// ����݂�ID
enum class ACT_ID
{
	IDLE,		// �ҋ@��
	RUN,		// ���s��
	JUMP,		// �ެ��ߊJ�n
	JUMPING,	// �ެ��ߒ�
	FALL,		// ����
	MAX
};

struct ActData;

using actFunc = std::function<bool(cocos2d::Sprite&,ActData&)>;

// ����݊i�[�p�\����
struct ActData
{
	ACT_ID actID;	
	std::list<ACT_ID>whiteList;		// ���삵�Ă�������݂��i�[����ؽ�
	std::list<ACT_ID>blackList;		// ���삵�Ă͂����Ȃ�����݂��i�[����ؽ�
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
	
	// ������ް��̒ǉ�
	void AddAct(std::string actName,ActData& data);	
	// ������ް�����������֐�
	void ActRun();
	// ���s����Ă��鱸��݂�ID���擾
	ACT_ID GetActID() { return m_actID; };
	// ����݂�ID��ݒ�
	void SetActID(ACT_ID actID) { m_actID = actID; }
	// �����Ă���������擾
	DIR GetActDir() { return m_actDir; };
private:
	std::map<std::string, ActData> m_actData;			// ����݃f�[�^
	cocos2d::Sprite* m_sprite;							// ����݂�������ײĂ̏��
	ACT_ID m_actID;										// ���s����Ă��鱸��݂�ID
	DIR m_actDir;										// �����Ă������										
};

