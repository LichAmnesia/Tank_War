#include "labyrith.h"
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include "TankGame.h"
#include "Tank_ele.h"
int Wall[34][34];	// 墙壁
int entranceX;		// 入口
int entranceY;
int exitX;			// 出口
int exitY;
int Play1_X;		// 玩家1
int Play1_Y;
int Play2_X;			//玩家2
int Play2_Y;

// 默认构造函数
FrameWindow::FrameWindow()
{
	initgraph(960, 660);					// 建立图形界面
	setbkcolor(LIGHTGREEN);					// 设置背景颜色为亮绿色
	direct = 0;								// 设置 direct 的初值为 0
	control = 0;							// 默认控制权为 0 
	loadimage(&img, "res\\bk.jpg", 20, 20);	// 加载图片
	loadimage(&bksimg, "res\\tank_bk.jpg", 20, 20);

	HCURSOR hcur = LoadCursor(NULL, IDC_CROSS);		// 加载系统预置的鼠标样式
	HWND hwnd = GetHWnd();							// 获取绘图窗口句柄
	SetClassLong(hwnd, GCL_HCURSOR, (long)hcur);	// 设置窗口类的鼠标样式
}

void FrameWindow::Run()
{
	cleardevice();		// 清屏
	NewBackground();	// 绘制新背景图
	DrawSome();			// 绘制些神马
	control = 0;		// 首先将函数对程序程序的控制权置 0
	direct = 0;			// 设置 direct 的初值为 0
	TankGame newGame;
	// 主循环
	while(1)
	{
		if(kbhit())													// 检测按键
		{
 			direct = getch();										// 从按键获取输入
			mciSendString("play  res\\key.wav", NULL, 0, NULL);		// 按键声
			if( direct == 115 &&  control == 0)						// s 的键值为 115
			{
				StartDrawLabyrith();								// 开始绘制迷宫
			}


			if(direct == 101 && control == 2)						// e 的键值为 101
			{
				SetLabyrith();										// 设置迷宫的入口和出口
			}

			if(direct == 100 && control == 3)						// d 的键值为 100
			{
				control = -1;										// 将 control 设置为 -1 的目的是
																	// 让程序从 Demo() 回到 Run() 时只响应刷新操作
				Demo();												// 寻找路径并演示
				Sleep(2000);
				getch();
				break;
			}
			if (direct == 110 ){									   //
																	//随机出生点位啊 ！ 然后开始
				FrameWindow::RandomMap();							//随机地图
				outtextxy(810, 400, "游戏开始  ");
				newGame.start();
				break;
			}
			if (direct == 104 &&control == 5){ 						 //开始游戏
				outtextxy(810, 400, "游戏开始  ");
				newGame.start();
				break;
			} 
			if(direct == 63 && (control == 0 || control == -1))		// 按 F5 刷新
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

// 绘制新背景
void FrameWindow::NewBackground()
{
	float H, S, L;					// 定义 HSL 颜色模型的 3 个变量
	H = 110;						// 色相
	S = 1;							// 饱和度
	L = 0.4522f;					// 亮度
	for(int y = 0; y != 660; y++)	// 绘制迷宫背景颜色	 从上往下绘制颜色
	{
		setcolor(BLACK);
		line(0,y,660,y);
		//L += 0.000125f;
		//S -= 0.00125f;
		//setcolor(HSLtoRGB(H, S, L));
		//line(0, y, 660, y);
	}

	H = 50;							// 色相
	S = -3.2555f;					// 饱和度
	L = 0.525617f;					// 亮度
	for(int y = 0; y != 660; ++y)		// 绘制提示信息部分背景
	{
		L += 0.000000085f;
		S -= 0.0015f;
		setcolor(HSLtoRGB(H, S, L));
		line(660, y, 960, y);
	}
}

// 绘制些神马
void FrameWindow::DrawSome()
{
	setcolor(LIGHTRED);
	int i;
	for(i = 0; i < 34; ++i)								
	{
		// 外围墙壁在 Wall 数组中的位置置 1 
		Wall[0][i] = 1;
		Wall[i][0] = 1;
		Wall[32][i] = 1;
		Wall[i][32] = 1;

		// 绘制外围墙壁
		putimage(0 *20 , i * 20 , &img);
		putimage(i * 20 , 0 * 20, &img);
		putimage(640, i * 20 , &img);
		putimage(i * 20 , 640, &img);
		putimage(940, i * 20 , &img);

		//setcolor(WHITE);
		//line(i * 20, 0, i * 20, 660);		// 绘制格子线
		//line(0, i * 20, 660, i * 20);		// 绘制格子线
	}

	for(i = 0; i < 15; ++i)					// 绘制提示区域外围框
	{
		putimage(i * 20 + 661, 1, &img);
		putimage(i * 20 + 661, 641, &img);
	}

	for(i = 1; i <= 31; ++i)				// 其它的 Wall 数组的值暂时置 0
	{
		for(int j = 1; j <= 31; ++j)
		{
			Wall[i][j] = 0;
		}
	}

	// 绘制提示信息
	RECT r = {710, 40, 900, 300};
	setbkmode(TRANSPARENT);					// 设置输出文字背景模式为透明
	setcolor(BLUE);							// 设置输出文字颜色
	setfont(15, 0, "宋体");
	
	// 输出提示信息
	drawtext("游戏操作介绍：\n\n N: 直接开始并随机地图.\n\n \
		S: 绘制图形之后再玩,鼠标左键绘制墙壁，鼠标右键擦除墙壁.\n\n \
		按键E:设置玩家出生点,第一个是玩家1第二个是玩家2,右键取消设置.\n\n \
		设置完成之后按键H:开始游戏\n\n	   \
		",&r,DT_WORDBREAK);
	/*drawtext("游戏操作介绍：\n\n按键 S：绘制迷宫。\n鼠标左键绘制墙壁，\
		鼠标右键擦除墙壁。\n\n按键 E：设置迷宫的入口和出口。\n使用鼠标\
		左键来设置入口和出口，右键取消设置。\n\n按键 D：进行迷宫的探索\
		，寻找从入口到出口的最短路径，由小球来演示从入口到出口的路径。",
		&r, DT_WORDBREAK);*/

	setbkmode(OPAQUE);						// 恢复默认填充颜色

	// 输出提示信息
	outtextxy(730, 400, "状态: ");
	outtextxy(810, 400, "等待绘制");
	outtextxy(750, 500, "按 F5 重新开始");
}

// 开始绘制迷宫
void FrameWindow::StartDrawLabyrith()
{
	int x = 0, y = 0;						// 标记鼠标的坐标使用
	outtextxy(810, 400, "正在绘制");		// 修改迷宫状态
	FlushMouseMsgBuffer();					// 清空鼠标消息缓冲区
 
	// 主循环
	while(1)
	{
		if(kbhit())
		{
			direct = getch();									// 获取按键信息
			mciSendString("play  res\\key.wav", NULL, 0, NULL);	// 按键声
			if(direct == 101)									// e 的键值为 101
			{
				control = 2;									// 控制权值为 2 
				break;
			}
			else if(direct == 63)								// F5 刷新
			{
 				break;
			}else if(direct == 110){    //随机地图然后开始游戏
				control = 4;break;
			}
		}
		else if(MouseHit())
		{

			msg = GetMouseMsg();										// 获取鼠标消息
			x = msg.x / 20;												// 获取鼠标所在格子在 Wall 中的位置
			y = msg.y / 20;
			if(msg.x > 20 && msg.x < 630 && msg.y > 20 && msg.y < 630)	// 只能在这个区域里面响应鼠标消息
			{
				switch(msg.uMsg)										// 消息的种类
				{
					case WM_LBUTTONDOWN:								// 左键按下
						{
							Wall[x][y] = 1;								// y 对应行, x 对应列, 将对应的位置置 1
							putimage(x * 20 , y * 20 , &img);		// 放置图片
						}
						break;
					case WM_RBUTTONDOWN:								// 右键按下
						{
							Wall[x][y] = 0;								// y 对应行, x 对应列, 将对应的位置置 0
							putimage(x * 20 , y * 20, &bksimg);
							//PrintGrid(x * 20, y * 20);					// 重新绘制这个格子
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

// 设置play1和play2
void FrameWindow::SetLabyrith()
{
	int x = 0, y = 0;	// 临时参数
	Play1_X = -1;		// play1
	Play1_Y = -1;
	Play2_X = -1;		// play2 
	Play2_Y = -1;	

	entranceX = -1;		// 入口
	entranceY = -1;
	exitX = -1;			// 出口
	exitY = -1;	

	outtextxy(810, 400, "设置Play1");	// 提示信息
	
	// 主循环
	while(1)
	{
		if(kbhit())						// 键盘消息
		{
			direct = getch();										// 获取消息
			mciSendString("play  res\\key.wav", NULL, 0, NULL);		// 按键声
			if(direct == 100 && entranceX != -1 && exitX != -1)		// 如果出入口都设置好, 按 d 键退出设置模式
			{
				control = 3;										// 控制权变为 3, 回到 Run 中由其判断由谁控制程序;
				break;
			}
			else if(direct == 63)									// F5 刷新
			{
				control = 0;
				break;
			}else if(direct == 104 && entranceX != -1 && exitX != -1){								// 	开始游戏
				control = 5;
				break;
			}

		}
		else if(MouseHit())
		{
			msg = GetMouseMsg();												// 获取鼠标消息
			x = msg.x / 20;														// 获取鼠标所在格子在 Wall 中的位置
			y = msg.y / 20;	

			if(entranceX != -1 && exitX != -1)									// 完成设置
			{
				outtextxy(810, 400, "设置完成  ");
			}

			if(msg.x > 20 && msg.x < 630 && msg.y > 20 && msg.y < 630)			// 只能在这个区域里面响应鼠标消息
			{
				if(Wall[x][y] == 0 && msg.uMsg == WM_LBUTTONDOWN && !Wall[x-1][y-1] && !Wall[x][y-1] && !Wall[x+1][y-1] && !Wall[x-1][y] &&  !Wall[x+1][y] && !Wall[x-1][y+1] && !Wall[x][y+1] && !Wall[x+1][y+1])				// 如果这个位置不是墙壁, 并且按下左键
				{
					if(entranceX == -1 && (exitX != x || exitY != y))			// 确保此处没被设置
					{
						entranceX = x;											// play1位置
						entranceY = y;
						Play1_X = x;
						Play1_Y = y;
						
						
						Wall[x][y] = 1;
						SignPlay(x,y,2);
						
						outtextxy(x * 20 + 6, y * 20 + 5,_T("O"));			// 将此处标记为 In 

						if(exitX == -1)											// 若此时还未设置出口
						{
							outtextxy(810, 400, "设置玩家2");					// 改变迷宫状态
						}
					}
					else if(exitX == -1 && (entranceX != x || entranceY != y))	// 此处未设置出口且不是入口位置
					{
						exitX = x;												// 出口位置
						exitY = y;
						Play2_X = x;
						Play2_Y = y;
						
						
						Wall[x][y] = 1;
						SignPlay(x,y,3);
						
						outtextxy(x * 20 + 6, y * 20 + 5,_T("T"));			// 将此处标记为 Out

						if(entranceX == -1)										// 若此时还未设置入口
						{
							outtextxy(810, 400, "设置玩家1");					// 改变迷宫状态
						}
					}
				}
				else if(Wall[x][y] != 0 &&msg.uMsg == WM_RBUTTONDOWN)			// 如果这个位置不是墙壁, 并且按下右键
				{
					if(x == entranceX && y == entranceY)						// 取消设置入口
					{
						entranceX = -1;
						entranceY = -1;
						Wall[x][y] = 0;
						SignPlay(x,y,0);
						outtextxy(810, 400, "设置玩家1");						// 改变迷宫状态
						putimage(x * 20 , y * 20, &bksimg);
						//PrintGrid(x * 20, y * 20);								// 从新绘制格子
						setcolor(BLUE);											// 恢复原线条颜色
					}
					else if(x == exitX && y == exitY)							// 取消设置出口
					{
						exitX = -1;
						exitY = -1;
						Wall[x][y] = 0;
						SignPlay(x,y,0);
						outtextxy(810, 400, "设置玩家2");						// 改变迷宫状态
						putimage(x * 20 , y * 20, &bksimg);
						//PrintGrid(x * 20, y * 20);								// 重新绘制格子
						setcolor(BLUE);											// 恢复原线条颜色
					}
				} 
			} 
		} 
	} 
} 
void FrameWindow::RandomMap(){	  //随机地图
	for(int i = 1; i <= 31; ++i)				// 其它的 Wall 数组的值暂时置 0
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
// 探索迷宫路径, 并演示成果
void FrameWindow::Demo()
{
	Queue qu;
	Node node;
	int zx[4] = {1,0,-1,0},zy[4] = {0,1,0,-1};		// 四个方向
	int find = 0;									// find 值为 1 表示结束寻找路径
	int x = 0, y = 0;								// 临时参数 x, y

	node.x = entranceX;								// 入口位置
	node.y = entranceY;
	outtextxy(810, 400, "正在演示");				// 更改迷宫状态
	qu.Push(node);									// 入队操作

	// 广度搜索算法寻找最短路径
	while(qu.GetFront() < qu.GetRear() && find == 0)
	{
		node.x = qu.visit(qu.GetFront()).x;			// 新队头的坐标
		node.y = qu.visit(qu.GetFront()).y;

		for(int i = 0; i < 4; ++i)					// 朝四个方向探索
		{
			x = node.x;
			y = node.y;

			node.x += zx[i];
			node.y += zy[i];

			if(Wall[node.x][node.y] != 1)			// 如果旁边的位置不是墙壁并且没有被访问
			{
				qu.Push(node);						// 将此位置加入队列
				Wall[node.x][node.y] = 1;
			}

			if(node.x == exitX && node.y == exitY)	// 找到出口位置
			{
				qu.Push(node);						// 将出口位置加入队列
				find = 1;							// find 置 1, 表示找到出口
				break;
			}

			node.x = x;
			node.y = y;
		}
		qu.Pop();							// 将队头出队
	}

	if(find == 1)							// 如果找到出口
	{
		qu.ResetPre();						// 重置节点前驱
		qu.PrintRoute();					// 输出路径
	}
	else
	{
		outtextxy(760, 440, "不存在路径");	// 否则, 视为不存在路径
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

// 绘制新格子
void PrintGrid(int x, int y)
{
	float H = 110, S = 1, L = 0.4522f;	// 设置 H S L的初值
	S -= (float)y * 0.00125f;			// 设置 S 在这线条的值
	L += (float)y * 0.000125f;			// 设置 L 在这个线条上
	for(int i = y + 1; i < y + 20; ++i)	// 循环绘制线条
	{
		L += 0.000125f;
		S -= 0.00125f;
		//setcolor(HSLtoRGB(H, S, L));
		setcolor(BLACK);
		line(x + 1, i, x + 19, i);
	}
}

// 默认构造函数
Queue::Queue()
{
	data = new Node[QueueMaxLength];	// 申请队列存储空间
	front = 0;							// 队头为 0
	rear = 0;							// 队尾为 0
}

// 析构函数
Queue::~Queue()
{
	delete (data);	// 释放队列存储空间
}

// 出队操作
void Queue::Pop()
{
	++front;		// 出队操作
}

// 入队操作
void Queue::Push(Node node)
{
	data[rear].x = node.x;
	data[rear].y = node.y;

	if(rear == 0)						// 如果是第一个元素入队, 将其前驱指向空
	{
		data[rear].pre = NULL;
	}
	else
	{
		data[rear].pre = &data[front];	// 不是, 将前驱指向队头
	}
	++rear;								// 队尾加 1
}

// 获取队头
inline int Queue::GetFront()
{
	return front;
}

// 获取队尾
inline int Queue::GetRear()
{
	return rear;
}

// 访问队列
Node Queue::visit(int i)
{
	return data[i];
}

// 重置节点前驱
void Queue::ResetPre()
{
	Node *s = &data[rear - 1];	// 指向出口
	Node *p = s->pre;			// 出口的前驱
	Node *r ;

	// 主循环
	while(1)
	{
		r = p->pre;				// r 指向 p 的前驱
		p->pre = s;				// p 的前驱指向 s
		s = p;					// s 指向 p
		p = r;					// p 指向 r
		if(r == NULL)			// 如果 r 为空, 退出循环
		{
			break;
		}
	}
}

// 输出路径
void Queue::PrintRoute()
{
	Node * s = data[0].pre;								// 入口位置

	// 主循环
	while(s != &data[rear - 1])
	{
		setfillstyle(LIGHTRED);							// 设置填充颜色

		// 绘制圆
		fillcircle(s->x * 20 + 10, s->y * 20 + 10, 5);
		Sleep(100);
		s = s->pre;										// s 指向其前驱
	}
	outtextxy(810, 400, "演示完成");					// 改变迷宫状态
}

