#ifndef CUFO_ABDUCTION_H
#define CUFO_ABDUCTION_H
#include "CState.h"
#include "CInput.h"

class CUfoAbduction : public CState
{
public:
	void Start(CXCharacter* parent) override;
	void Update() override;
private:
	CInput mInput;
};


#endif // !CUFO_ABDUCTION_H



