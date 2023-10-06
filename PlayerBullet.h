#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "MatrixTrans.h"
#include "Model.h"


class PlayerBullet 
{
public:


	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);
	

	void Update();


	void Draw(const ViewProjection& viewProjection);

	bool IsDead() const { return isDead_; }


private:

	// ワールド変換データ
	WorldTransform worldTransform_;

	ViewProjection viewProjection_;

	// 弾の速度
	Vector3 velocity_;

	// モデル
	Model* bulletModel_ = nullptr;

	// テクスチャハンドル
	uint32_t bulletTextureHandle_ = 0u;

	//寿命
	static const int32_t kLifeTime = 60 * 5;

	//デスタイマー
	int32_t deathTimer_ = kLifeTime;

	//デスフラグ
	bool isDead_ = false;


};
