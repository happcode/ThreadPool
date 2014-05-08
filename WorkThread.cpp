#include "StdAfx.h"
#include "WorkThread.h"
#include "Task.h"


CWorkThread::CWorkThread(void)
	: m_hThread(NULL)
	, m_hEvent(NULL)
	, m_pTask(NULL)
{
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
	DWORD dwThreadId;
	m_hThread = CreateThread(NULL, 0, threadPro, this, 0, &dwThreadId);
	// 创建事件对象，用于控制何时执行任务
	// 自动置位：每次结束后使线程处于等待状态；初始状态：该线程是否拥有该事件
	m_hEvent = CreateEvent(NULL, false, false, NULL);
}

void CWorkThread::Release()
{
	// 关闭线程、事件
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

	// 一直判断线程状态、是否进行工作
	while (WAIT_OBJECT_0 != WaitForSingleObject(pThread->GetEvent(), INFINITE))
	{
		// 工作
		pThread->ExecuteTask();
		// 善后
		pThread->FinishWork();
	}

	return 0;
}

// 线程执行任务前的准备工作
bool CWorkThread::StartWork(CTask* pTask)
{
	m_pTask = pTask;
	// 线程即将处于激活状态，放入激活列表中

	// 激活线程 开始工作
	SetEvent(m_hEvent);
	return true;
}

// 线程执行任务后的善后工作
bool CWorkThread::FinishWork()
{	
	// 这时线程处于空闲状态，将其放入到线程池的空闲栈中
	return true;
}

bool CWorkThread::ExecuteTask()
{
	// 执行工作
	m_pTask->Work();
	return true;
}
