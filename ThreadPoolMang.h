#pragma once

//////////////////////////////////////////////////////////////////////////
///
///		�̳߳أ����������̵߳ĵ��Ȼ���
///
//////////////////////////////////////////////////////////////////////////

#include <list>
#include "IThreadPoolInterface.h"
#include "Lock.h"

const int Thread_Count = 10;

class CLock;
class CTask;
class CWorkThread;
class CThreadPoolMang:public IThreadPool
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
	void BlockThread(CWorkThread* pThread);

	// ��ȡ����
	int GetThreadCount(){return m_nThreadCount;}
	bool IsTaskFinsihAll(){return m_sBlockThread.size() == m_nThreadCount;}
	CLock& GetLock(){return m_lGlobalCounter;}

	//
	HANDLE GetThreadHandle();

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

	// ��Ŵ�������״̬���߳�
	std::stack<CWorkThread*> m_sBlockThread;
	// ��ż���״̬���߳�
	std::list<CWorkThread*> m_lstActiveThread;

	//
	int m_nThreadCount;

	// �����̻߳�����
	CLock m_lActiveThread;
	// �����̻߳�����
	CLock m_lBlockThread;
	// ���񻥳���
	CLock m_lTaskDeque;


	// ȫ�ּ�����
	CLock m_lGlobalCounter;
};

