#ifndef CUFO_ABDUCTION_H
#define CUFO_ABDUCTION_H
#include "CState.h"
#include "CInput.h"
#include "CColliderCapsule.h"

class CUfoAbduction : public CState
{
public:
	CUfoAbduction();
	void Start(CXCharacter* parent) override;
	void Update() override;
	// 衝突処理
	// Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o) override;
private:
	int mStepNum; //ステップの順番を表す     
	CInput mInput;
	
};


#endif // !CUFO_ABDUCTION_H



