#include "CRancherDamage.h"
#include "CUfo.h"
#include <stdio.h>

CRancherDamage::CRancherDamage()
	:mTime(20)
{
}

void CRancherDamage::Start(CXCharacter* parent)
{
	//親のポインタを保存
	mpParent = parent;

	mState = EState::EDAMAGE; //状態の種類をダメージ状態にする
}

void CRancherDamage::Update()
{
	//TODO:プレイヤーとの距離に応じて、time,ノックバックの威力を変える
	CVector fwd = CUfo::Instance()->CombinedMatrix().VectorZ();
	CVector pos = mpParent->Position();
	mpParent->Position(pos + fwd.Normalize() * 1.0f);
	
	if (mTime-- < 0)
	{
		mState = EState::EIDLE;
		mTime = 20;
	}

}

void CRancherDamage::Collision(CCollider* m, CCollider* o)
{

}
