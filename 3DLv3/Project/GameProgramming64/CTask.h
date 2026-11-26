#ifndef CTASK_H
#define CTASK_H
class CTaskManager;
class CCollisionManager;

//識別タグ
enum class ETag {
	ENONE, //未設定
	EUFO, //プレイヤー
	EUFO_ATTACK_BEAM, //UFOの攻撃
	EABDUCTION_HATCH, //UFOの開口部
	ERANCHER, //牧場主
	ESWORD, //剣
	EBULLET, //弾
	ECube   //壁(テスト用) TODO:後で消す
};
/*
タスククラス
タスクリストの要素
*/
class CTask {
	friend CTaskManager;
	friend CCollisionManager;
public:
	//衝突処理
	virtual void Collision() {}

	//デフォルトコンストラクタ
	CTask()
		: mpNext(nullptr), mpPrev(nullptr), mPriority(0), mEnabled(true), mTag(ETag::ENONE) {}
	//デストラクタ virtualにしないと子クラスのデストラクタが呼ばれない
	virtual ~CTask() {}
	//更新
	virtual void Update() {}
	//描画
	virtual void Render() {}

	// タグの取得
	ETag& Tag() { return mTag; }
	//タグの設定
	//tag :識別タグ
	void Tag(ETag tag) { mTag = tag; }

	//有効フラグの設定
	void Enabled(bool enabled) { mEnabled = enabled; }

protected:
	int mPriority;	//優先度
	bool mEnabled;	//有効フラグ
private:
	CTask* mpNext;//次のポインタ
	CTask* mpPrev;//前のポインタ
	ETag mTag; //識別タグ
};

#endif
