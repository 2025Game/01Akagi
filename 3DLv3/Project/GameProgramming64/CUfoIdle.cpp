#include "CUfoIdle.h"


// 回転速度
#define ROTATIONSPEED 2.0f

void CUfoIdle::Start(CXCharacter* parent)
{
	// 親のポインタを保存
	mpParent = parent;

	mState = EState::EIDLE;  // 状態の種類を待機にする
}

void CUfoIdle::Update()
{
	// Aキーで左回転、Dキーで右回転
	if (mInput.Key('A'))
	{
		mState = EState::EMOVE;
	}
	if (mInput.Key('D'))
	{
		mState = EState::EMOVE;
	}
	if (mInput.Key('W'))
	{
		mState = EState::EMOVE;
	}
	if (mInput.Key('S'))
	{
		mState = EState::EMOVE;
	}
	if (mInput.Key(VK_SPACE))
	{
		mState = EState::EMOVE;
	}
	if (mInput.Key(VK_SHIFT))
	{
		mState = EState::EMOVE;
	}
	
	
}
