#ifndef CRANCHER_WALK_H
#define CRANCHER_WALK_H
#include "CState.h"
#include "CVector.h"

class CRancherWalk : public CState
{
public:
	CRancherWalk(CXCharacter* parent);
	void Update() override;
	void SetPoint();
private:
	int mStateStep; //ステップの順番     
	CVector mDestinationPos; //目的地の座標
	int time;
};


#endif // !CRANCHER_WALK_H
