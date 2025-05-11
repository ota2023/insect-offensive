#include "Task.h"
#include "TaskManager.h"

Task::Task()
{
}

//�R���X�g���N�^
Task::Task(int prio, int sortOrder,CAST _id)
	:m_isEnable(true)
	,m_isShow(true)
	,m_isKill(false)
	,m_prio(prio)
	,m_sortOrder(sortOrder)
	,m_id(_id)
{
	//TaskManager�̃��X�g�Ɏ��g��ǉ�
	TaskManager::Instance()->Add(this);

}

//�f�X�g���N�^
Task::~Task()
{
	//TaskManager�̃��X�g���玩�g����菜��
	TaskManager::Instance()->Remove(this);
}

//�L���t���O��ݒ�
void Task::SetEnable(bool enable)
{
	m_isEnable = enable;
}

//�L���t���O���擾
bool Task::IsEnable() const
{
	return m_isEnable;
}

void Task::SetShow(bool show)
{
	m_isShow = show;
}

bool Task::IsShow() const
{
	return m_isShow;
}

void Task::Kill()
{
	m_isKill = true;
}

bool Task::IsKill() const
{
	return m_isKill;
}

void Task::SetPriority(int prio)
{
	m_prio = prio;
	//��x���X�g�����菜���āA�ʓx�ǉ����Ȃ������Ƃŕ��ёւ���
	TaskManager::Instance()->Remove(this, true);
	TaskManager::Instance()->Add(this, true);
}

int Task::GetPriority() const
{
	return m_prio;
}

void Task::SetSortOeder(int order)
{
	m_sortOrder = order;
	//��x���X�g�����菜���āA�ʓx�ǉ����Ȃ������Ƃŕ��ёւ���
	TaskManager::Instance()->Remove(this, true);
	TaskManager::Instance()->Add(this, true);
}

int Task::GetSortOeder() const
{
	return m_sortOrder;
}

CAST Task::GetId() const
{
	return m_id;
}

//�X�V
void Task::Update()
{

}

//�`��
void Task::Render()
{

}
