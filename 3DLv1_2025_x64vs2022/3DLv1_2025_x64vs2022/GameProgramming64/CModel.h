#ifndef CMODEL_H_
#define CMODEL_H_
/*
モデルクラス
モデルデータの入力や表示
*/
class CModel
{
public:
	//モデルファイルの入力
	//Load(モデルファイル名, マテリアルファイル名)
	void Load(const char* obj, const char* mtl);
};
#endif // !CMODEL_H_

