#include "Player.h"
#include "Bee.h"
#include "Catp.h"
#include "PlayerAttack.h"

#define CHIP_WIDTH 640		// 1�R�}�̃T�C�Y
#define CHIP_HEIGHT 360 
#define CENTER_POS CVector2D(CHIP_WIDTH/2, CHIP_HEIGHT/2)	// ���S���W
#define MOVE_SPEED_Z 4.0f	// �������̈ړ����x
#define JUMP_SPEED 25.0f	// �W�����v���x
#define GRAVITY -1.0f		// �d��
#define LEFT_UPPER_LIMIT 240.0f	//���ړ�����(����)
#define RIGHT_UPPER_LIMIT 3.0f	//�E�ړ�����(����)
#define UPPER_LIMIT 5.0f	//��ړ�����(����)
#define LOWER_LIMIT 1.0f	//���ړ�����(����)


// �v���C���[�̃A�j���[�V�����f�[�^�̑O�錾
TexAnimData Player::ANIM_DATA[(int)EAnimType::Num] =
{
	// �ҋ@�A�j���[�V����
	{
		new TexAnim[4]
		{
			{0, 10}, {1, 10}, {2, 10},
			{3, 10},
		},
		4
	},
	// �ړ��A�j���[�V����
	{
		new TexAnim[3]
		{
			{12, 6}, {13, 6}, {14, 6},

		},
		3
	},
	// ���S�A�j���[�V����
	{
		new TexAnim[3]
		{
			{12, 12},
			{13, 12},
			{14, 12},
		},
		3
	},
	// �U���A�j���[�V����
	{
		new TexAnim[4]
		{
			{5, 6},
			{6, 6},
			{7, 6},
			{8, 6},
		},
		4
	},

	// �W�����v�A�j���[�V����
	{
		new TexAnim[3]
		{
			{8, 6},
			{9, 6},
			{10,6}
		},
		3
	},
};


// �R���X�g���N�^
Player::Player(const CVector3D& pos)
	: CharaBase(pos,CAST::PLAYER)
	, m_state(EState::Idle)
	, m_stateStep(0)
	, mp_image(nullptr)
	, m_invincible(false)
	, m_invTimer(0)
	, m_atk(false)
{
	m_hp = 100;
	m_rect.TopX = CHIP_WIDTH / 4; m_rect.TopY = CHIP_HEIGHT / 4;
	m_rect.TopZ = -10; m_rect.Width = CHIP_WIDTH / 4;
	m_rect.Height = CHIP_HEIGHT / 3; m_rect.Depth = 20;

	// �v���C���[�̉摜��ǂݍ���
	mp_image = CImage::CreateImage
	(
		"�J�}�L���Q�A�j���[�V����.png",	// �摜�t�@�C���̃p�X
		ANIM_DATA,		// �A�j���[�V�����̃f�[�^
		CHIP_WIDTH, CHIP_HEIGHT	// 1�R�}�̕��ƍ���
	);
	mp_image->ChangeAnimation((int)EAnimType::Idle);
	mp_image->SetCenter(CENTER_POS);
	mp_image->SetSize(CHIP_WIDTH * 0.7, CHIP_HEIGHT * 0.7);

}

// �f�X�g���N�^
Player::~Player()
{
	// �摜�f�[�^���폜
	delete mp_image;
}

CVector3D Player::GetPlyPos()
{
	return m_pos;
}

SRect3D Player::GetRect()
{
	return m_rect;
}

// ���݂̏�Ԃ�؂�ւ�
void Player::ChangeState(EState state)
{
	if (m_state == state) return;

	m_state = state;
	m_stateStep = 0;
}

// �ړ������̍X�V
bool Player::UpdateMove()
{
	bool isMove = false;
	m_pos.x =max(m_pos.x-1.5f,LEFT_UPPER_LIMIT);

	// ���L�[�������Ă����
	if (HOLD(CInput::eLeft))
	{
		// �������ֈړ�
		//m_pos.x -= move_Speed_X;
		 m_pos.x = max(m_pos.x - move_Speed_X, LEFT_UPPER_LIMIT);
		mp_image->SetFlipH(true);	//�摜�̌���
		isMove = true;
	}
	// �E�L�[�������Ă����
	else if (HOLD(CInput::eRight))
	{
		// �E�����ֈړ�
		//m_pos.x += move_Speed_X;
		 m_pos.x = min(m_pos.x + move_Speed_X, SCREEN_WIDTH - CHIP_WIDTH / RIGHT_UPPER_LIMIT);
		mp_image->SetFlipH(false);	//�摜�̌���
		isMove = true;
	}
	// ��L�[�������Ă����
	if (HOLD(CInput::eUp))
	{
		// �������ֈړ�
		//m_pos.z -= MOVE_SPEED_Z;
		m_pos.z = max(m_pos.z - MOVE_SPEED_Z, -SCREEN_HEIGHT / UPPER_LIMIT);
		isMove = true;
	}
	// ���L�[�������Ă����
	else if (HOLD(CInput::eDown))
	{
		// ��O�����ֈړ�
		//m_pos.z += MOVE_SPEED_Z;
		m_pos.z = min(m_pos.z + MOVE_SPEED_Z, SCREEN_HEIGHT / 2 - CHIP_HEIGHT / LOWER_LIMIT);
		isMove = true;
	}

	return isMove;
}

// �ҋ@���̍X�V����
void Player::StateIdle()
{
	// �ړ�����
	bool isMove = UpdateMove();

	// �ړ���Ԃɍ��킹�āA�A�j���[�V������؂�ւ�
	EAnimType anim = isMove ? EAnimType::Move : EAnimType::Idle;
	mp_image->ChangeAnimation((int)anim);

	// [SPACE]�L�[�ŃW�����v��Ԃֈڍs
	if (PUSH(CInput::eButton5))
	{
		ChangeState(EState::Jump);
	}
	// [J]�L�[�ōU����Ԃֈڍs
	else if (PUSH(CInput::eButton2))
	{
		ChangeState(EState::Attack);
	}
}

// �W�����v���̍X�V����
void Player::StateJump()
{
	// �X�e�b�v���Ƃɏ�����؂�ւ�
	switch(m_stateStep)
	{
		// �X�e�b�v0�F�W�����v�J�n
		case 0:
			// Y���i�����j�̈ړ����x�ɃW�����v�𑬓x��ݒ肵�A
			// �ڒn��Ԃ���������
			m_moveSpeedY = JUMP_SPEED;
			move_Speed_X = move_Speed_X * 2;
			m_isGrounded = false;
			m_stateStep++;
			break;
		// �X�e�b�v1�F�W�����v�I��
		case 1:
			// �ڒn������A�ҋ@��Ԃֈڍs
			if (m_isGrounded)
			{
				move_Speed_X = move_Speed_X / 2;
				ChangeState(EState::Idle);
			}
			break;
	}

	// �ړ�����
	bool isMove = UpdateMove();
	mp_image->ChangeAnimation((int)EAnimType::Jump);
}

// �U�����̍X�V����
void Player::StateAttack()
{
	m_pos.x = max(m_pos.x - 1.5f, LEFT_UPPER_LIMIT);

	// �X�e�b�v���Ƃɏ�����؂�ւ�
	switch (m_stateStep)
	{
		// �X�e�b�v0�F�U���A�j���[�V�����ɐ؂�ւ�
		case 0:
			mp_image->ChangeAnimation((int)EAnimType::Attack, false);
			m_stateStep++;
			break;
		case 1:

			//�@�U������𐶐�
			TaskManager::Instance()->Add(new PlayerAttack(
				CVector3D(m_pos.x,
									m_pos.y, m_pos.z)));
			//printf("�����蔻�萶�� X:%f,Y:%f,X:%f\n",m_pos.x, m_pos.y, m_pos.z);
			SetAtk(true);
			m_stateStep++;
			break;
		case 2:
			// �U���A�j���[�V�������I��������A�ҋ@��Ԃֈڍs
			if (mp_image->CheckAnimationEnd())
			{
				PlayerAttack* plyatk = (PlayerAttack*)TaskManager::
					Instance()->GetTask(CAST::ATTACK);
				printf("�����蔻�� X:%f,Y:%f,X:%f\n", plyatk->GetPos().x, GetPos().y, GetPos().z);

				SetAtk(false);
				ChangeState(EState::Idle);
			}
			break;
	}
}

// ���S���̍X�V����
void Player::StateDeath()
{
}



void Player::Damage(int damage)
{
	m_hp = max(m_hp - damage, 0);

	if (m_hp <= 0) {
		//���S����
	}
}

void Player::HitCheckBee(void)
{
	Bee* bee = (Bee*)TaskManager::
		Instance()->GetTask(CAST::BEE);
	bee->CheckCollisionEnemy(m_pos.x, m_pos.y, m_pos.z, m_rect);

}

void Player::SetInv(bool _inv)
{
	m_invincible = _inv;
}

bool Player::GetInv()
{
	return m_invincible;
}

void Player::InvTime()
{
	if (m_invincible) {
		if ((m_invTimer++ % 6) < 3) {
			SetShow(false);
		}
		else {
			SetShow(true);
		}
		if (++m_timer >= 45) {
			m_timer = 0;
			SetShow(true);
			SetInv(false);
		}
	}

}

void Player::SetAtk(bool _atk)
{
	m_atk = _atk;
}

bool Player::GetAtk()
{
	return	m_atk;
}

void Player::HitCheckCatp(void)
{
	Catp* catp = (Catp*)TaskManager::
		Instance()->GetTask(CAST::CATP);
	catp->CheckCollisionEnemy(m_pos.x, m_pos.y, m_pos.z, m_rect);

}

bool Player::CheckCollisionPlayer(float _enemyShotX, float _enemyShotY, 
					float _enemyShotZ, SRect3D _enemyRect)
{
	if (!m_invincible) {
		if (IsHitBox3D(_enemyShotX, _enemyShotY, _enemyShotZ, m_pos.x, m_pos.y,
			m_pos.z, _enemyRect, m_rect))
		{
			printf("�v���C���[�Ƀ_���[�W�I\n");
			//Damage(1);	//1�͎b��l
			SetInv(true);
			return true;
		}
	}
	return false;
}


// �X�V����
void Player::Update()
{
	// ���݂̏�Ԃɍ��킹�āA������؂�ւ���
	switch (m_state)
	{
	case EState::Idle:		StateIdle();	break;
	case EState::Jump:		StateJump();	break;
	case EState::Attack:	StateAttack();	break;
	case EState::Death:		StateDeath();	break;
	}

	// Y���i�����j�̈ړ������W�ɔ��f
	m_pos.y += m_moveSpeedY;
	m_moveSpeedY += GRAVITY;	// Y���̈ړ����x�ɏd�͂����Z
	// �n�ʂ�艺�ɂ�����
	if (m_pos.y <= 0.0f)
	{
		// �n�ʂ̍��W�֖߂�
		m_pos.y = 0.0f;
		m_moveSpeedY = 0.0f;
		m_isGrounded = true;
	}
	//���G����
	InvTime();


	//HitCheckCatp();
	//HitCheckBee();

	// �C���[�W�ɍ��W��ݒ肵�āA�A�j���[�V�������X�V
	mp_image->SetPos(CalcScreenPos());
	mp_image->UpdateAnimation();

	//printf("Plyer X:%f,Y:%f,Z:%f\n", m_pos.x, m_pos.y, m_pos.z);
}

// �`�揈��
void Player::Render()
{
	RenderShadow();

	mp_image->Draw();

}
