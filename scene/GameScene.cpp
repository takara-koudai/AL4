#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include "Skydome.h"
#include "Ground.h"

GameScene::GameScene() {}

GameScene::~GameScene() 
{ 
	//delete playerSprite_;
	//delete model_;
	
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	worldTransform_.Initialize();
	viewProjection_.Initialize();

	//debugCamera_ = new DebugCamera(1280, 720);

	TextureHandle_ = TextureManager::Load("mario.jpg");

	//天球
	skydomeModel_.reset(Model::CreateFromOBJ("skydome",true));

	//グラウンド
	groundModel_.reset(Model::CreateFromOBJ("ground", true));

	playerSprite_ = Sprite::Create(TextureHandle_, {100, 50});

	//model_ = Model::Create();
	
	model_.reset(Model::Create());

	//自キャラの生成
	//player_ = new Player();

	//プレイヤー
	player_ = std::make_unique<Player>();

	player_->Initialize(model_.get(), TextureHandle_);
	//player_->Initialize(model_, TextureHandle_);

	//天球
	skydome_ = std::make_unique<Skydome>();

	skydome_->Initialize(skydomeModel_.get());

	//グラウンド
	ground_ = std::make_unique<Ground>();

	ground_->Initialize(groundModel_.get());

	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	//軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

}

void GameScene::Update() 
{ 
	//debugCamera_->Update();

	skydome_->Update();
	ground_->Update();

	player_->Update(); 

	

	#ifdef _DEBUG

	if (input_->TriggerKey(DIK_K) == isDebugCameraActive_ == false) {
		isDebugCameraActive_ = true;

		// debugCamera->Update();
	} else if (input_->TriggerKey(DIK_K) == isDebugCameraActive_ == true) {
		isDebugCameraActive_ = false;
	}

#endif // DEBUG

	// Cameraの処理
	if (isDebugCameraActive_) {

		debugCamera_->Update();

		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();

	} else {
		// ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	skydome_->Draw(viewProjection_);
	ground_->Draw(viewProjection_);

	player_->Draw(viewProjection_);

	//model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), TextureHandle_);
	

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
