#include "CRancherIdle.h"
#include "CXCharacter.h"

void CRancherIdle::Start(CXCharacter* parent)
{
	// 親のポインタを保存
	mpParent = parent;
	// アニメーションの変更
	mpParent->ChangeAnimation(0, true, 60);
	mState = EState::EIDLE;  // 状態の種類を待機にする
}

void CRancherIdle::Update()
{
	mState = EState::EWALK;
}
