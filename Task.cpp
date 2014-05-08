#include "StdAfx.h"
#include "Task.h"

using namespace std;

CTask::CTask(void)
	: m_nLevel(LOW)
{
}

CTask::CTask( PRIORITY_PROP nLevel )
{
	m_nLevel = nLevel;
}


CTask::~CTask(void)
{
}

void CTask::Work()
{
	cout << "I'm working......" << endl;
}
