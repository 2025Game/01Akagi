#include "CUfoAbduction.h"
#include "CXCharacter.h"
#include "CCamera.h"
#include "Utility.h"
#define VELOCITY 0.1f   //カメラの移動距離
#define ABDUCTION_CAMERA_POS CVector(0.0f, 7.0f, 0.0f)  //アブダクション中のカメラの位置

CUfoAbduction::CUfoAbduction()
	: mStepNum(0)
	, mVelocity(VELOCITY)  //カメラの移動量
    , mMoveDist(0.0f)      //カメラがこれまで進んだ距離
    , mTotalDist(0.0f)     //カメラの目的までの距離
	, mCameraStartPos(0.0f,0.0f,0.0f)
{
}

void CUfoAbduction::Start(CXCharacter* parent)
{
	//親のポインタを保存
	mpParent = parent;
    
	mState = EState::EABDUCTION; //状態の種類をアブダクション中にする

	mCameraStartPos = CCamera::Instance()->Position();
}

void CUfoAbduction::Update()
{
	//左クリックが押されていないと
	if (mInput.Key(VK_LBUTTON) == false)
	{
		//待機状態にする
		mState = EState::EIDLE;



		//カメラ移動に使うメンバ変数を初期化
		mMoveDist = 0.0f;
		mTotalDist = 0.0f;
		mVelocity = VELOCITY;
		mStepNum = 0;
	}
	//左クリックを押したまま右クリックを押すと
	else if(mInput.Key(VK_RBUTTON)) 
	{
		//攻撃状態にする
		mState = EState::EATTACK;
	}



	// ステップごとに処理を切り替え
	switch (mStepNum)
	{
	case 0: {  //カメラ移動の設定

		//カメラ位置の目的地までの長さを入れる
		mTotalDist = (ABDUCTION_CAMERA_POS - mCameraStartPos).Length();
		mStepNum++;

		break;
	}
	case 1: {   //カメラを移動させる

		mMoveDist += mVelocity;   //ここまで進んだ距離に移動量を加算していく
		mVelocity += mVelocity / 3.0;
		float t = mMoveDist / mTotalDist;

		if (t < 1.0f)
		{
			CVector p = CCamera::Instance()->Position();
			//カメラの位置をプレイヤーの位置から、少し上にする
			CCamera::Instance()->Position((Utility::lerp(mCameraStartPos, ABDUCTION_CAMERA_POS, t)));
			CCamera::Instance()->LookAt(CVector(0.0f, 0.0f, 0.0f));
			
		}
		else
		{
			t = 1.0f;
			//カメラの位置をプレイヤーの位置から、少し上にする
			CCamera::Instance()->Position(Utility::lerp(mCameraStartPos, ABDUCTION_CAMERA_POS, t));
		}

		
		
		break;
	}
	case 2:

		break;

	}
	
}

void CUfoAbduction::Collision(CCollider* m, CCollider* o)
{
	;
}
