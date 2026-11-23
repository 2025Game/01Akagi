#ifndef CUFO_ATTACK_H
#define CUFO_ATTACK_H
#include "CState.h"
#include "CInput.h"

class CUfoAttack : public CState
{
public:
	void Start(CXCharacter* parent) override;
	void Update() override;
private:
	CInput mInput;
};

#endif // !CUFO_ATTACK_H

