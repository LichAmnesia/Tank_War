#ifndef TANKELE_H_GUARD
#define TANKELE_H_GUARD
#include <graphics.h>

using namespace std;
struct Bullet{
	int x,y;
	int direction;
	bool IsLau;
	int len ;
};


class Tank
{
public:
	Tank();
	~Tank();
	IMAGE img[9];
	void LoadImg(int flag);
	void getdir(int dir);
	int x,y;
	int blood;
	int PreTime;
	int Killtime;
	int bulletnum;
	Bullet bullet[5];
	int direction; // 8������ 1����2�J��3����4�K��5����6�L��7����8�I
	int Prekilltime; //�ϴ�ɱ��ʱ��
	int Prekillnum; //�ϴ�ɱ����
	int Isrevive;
private:
	
	
	int isbullet;
	
	//int flag;
	void Sign(int x,int y,int value); //���tank���ڵķ���
	void SignBult(); //����ӵ���
	
};





#endif;