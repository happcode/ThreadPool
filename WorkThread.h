#pragma once

//////////////////////////////////////////////////////////////////////////
//
//		工作线程类
//
//////////////////////////////////////////////////////////////////////////

class CTask;
class CThreadPoolMang;
class CWorkThread
{
public:
	CWorkThread(CThreadPoolMang* pThreadManger, int nIndex);
	~CWorkThread(void);

private:
	// 初始化、释放
	void Initial();
	void Release();

	// 线程工作函数
	static DWORD WINAPI threadPro(LPVOID pParam);

public:
	// 任务开始前后、线程的准备、善后工作
	bool BeforeWork(CTask* pTask);
	bool AfterWork();

public:
	// 
	bool ExecuteTask();

	// 获取数据
	HANDLE GetEvent(){return m_hEvent;}

	void ExitThread(){m_bIsExit = true;}
	bool IsExit(){return m_bIsExit;}
private:
	CThreadPoolMang* m_pThreadPoolManger;
	HANDLE m_hThread;
	HANDLE m_hEvent;
	CTask* m_pTask;
	DWORD  m_nThreadIndex;
	bool   m_bIsExit;
};

