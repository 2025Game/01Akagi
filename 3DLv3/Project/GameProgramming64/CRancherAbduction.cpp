#include "CRancherAbduction.h"
#include "CXCharacter.h"

void CRancherAbduction::Start(CXCharacter* parent)
{
	//親のポインタを保存
	mpParent = parent;

	mState = EState::EABDUCTION; //状態の種類を歩くにする
}

void CRancherAbduction::Update()
{
	CVector position;
	position = mpParent->Position();

	mpParent->Position(position + CVector(0.0f, 1.f, 0.0f));
}
