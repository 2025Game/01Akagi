#ifndef CCOLLIDER_H
#define CCOLLIDER_H
//キャラクタクラスのインクルード
#include "CCharacter3.h"
class CCollisionManager;

/*
コライダクラス
衝突判定データ
*/
class CCollider : public CTransform , CTask {
	friend CCollisionManager;
public:
	//優先度の変更
	virtual void ChangePriority();

	//優先度の変更
	void ChangePriority(int priority);

	//CollisionTriangleSphere(三角コライダ, 球コライダ, 調整値)
	//retrun:true（衝突している）false(衝突していない)
	//調整値:衝突しない位置まで戻す値
	static bool CollisionTriangleSphere(CCollider* triangle,
		CCollider* sphere, CVector* adjust);

	//CollisionTriangleLine(三角コライダ, 線分コライダ, 調整値)
	//retrun:true（衝突している）false(衝突していない)
	//調整値:衝突しない位置まで戻す値
	static bool CollisionTriangleLine(CCollider* triangle, CCollider* line, CVector* adjust);

	//カプセルコライダとカプセルコライダの衝突判定
    //static bool CollisionCapsuleCapsule(カプセル1, カプセル2, 調整値)
    //調整値:カプセル1が衝突しない位置まで移動する移動量
    //戻り値:true 衝突している false 衝突していない
	static bool CollisionCapsuleCapsule(
		CCollider* m, CCollider* o, CVector* adjust);

	//コライダタイプ
	enum class EType {
		ESPHERE,//球コライダ
		ETRIANGLE,//三角コライダ
		ELINE, //線分コライダ
		ECAPSULE,
	};
	CCollider::EType Type();

	//デフォルトコンストラクタ
	CCollider();

	//衝突判定
	//Collision(コライダ1, コライダ2)
	//retrun:true（衝突している）false(衝突していない)
	static bool Collision(CCollider* m, CCollider* o);
	
	//CalcCalcPointLineDist(点, 始点, 終点, 線上の最短点, 割合)
    //点と線(始点、終点を通る直線)の最短距離を求める
	static float CalcPointLineDist(const CVector& p, const CVector& s, const CVector& e,
		CVector* mp, float* t);

	//CalcLineLineDist(始点1, 終点1, 始点2, 終点2, 交点1, 交点2, 比率1, 比率2)
    //2線間nの最短距離を返す
	static float CalcLineLineDist(
		const CVector& s1, //始点1
		const CVector& e1, //終点1
		const CVector& s2, //始点2
		const CVector& e2, //終点2
		CVector* mp1, //交点1
		CVector* mp2, //交点2
		float* t1, //比率1
		float* t2 //比率2
	);
	


	~CCollider();
	//コンストラクタ
	//CCollider(親, 親行列, 位置, 半径)
	CCollider(CCharacter3* parent, CMatrix* matrix,
		const CVector& position, float radius);
	//親ポインタの取得
	CCharacter3* Parent();
	//描画
	void Render();
protected:
	EType mType;//コライダタイプ
	//頂点
	CVector mV[3];

	CCharacter3* mpParent;//親
	const CMatrix* mpMatrix;//親行列
	float mRadius;	//半径
};
#endif

