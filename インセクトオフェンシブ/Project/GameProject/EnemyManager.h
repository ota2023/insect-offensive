#pragma once

class EnemyBase;

// �G�Ǘ��N���X
class EnemyManager
{
public:
	// �C���X�^���X�擾
	static EnemyManager* Instance();
	// �C���X�^���X�j��
	static void ClearInstance();

	// �G�����X�g�ɒǉ�
	void Add(EnemyBase* enemy);
	// �G�����X�g�����菜��
	void Remove(EnemyBase* enemy);

	//�����`��
	void Print();


private:
	// �R���X�g���N�^
	EnemyManager();
	// �f�X�g���N�^
	~EnemyManager();

	// �C���X�^���X
	static EnemyManager* sp_instance;
	// �����ς݂̃G�l�~�[�̃��X�g
	std::list<EnemyBase*> m_enemyList;
};
