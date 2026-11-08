#ifndef CRANCHER_ATTACK_H
#define CRANCHER_ATTACK_H
#include "CState.h"

class CRancherAttack : public CState
{
public:
	void Start(CXCharacter* parent) override;
	void Update() override;
private:
	int mWaitTime;  //止める時間
	int mStepNum; //ステップの順番を表す 
};

#endif // !
