#include "StdAfx.h"
#include "Task.h"

using namespace std;

CTask::CTask( int nTaskIndex, PRIORITY_PROP nLevel, int nSleep)
	: m_nTaskIndex(nTaskIndex)
	, m_nLevel(nLevel)
	, m_nSleep(nSleep)
	, m_bFinish(false)
{
}


CTask::~CTask(void)
{
}

void CTask::Work(DWORD& nThreadId)
{
	printf("Task Index = %4d, Exe Thread Index = %4d, Level = %s, SleepTime = %4d\r\n", m_nTaskIndex, nThreadId, (m_nLevel==LOW)?"ตอ":"ธ฿", m_nSleep);

	Sleep(m_nSleep);
	m_bFinish = true;
}
