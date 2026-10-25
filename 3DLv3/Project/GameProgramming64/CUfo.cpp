#include "CUfo.h"
#include "CCollisionManager.h"
#include "CCamera.h"

#define UFO_MODEL "res\\paladin\\Paladin WProp J Nordstrom@Idle.fbx.x"
#define UFO_RADIUS 2.0f


CUfo::CUfo()
	:mCollider(this, &mMatrix, CVector(0.0f,1.5f,0.0f), UFO_RADIUS)
{


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

	//タグの設定
	Tag(ETag::EPLAYER);
	mCollider.Tag(ETag::EPLAYER);

	//カメラの親をプレイヤーにする
	CCamera::Instance()->Parent(this);
	
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
		default:
			break;
		}
		mpState->Start(this);
	}

	// 親クラスの更新
	CXCharacter::Update();

	//カメラの位置をプレイヤーの位置から、少し上にする
	CCamera::Instance()->Position(CVector(0.0f, 4.0f, 0.0f));

	
}

void CUfo::Collision(CCollider* m, CCollider* o)
{
	if (o == &mCollider)
	{
		//相手がプレイヤーのコライダの時は、衝突処理を行わない
		return;
	}


	// 状態クラスの衝突処理
	mpState->Collision(m, o);

	//自身のコライダタイプの判定
	switch (m->Type()) {
	case CCollider::EType::ESPHERE:
		
		break;
	}
}
//衝突処理
void CUfo::Collision()
{
	mCollider.ChangePriority();
}
void CUfo::Init(CModelX* model)
{
	CXCharacter::Init(model);
}