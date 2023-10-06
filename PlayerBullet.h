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

	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	ViewProjection viewProjection_;

	// �e�̑��x
	Vector3 velocity_;

	// ���f��
	Model* bulletModel_ = nullptr;

	// �e�N�X�`���n���h��
	uint32_t bulletTextureHandle_ = 0u;

	//����
	static const int32_t kLifeTime = 60 * 5;

	//�f�X�^�C�}�[
	int32_t deathTimer_ = kLifeTime;

	//�f�X�t���O
	bool isDead_ = false;


};
