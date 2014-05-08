#pragma once

//////////////////////////////////////////////////////////////////////////
//
//		工作线程类
//
//////////////////////////////////////////////////////////////////////////

class CTask;
class CWorkThread
{
public:
	CWorkThread(void);
	~CWorkThread(void);

private:
	// 初始化、释放
	void Initial();
	void Release();

	// 线程工作函数
	static DWORD WINAPI threadPro(LPVOID pParam);

	// 任务开始前后、线程的准备、善后工作
	bool StartWork(CTask* pTask);
	bool FinishWork();

	// 
	bool ExecuteTask();

	// 获取数据
	HANDLE GetEvent(){return m_hEvent;}

private:
	HANDLE m_hThread;
	HANDLE m_hEvent;
	CTask* m_pTask;
};

