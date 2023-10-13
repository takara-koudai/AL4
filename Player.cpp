#include "Player.h"
#include <cassert>
#include "MatrixTrans.h"
#include "ImGuiManager.h"
#include "PlayerBullet.h"

Player::~Player() 
{
	//for (PlayerBullet* bullet : playerBullets_) 
	//{
	//	delete playerBullet_;
	//}
}

void Player::Initialize(Model* model, uint32_t textureHandle) 
{ 
	input_ = Input::GetInstance();

	assert(model);

	playerModel_ = model;
	playerTextureHandle_ = textureHandle;

	worldTransform_.Initialize();

	worldTransform_.translation_ = {0.0f, 2.0f, 0.0f};

}

void Player::Update()
{
	//デスフラグの立った弾を削除
	/* playerBullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});*/


	Vector3 move = {0, 0, 0};

	//キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;
	//回転速さ[ラジアン/frame]
	const float kRotSpeed = 0.02f;

	//移動
	if (input_->PushKey(DIK_W))
	{
		move.y += kCharacterSpeed;
	}
	else if (input_->PushKey(DIK_S))
	{
		move.y -= kCharacterSpeed;
	}

	if (input_->PushKey(DIK_A))
	{
		move.x -= kCharacterSpeed;
	}
	else if (input_->PushKey(DIK_D))
	{
		move.x += kCharacterSpeed;
	}

	//回転
	if (input_->PushKey(DIK_LEFT))
	{
		worldTransform_.rotation_.y -= kRotSpeed;
	}
	else if (input_->PushKey(DIK_RIGHT))
	{
		worldTransform_.rotation_.y += kRotSpeed;
	}

	
	// 移動限界座標
	const float kMoveLimitX = (35.0f);
	const float kMoveLimitY = (18.0f);

	// 範囲を越えない処理

	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	
	Vector3 position;

	position.x = worldTransform_.matWorld_.m[3][0];
	position.y = worldTransform_.matWorld_.m[3][1];
	position.z = worldTransform_.matWorld_.m[3][2];

	/* Attack(position);
	for (PlayerBullet* bullet : playerBullets_)
	{
		bullet->Update();
	}*/


	// 座標移動(ベクトルの加算)
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	worldTransform_.UpdateMatrix();



	//ImGui
	/* ImGui::Begin("player");

	float playerPos[] = 
	{
	    worldTransform_.translation_.x, 
		worldTransform_.translation_.y,
	    worldTransform_.translation_.z
	};

	ImGui::SliderFloat3("playerPos", playerPos, -20.0f, 25.0f);

	ImGui::End();

	worldTransform_.translation_.x = playerPos[0];
	worldTransform_.translation_.y = playerPos[1];
	worldTransform_.translation_.z = playerPos[2];*/
}

void Player::Draw(ViewProjection& viewProjection) 
{
	playerModel_->Draw(worldTransform_, viewProjection, playerTextureHandle_);

	for (PlayerBullet* bullet : playerBullets_)
	{
		bullet->Draw(viewProjection);
	}
}


/* void Player::Attack(Vector3& position) { 
	if (input_->TriggerKey(DIK_SPACE))
	{
		
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		//速度ベクトルを自機の向きに合わせて回転させる
		velocity = TransformNormal(velocity, worldTransform_.matWorld_);


		//弾生成
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(playerModel_, position, velocity);


		playerBullets_.push_back(newBullet);
	}

}*/