

#ifndef labyrith_h
#define labyrith_h

#include <iostream>
#include <graphics.h>
#include<windows.h>
#include <conio.h>

#pragma comment(lib, "WINMM.LIB") 

using namespace std;

int const QueueMaxLength = 1000000;	// ��ջ��󳤶�

struct Node							// ����һ���ڵ�
{
	int x;							// ������ε� x ����
	int y;							// ������ε� y ����
	Node *pre;						// ��������ڵ�
};

class FrameWindow					// ����һ�����ڿ��
{
private:
	IMAGE img,bksimg;				// ǽ��ͼƬ
	int direct;						// �������ⰴ��ʱ���������Թ�
	int control;					// ��ǳ�����ƿ���Ȩ
	MOUSEMSG msg;					// �����Ϣ
public:
	void SignPlay(int dx,int dy,int flag); //���play1play2λ��
	FrameWindow();					// Ĭ�Ϲ��캯��
	void NewBackground();			// �����±���
	void DrawSome();				// ����Щʲô
	void Run();						// ���п���
	void StartDrawLabyrith();		// ��ʼ�����Թ�
	void SetLabyrith();				// �����Թ�
	void Demo();					// Ѱ��·��, ����ʾ
	void RandomMap();
	void RMap_1();void RMap_2();void RMap_3();void RMap_4();

};


class Queue							// ���������
{
private:
	Node *data;						// ������
	int front;						// ��ͷ
	int rear;						// ��β
public:
	Queue();						// ����Ĭ�Ϲ��캯��
	~Queue();						// ��������
	void Pop();						// ���Ӳ���
	void Push(Node node);			// ��Ӳ���
	void ResetPre();				// ���ýڵ�ǰ��
	Node visit(int i);				// ���ʽڵ�
	inline int GetFront();			// ��ȡ��ͷ
	inline int GetRear();			// ��ȡ��β
	void PrintRoute();				// ��ӡ·��
};

void PrintGrid(int x, int y);		// ���û�ȡ������ĳ����Ϊǽ��֮��, ���»��Ƹ���

extern int Wall[34][34];;			// ǽ�ڱ������
extern int entranceX;				// ���
extern int entranceY;
extern int exitX;					// ����
extern int exitY;
extern int Play1_X;		// ���1
extern int Play1_Y;
extern int Play2_X;			//���2
extern int Play2_Y;
#endif
