#pragma once

//////////////////////////////////////////////////////////////////////////
//
//		�����߳���
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
	// ��ʼ�����ͷ�
	void Initial();
	void Release();

	// �̹߳�������
	static DWORD WINAPI threadPro(LPVOID pParam);

public:
	// ����ʼǰ���̵߳�׼�����ƺ���
	bool BeforeWork(CTask* pTask);
	bool AfterWork();

public:
	// 
	bool ExecuteTask();

	// ��ȡ����
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

