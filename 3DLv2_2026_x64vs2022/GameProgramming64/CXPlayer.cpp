#include "CXPlayer.h"
#include "CCollisionManager.h"
#include "CCamera.h"

#define _USE_MATH_DEFINES
#include <math.h>
// ラジアンを度数に変換するための定数
const float RAD_TO_DEG = 180.0f / (float)M_PI;

#define GRAVITY 0.0625f     // 重力


CXPlayer::CXPlayer()
	: mColliderLine(this, &mMatrix, CVector(0.0f, 3.5f, 0.0f), CVector(0.0f,0.0f,0.0f))
	, mColliderCapsule(this, &mMatrix, CVector(0.0f, 3.5f, 0.0f), CVector(0.0f,0.0f,0.0f), 0.5f)
	, mColliderSword(this, nullptr, CVector(), CVector(), 0.1f)
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

	//カメラの親をプレイヤーにする
	CCamera::Instance()->Parent(this);

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

	//カメラの位置をプレイヤーの位置から、少し上にする
	CCamera::Instance()->Position(CVector(0.0f, 4.0f, 0.0f));

	mColliderCapsule.Update();
	mColliderSword.Update();
}
void CXPlayer::Collision(CCollider* m, CCollider* o)
{
	if (o == &mColliderCapsule || o == &mColliderSword)
	{
		//相手がプレイヤーのコライダの時は、衝突処理を行わない
		return;
	}

	// 状態クラスの衝突処理
	mpState->Collision(m, o);

	//自身のコライダタイプの判定
	switch (m->Type()) {
	/*
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
				//前方の位置を求める
				CVector forward = (CVector(0.0f, 0.0f, 1.0f) * mMatrix + adjust);
				if (o->Parent())
				{
					mPosition = mPosition *
						o->Parent()->CombinedMatrix().Inverse();
			
					//親のローカル座標へ変換
					forward = forward * o->Parent()->CombinedMatrix().Inverse();
					
				}
				
				//ローカル座標での向きを求める
				forward = forward - mPosition;
				//atan2fとRAD_TO_DEGを使ってY軸の回転角度を度数で求める
				//求めた回転角度をY軸に設定する
				mRotation = CVector(mRotation.X(), atan2f(forward.X(), forward.Z()) * RAD_TO_DEG, mRotation.Z());
				

				//親の設定
				mpParent = o->Parent();

				//行列の更新
				CTransform::Update();
			}
		}
		break;
	*/
	case CCollider::EType::ECAPSULE:
		if (o->Type() == CCollider::EType::ECAPSULE)
		{
			CVector adjust;//調整用ベクトル
			//カプセルとカプセルの衝突判定
			if (CCollider::CollisionCapsuleCapsule(m, o, &adjust))
			{
				//衝突している場合、プレイヤーの位置を調整する
				mPosition = CVector() * mMatrix + adjust;
				//親子関係がある場合
				if (m->Parent() && m->Parent()->Parent())
				{
					//親のローカル座標へ変換
					mPosition = mPosition *
						m->Parent()->Parent()->CombinedMatrix().Inverse();
				}
				//行列の更新
				CTransform::Update();
			}
		}
		if (o->Type() == CCollider::EType::ETRIANGLE)
		{
			CVector adjust;//調整用ベクトル
			//三角形とカプセルの衝突判定
			if (CCollider::CollisionTriangleCapsule(o, m, &adjust))
			{
				//位置の更新(mPosition + adjust)
				//現在でのワールド座標の位置
				mPosition = (CVector() * mMatrix + adjust);
				//前方の位置を求める
				CVector forward = (CVector(0.0f, 0.0f, 1.0f) * mMatrix + adjust);
				if (o->Parent())
				{
					mPosition = mPosition *
						o->Parent()->CombinedMatrix().Inverse();

					//親のローカル座標へ変換
					forward = forward * o->Parent()->CombinedMatrix().Inverse();

				}

				//ローカル座標での向きを求める
				forward = forward - mPosition;
				//atan2fとRAD_TO_DEGを使ってY軸の回転角度を度数で求める
				//求めた回転角度をY軸に設定する
				mRotation = CVector(mRotation.X(), atan2f(forward.X(), forward.Z()) * RAD_TO_DEG, mRotation.Z());


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
	
	mColliderCapsule.ChangePriority();
	CCollisionManager::Instance()->Collision(
		&mColliderCapsule, COLLISIONRANGE);

	//コライダの優先度変更
	mColliderSword.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Instance()->Collision(
		&mColliderSword,
		COLLISIONRANGE);
	
}

const CMatrix& CXPlayer::FrameCombinedMatrix(const char* name)
{
	//フレーム名から行列を取得する
	for (size_t i = 0; i < mpModel->Frames().size(); i++) {
		if (strcmp(mpModel->Frames()[i]->Name(), name) == 0) {
			return mpModel->Frames()[i]->CombinedMatrix();
		}
	}
	static CMatrix dummy; //ダミーの行列
	return dummy;
}

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//剣コライダの設定
	mColliderSword.Set(this,
		&FrameCombinedMatrix("RightHand"),
		CVector(-15.0f, 0.0f, 20.0f),
		CVector(-15.0f, 0.0f, 70.0f), 0.1f);

}