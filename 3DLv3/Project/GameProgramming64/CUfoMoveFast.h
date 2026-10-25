#ifndef CUFO_MOVEFAST_H
#define CUFO_MOVEFAST_H
#include "CState.h"
#include "CInput.h"


class CUfoMoveFast : public CState
{
public:
	void Start(CXCharacter* parent) override;
	void Update() override;
private:
	CInput mInput;
};

#endif // 

