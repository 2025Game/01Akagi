#include "CUfoAbduction.h"

void CUfoAbduction::Start(CXCharacter* parent)
{
	//親のポインタを保存
	mpParent = parent;
    
	mState = EState::EATTACK; //状態の種類をアブダクション中にする
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
	
}
