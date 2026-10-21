#include "CPaladinIdle.h"
#include "CXCharacter.h"

#define ANIMATION_FILE "res\\paladin\\sword and shield idle.fbx.x"
int CPaladinIdle::msAnimNo = 0;

CPaladinIdle::CPaladinIdle(CXCharacter* parent)
{
	//モデルの読み込み
	static bool first = true;
	if (first) {
		//アニメーションの読み込み
		parent->Model()->AddAnimationSet(ANIMATION_FILE);
		msAnimNo = parent->Model()->AnimationSet().size() - 1;
		first = false;
	}
	//親のポインタを保存
	mpParent = parent;
}
void CPaladinIdle::Start()
{
	int animation_size =
		mpParent->Model()->AnimationSet()[msAnimNo]->MaxTime();
	//アニメーションの変更
	mpParent->ChangeAnimation(msAnimNo, true, animation_size);
	mState = EState::EIDLE; //状態の種類を待機にする
}
void CPaladinIdle::Update()
{
}

void CPaladinIdle::Collision(CCollider* m, CCollider* o)
{
	// 自身のコライダタイプの判定
	switch (m->Type())
	{
	case CCollider::EType::ECAPSULE: // カプセルコライダ
		// 相手のコライダがカプセルコライダの時
		if (o->Type() == CCollider::EType::ECAPSULE)
		{
			

			CVector adjusts; // 調整用ベクトル
			


			// カプセルとカプセルの衝突判定
			if (CCollider::CollisionCapsuleCapsule(o, m, &adjusts))
			{
				
				if (o->Parent()->Tag() == ETag::EPLAYER &&
					o->Parent()->State() == EState::EATTACK &&
					o->Tag() == ETag::ESWORD)
				{
					// ダメージ状態にする
					mState = EState::EDAMAGE;
					

				}
				
			}
		}
		break;
	}
}
