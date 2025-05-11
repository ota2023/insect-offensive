#pragma once
#include "Task.h"

class Task;	//�N���X�̑O�錾
			//�O�錾�����Ń|�C���^�͈�����
class ObjectBase;

//�^�X�N���Ǘ�����N���X
class TaskManager
{
public:	//�V���O���g��(�C�ɂȂ�l�͒��ׂĂ݂�)
	//TaskManager�̃C���X�^���X���擾
	static TaskManager* Instance();
	//TaskManager�̃C���X�^���X��j��
	static void ClearInstance();
	
	//�^�X�N���X�g�Ƀ^�X�N��ǉ�
	void Add(Task* task, bool sort = false);
	//�^�X�N���X�g����^�X�N����菜��
	void Remove(Task* task, bool sort = false);

	//�S�Ẵ^�X�N���폜
	void DeleteAll();
	//�폜�t���O�������Ă���^�X�N���폜
	void DeleteKilledTask();

	//�w�肵��id�������A�w�肵���ԍ��̃^�X�N��Ԃ�
	Task* GetTask(CAST _id, DWORD _number = 0);

	//�w�肵���O���[�v��(id)�̃^�X�N����Ԃ�
	DWORD GetCount(CAST _id);
	
	//���X�g�ɓo�^����Ă���^�X�N���X�V
	void Update();
	//���X�g�ɓo�^����Ă���^�X�N��`��
	void Render();

private:
	//�R���X�g���N�^
	TaskManager();
	//�f�X�g���N�^
	~TaskManager();

	//TaskManager�̃C���X�^���X
	static TaskManager* ms_instance;
	//�����ς݂̃^�X�N���X�g
	std::list<Task*> m_taskList;	//�����ς݂̃^�X�N�̃��X�g
	//�����ς݂̃I�u�W�F�N�g�̃��X�g
	std::list<Task*> m_objectList;

};