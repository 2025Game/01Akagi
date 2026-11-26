#ifndef CUFO_ATTACK_H
#define CUFO_ATTACK_H
#include "CState.h"
#include "CInput.h"
#include "CColliderCapsule.h"

class CUfoAttack : public CState
{
public:
	void Start(CXCharacter* parent) override;
	void Update() override;
	//衝突処理
	//Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o) override;
	//衝突処理
	void Collision();
private:
	CInput mInput;
	
};

#endif // !CUFO_ATTACK_H

