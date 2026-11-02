#ifndef CRANCHER_H
#define CRANCHER_H
#include "CXCharacter.h"
#include "CColliderCapsule.h"
#include "CRancherIdle.h"
#include "CRancherWalk.h"

class CRancher :public CXCharacter
{
public:
	//CRancher(位置, 回転, 拡大縮小)
	CRancher(const CVector& pos, const CVector& rot = CVector()
		, const CVector& scale = CVector(2.5f, 2.5f, 2.5f));
	void Update() override;
	//衝突処理
	//Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o);
	//衝突処理
	void Collision();
private:
	static CModelX msModel;
	CColliderCapsule mColliderCapsule; //カプセルコライダ
	CState* mpState;  //状態処理
	std::unique_ptr<CRancherIdle> mpIdle;     //待機状態
	std::unique_ptr<CRancherWalk> mpWalk;     //歩く状態
};
#endif // !CRANCHER_H
