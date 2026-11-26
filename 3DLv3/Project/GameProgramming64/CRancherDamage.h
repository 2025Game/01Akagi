#ifndef CRANCHER_DAMAGE_H
#define CRANCHER_DAMAGE_H
#include "CState.h"
#include "CColliderCapsule.h"

class CRancherDamage : public CState
{
public:
	CRancherDamage();
	void Start(CXCharacter* parent) override;
	void Update() override;
	//衝突処理
	//Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o) override;
	//衝突処理
	void Collision();
private:
	int mTime;
};

#endif // !CUFO_ATTACK_H

