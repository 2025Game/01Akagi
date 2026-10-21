#include "CPlayerJump.h"

#define GRAVITY CVector(0.0f, -0.0312f, 0.0f) // 重力加速度
#define JUMP_V CVector(0.0f, 0.6f, 0.0f)      // ジャンプ初速

void CPlayerJump::Start(CXCharacter* parent)
{
	mpParent = parent;
	mpParent->ChangeAnimation(7, false, 60.0f);
	mState = EState::EJUMP;

	mJumpV = JUMP_V;
}

void CPlayerJump::Update()
{
	// ジャンプの速度分だけ、上方向に移動させる
	mpParent->Position(mpParent->Position() + mJumpV);
	// 重力加速度分だけ、下方向への速度を増やす
	mJumpV = mJumpV + GRAVITY;

}

void CPlayerJump::Collision(CCollider* m, CCollider* o)
{
	// 自身のコライダタイプの判定
	switch (m->Type())
	{
	case CCollider::EType::ECAPSULE: // カプセルコライダ
		// 相手のコライダが三角コライダの時
		if (o->Type() == CCollider::EType::ETRIANGLE)
		{
			CVector adjusts; // 調整用ベクトル
			// 三角形とカプセルの衝突判定
			if (CCollider::CollisionTriangleCapsule (o, m, &adjusts))
			{
				// 待機状態にする
				mState = EState::EIDLE;
			}
		}
		break;
	}
}


