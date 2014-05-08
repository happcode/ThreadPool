#pragma once

//////////////////////////////////////////////////////////////////////////
///
///		线程池：管理所有线程的调度回收
///
//////////////////////////////////////////////////////////////////////////

#include <list>

const int Thread_Count = 10;

class CTask;
class CWorkThread;
class CLock;
class CThreadPoolMang
{
public:
	CThreadPoolMang(int nThreadCount = Thread_Count);
	~CThreadPoolMang(void);


private:
	// 初始化，释放资源
	void Initial();
	void Release();

public:
	// 
	void AddTask(CTask* pTask);

	// 线程状态改变时，放入不同的容器中
	void SwitchThreadPos(CWorkThread* pThread, bool bActiveStat);


	// 获取数据
	int GetThreadCount(){return m_nThreadCount;}

private:
	/************************************************************************/
	/* 在线程结束时该线程会放入到空闲队列中，分配任务时也会访问空闲队列；
	/* 由于多线程同时操作（write）stl容器，所以得加锁互斥。
	/* CRITICAL_SECTION、MUTEX都可以选择，都拥有线程所有权，Mutex可用于进程间互斥。
	/* CRITICAL_SECTION不是内核对象，花销少
	/************************************************************************/

	// 双向队列存放任务，优先级高的任务从前面插入
	std::deque<CTask*> m_deqTask;
	// 存放执行过的任务(应该是谁创建谁释放)
	//std::vector<CTask*> m_vcInvalidTask;

	// 存放处于激活状态的线程
	std::list<CWorkThread*> m_lstActiveThread;
	// 存放阻塞状态的线程
	std::stack<CWorkThread*> m_sBlockThread;

	//
	int m_nThreadCount;

	// 互斥锁
	CLock* m_pLockThreadContainer;	
};

