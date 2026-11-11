#include "CRancherAttack.h"
#include "CUfo.h"
#include "CVector.h"
#include "CBullet.h"
#include <cmath>

#define INTERVAL_TIME 200  //準備時間
#define RELOAD_TIME 20  //リロード時間
#define RADIUS 30.0f  //攻撃するまでの硬直時間

CRancherAttack::CRancherAttack()
	: mWaitTime(INTERVAL_TIME)
	, mStepNum(0)
{
}

void CRancherAttack::Start(CXCharacter* parent)
{
	//親のポインタを保存
	mpParent = parent;
	// アニメーションの変更
	mpParent->ChangeAnimation(0, true, 60);
	
	mState = EState::EATTACK; //状態の種類を攻撃にする

}

void CRancherAttack::Update()
{
	CVector PlayerPos = CUfo::Instance()->Position();
	CVector target = PlayerPos - mpParent->Position();
	
	//水平方向の距離（XZ平面上の距離）を求める
	float distanceXZ = sqrt(target.X() * target.X() + target.Z() * target.Z());

	//各軸の回転角度を求める
	float dx_rad = -atan2(target.Y(), distanceXZ);
	float dy_rad = atan2(target.X(), target.Z());

	//Z軸の回転は0にする
	float dz_rad = 0.0f;

	//ラジアンをに変換する
	const float RAD_TO_DEG = 180.0f / 3.14f;

	float dx = dx_rad * RAD_TO_DEG;
	float dy = dy_rad * RAD_TO_DEG;
	float dz = dz_rad * RAD_TO_DEG;

	//回転を適用(プレイヤーへ水平方向に向けて)
	//Y軸にはモデルを正面にさせるための数を加算する
	CVector r(0.0f, dy + 30.0f, dz);
	mpParent->Rotation(r);

	//
	CVector lookat(dx, dy, dz);


	

	// ステップごとに処理を切り替え
	switch (mStepNum)
	{
	case 0: {  //弾を撃つ

		//弾を撃つまでの準備時間が経過したら
		if (mWaitTime-- < 0)
		{
			mWaitTime = RELOAD_TIME;  //リロード時間を入れる
			mStepNum++; //ステップを進める

			//弾を撃つ
			CBullet* bullet = new CBullet();
			bullet->Set(2.0f, 1.5f);
			bullet->Rotation(lookat);
			bullet->Position(
				 CVector(0.0f, 1.0f, 1.0f) * mpParent->Matrix());
			bullet->Update();

		}
		
		break;
	}
	case 1: //リロード時間
		//
		if (mWaitTime-- < 0)
		{
			mStepNum = 0;  
			mWaitTime = INTERVAL_TIME;  //攻撃するまでの硬直時間を入れる
			mState = EState::EWALK;
		}
		break;
	}
	
	
	
	
	
}
