#include "Slime.h"

#define CHIP_WIDTH 479		// 1�R�}�̃T�C�Y
#define CHIP_HEIGHT  376
#define CENTER_POS CVector2D(239.5f, 188.0f)	// ���S���W
#define move_Speed_X 2.5f //�@�������̈ړ����x

// �X���C���̃A�j���[�V�����f�[�^
/*TexAnimData Slime::ANIM_DATA[(int)EAnimType::Num] =
{
	{
		new TexAnim[4]
		{
			{ 0, 6}, { 1, 6},
			{ 2, 6}, { 3, 6},
		},
		4
	},
	{
		new TexAnim[5]
		{
			{5, 6}, {6, 6}, {7, 6},
			{8, 6}, {9, 6},
		},
		5
	},
};*/

// �R���X�g���N�^
Slime::Slime(int type, const CVector3D& pos)
	: EnemyBase(pos,CAST::SPIDER)
	, mp_image(nullptr)
	, m_type(type)
{
	m_hp = 200;

	// �w偂̉摜��ǂݍ���
	std::string imagePath = "�N���Q�ړ��Q01�Q�{�ԃf�[�^.png";
	//if (m_type == 0) imagePath = "slime_a.png";
	//else if (m_type == 1) imagePath = "slime_b.png";
	//else if (m_type == 2) imagePath = "slime_c.png";
	mp_image = CImage::CreateImage
	(
		imagePath.c_str(),	// �摜�t�@�C���̃p�X
		nullptr,			// �A�j���[�V�����̃f�[�^
		CHIP_WIDTH, CHIP_HEIGHT		// 1�R�}�̕��ƍ���

	);
	mp_image->ChangeAnimation(0);
	mp_image->SetCenter(CENTER_POS);
	mp_image->SetSize(CHIP_WIDTH * 0.7, CHIP_HEIGHT * 0.7);
	mp_image->SetFlipH(false);
}

// �f�X�g���N�^
Slime::~Slime()
{
	// �摜�f�[�^���폜
	delete mp_image;
}

// ���S����
void Slime::Death()
{
	// ���S��Ԃֈڍs
	ChangeState(EState::Death);
}

// ���݂̏�Ԃ�؂�ւ�
void Slime::ChangeState(EState state)
{
	if (m_state == state) return;

	m_state = state;
	m_stateStep = 0;
}

// �ړ������̍X�V
bool Slime::UpdateMove()
{

	//m_pos.x -= move_Speed_X;
	mp_image->SetFlipH(false);

	bool isMove = true;

	return isMove;
}

// �ҋ@���̍X�V����
void Slime::StateIdle()
{

	// �ҋ@�A�j���[�V�������Đ�
	mp_image->ChangeAnimation((int)EAnimType::Idle);
}

// ���S���̍X�V����
void Slime::StateDeath()
{

	// �X�e�b�v���Ƃɏ�����؂�ւ�
	switch (m_stateStep)
	{
		// �X�e�b�v0�F���S�A�j���[�V�������Đ�
	case 0:
		mp_image->ChangeAnimation((int)EAnimType::Death, false);
		m_stateStep++;
		break;
		// �X�e�b�v1�F�A�j���[�V�����I���҂�
	case 1:
		// �A�j���[�V�������I��������A�폜
		if (mp_image->CheckAnimationEnd())
		{
			// �폜�t���O�𗧂Ă�
			Kill();
		}
		break;
	}
}

// �X�V����
void Slime::Update()

{
	/*if (PUSH(CInput::eButton5))
	{
		ChangeState(EState::Death);
	}*/

	// ��Ԃɍ��킹�āA�X�V������؂�ւ���
	switch (m_state)
	{
	case EState::Idle:	StateIdle();	break;
	case EState::Death:	StateDeath();	break;
	}

	if (UpdateMove())
	{
	}

	// �C���[�W�ɍ��W��ݒ肵�āA�A�j���[�V�������X�V
	mp_image->SetPos(CalcScreenPos());
	mp_image->UpdateAnimation();
}

// �`�揈��
void Slime::Render()
{
	mp_image->Draw();
	RenderShadow();
}
