#pragma once
#pragma execution_character_set("utf-8")
#include <array>
#include <cocos2d.h>
#include <input/input.h>

constexpr float playerSpeed = 3.0f;			// ��ڲ԰�̈ړ���
constexpr float offsetX = 24.0f;			// ���E�p�̵̾�č��W��
constexpr float bustOffsetY = 35.0f;		// ���S����̵̾�č��W��
constexpr float legOffsetY = 65.0f;			// ���S��艺�̵̾�č��W��

class Player : public cocos2d::Sprite
{
public:
	static Player* createPlayer();	
	Player();
	~Player();
	void update(float dt);					// ���X�V
private:
	bool Init();							// �ϐ����Ұ��݂̏�����
	
	cocos2d::AnimationCache* m_animSave;	// ��Ұ��݂��ް��ۑ��p�ϐ�

	input* m_input;							// ���̓��͏��
	
	bool m_jumpFlag;						// �ެ��ߗp�׸�
	cocos2d::Vec2 m_speed[static_cast<size_t>(DIR::MAX)];	// �ړ����x
	cocos2d::Vec2 m_moveLimit;				// �ړ�����
	std::map<DIR, std::pair<cocos2d::Vec2, cocos2d::Vec2>> m_offset;

	CREATE_FUNC(Player);
};