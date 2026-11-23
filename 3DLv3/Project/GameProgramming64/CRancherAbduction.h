#ifndef CRANCHER_ABDUCTION_H
#define CRANCHER_ABDUCTION_H
#include "CState.h"
#include "CCollider.h"

class CRancherAbduction : public CState
{
public:
	void Start(CXCharacter* parent) override;
	void Update() override;
	// 衝突処理
	// Collision(コライダ1, コライダ2)
    void Collision(CCollider* m, CCollider* o) override;
private:

};

#endif // !CRANCHER_ABDUCTION

