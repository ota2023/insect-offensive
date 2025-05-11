#pragma once
#include "EnemyBase.h"

class Slime : public EnemyBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="type">�X���C���̎��</param>
	/// <param name="pos">�����ʒu</param>
	Slime(int type, const CVector3D& pos);
	// �f�X�g���N�^
	~Slime();

	// ���S����
	virtual void Death() override;

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;



private:
	// ���
	enum class EState
	{
		Idle,	// �ҋ@���
		Death,	// ���S
	};
	void ChangeState(EState state);

	bool UpdateMove();


	// �ҋ@���̍X�V����
	void StateIdle();
	// ���S���̍X�V����
	void StateDeath();

	EState m_state;
	int m_stateStep;

	// �A�j���[�V�����̎��
	enum class EAnimType
	{
		Idle,	// �ҋ@
		Death,	// ���S

		Num,
	};
	static TexAnimData ANIM_DATA[];
	CImage* mp_image;	// �摜
	int m_type;			// �X���C���̎��


};