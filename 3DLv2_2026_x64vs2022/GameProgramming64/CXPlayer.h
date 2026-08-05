#ifndef CXPLAYER_H
#define CXPLAYER_H

#include "CXCharacter.h"
#include "CColliderLine.h"
#include "CColliderCapsule.h"
//#include "CState.h"
#include "CXPlayerIdle.h"
#include "CPlayerWalk.h"
#include "CPlayerAttack.h"
#include "CPlayerJump.h"

class CXPlayer :public CXCharacter
{
public:
	CXPlayer();
	void Update() override;
	//衝突処理
    //Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o);
	//衝突処理
	void Collision();
	const CMatrix& FrameCombinedMatrix(const char* name);
	void Init(CModelX* model);
private:
	CColliderLine mColliderLine;
	CColliderCapsule mColliderCapsule;
	CColliderCapsule mColliderSword; //カプセルコライダ
	//EState mState;        // 状態の保持
	CState* mpState;      // 状態処理
	std::unique_ptr <CXPlayerIdle> mpIdle;     //待機状態
	std::unique_ptr<CPlayerWalk> mpWalk;       //歩く状態
	std::unique_ptr<CPlayerAttack> mpAttack;   //攻撃状態
	std::unique_ptr<CPlayerJump> mpJump;       //ジャンプ状態
};

#endif // !CXPLAYER_H
