#pragma once
#include <windows.h>

class MyTimer
{
private:
	LARGE_INTEGER m_clk;		// ����ʱ����Ϣ
	LONGLONG m_oldclk;			// ���濪ʼʱ�Ӻͽ���ʱ��
	int m_freq;					// ʱ��Ƶ��(ʱ��ʱ�任����)��ʱ���

public:
	MyTimer();
	void Sleep(int ms);
	void Reset();
};

