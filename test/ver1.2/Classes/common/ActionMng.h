#pragma once
#include <cocos2d.h>
#include <input/input.h>

USING_NS_CC;

// ｱｸｼｮﾝのID
enum class ACT_ID
{
	IDLE,		// 待機中
	RUN,		// 走行中
	JUMP,		// ｼﾞｬﾝﾌﾟ開始
	JUMPING,	// ｼﾞｬﾝﾌﾟ中
	FALL,		// 落下開始
	FALLING,	// 落下中
	MAX
};

struct ActData;

using actFunc = std::function<bool(cocos2d::Sprite&,ActData&)>;

struct ActData	// ｱｸｼｮﾝ格納用構造体
{
	ACT_ID actID;	
	std::list<ACT_ID>whiteList;		// 動作していいｱｸｼｮﾝを格納するﾘｽﾄ
	std::list<ACT_ID>blackList;		// 動作してはいけないｱｸｼｮﾝを格納するﾘｽﾄ
	std::list<actFunc>checkModule;	// ﾓｼﾞｭｰﾙを格納するﾘｽﾄ
	actFunc runAct;					// 実際に動作するｱｸｼｮﾝ
	DIR dir;						// 方向の情報
	cocos2d::Point move;			// 移動量
	INPUT_STATE state;				// ｷｰの入力状態
	std::pair<Vec2,Vec2>colOffset;	// 当たり判定用ｵﾌｾｯﾄ座標
};

class ActionMng
{
public:
	ActionMng(cocos2d::Sprite* sp);
	~ActionMng();
	
	void AddAct(std::string actName,ActData& data);	// ｱｸｼｮﾝﾃﾞｰﾀの追加
	void ActRun();									// ｱｸｼｮﾝﾃﾞｰﾀを処理する関数
	ACT_ID GetActID() { return m_actID; };			// 実行されているｱｸｼｮﾝのIDを取得
private:
	std::map<std::string, ActData> m_actData;		// ｱｸｼｮﾝデータ
	cocos2d::Sprite* m_sprite;						// ｱｸｼｮﾝさせるｽﾌﾟﾗｲﾄの情報
	ACT_ID m_actID;									// 実行されているｱｸｼｮﾝのID
};

