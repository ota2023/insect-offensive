#include "EnemyManager.h"
#include "EnemyBase.h"
#include "Player.h"

EnemyManager* EnemyManager::sp_instance = nullptr;

// �C���X�^���X�擾
EnemyManager* EnemyManager::Instance()
{
	// �C���X�^���X���Ȃ���΁A����
	if (sp_instance == nullptr)
	{
		sp_instance = new EnemyManager();
	}
	return sp_instance;
}

// �C���X�^���X�j��
void EnemyManager::ClearInstance()
{
	if (sp_instance != nullptr)
	{
		delete sp_instance;
	}
}

// �G�����X�g�ɒǉ�
void EnemyManager::Add(EnemyBase* enemy)
{
	m_enemyList.push_back(enemy);
}

// �G�����X�g�����菜��
void EnemyManager::Remove(EnemyBase* enemy)
{
	m_enemyList.remove(enemy);
}

void EnemyManager::Print()
{
	printf("���\n");

}





// �R���X�g���N�^
EnemyManager::EnemyManager()
{
}

// �f�X�g���N�^
EnemyManager::~EnemyManager()
{
	sp_instance = nullptr;
}
