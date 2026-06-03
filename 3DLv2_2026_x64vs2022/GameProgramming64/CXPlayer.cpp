#include "CXPlayer.h"
#include "CCollisionManager.h"

#define GRAVITY 0.0625f     // 重力


CXPlayer::CXPlayer()
	:mColliderLine(this, &mMatrix, CVector(0.0f, 3.5f, 0.0f), CVector(0.0f,0.0f,0.0f))
{
	// 待機状態の作成
	mpIdle = std::make_unique<CXPlayerIdle>();
	// 最初は待機状態
	// get()はunique_ptrが保持しているポインタを取得する関数
	mpState = mpIdle.get();
	mpState->Start(this);
	mState = mpState->State();

	//歩く状態の作成
	mpWalk = std::make_unique<CPlayerWalk>();
	//攻撃状態の作成
	mpAttack = std::make_unique<CPlayerAttack>();
	//ジャンプ状態の作成
	mpJump = std::make_unique<CPlayerJump>();

}
void CXPlayer::Update()
{
	// 状態の更新
	mpState->Update();
	//状態の切り替え
	if (mState != mpState->State())
	{
		mState = mpState->State();
		switch (mState) {
		case EState::EIDLE:
			mpState = mpIdle.get();
			break;
		case EState::EWALK:
			mpState = mpWalk.get();
			break;
		case EState::EATTACK:
			mpState = mpAttack.get();
			break;
		case EState::EJUMP:
			mpState = mpJump.get();
			break;
		default:
			break;
		}
		mpState->Start(this);
	}


	// GRAVITYの大きさぶんだけ、下方向へ移動させる
	mPosition = mPosition - CVector(0.0f, GRAVITY, 0.0f);

	// 親クラスの更新
	CXCharacter::Update();
}
void CXPlayer::Collision(CCollider* m, CCollider* o)
{
	// 状態クラスの衝突処理
	mpState->Collision(m, o);

	//自身のコライダタイプの判定
	switch (m->Type()) {
	case CCollider::EType::ELINE://線分コライダ
		//相手のコライダが三角コライダの時
		if (o->Type() == CCollider::EType::ETRIANGLE)
		{
			CVector adjust;//調整用ベクトル
			//三角形と線分の衝突判定
			if (CCollider::CollisionTriangleLine(
				o, m, &adjust))
			{
				//位置の更新(mPosition + adjust)
				//現在でのワールド座標の位置
				mPosition = (CVector() * mMatrix + adjust);
				if (o->Parent())
				{
					mPosition = mPosition *
						o->Parent()->CombinedMatrix().Inverse();
				}
				//親の設定
				mpParent = o->Parent();

				//行列の更新
				CTransform::Update();
			}
		}
		break;
	}
}
//衝突処理
void CXPlayer::Collision()
{
	//コライダの優先度変更
	mColliderLine.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Instance()->Collision(
		&mColliderLine, COLLISIONRANGE);

}