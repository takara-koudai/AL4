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

	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	ViewProjection viewProjection;

	//���f��
	Model* playerModel_ = nullptr;

	//�e�N�X�`��
	uint32_t playerTextureHandle_ = 0u;

	//�L�[�{�[�h����
	Input* input_ = nullptr;

	//�e
	PlayerBullet* playerBullet_ = nullptr;

	//�e���X�g
	std::list<PlayerBullet*> playerBullets_;

};
