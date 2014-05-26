#pragma once

//////////////////////////////////////////////////////////////////////////
//
//		任务具体类
//
//////////////////////////////////////////////////////////////////////////

#include "ITaskInterface.h"

// 任务优先级权限
enum PRIORITY_PROP
{
	LOW = 0,
	HIGH
};

class CTask : public ITask
{
public:
	CTask(int nTaskIndex, PRIORITY_PROP nLevel = LOW, int nSleep = 10000);
	~CTask(void);

public:
	virtual void Work(DWORD& nThreadId);


	// 取数据
	PRIORITY_PROP PriorityLevel(){return m_nLevel;}

	bool TaskFinished(){return m_bFinish;}
private:
	PRIORITY_PROP m_nLevel;
	bool m_bFinish;
	int m_nSleep;
	int m_nTaskIndex;
};

