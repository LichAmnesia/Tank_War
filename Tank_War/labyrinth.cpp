#include "labyrith.h"
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include "TankGame.h"
#include "Tank_ele.h"
int Wall[34][34];	// ǽ��
int entranceX;		// ���
int entranceY;
int exitX;			// ����
int exitY;
int Play1_X;		// ���1
int Play1_Y;
int Play2_X;			//���2
int Play2_Y;

// Ĭ�Ϲ��캯��
FrameWindow::FrameWindow()
{
	initgraph(960, 660);					// ����ͼ�ν���
	setbkcolor(LIGHTGREEN);					// ���ñ�����ɫΪ����ɫ
	direct = 0;								// ���� direct �ĳ�ֵΪ 0
	control = 0;							// Ĭ�Ͽ���ȨΪ 0 
	loadimage(&img, "res\\bk.jpg", 20, 20);	// ����ͼƬ
	loadimage(&bksimg, "res\\tank_bk.jpg", 20, 20);

	HCURSOR hcur = LoadCursor(NULL, IDC_CROSS);		// ����ϵͳԤ�õ������ʽ
	HWND hwnd = GetHWnd();							// ��ȡ��ͼ���ھ��
	SetClassLong(hwnd, GCL_HCURSOR, (long)hcur);	// ���ô�����������ʽ
}

void FrameWindow::Run()
{
	cleardevice();		// ����
	NewBackground();	// �����±���ͼ
	DrawSome();			// ����Щ����
	control = 0;		// ���Ƚ������Գ������Ŀ���Ȩ�� 0
	direct = 0;			// ���� direct �ĳ�ֵΪ 0
	TankGame newGame;
	// ��ѭ��
	while(1)
	{
		if(kbhit())													// ��ⰴ��
		{
 			direct = getch();										// �Ӱ�����ȡ����
			mciSendString("play  res\\key.wav", NULL, 0, NULL);		// ������
			if( direct == 115 &&  control == 0)						// s �ļ�ֵΪ 115
			{
				StartDrawLabyrith();								// ��ʼ�����Թ�
			}


			if(direct == 101 && control == 2)						// e �ļ�ֵΪ 101
			{
				SetLabyrith();										// �����Թ�����ںͳ���
			}

			if(direct == 100 && control == 3)						// d �ļ�ֵΪ 100
			{
				control = -1;										// �� control ����Ϊ -1 ��Ŀ����
																	// �ó���� Demo() �ص� Run() ʱֻ��Ӧˢ�²���
				Demo();												// Ѱ��·������ʾ
				Sleep(2000);
				getch();
				break;
			}
			if (direct == 110 ){									   //
																	//���������λ�� �� Ȼ��ʼ
				FrameWindow::RandomMap();							//�����ͼ
				outtextxy(810, 400, "��Ϸ��ʼ  ");
				newGame.start();
				break;
			}
			if (direct == 104 &&control == 5){ 						 //��ʼ��Ϸ
				outtextxy(810, 400, "��Ϸ��ʼ  ");
				newGame.start();
				break;
			} 
			if(direct == 63 && (control == 0 || control == -1))		// �� F5 ˢ��
			{
				break;
			}
		}
		else
		{
			Sleep(10);
		}
	}	   
}

// �����±���
void FrameWindow::NewBackground()
{
	float H, S, L;					// ���� HSL ��ɫģ�͵� 3 ������
	H = 110;						// ɫ��
	S = 1;							// ���Ͷ�
	L = 0.4522f;					// ����
	for(int y = 0; y != 660; y++)	// �����Թ�������ɫ	 �������»�����ɫ
	{
		setcolor(BLACK);
		line(0,y,660,y);
		//L += 0.000125f;
		//S -= 0.00125f;
		//setcolor(HSLtoRGB(H, S, L));
		//line(0, y, 660, y);
	}

	H = 50;							// ɫ��
	S = -3.2555f;					// ���Ͷ�
	L = 0.525617f;					// ����
	for(int y = 0; y != 660; ++y)		// ������ʾ��Ϣ���ֱ���
	{
		L += 0.000000085f;
		S -= 0.0015f;
		setcolor(HSLtoRGB(H, S, L));
		line(660, y, 960, y);
	}
}

// ����Щ����
void FrameWindow::DrawSome()
{
	setcolor(LIGHTRED);
	int i;
	for(i = 0; i < 34; ++i)								
	{
		// ��Χǽ���� Wall �����е�λ���� 1 
		Wall[0][i] = 1;
		Wall[i][0] = 1;
		Wall[32][i] = 1;
		Wall[i][32] = 1;

		// ������Χǽ��
		putimage(0 *20 , i * 20 , &img);
		putimage(i * 20 , 0 * 20, &img);
		putimage(640, i * 20 , &img);
		putimage(i * 20 , 640, &img);
		putimage(940, i * 20 , &img);

		//setcolor(WHITE);
		//line(i * 20, 0, i * 20, 660);		// ���Ƹ�����
		//line(0, i * 20, 660, i * 20);		// ���Ƹ�����
	}

	for(i = 0; i < 15; ++i)					// ������ʾ������Χ��
	{
		putimage(i * 20 + 661, 1, &img);
		putimage(i * 20 + 661, 641, &img);
	}

	for(i = 1; i <= 31; ++i)				// ������ Wall �����ֵ��ʱ�� 0
	{
		for(int j = 1; j <= 31; ++j)
		{
			Wall[i][j] = 0;
		}
	}

	// ������ʾ��Ϣ
	RECT r = {710, 40, 900, 300};
	setbkmode(TRANSPARENT);					// ����������ֱ���ģʽΪ͸��
	setcolor(BLUE);							// �������������ɫ
	setfont(15, 0, "����");
	
	// �����ʾ��Ϣ
	drawtext("��Ϸ�������ܣ�\n\n N: ֱ�ӿ�ʼ�������ͼ.\n\n \
		S: ����ͼ��֮������,����������ǽ�ڣ�����Ҽ�����ǽ��.\n\n \
		����E:������ҳ�����,��һ�������1�ڶ��������2,�Ҽ�ȡ������.\n\n \
		�������֮�󰴼�H:��ʼ��Ϸ\n\n	   \
		",&r,DT_WORDBREAK);
	/*drawtext("��Ϸ�������ܣ�\n\n���� S�������Թ���\n����������ǽ�ڣ�\
		����Ҽ�����ǽ�ڡ�\n\n���� E�������Թ�����ںͳ��ڡ�\nʹ�����\
		�����������ںͳ��ڣ��Ҽ�ȡ�����á�\n\n���� D�������Թ���̽��\
		��Ѱ�Ҵ���ڵ����ڵ����·������С������ʾ����ڵ����ڵ�·����",
		&r, DT_WORDBREAK);*/

	setbkmode(OPAQUE);						// �ָ�Ĭ�������ɫ

	// �����ʾ��Ϣ
	outtextxy(730, 400, "״̬: ");
	outtextxy(810, 400, "�ȴ�����");
	outtextxy(750, 500, "�� F5 ���¿�ʼ");
}

// ��ʼ�����Թ�
void FrameWindow::StartDrawLabyrith()
{
	int x = 0, y = 0;						// �����������ʹ��
	outtextxy(810, 400, "���ڻ���");		// �޸��Թ�״̬
	FlushMouseMsgBuffer();					// ��������Ϣ������
 
	// ��ѭ��
	while(1)
	{
		if(kbhit())
		{
			direct = getch();									// ��ȡ������Ϣ
			mciSendString("play  res\\key.wav", NULL, 0, NULL);	// ������
			if(direct == 101)									// e �ļ�ֵΪ 101
			{
				control = 2;									// ����ȨֵΪ 2 
				break;
			}
			else if(direct == 63)								// F5 ˢ��
			{
 				break;
			}else if(direct == 110){    //�����ͼȻ��ʼ��Ϸ
				control = 4;break;
			}
		}
		else if(MouseHit())
		{

			msg = GetMouseMsg();										// ��ȡ�����Ϣ
			x = msg.x / 20;												// ��ȡ������ڸ����� Wall �е�λ��
			y = msg.y / 20;
			if(msg.x > 20 && msg.x < 630 && msg.y > 20 && msg.y < 630)	// ֻ�����������������Ӧ�����Ϣ
			{
				switch(msg.uMsg)										// ��Ϣ������
				{
					case WM_LBUTTONDOWN:								// �������
						{
							Wall[x][y] = 1;								// y ��Ӧ��, x ��Ӧ��, ����Ӧ��λ���� 1
							putimage(x * 20 , y * 20 , &img);		// ����ͼƬ
						}
						break;
					case WM_RBUTTONDOWN:								// �Ҽ�����
						{
							Wall[x][y] = 0;								// y ��Ӧ��, x ��Ӧ��, ����Ӧ��λ���� 0
							putimage(x * 20 , y * 20, &bksimg);
							//PrintGrid(x * 20, y * 20);					// ���»����������
							setcolor(BLUE );
						}
						break;
					default:break;
					}
			}

		}
		else 
		{
			Sleep(10);
		}
	}
}

// ����play1��play2
void FrameWindow::SetLabyrith()
{
	int x = 0, y = 0;	// ��ʱ����
	Play1_X = -1;		// play1
	Play1_Y = -1;
	Play2_X = -1;		// play2 
	Play2_Y = -1;	

	entranceX = -1;		// ���
	entranceY = -1;
	exitX = -1;			// ����
	exitY = -1;	

	outtextxy(810, 400, "����Play1");	// ��ʾ��Ϣ
	
	// ��ѭ��
	while(1)
	{
		if(kbhit())						// ������Ϣ
		{
			direct = getch();										// ��ȡ��Ϣ
			mciSendString("play  res\\key.wav", NULL, 0, NULL);		// ������
			if(direct == 100 && entranceX != -1 && exitX != -1)		// �������ڶ����ú�, �� d ���˳�����ģʽ
			{
				control = 3;										// ����Ȩ��Ϊ 3, �ص� Run �������ж���˭���Ƴ���;
				break;
			}
			else if(direct == 63)									// F5 ˢ��
			{
				control = 0;
				break;
			}else if(direct == 104 && entranceX != -1 && exitX != -1){								// 	��ʼ��Ϸ
				control = 5;
				break;
			}

		}
		else if(MouseHit())
		{
			msg = GetMouseMsg();												// ��ȡ�����Ϣ
			x = msg.x / 20;														// ��ȡ������ڸ����� Wall �е�λ��
			y = msg.y / 20;	

			if(entranceX != -1 && exitX != -1)									// �������
			{
				outtextxy(810, 400, "�������  ");
			}

			if(msg.x > 20 && msg.x < 630 && msg.y > 20 && msg.y < 630)			// ֻ�����������������Ӧ�����Ϣ
			{
				if(Wall[x][y] == 0 && msg.uMsg == WM_LBUTTONDOWN && !Wall[x-1][y-1] && !Wall[x][y-1] && !Wall[x+1][y-1] && !Wall[x-1][y] &&  !Wall[x+1][y] && !Wall[x-1][y+1] && !Wall[x][y+1] && !Wall[x+1][y+1])				// ������λ�ò���ǽ��, ���Ұ������
				{
					if(entranceX == -1 && (exitX != x || exitY != y))			// ȷ���˴�û������
					{
						entranceX = x;											// play1λ��
						entranceY = y;
						Play1_X = x;
						Play1_Y = y;
						
						
						Wall[x][y] = 1;
						SignPlay(x,y,2);
						
						outtextxy(x * 20 + 6, y * 20 + 5,_T("O"));			// ���˴����Ϊ In 

						if(exitX == -1)											// ����ʱ��δ���ó���
						{
							outtextxy(810, 400, "�������2");					// �ı��Թ�״̬
						}
					}
					else if(exitX == -1 && (entranceX != x || entranceY != y))	// �˴�δ���ó����Ҳ������λ��
					{
						exitX = x;												// ����λ��
						exitY = y;
						Play2_X = x;
						Play2_Y = y;
						
						
						Wall[x][y] = 1;
						SignPlay(x,y,3);
						
						outtextxy(x * 20 + 6, y * 20 + 5,_T("T"));			// ���˴����Ϊ Out

						if(entranceX == -1)										// ����ʱ��δ�������
						{
							outtextxy(810, 400, "�������1");					// �ı��Թ�״̬
						}
					}
				}
				else if(Wall[x][y] != 0 &&msg.uMsg == WM_RBUTTONDOWN)			// ������λ�ò���ǽ��, ���Ұ����Ҽ�
				{
					if(x == entranceX && y == entranceY)						// ȡ���������
					{
						entranceX = -1;
						entranceY = -1;
						Wall[x][y] = 0;
						SignPlay(x,y,0);
						outtextxy(810, 400, "�������1");						// �ı��Թ�״̬
						putimage(x * 20 , y * 20, &bksimg);
						//PrintGrid(x * 20, y * 20);								// ���»��Ƹ���
						setcolor(BLUE);											// �ָ�ԭ������ɫ
					}
					else if(x == exitX && y == exitY)							// ȡ�����ó���
					{
						exitX = -1;
						exitY = -1;
						Wall[x][y] = 0;
						SignPlay(x,y,0);
						outtextxy(810, 400, "�������2");						// �ı��Թ�״̬
						putimage(x * 20 , y * 20, &bksimg);
						//PrintGrid(x * 20, y * 20);								// ���»��Ƹ���
						setcolor(BLUE);											// �ָ�ԭ������ɫ
					}
				} 
			} 
		} 
	} 
} 
void FrameWindow::RandomMap(){	  //�����ͼ
	for(int i = 1; i <= 31; ++i)				// ������ Wall �����ֵ��ʱ�� 0
	{
		for(int j = 1; j <= 31; ++j)
		{
			putimage(i * 20 , j * 20, &bksimg);
			Wall[i][j] = 0;
		}
	}

	srand(time(NULL));
	int cnt = rand() % 4 + 1;
	//cnt = 4;
	switch (cnt)
	{
	case 1: RMap_1(); break;
	case 2: RMap_2(); break;
	case 3: RMap_3(); break;
	case 4: RMap_4(); break;
	default:
		break;
	}


}
void FrameWindow::RMap_1(){
	for (int i = 7; i <= 8; i++){
		for (int j = 1; j <= 5; j++) 
			Wall[i][j] = 1;
		for (int j = 27; j <= 31; j++) 
			Wall[i][j] = 1;
	}
	for (int i = 25; i <= 26; i++){
		for (int j = 1; j <= 5; j++) 
			Wall[i][j] = 1;
		for (int j = 27; j <= 31; j++) 
			Wall[i][j] = 1;
	}
	for (int i = 1; i <= 4; i++){
		Wall[i][14] = 1;
		Wall[i][18] = 1;
	}
	for (int i = 9; i <= 14; i++){
		Wall[i][14] = 1;
		Wall[i][18] = 1;
	}
	for (int i = 18; i <= 23; i++){
		Wall[i][14] = 1;
		Wall[i][18] = 1;
	}
	for (int i = 28; i <= 31; i++){
		Wall[i][14] = 1;
		Wall[i][18] = 1;
	}
	for (int i = 9; i <= 14; i++){
		Wall[i][10] = 1;
		Wall[i][9] = 1;
		Wall[i][22] = 1;
		Wall[i][23] = 1;
	}
	for (int i = 18; i <= 23; i++){
		Wall[i][10] = 1;
		Wall[i][9] = 1;
		Wall[i][22] = 1;
		Wall[i][23] = 1;
	}
	
	for (int i = 1; i <= 31; i++)
		for (int j = 1; j <= 31; j++)
			if(Wall[i][j])
				putimage(i*20,j*20,&img);

	Play1_X = 26;Play1_Y = 16;
	Play2_X = 6;Play2_Y = 16;

}
void FrameWindow::RMap_2(){
	for (int i = 1; i <= 2; i++)
		for (int j = 15; j <= 17; j++)
			Wall[i][j] = 1;
	for (int i = 7; i <= 10; i++){
		for (int j = 7; j <= 10; j++)
			Wall[i][j] = 1;
		for (int j = 22; j <= 25; j ++)
			Wall[i][j] = 1;
	}
	for (int i = 8; i <= 9; i++)
		for (int j = 15; j <= 17; j++)
			Wall[i][j] = 1;
	for (int i = 15; i <= 17; i++){
		for (int j = 1; j <= 2; j++)
			Wall[i][j] = 1;
		for (int j = 8; j <= 9; j++)
			Wall[i][j] = 1;
		for (int j = 15; j <= 17; j++)
			Wall[i][j] = 1;
		for (int j = 23; j <= 24; j++)
			Wall[i][j] = 1;
		for (int j = 30; j <= 31; j++)
			Wall[i][j] = 1;
	}
	
	for (int i = 22; i <= 25; i++){
		for (int j = 7; j <= 10; j++)
			Wall[i][j] = 1;
		for (int j = 22; j <= 25; j ++)
			Wall[i][j] = 1;
	}
	for (int i = 23; i <= 24; i++)
		for (int j = 15; j <= 17; j++)
			Wall[i][j] = 1;
	for (int i = 30; i <= 31; i++)
		for (int j = 15; j <= 17; j++)
			Wall[i][j] = 1;

	for (int i = 1; i <= 31; i++)
		for (int j = 1; j <= 31; j++)
			if(Wall[i][j])
				putimage(i*20,j*20,&img);

	Play1_X = 29;Play1_Y = 29;
	Play2_X = 3;Play2_Y = 3;


}
void FrameWindow::RMap_3(){
	for (int i = 5; i <= 6; i++)
		for (int j = 1; j <= 4; j ++)
			Wall[i][j] = 1;
	for (int i = 1; i <= 6; i++)
		for (int j = 9; j <= 10; j++)
			Wall[i][j] = 1;
	for (int i = 1; i <= 4; i++)
		for (int j = 15; j <= 16; j++)
			Wall[i][j] = 1;
	for (int i = 5; i <= 6; i++)
		for (int j = 21; j <= 24; j++)
			Wall[i][j] = 1;
	for (int i = 5; i <= 6; i++)
		for (int j = 29; j <= 31; j++)
			Wall[i][j] = 1;
	for (int i = 11; i <= 12; i++)
		for (int j = 1; j <= 2; j++)
			Wall[i][j] = 1;
	for (int i = 11; i <= 12; i++)
		for (int j = 7; j <= 8; j++)
			Wall[i][j] = 1;
	for (int i = 11; i <= 12; i++)
		for (int j = 13; j <= 20; j++)
			Wall[i][j] = 1;
	for (int i = 13; i <= 16; i++)
		for (int j = 31; j <= 31; j++)
			Wall[i][j] = 1;
	for (int i = 13; i <= 16; i++)
		for (int j = 26; j <= 27; j++)
			Wall[i][j] = 1;

	for (int i = 17; i <= 21; i++)
		for (int j = 1; j <= 1; j++)
			Wall[i][j] = 1;
	for (int i = 17; i <= 21; i++)
		for (int j = 5; j <= 6; j++)
			Wall[i][j] = 1;
	for (int i = 17; i <= 22; i++)
		for (int j = 11; j <= 12; j++)
			Wall[i][j] = 1;
	for (int i = 17; i <= 18; i++)
		for (int j = 17; j <= 20; j++)
			Wall[i][j] = 1;
	for (int i = 21; i <= 24; i++)
		for (int j = 26; j <= 27; j++)
			Wall[i][j] = 1;
	for (int i = 21; i <= 24; i++)
		for (int j = 31; j <= 31; j++)
			Wall[i][j] = 1;

	for (int i = 23; i <= 27; i++)
		for (int j = 17; j <= 18; j++)
			Wall[i][j] = 1;

	for (int i = 26; i <= 27; i++)
		for (int j = 5; j <= 6; j++)
			Wall[i][j] = 1;
	for (int i = 27; i <= 31; i++)
		for (int j = 11; j <= 12; j++)
			Wall[i][j] = 1;
	for (int i = 29; i <= 31; i++)
		for (int j = 23; j <= 25; j++)
			Wall[i][j] = 1;

	for (int i = 1; i <= 31; i++)
		for (int j = 1; j <= 31; j++)
			if(Wall[i][j])
				putimage(i*20,j*20,&img);

	Play1_X = 28;Play1_Y = 29;
	Play2_X = 2;Play2_Y = 2;
}

void FrameWindow::RMap_4(){
	for (int i = 4; i <= 7; i++)
		for (int j = 1; j <= 3; j++)
			Wall[i][j] = 1;
	for (int i = 1; i <= 1; i++)
		for (int j = 9; j <= 20; j++)
			Wall[i][j] = 1;
	for (int i = 2; i <= 4; i++)
		for (int j = 9; j <= 10; j++)
			Wall[i][j] = 1;
	for (int i = 8; i <= 11; i++)
		for (int j = 4; j <= 5; j++)
			Wall[i][j] = 1;

	for (int i = 8; i <= 10; i++)
		for (int j = 9; j <= 16; j++)
			Wall[i][j] = 1;
	for (int i = 11; i <= 14; i++)
		for (int j = 15; j <= 16; j++)
			Wall[i][j] = 1;
	for (int i = 8; i <= 10; i++)
		for (int j = 21; j <= 25; j++)
			Wall[i][j] = 1;
	for (int i = 8; i <= 10; i++)
		for (int j = 30; j <= 31; j++)
			Wall[i][j] = 1;

	for (int i = 15; i <= 16; i++)
		for (int j = 17; j <= 20; j++)
			Wall[i][j] = 1;
	for (int i = 15; i <= 16; i++)
		for (int j = 25; j <= 31; j++)
			Wall[i][j] = 1;
	for (int i = 17; i <= 23; i++)
		for (int j = 25; j <= 25; j++)
			Wall[i][j] = 1;

	for (int i = 19; i <= 20; i++)
		for (int j = 1; j <= 10; j++)
			Wall[i][j] = 1;
	for (int i = 21; i <= 22; i++)
		for (int j = 1; j <= 2; j++)
			Wall[i][j] = 1;

	for (int i = 27; i <= 28; i++)
		for (int j = 4; j <= 5; j++)
			Wall[i][j] = 1;

	for (int i = 24; i <= 31; i++)
		for (int j = 9; j <= 10; j++)
			Wall[i][j] = 1;
	for (int i = 23; i <= 27; i++)
		for (int j = 14; j <= 15; j++)
			Wall[i][j] = 1;
	for (int i = 26; i <= 31; i++)
		for (int j = 20; j <= 21; j++)
			Wall[i][j] = 1;

	for (int i = 27; i <= 28; i++)
		for (int j = 29; j <= 31; j++)
			Wall[i][j] = 1;



	for (int i = 1; i <= 31; i++)
		for (int j = 1; j <= 31; j++)
			if(Wall[i][j])
				putimage(i*20,j*20,&img);

	Play1_X = 30;Play1_Y = 30;
	Play2_X = 2;Play2_Y = 2;
}
// ̽���Թ�·��, ����ʾ�ɹ�
void FrameWindow::Demo()
{
	Queue qu;
	Node node;
	int zx[4] = {1,0,-1,0},zy[4] = {0,1,0,-1};		// �ĸ�����
	int find = 0;									// find ֵΪ 1 ��ʾ����Ѱ��·��
	int x = 0, y = 0;								// ��ʱ���� x, y

	node.x = entranceX;								// ���λ��
	node.y = entranceY;
	outtextxy(810, 400, "������ʾ");				// �����Թ�״̬
	qu.Push(node);									// ��Ӳ���

	// ��������㷨Ѱ�����·��
	while(qu.GetFront() < qu.GetRear() && find == 0)
	{
		node.x = qu.visit(qu.GetFront()).x;			// �¶�ͷ������
		node.y = qu.visit(qu.GetFront()).y;

		for(int i = 0; i < 4; ++i)					// ���ĸ�����̽��
		{
			x = node.x;
			y = node.y;

			node.x += zx[i];
			node.y += zy[i];

			if(Wall[node.x][node.y] != 1)			// ����Աߵ�λ�ò���ǽ�ڲ���û�б�����
			{
				qu.Push(node);						// ����λ�ü������
				Wall[node.x][node.y] = 1;
			}

			if(node.x == exitX && node.y == exitY)	// �ҵ�����λ��
			{
				qu.Push(node);						// ������λ�ü������
				find = 1;							// find �� 1, ��ʾ�ҵ�����
				break;
			}

			node.x = x;
			node.y = y;
		}
		qu.Pop();							// ����ͷ����
	}

	if(find == 1)							// ����ҵ�����
	{
		qu.ResetPre();						// ���ýڵ�ǰ��
		qu.PrintRoute();					// ���·��
	}
	else
	{
		outtextxy(760, 440, "������·��");	// ����, ��Ϊ������·��
	}

}

void FrameWindow::SignPlay(int dx,int dy,int flag){
	Wall[dx-1][dy-1] = flag;
	Wall[dx][dy-1] = flag;
	Wall[dx+1][dy-1] =flag;
	Wall[dx-1][dy] = flag;
	Wall[dx][dy] = flag;
	Wall[dx+1][dy] = flag;
	Wall[dx-1][dy+1] = flag;
	Wall[dx][dy+1] = flag;
	Wall[dx+1][dy+1] = flag;
}

// �����¸���
void PrintGrid(int x, int y)
{
	float H = 110, S = 1, L = 0.4522f;	// ���� H S L�ĳ�ֵ
	S -= (float)y * 0.00125f;			// ���� S ����������ֵ
	L += (float)y * 0.000125f;			// ���� L �����������
	for(int i = y + 1; i < y + 20; ++i)	// ѭ����������
	{
		L += 0.000125f;
		S -= 0.00125f;
		//setcolor(HSLtoRGB(H, S, L));
		setcolor(BLACK);
		line(x + 1, i, x + 19, i);
	}
}

// Ĭ�Ϲ��캯��
Queue::Queue()
{
	data = new Node[QueueMaxLength];	// ������д洢�ռ�
	front = 0;							// ��ͷΪ 0
	rear = 0;							// ��βΪ 0
}

// ��������
Queue::~Queue()
{
	delete (data);	// �ͷŶ��д洢�ռ�
}

// ���Ӳ���
void Queue::Pop()
{
	++front;		// ���Ӳ���
}

// ��Ӳ���
void Queue::Push(Node node)
{
	data[rear].x = node.x;
	data[rear].y = node.y;

	if(rear == 0)						// ����ǵ�һ��Ԫ�����, ����ǰ��ָ���
	{
		data[rear].pre = NULL;
	}
	else
	{
		data[rear].pre = &data[front];	// ����, ��ǰ��ָ���ͷ
	}
	++rear;								// ��β�� 1
}

// ��ȡ��ͷ
inline int Queue::GetFront()
{
	return front;
}

// ��ȡ��β
inline int Queue::GetRear()
{
	return rear;
}

// ���ʶ���
Node Queue::visit(int i)
{
	return data[i];
}

// ���ýڵ�ǰ��
void Queue::ResetPre()
{
	Node *s = &data[rear - 1];	// ָ�����
	Node *p = s->pre;			// ���ڵ�ǰ��
	Node *r ;

	// ��ѭ��
	while(1)
	{
		r = p->pre;				// r ָ�� p ��ǰ��
		p->pre = s;				// p ��ǰ��ָ�� s
		s = p;					// s ָ�� p
		p = r;					// p ָ�� r
		if(r == NULL)			// ��� r Ϊ��, �˳�ѭ��
		{
			break;
		}
	}
}

// ���·��
void Queue::PrintRoute()
{
	Node * s = data[0].pre;								// ���λ��

	// ��ѭ��
	while(s != &data[rear - 1])
	{
		setfillstyle(LIGHTRED);							// ���������ɫ

		// ����Բ
		fillcircle(s->x * 20 + 10, s->y * 20 + 10, 5);
		Sleep(100);
		s = s->pre;										// s ָ����ǰ��
	}
	outtextxy(810, 400, "��ʾ���");					// �ı��Թ�״̬
}

