#include "CPaladinIdle.h"
#include "CXCharacter.h"

#define ANIMATION_FILE "res\\paladin\\sword and shield idle.fbx.x"
int CPaladinIdle::msAnimNo = 0;

CPaladinIdle::CPaladinIdle(CXCharacter* parent)
{
	//モデル䛾読み込み
	static bool first = true;
	if (first) {
		//アニメーション䛾読み込み
		parent->Model()->AddAnimationSet(ANIMATION_FILE);
		msAnimNo = parent->Model()->AnimationSet().size() - 1;
		first = false;
	}
	//親䛾ポインタを保存
	mpParent = parent;
}
void CPaladinIdle::Start()
{
	int animation_size =
		mpParent->Model()->AnimationSet()[msAnimNo]->MaxTime();
	//アニメーション䛾変更
	mpParent->ChangeAnimation(msAnimNo, true, animation_size);
	mState = EState::EIDLE; //状態䛾種類を待機䛻䛩る
}
void CPaladinIdle::Update()
{
}