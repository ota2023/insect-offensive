#include "CharaBase.h"

// �R���X�g���N�^
CharaBase::CharaBase()
	//: CharaBase(CVector3D::zero)
{
}

CharaBase::CharaBase(const CVector3D& pos,CAST _id)
	: ObjectBase(pos,_id)
	, m_maxHp(100)
	, m_hp(m_maxHp)
	, m_isDeath(false)
{
}

// �f�X�g���N�^
CharaBase::~CharaBase()
{
}

// �_���[�W���󂯂�
void CharaBase::TakeDamage(int damage)
{
	if (m_hp == 0) return;	// HP0�Ȃ̂ŃX���[

	// ����HP���_���[�W�ʂ����Ȃ�
	if (m_hp > damage)
	{
		m_hp -= damage;	// ���̂܂�HP�����炷
	}
	// �_���[�W�ʂ̕����傫��
	else
	{
		// HP��0�ɂ��āA���S���������s
		m_hp = 0;
		Death();
	}
}

// ���S����
void CharaBase::Death()
{
	m_isDeath = true;
}
