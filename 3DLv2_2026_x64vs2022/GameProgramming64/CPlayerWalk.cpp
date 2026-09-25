#include "CPlayerWalk.h"
#include "CXCharacter.h"
#include "CCamera.h"

//移動速度
#define VELOCITY 0.1f
// 回転速度
#define ROTATIONSPEED 2.0f

void CPlayerWalk::Start(CXCharacter* parent)
{
	//親のポインタを保存
	mpParent = parent;
	//アニメーションの変更
	mpParent->ChangeAnimation(1, true, 60);
	mState = EState::EWALK; //状態の種類を歩くにする
}


void CPlayerWalk::Update()
{
	if (mInput.Key('W'))
	{
		CVector p = mpParent->Position();
		mpParent->Position(p +
			mpParent->MatrixRotate().VectorZ() * VELOCITY);
	}
	else
	{
		//Wキーが押されていないときは待機状態にする
		mState = EState::EIDLE;
	}

	// Aキーで左回転、Dキーで右回転
	if (mInput.Key('A'))
	{
		CVector r = mpParent->Rotation() +
			CVector(0.0f, ROTATIONSPEED, 0.0f);
		mpParent->Rotation(r);
	}
	if (mInput.Key('D'))
	{
		CVector r = mpParent->Rotation() +
			CVector(0.0f, -ROTATIONSPEED, 0.0f);
		mpParent->Rotation(r);
	}
	if (mInput.Key('I'))
	{
		mState = EState::EATTACK;
	}
	if (mInput.Key(VK_SPACE))
	{
		mState = EState::EJUMP;
	}

	//1.カメラの右方向ベクトルを取得する
	CVector cx;
	cx = CCamera::Instance()->ModelViewInverse().VectorX();
	// 2.プレイヤーの前方向ベクトルを取得する
	CVector fwd = mpParent->CombinedMatrix().VectorZ();
	//3.内積を計算して、回転量 (10度以内)を求める
	CVector rot(0.0f, cx.Dot(fwd) * 10.0f, 0.0f);

	//4.プレイヤーをカメラ方向へ回転させるる
	mpParent->Rotation(mpParent->Rotation() + rot);
	//カメラは逆回転させる
	//プレイヤーが回転してもカメラも一緒に回転するので、回わってしまうため。
	CCamera::Instance()->Rotation(CCamera::Instance()->Rotation() - rot);

}