#ifndef CUFO_IDLE_H
#define CUFO_IDLE_H
#include "CState.h"
#include "CInput.h"

class CUfoIdle : public CState
{
public:
	void Start(CXCharacter* parent) override;
	void Update() override;
private:
	CInput mInput;
};

#endif // !CUFOIDLE_H
