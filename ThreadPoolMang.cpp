// 线程池管理类实现

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
	// 创建线程池
	for (int i = 0; i < m_nThreadCount; i++)
	{
		m_sBlockThread.push(new CWorkThread());
	}
	// 创建互斥锁
	m_pLockThreadContainer = new CLock();
}

void CThreadPoolMang::Release()
{
	// 释放资源
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
	// 加入任务列表
	if (HIGH == pTask->PriorityLevel())
	{
		m_deqTask.push_front(pTask);
	}
	else
	{
		m_deqTask.push_back(pTask);
	}
	
	// 开始查找线程执行任务

}

void CThreadPoolMang::SwitchThreadPos( CWorkThread* pThread, bool bActiveStat )
{

}
