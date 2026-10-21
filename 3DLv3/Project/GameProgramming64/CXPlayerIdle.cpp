#include "CXPlayerIdle.h"
#include "CXCharacter.h"

// 回転速度
#define ROTATIONSPEED 2.0f

void CXPlayerIdle::Start(CXCharacter* parent)
{
	// 親のポインタを保存
	mpParent = parent;
	// アニメーションの変更
	mpParent->ChangeAnimation(0, true, 60);
	mState = EState::EIDLE;  // 状態の種類を待機にする
}

void CXPlayerIdle::Update()
{
	// Aキーで左回転、Dキーで右回転
	if (mInput.Key('A'))
	{
		mState = EState::EWALK;
	}
	if (mInput.Key('D'))
	{
		mState = EState::EWALK;
	}
	if (mInput.Key('W'))
	{
		mState = EState::EWALK;
	}
	if (mInput.Key('S'))
	{
		mState = EState::EWALK;
	}
	if (mInput.Key('I'))
	{
		mState = EState::EATTACK;
	}
	if (mInput.Key(VK_SPACE))
	{
		mState = EState::EJUMP;
	}
	//マウスの左ボタンが押されたら
	if (mInput.Key(VK_LBUTTON))
	{
		mState = EState::EATTACK;
	}
	
}
