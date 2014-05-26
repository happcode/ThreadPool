#include "StdAfx.h"
#include "WorkThread.h"
#include "ThreadPoolMang.h"
#include "Task.h"


CWorkThread::CWorkThread(CThreadPoolMang* pThreadManger, int nThreadIndex)
	: m_pThreadPoolManger(pThreadManger)
	, m_hThread(NULL)
	, m_hEvent(NULL)
	, m_pTask(NULL)
	, m_nThreadIndex(0)
	, m_bIsExit(false)
{
	assert(m_pThreadPoolManger != NULL);
	//pThreadManger->GetLock().Lock();
	m_nThreadIndex = nThreadIndex;
	//pThreadManger->GetLock().UnLock();

	// ��ʼ��
	Initial();
}


CWorkThread::~CWorkThread(void)
{
	// �ͷ���Դ
	Release();
}

void CWorkThread::Initial()
{	
	// �����߳�	
	m_hThread = CreateThread(NULL, 0, threadPro, this, 0, NULL);
	// �����¼��������ڿ��ƺ�ʱִ������
	// �Զ���λ��ÿ�ν�����ʹ�̴߳��ڵȴ�״̬����ʼ״̬�����߳��Ƿ�ӵ�и��¼�
	m_hEvent = CreateEvent(NULL, false, false, NULL);
}

void CWorkThread::Release()
{	
	// �ر��̡߳��¼�
	CloseHandle(m_hEvent);
	CloseHandle(m_hThread);	
}

DWORD WINAPI CWorkThread::threadPro( LPVOID pParam )
{	
	CWorkThread* pThread = (CWorkThread*)pParam;
	assert(pThread != NULL);

	// һֱ�ж��߳�״̬���Ƿ���й���
	while(true)
	{
		if (WAIT_OBJECT_0 == WaitForSingleObject(pThread->GetEvent(), INFINITE))
		{
			// ����
			pThread->ExecuteTask();
			// �ƺ�
			pThread->AfterWork();		
		}
	}

	return 0;
}

// �߳�ִ������ǰ��׼������
bool CWorkThread::BeforeWork(CTask* pTask)
{
	// ���乤��
	m_pTask = pTask;
	// �����߳� ��ʼ����
	SetEvent(m_hEvent);
	return true;
}

// �߳�ִ���������ƺ���
bool CWorkThread::AfterWork()
{	
	// �ͷ�������Դ
	delete m_pTask;
	m_pTask = NULL;

	// ��ʱ�̴߳��ڿ���״̬��������뵽�̳߳صĿ���ջ��
	m_pThreadPoolManger->BlockThread(this);
	return true;
}

bool CWorkThread::ExecuteTask()
{
	assert(m_pTask != NULL);
	// ִ�й���
	m_pTask->Work(m_nThreadIndex);
	return true;
}
