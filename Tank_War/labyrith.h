

#ifndef labyrith_h
#define labyrith_h

#include <iostream>
#include <graphics.h>
#include<windows.h>
#include <conio.h>

#pragma comment(lib, "WINMM.LIB") 

using namespace std;

int const QueueMaxLength = 1000000;	// 堆栈最大长度

struct Node							// 定义一个节点
{
	int x;							// 保存矩形的 x 坐标
	int y;							// 保存矩形的 y 坐标
	Node *pre;						// 保存其根节点
};

class FrameWindow					// 定义一个窗口框架
{
private:
	IMAGE img,bksimg;				// 墙壁图片
	int direct;						// 接受特殊按键时结束绘制迷宫
	int control;					// 标记程序控制控制权
	MOUSEMSG msg;					// 鼠标消息
public:
	void SignPlay(int dx,int dy,int flag); //标记play1play2位置
	FrameWindow();					// 默认构造函数
	void NewBackground();			// 绘制新背景
	void DrawSome();				// 绘制些什么
	void Run();						// 运行控制
	void StartDrawLabyrith();		// 开始绘制迷宫
	void SetLabyrith();				// 设置迷宫
	void Demo();					// 寻找路径, 并演示
	void RandomMap();
	void RMap_1();void RMap_2();void RMap_3();void RMap_4();

};


class Queue							// 定义队列类
{
private:
	Node *data;						// 数据域
	int front;						// 队头
	int rear;						// 队尾
public:
	Queue();						// 队列默认构造函数
	~Queue();						// 析构函数
	void Pop();						// 出队操作
	void Push(Node node);			// 入队操作
	void ResetPre();				// 重置节点前驱
	Node visit(int i);				// 访问节点
	inline int GetFront();			// 获取队头
	inline int GetRear();			// 获取队尾
	void PrintRoute();				// 打印路径
};

void PrintGrid(int x, int y);		// 在用户取消设置某格子为墙壁之后, 从新绘制格子

extern int Wall[34][34];;			// 墙壁标记数组
extern int entranceX;				// 入口
extern int entranceY;
extern int exitX;					// 出口
extern int exitY;
extern int Play1_X;		// 玩家1
extern int Play1_Y;
extern int Play2_X;			//玩家2
extern int Play2_Y;
#endif
