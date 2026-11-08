#ifndef CRANCHER_IDLE_H
#define CRANCHER_IDLE_H
#include "CState.h"

class CRancherIdle : public CState
{
public:
	void Start(CXCharacter* parent) override;
	void Update() override;
private:
};

#endif // !CRANCHER_IDLE_H
