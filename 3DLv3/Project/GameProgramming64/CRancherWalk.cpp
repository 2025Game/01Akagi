#include "CRancherWalk.h"
#include "CXCharacter.h"
#include "CBullet.h"
#include "Random.h"
#include "CUfo.h"

//移動速度
#define VELOCITY 0.1f
// 回転速度
#define ROTATIONSPEED 2.0f
#define WAITTIME 100.0f

CRancherWalk::CRancherWalk()
	: mStepNum(0)
	, mDestinationPos(CVector(0.0f,0.0f,0.0f))
	, mWaitTime(WAITTIME)
{
}

void CRancherWalk::Start(CXCharacter* parent)
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
	switch (mStepNum)
	{
	case 0: {  //目的地を設定する
		SetPoint();

		mStepNum++; //ステップを進める
		break;
	}
	case 1: {   //目的地に進む

		//目的地までの距離を求める
		CVector ToDestination, RancherPos;
		RancherPos = mpParent->Position();
		ToDestination = mDestinationPos - RancherPos;

		//内積を計算して、方向を求める
		float dx = ToDestination.Dot(mpParent->MatrixRotate().VectorX());
		float dz = ToDestination.Dot(mpParent->MatrixRotate().VectorZ());

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
		mpParent->Position(RancherPos +
			mpParent->MatrixRotate().VectorZ() * VELOCITY);
		
		//目的地に近くなったら
		if (ToDestination.Length() < 10.0f)
		{	
			mStepNum = 0;
		}
		
		//周りにプレイヤー(UFOがいると)
		CVector PlayerPos = CUfo::Instance()->Position();
		if ((RancherPos - PlayerPos).Length() < 50.0f)
		{
			mState = EState::EATTACK;   //攻撃状態にする
			printf("近づいた");
			
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
