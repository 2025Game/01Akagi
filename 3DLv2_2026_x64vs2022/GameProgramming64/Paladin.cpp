#include "Paladin.h"
#include "CCollisionManager.h"


#define _USE_MATH_DEFINES
#include <math.h>
// ラジアンを度数に変換するための定数
const float RAD_TO_DEG = 180.0f / (float)M_PI;

#define PALADIN_MODEL "res\\paladin\\Paladin WProp J Nordstrom@Idle.fbx.x"
#define GRAVITY 0.0625f     // 重力

//static変数の定義
CModelX CPaladin::msModel;

CPaladin::CPaladin(const CVector& pos, const CVector& rot,

	const CVector& scale)
	: mCollider(this, &mCombinedMatrix, CVector(0.0f, 4.0f, 0.0f),
		CVector(0.0f, 0.0f, 0.0f), 0.5f)

{
	//static変数は初期値の状態で1つだけ作成され削除されない。
	//1つ作成されたらその後初期値の代入はされない。
	static bool first = true;
	if (first)
	{
		msModel.Load(PALADIN_MODEL);
		first = false;
	}
	Init(&msModel);
	mPosition = pos;
	mRotation = rot;
	mScale = scale;

	// 待機状態の作成
	mpIdle = std::make_unique<CPaladinIdle>(this);
	
	
	mpState = mpIdle.get();
	mpState->Start();
	mState = mpState->State();
	//状態の更新
	mpState->Update();



	//ダメージ状態の作成
	mpDamage = std::make_unique<CPaladinDamage>(this);
	
}
void CPaladin::Collision(CCollider* m, CCollider* o)
{
	// 状態クラスの衝突処理
	mpState->Collision(m, o);

	//自身のコライダタイプの判定
	switch (m->Type()) {
	case CCollider::EType::ECAPSULE:
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
void CPaladin::Update()
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
		case EState::EDAMAGE:
			mpState = mpDamage.get();
			break;
		default:
			break;
		}
		mpState->Start();

	}
	// GRAVITYの大きさぶんだけ、下方向へ移動させる
	mPosition = mPosition - CVector(0.0f, GRAVITY, 0.0f);

	// 親クラスの更新
	CXCharacter::Update();

	mCollider.Update();
}

void CPaladin::Collision()
{
	mCollider.ChangePriority();
	CCollisionManager::Instance()->Collision(
		&mCollider, COLLISIONRANGE);
}