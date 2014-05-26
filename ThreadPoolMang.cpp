// �̳߳ع�����ʵ��

#include "StdAfx.h"
#include "ThreadPoolMang.h"
#include "WorkThread.h"
#include "Task.h"

CThreadPoolMang::CThreadPoolMang(int nThreadCount)
	: m_nThreadCount(nThreadCount)	
{	
	Initial();
}


CThreadPoolMang::~CThreadPoolMang(void)
{
	Release();
}

void CThreadPoolMang::Initial()
{
	// �����̳߳�
	int i = 0;
	while ( i < m_nThreadCount )
	{
		m_sBlockThread.push(new CWorkThread(this, i+1));
		//m_lGlobalCounter.Lock();����ֱ�Ӵ����߳��У������������
		i++;
		//m_lGlobalCounter.UnLock();
	}
}

void CThreadPoolMang::Release()
{
	// �ͷ���Դ
	while (!m_sBlockThread.empty())
	{
		CWorkThread* pThread = m_sBlockThread.top();
		//pThread->ExitThread();
		delete pThread;
		m_sBlockThread.pop();
	}
}

void CThreadPoolMang::AddTask( CTask* pTask )
{
	// 1.�Ƿ��п����̣߳�����ʼִ������
	if (!m_sBlockThread.empty())
	{
		// ����stl�������̼߳���
		m_lBlockThread.Lock();		
		CWorkThread* pThread = m_sBlockThread.top();
		assert(pThread != NULL);
		m_sBlockThread.pop();
		m_lBlockThread.UnLock();

		// ֪ͨ�߳�δ����״̬
		pThread->BeforeWork(pTask);

		// ���̼߳��뵽�����߳���
		m_lActiveThread.Lock();
		m_lstActiveThread.push_back(pThread);
		m_lActiveThread.UnLock();
		return;
	}

	// 2.û���򣬼��������б�ȴ�
	m_lTaskDeque.Lock();
	if (HIGH == pTask->PriorityLevel())
	{
		m_deqTask.push_front(pTask);
	}
	else
	{
		m_deqTask.push_back(pTask);
	}
	m_lTaskDeque.UnLock();
}

void CThreadPoolMang::BlockThread( CWorkThread* pThread )
{
	assert(pThread != NULL);
	// ���ж��Ƿ�������δִ��
	if (!m_deqTask.empty())
	{
		// ȡ������
		m_lTaskDeque.Lock();
		CTask* pTask = m_deqTask.front();
		assert(pTask != NULL);
		m_deqTask.pop_front();
		m_lTaskDeque.UnLock();

		// Ϊ�̷߳�������,
		pThread->BeforeWork(pTask);
		return;
	}

	// 2.û���������̼߳��뵽������������
	m_lBlockThread.Lock();
	m_sBlockThread.push(pThread);
	m_lBlockThread.UnLock();

	// 3.���ҳ弤���߳��б����Ƴ�
	m_lActiveThread.Lock();
	m_lstActiveThread.remove(pThread);
	m_lActiveThread.UnLock();
}

HANDLE CThreadPoolMang::GetThreadHandle()
{
	return new HANDLE[10];
}
