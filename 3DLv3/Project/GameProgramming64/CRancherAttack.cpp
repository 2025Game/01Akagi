#include "CRancherAttack.h"
#include "CUfo.h"
#include "CVector.h"
#include <cmath>

void CRancherAttack::Start(CXCharacter* parent)
{
	//親のポインタを保存
	mpParent = parent;
	// アニメーションの変更
	mpParent->ChangeAnimation(0, true, 60);
	
	mState = EState::EATTACK; //状態の種類を攻撃にする

	mWaitTime = 200;
	mStepNum = 0;
}

void CRancherAttack::Update()
{
	CVector PlayerPos = CUfo::Instance()->Position();
	CVector target = PlayerPos - mpParent->Position();
	
	//Y軸の回転角度を求める
	float dy_rad = atan2(target.X(), target.Z());


	//X軸,Z軸の回転は0にする
	float dx_rad = 0.0f;
	float dz_rad = 0.0f;

	//ラジアンをに変換する
	const float RAD_TO_DEG = 180.0f / 3.14159265f;

	float dx = dx_rad * RAD_TO_DEG;
	float dy = dy_rad * RAD_TO_DEG;
	float dz = dz_rad * RAD_TO_DEG;

	//回転を適用(プレイヤーの方向に向く)
	CVector r(dx, dy, dz);
	mpParent->Rotation(r);


	

	// ステップごとに処理を切り替え
	/*
	switch (mStepNum)
	{
	case 0: {  //目的地を設定する

		mStepNum++; //ステップを進める
		break;
	}
	
	case 2:

		break;

	}
	*/
	
	if (mWaitTime-- < 0)
	{
		mState = EState::EWALK;
		mWaitTime = 200;
	}
	
	
}
