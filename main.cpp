// main.cpp : 定义控制台应用程序的入口点。
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
			// 优先级高的先执行
			pThreadPool->AddTask(new CTask(i+1, HIGH));
			continue;
		}
 		pThreadPool->AddTask(new CTask(i+1));
 	}	

	// 应该有个机制来判断所有线程是否结束
	while(!pThreadPool->IsTaskFinsihAll());
	delete pThreadPool;
		
	
	system("pause");
	// check memory leaks
	_CrtDumpMemoryLeaks(); 
	return 0;
}

