#pragma once
#include "CharaBase.h"

// �G�̃x�[�X�N���X
class EnemyBase : public CharaBase
{
public:
	// �R���X�g���N�^
	EnemyBase();
	EnemyBase(const CVector3D& pos,CAST _id);
	// �f�X�g���N�^
	virtual ~EnemyBase();

private:
};
