#pragma once
#include "CState.h"
#include "CCharacter3.h"
#include "CCollider.h"
class CPaladinIdle : public CState
{
public:
	CPaladinIdle(CXCharacter* parent);
	void Start() override;
	void Update() override;

	// 衝突処理
	// Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o) override;
private:
	static int msAnimNo; //アニメーション番号

	
};
