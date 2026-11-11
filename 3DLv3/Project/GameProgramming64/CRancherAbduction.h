#ifndef CRANCHER_ABDUCTION_H
#define CRANCHER_ABDUCTION_H
#include "CState.h"


class CRancherAbduction : public CState
{
public:
	void Start(CXCharacter* parent) override;
	void Update() override;
private:

};

#endif // !CRANCHER_ABDUCTION

