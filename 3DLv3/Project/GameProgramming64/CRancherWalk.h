#ifndef CRANCHER_WALK_H
#define CRANCHER_WALK_H
#include "CState.h"
#include "CVector.h"

class CRancherWalk : public CState
{
public:
	CRancherWalk();
	void Start(CXCharacter* parent) override;
	void Update() override;
	void SetPoint();
private:
	int mStepNum; //ステップの順番を表す     
	CVector mDestinationPos; //目的地の座標
	int mWaitTime;  //止める時間
};


#endif // !CRANCHER_WALK_H
