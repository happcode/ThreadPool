// 线程池管理类实现

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
	// 创建线程池
	int i = 0;
	while ( i < m_nThreadCount )
	{
		m_sBlockThread.push(new CWorkThread(this, i+1));
		//m_lGlobalCounter.Lock();不是直接传入线程中，所以无需加锁
		i++;
		//m_lGlobalCounter.UnLock();
	}
}

void CThreadPoolMang::Release()
{
	// 释放资源
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
	// 1.是否有空闲线程，有则开始执行任务
	if (!m_sBlockThread.empty())
	{
		// 操作stl，阻塞线程加锁
		m_lBlockThread.Lock();		
		CWorkThread* pThread = m_sBlockThread.top();
		assert(pThread != NULL);
		m_sBlockThread.pop();
		m_lBlockThread.UnLock();

		// 通知线程未激活状态
		pThread->BeforeWork(pTask);

		// 将线程加入到激活线程中
		m_lActiveThread.Lock();
		m_lstActiveThread.push_back(pThread);
		m_lActiveThread.UnLock();
		return;
	}

	// 2.没有则，加入任务列表等待
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
	// 先判断是否有任务还未执行
	if (!m_deqTask.empty())
	{
		// 取出任务
		m_lTaskDeque.Lock();
		CTask* pTask = m_deqTask.front();
		assert(pTask != NULL);
		m_deqTask.pop_front();
		m_lTaskDeque.UnLock();

		// 为线程分配任务,
		pThread->BeforeWork(pTask);
		return;
	}

	// 2.没有任务，则将线程加入到阻塞队列中来
	m_lBlockThread.Lock();
	m_sBlockThread.push(pThread);
	m_lBlockThread.UnLock();

	// 3.并且冲激活线程列表中移除
	m_lActiveThread.Lock();
	m_lstActiveThread.remove(pThread);
	m_lActiveThread.UnLock();
}

HANDLE CThreadPoolMang::GetThreadHandle()
{
	return new HANDLE[10];
}
