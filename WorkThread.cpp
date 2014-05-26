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

	// 初始化
	Initial();
}


CWorkThread::~CWorkThread(void)
{
	// 释放资源
	Release();
}

void CWorkThread::Initial()
{	
	// 创建线程	
	m_hThread = CreateThread(NULL, 0, threadPro, this, 0, NULL);
	// 创建事件对象，用于控制何时执行任务
	// 自动置位：每次结束后使线程处于等待状态；初始状态：该线程是否拥有该事件
	m_hEvent = CreateEvent(NULL, false, false, NULL);
}

void CWorkThread::Release()
{	
	// 关闭线程、事件
	CloseHandle(m_hEvent);
	CloseHandle(m_hThread);	
}

DWORD WINAPI CWorkThread::threadPro( LPVOID pParam )
{	
	CWorkThread* pThread = (CWorkThread*)pParam;
	assert(pThread != NULL);

	// 一直判断线程状态、是否进行工作
	while(true)
	{
		if (WAIT_OBJECT_0 == WaitForSingleObject(pThread->GetEvent(), INFINITE))
		{
			// 工作
			pThread->ExecuteTask();
			// 善后
			pThread->AfterWork();		
		}
	}

	return 0;
}

// 线程执行任务前的准备工作
bool CWorkThread::BeforeWork(CTask* pTask)
{
	// 分配工作
	m_pTask = pTask;
	// 激活线程 开始工作
	SetEvent(m_hEvent);
	return true;
}

// 线程执行任务后的善后工作
bool CWorkThread::AfterWork()
{	
	// 释放任务资源
	delete m_pTask;
	m_pTask = NULL;

	// 这时线程处于空闲状态，将其放入到线程池的空闲栈中
	m_pThreadPoolManger->BlockThread(this);
	return true;
}

bool CWorkThread::ExecuteTask()
{
	assert(m_pTask != NULL);
	// 执行工作
	m_pTask->Work(m_nThreadIndex);
	return true;
}
