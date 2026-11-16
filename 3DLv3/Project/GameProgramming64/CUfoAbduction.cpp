#include "CUfoAbduction.h"
#include "CXCharacter.h"
#include "CCamera.h"

CUfoAbduction::CUfoAbduction()
	: mStepNum(0)
{
}

void CUfoAbduction::Start(CXCharacter* parent)
{
	//親のポインタを保存
	mpParent = parent;
    
	mState = EState::EABDUCTION; //状態の種類をアブダクション中にする


}

void CUfoAbduction::Update()
{
	if (mInput.Key(VK_LBUTTON))
	{

	}
	else
	{
		//左クリックが押されていないと待機状態にする
		mState = EState::EIDLE;
	}

	// ステップごとに処理を切り替え
	switch (mStepNum)
	{
	case 0: {  //カメラを移動させる
		
		//カメラの位置をプレイヤーの位置から、少し上にする
		CCamera::Instance()->Position(CVector(0.0f, 7.0f, 0.0f));
		break;
	}
	case 1: {   //

		
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
