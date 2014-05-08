#pragma once

//////////////////////////////////////////////////////////////////////////
//
//		�����߳���
//
//////////////////////////////////////////////////////////////////////////

class CTask;
class CWorkThread
{
public:
	CWorkThread(void);
	~CWorkThread(void);

private:
	// ��ʼ�����ͷ�
	void Initial();
	void Release();

	// �̹߳�������
	static DWORD WINAPI threadPro(LPVOID pParam);

	// ����ʼǰ���̵߳�׼�����ƺ���
	bool StartWork(CTask* pTask);
	bool FinishWork();

	// 
	bool ExecuteTask();

	// ��ȡ����
	HANDLE GetEvent(){return m_hEvent;}

private:
	HANDLE m_hThread;
	HANDLE m_hEvent;
	CTask* m_pTask;
};

