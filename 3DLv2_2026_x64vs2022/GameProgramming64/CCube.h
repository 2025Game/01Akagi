#pragma once
#include "CCharacter3.h"
#include "CColliderTriangle.h"
class CCube : public CCharacter3
{
public:
	CCube();
	void Update();
private:
	//モデルデータのインスタンス
	static CModel msModel;
	//コライダは上面だけつける
	CColliderTriangle mCollider[2];
};