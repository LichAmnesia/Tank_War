/********************************************
 * ������			:           Tank_War	*
 * ���� : Lich_Amnesia <chen3221@126.com>   *
 * ���뻷�� : VS2012 && EasyX Ver20130610   *
 * ����޸� :     2013-09-13			    *
 ********************************************/

#include "Tank_ele.h"
#include "TankGame.h"
#include "labyrith.h"
#include <Windows.h>
extern int mycontrol; 
// ������
int main()
{
	//HMODULE hmod = GetModuleHandle(NULL);  // ��ȡ��ǰ���̵ľ��
	//HCURSOR hcur = (HCURSOR)LoadImage(NULL, _T("D:\\Projects\\C++\\Tank_War\\res\\cross.cur"), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);
	FrameWindow frame;	// ����ͼ�ν���
	frame.Run();		// ���п��ƺ���

	while(mycontrol != 'q' && mycontrol != 'Q')			// ��ѭ��
	{
		frame.Run();	// ���п���
	} 

	//getch();			// ���а�����ʱ��ر�ͼ��
	closegraph();

	return 0;
}