#ifndef CUFO_MOVE_H
#define CUFO_MOVE_H
#include "CState.h"
#include "CInput.h"

class CUfoMove : public CState
{
public:
	void Start(CXCharacter* parent) override;
	void Update() override;
private:
	CInput mInput;
};

#endif // !CUFO_MOVE_H