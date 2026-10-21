#pragma once
#include "CTransform.h"
#include "CInput.h"
#include "CXCharacter.h"
/*
* カメラクラス
* 画面に表示するエリアを設定する
*/
class CCamera : public CTransform
{
public:
	static CCamera* Instance();
	void Update();
	void Parent(CXCharacter* parent);

	CMatrix ModelViewInverse();

	//表示エリアの設定
	//Start(左座標,右座標,下座標,上座標)
	static void Start(double left, double right
		, double bottom, double top);
	//表示終了
	static void End();
private:
	//マウスの座標
	double mX, mY;
	CCamera() 
	{
		//マウスの位置を取得する
		mInput.MouseGetPosition(&mX, &mY);
	}
	static CCamera* spInstance;
	CInput mInput;

	CMatrix mModelViewMatrix; //モデルビュー行列
	CMatrix mModelViewInverse; //モデルビュー逆行列
};
