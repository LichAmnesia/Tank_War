#pragma once
#include <windows.h>

class MyTimer
{
private:
	LARGE_INTEGER m_clk;		// 保存时钟信息
	LONGLONG m_oldclk;			// 保存开始时钟和结束时钟
	int m_freq;					// 时钟频率(时钟时间换算率)，时间差

public:
	MyTimer();
	void Sleep(int ms);
	void Reset();
};

