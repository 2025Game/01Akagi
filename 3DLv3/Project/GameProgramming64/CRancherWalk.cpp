#include "CRancherWalk.h"
#include "CXCharacter.h"
#include "CBullet.h"
#include "Random.h"
#include "CUfo.h"


//移動速度
#define VELOCITY 0.1f
// 回転速度
#define ROTATIONSPEED 2.0f

CRancherWalk::CRancherWalk(CXCharacter* parent)
	: mStateStep(0)
	, mDestinationPos(CVector(0.0f, 0.0f, 0.0f))
	, time(10)
{
	//親のポインタを保存
	mpParent = parent;
	//アニメーションの変更
	mpParent->ChangeAnimation(1, true, 60);
	mState = EState::EWALK; //状態の種類を歩くにする
}

void CRancherWalk::Update()
{

	// ステップごとに処理を切り替え
	switch (mStateStep)
	{
	case 0: {  //目的地を設定する
		SetPoint();

		mStateStep++; //ステップを進める
		break;
	}
	case 1: {   //目的地に進む

		CVector pos;
		pos = mDestinationPos - mpParent->Position();

		//内積を計算して、方向を求める
		float dx = pos.Dot(mpParent->MatrixRotate().VectorX());
		float dz = pos.Dot(mpParent->MatrixRotate().VectorZ());

		const float margin = 0.1f;
		float turnAmount = 5.0f; //回転量

		//目的地が真後ろになっている場合
		if (dz < 0.0f && abs(dx) < margin)
		{
			dx = -1.0f; //旋回させる
		}

		//左右方向へ回転
		if (dx > margin)
		{
			//左へ回転
			mpParent->Rotation(mpParent->Rotation() + CVector(0.0f, turnAmount, 0.0f));
		}
		else if (dx < -margin)
		{
		    //右へ回転
			mpParent->Rotation(mpParent->Rotation() - CVector(0.0f, turnAmount, 0.0f));


		}

		//前に進ませる
		CVector p = mpParent->Position();
		mpParent->Position(p +
			mpParent->MatrixRotate().VectorZ() * VELOCITY);

		//目的地に近くなったら
		if (pos.Length() < 10.0f)
		{
			mStateStep = 0;
		}
		break;
	}
	case 2:   

		break;

	}

	
	
}

//目的地を設定する
void CRancherWalk::SetPoint()
{
	float x, z;
	CVector pos = mpParent->Position();

	x = pos.X() + Random::get(-50.0f, 50.0f);
	z = pos.Z() + Random::get(-50.0f, 50.0f);
	printf("%f\n%f", x, z);
	mDestinationPos = CVector(x, pos.Y(), z);

}
