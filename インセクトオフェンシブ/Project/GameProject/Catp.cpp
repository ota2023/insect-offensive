#include "Catp.h"

#define CHIP_WIDTH 479		// 1�R�}�̃T�C�Y
#define CHIP_HEIGHT 376
#define CENTER_POS CVector2D(CHIP_WIDTH / 2, CHIP_HEIGHT / 2)	// ���S���W
#define move_Speed_X 1.5f //�@�������̈ړ����x


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
Catp::Catp(int type, const CVector3D& pos)
	: EnemyBase(pos,CAST::CATP)
	, mp_image(nullptr)
	, m_type(type)
{
	m_hp = 200;
	m_rect.TopX = CHIP_WIDTH / 4; m_rect.TopY = CHIP_HEIGHT / 4;
	m_rect.TopZ = -40; m_rect.Width = CHIP_WIDTH / 2;
	m_rect.Height = CHIP_HEIGHT / 2; m_rect.Depth = 80;

	// �ђ��̉摜��ǂݍ���
	std::string imagePath = "�ђ��Q�{�ԃf�[�^.png";
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
Catp::~Catp()
{
	// �摜�f�[�^���폜
	delete mp_image;
}

// ���S����
void Catp::Death()
{
	// ���S��Ԃֈڍs
	ChangeState(EState::Death);
}

void Catp::Damage(int damage)
{
	m_hp = max(m_hp - damage, 0);

	if (m_hp <= 0 ) {
		//���S����
		Death();
	}

}

bool Catp::CheckCollisionEnemy(float _playerShotX, float _playerShotY, float _playerShotZ, SRect3D _playerShotRect)
{
	if (IsHitBox3D(_playerShotX, _playerShotY, _playerShotZ, m_pos.x, m_pos.y,
		m_pos.z, _playerShotRect, m_rect))
	{
		//printf("�ђ��Ƀ_���[�W�I\n");
		//Damage(1);	//1�͎b��l
		Death();
		return true;
	}
	return false;
}

void Catp::HitCheck(void)
{
	Player* ptask = (Player*)TaskManager::
		Instance()->GetTask(CAST::PLAYER);
	if (!ptask)return;

	if (ptask->CheckCollisionPlayer(
		m_pos.x, m_pos.y, m_pos.z, m_rect));


}

// ���݂̏�Ԃ�؂�ւ�
void Catp::ChangeState(EState state)
{
	if (m_state == state) return;

	m_state = state;
	m_stateStep = 0;
}

// �ړ������̍X�V
bool Catp::UpdateMove()
{

	m_pos.x -= move_Speed_X;
	mp_image->SetFlipH(false);

	bool isMove = true;

	return isMove;
}

// �ҋ@���̍X�V����
void Catp::StateIdle()
{

	// �ҋ@�A�j���[�V�������Đ�
	mp_image->ChangeAnimation((int)EAnimType::Idle);
}

// ���S���̍X�V����
void Catp::StateDeath()
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
void Catp::Update()

{
	/*
	if (m_timer++ >= 1800)
	{
		m_timer = 0;
		ChangeState(EState::Death);
		//printf("�ђ���������\n");

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

	HitCheck();

	// �C���[�W�ɍ��W��ݒ肵�āA�A�j���[�V�������X�V
	mp_image->SetPos(CalcScreenPos());
	mp_image->UpdateAnimation();


}

// �`�揈��
void Catp::Render()
{
	RenderShadow();

	mp_image->Draw();

}