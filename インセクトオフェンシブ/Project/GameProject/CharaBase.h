#pragma once
#include "ObjectBase.h"

// �L�����N�^�[�̃x�[�X�N���X
class CharaBase : public ObjectBase
{
public:
	// �R���X�g���N�^
	CharaBase();
	CharaBase(const CVector3D& pos,CAST _id);
	// �f�X�g���N�^
	virtual ~CharaBase();

	// �_���[�W���󂯂�
	void TakeDamage(int damage);
	// ���S����
	virtual void Death();

protected:
	int m_maxHp;		// �ő�HP
	int m_hp;			// ����HP
	bool m_isDeath;		// ���S�t���O
};
