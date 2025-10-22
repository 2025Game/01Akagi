#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "CVector.h"
/*
三角形クラス
*/
class CTriangle {
public:
	//頂点座標設定
	//Vertex(頂点1, 頂点2, 頂点3)
	void Vertex(const CVector& v0, const CVector& v1, const CVector& v2);
	//法線設定
	//Normal(法線ベクトル)
	void Normal(const CVector& n);
	void Normal(const CVector& v0, const CVector& v1, const CVector& v2);
	//描画
	void Render();
	//マテリアル番号の取得
	int MaterialIdx();
	//マテリアル番号の設定
	//Material(マテリアル番号)
	void MaterialIdx(int idx);
	//UV設定
	void UV(const CVector& v0, const CVector& v1, const CVector& v2);

private:
	CVector mV[3]; //頂点座標
	CVector mN[3]; //法線
	CVector mUv[3];//テクスチャマッピング

	int mMaterialIdx; //マテリアル番号


};
#endif
