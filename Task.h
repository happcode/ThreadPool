#pragma once

//////////////////////////////////////////////////////////////////////////
//
//		���������
//
//////////////////////////////////////////////////////////////////////////

// �������ȼ�Ȩ��
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


	// ȡ����
	PRIORITY_PROP PriorityLevel(){return m_nLevel;}

private:
	PRIORITY_PROP m_nLevel;
};

