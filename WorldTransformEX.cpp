#include "WorldTransform.h"
#include "MatrixTrans.h"

void WorldTransform::UpdateMatrix()
{
	// �X�P�[���A��]�A���s�ړ����������čs����v�Z����
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);

	TransferMatrix();
}