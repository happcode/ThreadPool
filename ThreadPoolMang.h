#pragma once

//////////////////////////////////////////////////////////////////////////
///
///		�̳߳أ����������̵߳ĵ��Ȼ���
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
	// ��ʼ�����ͷ���Դ
	void Initial();
	void Release();

public:
	// 
	void AddTask(CTask* pTask);

	// �߳�״̬�ı�ʱ�����벻ͬ��������
	void SwitchThreadPos(CWorkThread* pThread, bool bActiveStat);


	// ��ȡ����
	int GetThreadCount(){return m_nThreadCount;}

private:
	/************************************************************************/
	/* ���߳̽���ʱ���̻߳���뵽���ж����У���������ʱҲ����ʿ��ж��У�
	/* ���ڶ��߳�ͬʱ������write��stl���������Եü������⡣
	/* CRITICAL_SECTION��MUTEX������ѡ�񣬶�ӵ���߳�����Ȩ��Mutex�����ڽ��̼以�⡣
	/* CRITICAL_SECTION�����ں˶��󣬻�����
	/************************************************************************/

	// ˫����д���������ȼ��ߵ������ǰ�����
	std::deque<CTask*> m_deqTask;
	// ���ִ�й�������(Ӧ����˭����˭�ͷ�)
	//std::vector<CTask*> m_vcInvalidTask;

	// ��Ŵ��ڼ���״̬���߳�
	std::list<CWorkThread*> m_lstActiveThread;
	// �������״̬���߳�
	std::stack<CWorkThread*> m_sBlockThread;

	//
	int m_nThreadCount;

	// ������
	CLock* m_pLockThreadContainer;	
};

