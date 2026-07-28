#ifndef CPALADIN_H
#define CPALADIN_H
#include "CXCharacter.h"
#include "CColliderCapsule.h"
#include "CPaladinIdle.h"
class CPaladin : public CXCharacter
{
public:
	//CPaladin(位置, 回転, 拡大縮小)
	CPaladin(const CVector& pos, const CVector& rot = CVector()
		, const CVector& scale = CVector(2.5f, 2.5f, 2.5f));
	void Update() override;
	//衝突処理
	//Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o);
	//衝突処理
	void Collision();
private:
	static CModelX msModel;
	CColliderCapsule mCollider; //カプセルコライダ
	EState mState;
	CState* mpState;
	std::unique_ptr<CPaladinIdle> mpIdle;
};
#endif