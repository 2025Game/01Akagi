#pragma once
#include "CState.h"
#include "CCharacter3.h"
class CPaladinIdle : public CState
{
public:
	CPaladinIdle() {};
	CPaladinIdle(CXCharacter* parent);
	void Start() override;
	void Update() override;
private:
	static int msAnimNo; //アニメーション番号

	
};
