#include "PlayerAttack.h"
#include "Player.h"
#include "Catp.h"
#include "Bee.h"

#define CHIP_WIDTH 150		// 1�R�}�̃T�C�Y
#define CHIP_HEIGHT 100 

PlayerAttack::PlayerAttack(const CVector3D& pos)
	:CharaBase(pos, CAST::ATTACK)

{
	m_rect.TopX = CHIP_WIDTH; m_rect.TopY = CHIP_HEIGHT;
	m_rect.TopZ = -30; m_rect.Width = CHIP_WIDTH * 2;
	m_rect.Height = CHIP_HEIGHT; m_rect.Depth = 40;
}

PlayerAttack::~PlayerAttack()
{
}

void PlayerAttack::HitCheckCatp() {
	DWORD count = TaskManager::
		Instance()->GetCount(CAST::CATP);
	//�G�̐��������[�v����
	for (DWORD i = 0; i < count; i++) {
		Catp* catp = (Catp*)TaskManager::
			Instance()->GetTask(CAST::CATP, i);
		if (!catp)continue;//�^�X�N(�G)������ł�����
								//�������X�L�b�v
		catp->CheckCollisionEnemy(m_pos.x,
			m_pos.y, m_pos.z, m_rect);
			
	}

	//printf("�����蔻�� X:%f,Y:%f,X:%f\n", m_pos.x, m_pos.y, m_pos.z);

}

void PlayerAttack::HitCheckBee() {
	DWORD count = TaskManager::
		Instance()->GetCount(CAST::BEE);
	//�G�̐��������[�v����
	for (DWORD i = 0; i < count; i++) {
		Bee* bee = (Bee*)TaskManager::
			Instance()->GetTask(CAST::BEE, i);
		if (!bee)continue;//�^�X�N(�G)������ł�����
		//�������X�L�b�v
		bee->CheckCollisionEnemy(m_pos.x,
			m_pos.y, m_pos.z, m_rect);

	}
}
void PlayerAttack::Update()
{
	Player* ply = (Player*)TaskManager::
		Instance()->GetTask(CAST::PLAYER);

	//printf("�����蔻�� X:%f,Y:%f,X:%f\n", 
		//m_pos.x,m_pos.y, m_pos.z);

	if (ply->GetAtk()) {
		HitCheckCatp();
		HitCheckBee();
	}

	if (ply->GetAtk() == false){
		Kill();
	}
}

void PlayerAttack::Render()
{
}
