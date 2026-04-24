#include "CXPlayer.h"

#define GRAVITY 0.0625f     // 重力

void CXPlayer::Update()
{
	// GRAVITYの大きさぶんだけ、下方向へ移動させる
	mPosition = mPosition - CVector(0.0f, GRAVITY, 0.0f);

	// 親クラスの更新
	CXCharacter::Update();
}