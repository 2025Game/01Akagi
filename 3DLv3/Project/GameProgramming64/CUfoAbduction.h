#ifndef CUFO_ABDUCTION_H
#define CUFO_ABDUCTION_H
#include "CState.h"
#include "CInput.h"
#include "CColliderCapsule.h"

class CUfoAbduction : public CState
{
public:
	void Start(CXCharacter* parent) override;
	void Update() override;
	// 衝突処理
	// Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o) override;
private:
	CInput mInput;
	
};


#endif // !CUFO_ABDUCTION_H



