#pragma once

//////////////////////////////////////////////////////////////////////////
//
//		任务具体类
//
//////////////////////////////////////////////////////////////////////////

// 任务优先级权限
enum PRIORITY_PROP
{
	LOW = 0,
	HIGH
};

class CTask
{
public:
	CTask(void);
	CTask(PRIORITY_PROP nLevel);
	~CTask(void);

public:
	void Work();


	// 取数据
	PRIORITY_PROP PriorityLevel(){return m_nLevel;}

private:
	PRIORITY_PROP m_nLevel;
};

