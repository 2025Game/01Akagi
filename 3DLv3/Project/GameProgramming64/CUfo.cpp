#include "CUfo.h"
#include "CCollisionManager.h"
#include "CCamera.h"
#include "CEffect.h"

#define UFO_MODEL "res\\paladin\\Paladin WProp J Nordstrom@Idle.fbx.x"
#define UFO_RADIUS 2.0f

//UFOのインスタンス
CUfo* CUfo::mpInstance = nullptr;

//インスタンスの取得
CUfo* CUfo::Instance()
{
	//インスタンスが無ければ
	if (mpInstance == nullptr)
	{	//インスタンスを生成する
		mpInstance = new CUfo();
	}
	return mpInstance;
}

CUfo::CUfo() //TODO:UFOにぴったりのコライダーを考える
	: mColliderCapsule(this, &mMatrix, CVector(0.0f,3.5f,0.0f), CVector(0.0f, 0.5f, 0.0f), UFO_RADIUS)
	, mAttackCapsule(this, &mMatrix, CVector(0.0f, 3.5f, 0.0f), CVector(0.0f, 3.5f, 50.0f), 5.0f)
	, mHp(10)
{

	mBottomCollider[0].Set(
		this,
		&mMatrix,
		CVector(-4.0f, 1.0f, -4.0f),
		CVector(4.0f, 1.0f, 4.0f),
		CVector(4.0, 1.0f, -4.0)
		);
	mBottomCollider[1].Set(
		this,
		&mMatrix,
		CVector(-4.0f, 1.0f, -4.0f),
		CVector(-4.0f, 1.0f, 4.0f),
		CVector(4.0, 1.0f, 4.0f)
		);
	
	// 待機状態の作成
	mpIdle = std::make_unique<CUfoIdle>();
	// 最初は待機状態
	// get()はunique_ptrが保持しているポインタを取得する関数
	mpState = mpIdle.get();
	mpState->Start(this);
	mState = mpState->State();

	//動く状態の作成
	mpMove = std::make_unique<CUfoMove>();
	//はやく動く状態の作成
	mpMoveFast = std::make_unique<CUfoMoveFast>();
	//アブダクション中状態の作成
	mpAbduction = std::make_unique<CUfoAbduction>();
	//攻撃状態の作成
	mpAttack = std::make_unique<CUfoAttack>();

	//タグの設定
	Tag(ETag::EUFO);
	mColliderCapsule.Tag(ETag::EUFO);
	mBottomCollider[0].Tag(ETag::EABDUCTION_HATCH);
	mBottomCollider[1].Tag(ETag::EABDUCTION_HATCH);
	mAttackCapsule.Tag(ETag::EUFO_ATTACK_BEAM);
	
	//カメラの親をプレイヤーにする
	CCamera::Instance()->Parent(this);
	
	mpInstance = this;
}

void CUfo::Update()
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
		case EState::EMOVE:
			mpState = mpMove.get();
			break;
		case EState::EMOVE_FAST:
			mpState = mpMoveFast.get();
			break;
		case EState::EABDUCTION:
			mpState = mpAbduction.get();
			break;
		case EState::EATTACK:
			mpState = mpAttack.get();
			break;
		default:
			break;
		}
		mpState->Start(this);
	}

	// 親クラスの更新
	CXCharacter::Update();

	//アブダクション中でないとき
	if (mpState->State() != EState::EABDUCTION)
	{
		//カメラの位置をプレイヤーの位置から、少し上にする
		CCamera::Instance()->Position(CVector(0.0f, 4.0f, 0.0f));
	}
	
	//コライダの更新
	mColliderCapsule.Update();
	mAttackCapsule.Update();
	
}

void CUfo::Collision(CCollider* m, CCollider* o)
{
	if (o == &mColliderCapsule 
		|| o == &mBottomCollider[0] || o == &mBottomCollider[1] 
		|| o == &mAttackCapsule)
	{
		//相手がプレイヤーのコライダの時は、衝突処理を行わない
		return;
	}

	// 状態クラスの衝突処理
	mpState->Collision(m, o);

	//自身のコライダタイプの判定
	switch (m->Type()) {
	case CCollider::EType::ECAPSULE:
		if (m == &mAttackCapsule) { return; } //攻撃用コライダは判定しない
		if (o->Type() == CCollider::EType::ETRIANGLE)
		{
			CVector adjust;//調整用ベクトル
			if (CCollider::CollisionTriangleCapsule(o, m, &adjust));
			{
				//位置の更新(mPosition + adjust)
				//現在でのワールド座標の位置
				mPosition = (CVector() * mMatrix + adjust);
			}

			//行列の更新
			CTransform::Update();
		}
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
		if (o->Type() == CCollider::EType::ESPHERE)
		{

			if (CCollider::Collision(m, o))
			{
				//弾に当たっているとき
				if (o->Tag() == ETag::EBULLET)
				{
					mHp--;
					printf("HP:%d\n", mHp);
					//エフェクト生成
					new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);

				}
			}
		}
		break;
	}
}
//衝突処理
void CUfo::Collision()
{
	mColliderCapsule.ChangePriority();
	CCollisionManager::Instance()->Collision(
		&mColliderCapsule, COLLISIONRANGE
	);

	mBottomCollider[0].ChangePriority();
	mBottomCollider[1].ChangePriority();
	CCollisionManager::Instance()->Collision(
		&mBottomCollider[0], COLLISIONRANGE
	);
	CCollisionManager::Instance()->Collision(
		&mBottomCollider[1], COLLISIONRANGE
	);
	mAttackCapsule.ChangePriority();
	CCollisionManager::Instance()->Collision(
		&mAttackCapsule, COLLISIONRANGE
	);

}
void CUfo::Init(CModelX* model)
{
	CXCharacter::Init(model);
}