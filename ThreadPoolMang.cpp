// �̳߳ع�����ʵ��

#include "StdAfx.h"
#include "ThreadPoolMang.h"
#include "WorkThread.h"
#include "Task.h"
#include "Lock.h"

using namespace std;

CThreadPoolMang::CThreadPoolMang(int nThreadCount)
	: m_nThreadCount(nThreadCount)
	, m_pLockThreadContainer(NULL)
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
	for (int i = 0; i < m_nThreadCount; i++)
	{
		m_sBlockThread.push(new CWorkThread());
	}
	// ����������
	m_pLockThreadContainer = new CLock();
}

void CThreadPoolMang::Release()
{
	// �ͷ���Դ
	while (!m_sBlockThread.empty())
	{
		CWorkThread* pThread = m_sBlockThread.top();
		delete pThread;
		m_sBlockThread.pop();
	}

	//
	delete m_pLockThreadContainer;
	m_pLockThreadContainer = NULL;
}

void CThreadPoolMang::AddTask( CTask* pTask )
{
	// ���������б�
	if (HIGH == pTask->PriorityLevel())
	{
		m_deqTask.push_front(pTask);
	}
	else
	{
		m_deqTask.push_back(pTask);
	}
	
	// ��ʼ�����߳�ִ������

}

void CThreadPoolMang::SwitchThreadPos( CWorkThread* pThread, bool bActiveStat )
{

}
