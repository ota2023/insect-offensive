#pragma once
#include "CharaBase.h"
#include "TaskManager.h"

class Player : public CharaBase
{
public:
	// �R���X�g���N�^
	Player(const CVector3D& pos);
	// �f�X�g���N�^
	~Player();


	//�v���C���[�̈ʒu���擾
	CVector3D GetPlyPos();
	//��`���擾
	SRect3D GetRect();

	//���G�ɂ���
	void SetInv(bool _inv);
	//���G��Ԃ����擾
	bool GetInv();

	//�U���t���O���Z�b�g
	void SetAtk(bool _atk);
	//�U���t���O�擾
	bool GetAtk();

	//�v���C���[�̓����蔻��
	bool CheckCollisionPlayer(float _enemyShotX, float _enemyShotY,
		float _enemyShotZ, SRect3D _enemyRect);	
	

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

private:
	// ���
	enum class EState
	{
		Idle,	// �ҋ@���
		Jump,	// �W�����v��
		Attack,	// �U����
		Death,	// ���S
	};
	void ChangeState(EState state);

	// �ړ������̍X�V
	bool UpdateMove();

	// �ҋ@���̍X�V����
	void StateIdle();
	// �W�����v���̍X�V����
	void StateJump();
	// �U�����̍X�V����
	void StateAttack();
	// ���S���̍X�V����
	void StateDeath();



	//�_���[�W����
	void Damage(int damage);

	//�ђ��̔���
	void HitCheckCatp(void);

	//�n�`�̔���
	void HitCheckBee(void);


	//���G����
	void InvTime();



	//���G�t���O
	bool m_invincible;	
	//���G���ԗp�^�C�}�[
	int m_invTimer;	

	// �������̈ړ����x
	float move_Speed_X = 7.0f;	
	//�U������̗L��
	bool m_atk;

	EState m_state;
	int m_stateStep;

	// �A�j���[�V�����̎��
	enum class EAnimType
	{
		Idle,	// �ҋ@
		Move,	// �ړ�
		Death,	// ���S
		Attack,	// �U��
		Jump,	// ����

		Num,
	};
	static TexAnimData ANIM_DATA[];
	CImage* mp_image;	// �v���C���[�̉摜

	float m_moveSpeedY;	// Y���i�����j�̈ړ����x
};
