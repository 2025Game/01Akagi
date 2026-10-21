#ifndef CGAMESCENE_H
#define CGAMESCENE_H
#include "CSceneBase.h"
#include "CModel.h"
#include "CModelX.h"
#include "CXCharacter.h"
#include "CXPlayer.h"
#include "CColliderMesh.h"
//ゲームシーン
class CGameScene :public CSceneBase
{
public:
	CGameScene();
	//シーン読み込み
	void Load();
	//シーンの更新処理
	void Update();
private:
	CModel mBackGround; //背景モデル
	CModelX mPlayer;

	CColliderMesh mColliderMesh; //メッシュコライダ

};
#endif