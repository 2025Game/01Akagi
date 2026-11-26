#ifndef CUFO_H
#define CUFO_H
#include "CXCharacter.h"
#include "CCollider.h"
#include "CColliderTriangle.h"
#include "CUfoIdle.h"
#include "CUfoMove.h"
#include "CUfoMoveFast.h"
#include "CUfoAbduction.h"
#include "CUfoAttack.h"


class CUfo : public CXCharacter
{
public:
	CUfo();
	//インスタンスの取得
	static CUfo* Instance();
	void Update() override;
	//衝突処理
	//Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o);
	//衝突処理
	void Collision();
	void Init(CModelX* model);
private:
	static CUfo* mpInstance;  //インスタンス
	CColliderCapsule mColliderCapsule;  //UFOの当たり判定
	CColliderCapsule mAttackCapsule;    //攻撃の当たり判定
	CColliderTriangle mBottomCollider[2];//底面の当たり判定(npc回収の判定に使う)
	CState* mpState;  //状態処理
	std::unique_ptr <CUfoIdle> mpIdle;     //待機状態
	std::unique_ptr<CUfoMove> mpMove;       //動く状態
	std::unique_ptr<CUfoMoveFast> mpMoveFast; //早く動く状態
	std::unique_ptr<CUfoAbduction> mpAbduction; //アブダクション中状態
	std::unique_ptr <CUfoAttack> mpAttack; //攻撃状態

	int mHp;
};

#endif // !CUFO_H

