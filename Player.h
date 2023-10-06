#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "ViewProjection.h"
#include "Input.h"
#include "PlayerBullet.h"
#include <list>

class Player 
{
public:

	void Initialize(Model* model,uint32_t textureHandle);

	void Update();

	void Draw(ViewProjection& viewProjection);

	void Attack(Vector3& position);

	~Player();

private:

	//ワールド変換データ
	WorldTransform worldTransform_;
	ViewProjection viewProjection;

	//モデル
	Model* playerModel_ = nullptr;

	//テクスチャ
	uint32_t playerTextureHandle_ = 0u;

	//キーボード入力
	Input* input_ = nullptr;

	//弾
	PlayerBullet* playerBullet_ = nullptr;

	//弾リスト
	std::list<PlayerBullet*> playerBullets_;

};
