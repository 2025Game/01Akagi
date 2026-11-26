#include "CRancherAbduction.h"
#include "CXCharacter.h"

void CRancherAbduction::Start(CXCharacter* parent)
{
	//親のポインタを保存
	mpParent = parent;

	mState = EState::EABDUCTION; //状態の種類をアブダクションにする
}

void CRancherAbduction::Update()
{
	CVector position;
	position = mpParent->Position();

	mpParent->Position(position + CVector(0.0f, 2.f, 0.0f));
}

void CRancherAbduction::Collision(CCollider* m, CCollider* o)
{
	// 自身のコライダタイプの判定
	switch (m->Type())
	{
	case CCollider::EType::ECAPSULE: // カプセルコライダ
		// 相手のコライダがトライアングルコライダの時
		if (o->Type() == CCollider::EType::ETRIANGLE)
		{


			CVector adjusts; // 調整用ベクトル

			// トライアングルとカプセルの衝突判定
			if (CCollider::CollisionTriangleCapsule(o, m, &adjusts))
			{

				//UFOの開口部に触れた場合
				if (o->Tag() == ETag::EABDUCTION_HATCH)
				{
					mpParent->Enabled(false);
					
				}

			}
		}
		break;
	}
}
