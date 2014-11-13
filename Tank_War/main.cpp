/********************************************
 * 程序名			:           Tank_War	*
 * 作者 : Lich_Amnesia <chen3221@126.com>   *
 * 编译环境 : VS2012 && EasyX Ver20130610   *
 * 最后修改 :     2013-09-13			    *
 ********************************************/

#include "Tank_ele.h"
#include "TankGame.h"
#include "labyrith.h"
#include <Windows.h>
extern int mycontrol; 
// 主函数
int main()
{
	//HMODULE hmod = GetModuleHandle(NULL);  // 获取当前进程的句柄
	//HCURSOR hcur = (HCURSOR)LoadImage(NULL, _T("D:\\Projects\\C++\\Tank_War\\res\\cross.cur"), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);
	FrameWindow frame;	// 建立图形界面
	frame.Run();		// 运行控制函数

	while(mycontrol != 'q' && mycontrol != 'Q')			// 主循环
	{
		frame.Run();	// 运行控制
	} 

	//getch();			// 当有按键的时候关闭图形
	closegraph();

	return 0;
}