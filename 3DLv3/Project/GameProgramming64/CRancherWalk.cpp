#include "CRancherWalk.h"
#include "CXCharacter.h"
#include "CBullet.h"
#include "CUfo.h"


//移動速度
#define VELOCITY 0.1f
// 回転速度
#define ROTATIONSPEED 2.0f

CRancherWalk::CRancherWalk(CXCharacter* parent)
	:time(5)
{
	//親のポインタを保存
	mpParent = parent;
	//アニメーションの変更
	mpParent->ChangeAnimation(1, true, 60);
	mState = EState::EWALK; //状態の種類を歩くにする
}

void CRancherWalk::Update()
{

	CVector p = mpParent->Position();
	mpParent->Position(p +
		mpParent->MatrixRotate().VectorZ() * VELOCITY);

	if (--time < 0)
	{
		CUfo* player = CUfo::Instance();
		//プレイヤーまでのベクトルを求める
		CVector vp = player->Position() - mpParent->Position();
		//左ベクトルとの内積を求める
		float dx = vp.Dot(mpParent->MatrixRotate().VectorX());
		//上ベクトルとの内積を求める
		float dy = vp.Dot(mpParent->MatrixRotate().VectorY());

		//X軸のズレが2.0未満
		if (-2.0f < dx && dx < 2.0f)
		{
			//Y軸のズレが2.0未満
			if (-2.0f < dy && dy < 2.0f)
			{
				//弾を発射します
				CBullet* bullet = new CBullet();
				bullet->Set(1.0f, 1.5f);
				bullet->Position(
					CVector(0.0f, 2.0f, 10.0f) * mpParent->Matrix());
				bullet->Rotation(mpParent->Rotation());
				bullet->Update();

				time = 5;
			}
		}
		
	}
	

	/*
	CBullet* bullet = new CBullet();
	bullet->Set(0.1f, 1.5f);
	bullet->Position(CVector(0.0f, 0.0f, 10.0f) * mpParent->Matrix());
	bullet->Rotation(mpParent->Rotation());
	bullet->Update();
	*/
}