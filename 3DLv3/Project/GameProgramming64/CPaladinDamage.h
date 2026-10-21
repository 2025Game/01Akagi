#pragma once
#include "CState.h"
class CPaladinDamage : public CState
{
public:
	CPaladinDamage(CXCharacter* parent);
	void Start() override;
	void Update() override;
private:
	static int msAnimNo;
};