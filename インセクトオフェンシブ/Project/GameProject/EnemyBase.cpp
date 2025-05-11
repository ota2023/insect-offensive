#include "EnemyBase.h"
#include "EnemyManager.h"

// �R���X�g���N�^
EnemyBase::EnemyBase()
	//: EnemyBase(CVector3D::zero)
{
}

EnemyBase::EnemyBase(const CVector3D& pos, CAST _id)
	: CharaBase(pos,_id)
{
	// �G�̊Ǘ��N���X�̃��X�g�Ɏ��g��ǉ�
	EnemyManager::Instance()->Add(this);
}

// �f�X�g���N�^
EnemyBase::~EnemyBase()
{
	// �G�̊Ǘ��N���X�̃��X�g���玩�g����菜��
	EnemyManager::Instance()->Remove(this);
}
