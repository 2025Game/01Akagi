#include "CPaladinDamage.h"
#include "CXCharacter.h"
// 指定されたアニメーションファイル
#define ANIMATION_FILE "res\\paladin\\sword and shield impact (3).fbx.x"
int CPaladinDamage::msAnimNo = 0;

CPaladinDamage::CPaladinDamage(CXCharacter* parent)
{
	//モデルの読み込み
	static bool first = true;
	if (first) {
		//アニメーションの読み込み
		parent->Model()->AddAnimationSet(ANIMATION_FILE);
		msAnimNo = parent->Model()->AnimationSet().size() - 1;
		first = false;
	}
	//親のポインタを保存
	mpParent = parent;

}
void CPaladinDamage::Start()
{
	int animation_size =
		mpParent->Model()->AnimationSet()[msAnimNo]->MaxTime();
	//アニメーションの変更
	mpParent->ChangeAnimation(msAnimNo, false, animation_size);

	mState = EState::EDAMAGE; //状態の種類をダメージにする
}
void CPaladinDamage::Update()
{
	// アニメーションが終了したら待機状態(EIDLE)へ遷移させる
	if (mpParent->IsAnimationFinished())
	{
		mState = EState::EIDLE;
		
	}
}