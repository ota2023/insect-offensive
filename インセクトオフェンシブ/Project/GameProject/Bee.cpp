#include "Bee.h"



#define CHIP_WIDTH 479		// 1�R�}�̃T�C�Y
#define CHIP_HEIGHT 376
#define CENTER_POS CVector2D(CHIP_WIDTH/2, CHIP_HEIGHT/2)	// ���S���W
#define move_Speed_X 3.0f //�@�������̈ړ����x

// �X���C���̃A�j���[�V�����f�[�^
TexAnimData Bee::ANIM_DATA[(int)EAnimType::Num] =
{
	{
		new TexAnim[2]
		{
			{ 0, 6}, { 1, 6},
		},
		2
	},
	{
		new TexAnim[5]
		{
			{5, 6}, {6, 6}, {7, 6},
			{8, 6}, {9, 6},
		},
		5
	},
};

// �R���X�g���N�^
Bee::Bee(int type, const CVector3D& pos)
	: EnemyBase(pos,CAST::BEE)
	, mp_image(nullptr)
	, m_type(type)
{
	m_hp = 200;
	m_rect.TopX = CHIP_WIDTH / 4; m_rect.TopY = CHIP_HEIGHT / 3;
	m_rect.TopZ = -10; m_rect.Width = CHIP_WIDTH / 2.5;
	m_rect.Height = CHIP_HEIGHT / 5; m_rect.Depth = 20;

	// �n�`�̉摜��ǂݍ���
	mp_image = CImage::CreateImage
	(
		"�n�`�Q01�Q�{�ԃf�[�^.png",	// �摜�t�@�C���̃p�X
		ANIM_DATA,		// �A�j���[�V�����̃f�[�^
		CHIP_WIDTH, CHIP_HEIGHT	// 1�R�}�̕��ƍ���
	);
	mp_image->ChangeAnimation((int)EAnimType::Idle);
	mp_image->SetCenter(CENTER_POS);
	mp_image->SetSize(CHIP_WIDTH * 0.7, CHIP_HEIGHT * 0.7);
	mp_image->SetFlipH(false);
}

// �f�X�g���N�^
Bee::~Bee()
{
	// �摜�f�[�^���폜
	delete mp_image;
}

// ���S����
void Bee::Death()
{
	// ���S��Ԃֈڍs
	ChangeState(EState::Death);
}

void Bee::Damage(int damage)
{
	m_hp = max(m_hp - damage, 0);

	if (m_hp <= 0) {
		//���S����
		Death();
	}
}

bool Bee::CheckCollisionEnemy(float _playerShotX, float _playerShotY, float _playerShotZ, SRect3D _playerShotRect)
{
	if (IsHitBox3D(_playerShotX, _playerShotY, _playerShotZ, m_pos.x, m_pos.y,
		m_pos.z, _playerShotRect, m_rect))
	{
		//printf("�n�`�Ƀ_���[�W�I\n");
		Death();
		//Damage(1);	//1�͎b��l
		return true;
	}
	return false;
}

void Bee::HitCheck(void)
{
	Player* ptask = (Player*)TaskManager::
		Instance()->GetTask(CAST::PLAYER);
	if (!ptask)return;

	if(ptask->CheckCollisionPlayer(
			m_pos.x, m_pos.y, m_pos.z, m_rect));

}

// ���݂̏�Ԃ�؂�ւ�
void Bee::ChangeState(EState state)
{
	if (m_state == state) return;

	m_state = state;
	m_stateStep = 0;
}

// �ړ������̍X�V
bool Bee::UpdateMove()
{
	m_pos.x -= move_Speed_X;

	Player* ptask = (Player*)TaskManager::
			Instance()->GetTask(CAST::PLAYER);
	m_pos.z = ptask->GetPlyPos().z;


	mp_image->SetFlipH(false);

	bool isMove = true;

	return isMove;
}

// �ҋ@���̍X�V����
void Bee::StateIdle()
{

	// �ҋ@�A�j���[�V�������Đ�
	mp_image->ChangeAnimation((int)EAnimType::Idle);
}

// ���S���̍X�V����
void Bee::StateDeath()
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
void Bee::Update()

{
	/*
	if (m_timer++ >= 1800)
	{
		m_timer = 0;
		ChangeState(EState::Death);
		//printf("�n�`��������\n");
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
void Bee::Render()
{
	RenderShadow();

	mp_image->Draw();
	mp_shadowImg->SetSize(CHIP_WIDTH * 0.5, CHIP_HEIGHT * 0.5);
	mp_shadowImg->SetCenter(CHIP_WIDTH * 0.5, CHIP_HEIGHT * 0.35);

}