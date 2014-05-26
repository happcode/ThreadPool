// main.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "ThreadPoolMang.h"
#include "Task.h"

int _tmain(int argc, _TCHAR* argv[])
{	
	CThreadPoolMang* pThreadPool = new CThreadPoolMang(5);
 	for (int i = 0; i < 11; i++)
 	{
		if (i == 10)
		{
			// ���ȼ��ߵ���ִ��
			pThreadPool->AddTask(new CTask(i+1, HIGH));
			continue;
		}
 		pThreadPool->AddTask(new CTask(i+1));
 	}	

	// Ӧ���и��������ж������߳��Ƿ����
	while(!pThreadPool->IsTaskFinsihAll());
	delete pThreadPool;
		
	
	system("pause");
	// check memory leaks
	_CrtDumpMemoryLeaks(); 
	return 0;
}

