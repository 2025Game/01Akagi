#ifndef CRANCHER_WALK_H
#define CRANCHER_WALK_H
#include "CState.h"

class CRancherWalk : public CState
{
public:
	CRancherWalk(CXCharacter* parent);
	void Update() override;
private:
	int time;
};


#endif // !CRANCHER_WALK_H
