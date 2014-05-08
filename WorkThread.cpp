#include "StdAfx.h"
#include "WorkThread.h"
#include "Task.h"


CWorkThread::CWorkThread(void)
	: m_hThread(NULL)
	, m_hEvent(NULL)
	, m_pTask(NULL)
{
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
	DWORD dwThreadId;
	m_hThread = CreateThread(NULL, 0, threadPro, this, 0, &dwThreadId);
	// �����¼��������ڿ��ƺ�ʱִ������
	// �Զ���λ��ÿ�ν�����ʹ�̴߳��ڵȴ�״̬����ʼ״̬�����߳��Ƿ�ӵ�и��¼�
	m_hEvent = CreateEvent(NULL, false, false, NULL);
}

void CWorkThread::Release()
{
	// �ر��̡߳��¼�
	CloseHandle(m_hThread);
	CloseHandle(m_hEvent);
}

DWORD WINAPI CWorkThread::threadPro( LPVOID pParam )
{	
	CWorkThread* pThread = (CWorkThread*)pParam;
	if (NULL == pThread)
	{
		// 
		return -1;
	}

	// һֱ�ж��߳�״̬���Ƿ���й���
	while (WAIT_OBJECT_0 != WaitForSingleObject(pThread->GetEvent(), INFINITE))
	{
		// ����
		pThread->ExecuteTask();
		// �ƺ�
		pThread->FinishWork();
	}

	return 0;
}

// �߳�ִ������ǰ��׼������
bool CWorkThread::StartWork(CTask* pTask)
{
	m_pTask = pTask;
	// �̼߳������ڼ���״̬�����뼤���б���

	// �����߳� ��ʼ����
	SetEvent(m_hEvent);
	return true;
}

// �߳�ִ���������ƺ���
bool CWorkThread::FinishWork()
{	
	// ��ʱ�̴߳��ڿ���״̬��������뵽�̳߳صĿ���ջ��
	return true;
}

bool CWorkThread::ExecuteTask()
{
	// ִ�й���
	m_pTask->Work();
	return true;
}
