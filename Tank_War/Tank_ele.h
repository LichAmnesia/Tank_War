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
	int direction; // 8个方向 1↑，2↗，3→，4↘，5↓，6↙，7←，8↖
	int Prekilltime; //上次杀人时间
	int Prekillnum; //上次杀人数
	int Isrevive;
private:
	
	
	int isbullet;
	
	//int flag;
	void Sign(int x,int y,int value); //标记tank所在的方框
	void SignBult(); //标记子弹；
	
};





#endif;