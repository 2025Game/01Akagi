#include"CPlayerAttack.h"

void CPlayerAttack::Start(CXCharacter* parent)
{
	mpParent = parent;
	mpParent->ChangeAnimation(3, false, 30);
	mState = EState::EATTACK;

	DelayCnt = 13;
}

void CPlayerAttack::Update()
{
	// アニメーションが終了しているか
	if (mpParent->IsAnimationFinished())
	{

		// 攻撃してしばらくしたら
		if (--DelayCnt <= 0)
		{
			// アニメーションが終了したら待機状態にする
			mState = EState::EIDLE;

			
		}
		
	}
}
