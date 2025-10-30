#ifndef CMODEL_H_
#define CMODEL_H_

//vectorのインクルード
#include <vector>
#include "CTriangle.h"
#include "CMaterial.h"
/*
モデルクラス
モデルデータの入力や表示
*/
class CModel
{
public:
	~CModel();
	//モデルファイルの入力
	//Load(モデルファイル名, マテリアルファイル名)
	void Load(const char* obj, const char* mtl);
	//描画
	void Render();
	//描画
	//Render(行列)
	void Render(const CMatrix& m);
private:
	//三角形の可変長配列
	std::vector<CTriangle> mTriangles;
	//マテリアルポインタの可変長配列
	std::vector<CMaterial*> mpMaterials;
};
#endif // !CMODEL_H_

