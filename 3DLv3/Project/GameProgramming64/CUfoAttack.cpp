#include "CUfoAttack.h"
#include "CXCharacter.h"
#include "CCollisionManager.h"
#define ATTACKCOLLISION_RANGE 100.0f

void CUfoAttack::Start(CXCharacter* parent)
{
	//親のポインタを保存
	mpParent = parent;

	mState = EState::EATTACK; //状態の種類を攻撃状態にする

}

void CUfoAttack::Update()
{
	if (mInput.Key(VK_LBUTTON) && mInput.Key(VK_RBUTTON))
	{
		
		printf("kougeki");
	}
	else
	{
		//左クリックが押されていないとアブダクション中にする
		mState = EState::EABDUCTION;
	}

}

void CUfoAttack::Collision(CCollider* m, CCollider* o)
{

}