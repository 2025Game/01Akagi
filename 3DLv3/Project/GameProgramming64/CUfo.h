#ifndef CUFO_H
#define CUFO_H

#include "CXCharacter.h"
#include "CCollider.h"
#include "CUfoIdle.h"
#include "CUfoMove.h"

class CUfo : public CXCharacter
{
public:
	CUfo();
	void Update() override;
	//衝突処理
	//Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o);
	//衝突処理
	void Collision();
	void Init(CModelX* model);
private:
	CCollider mCollider;
	CState* mpState;  //状態処理
	std::unique_ptr <CUfoIdle> mpIdle;     //待機状態
	std::unique_ptr<CUfoMove> mpMove;       //動く状態
};

#endif // !CUFO_H

