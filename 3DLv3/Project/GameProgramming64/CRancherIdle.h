#ifndef CRANCHER_IDLE_H
#define CRANCHER_IDLE_H
#include "CState.h"
#include "CCharacter3.h"
#include "CCollider.h"

class CRancherIdle : public CState
{
public:
	void Start(CXCharacter* parent) override;
	void Update() override;
	//衝突処理
	//Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o);
	//衝突処理
	void Collision();
};

#endif // !CRANCHER_IDLE_H
