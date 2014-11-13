#ifndef TANKGAME_H_GUARD
#define TANKGAME_H_GUARD

#include <conio.h>
#include <iostream>
#include <graphics.h>
#include "Tank_ele.h"
#include "Time.h"
#define UP_1                 1 //¡ü
#define DOWN_1               2 //¡ý
#define LEFT_1               4 //¡û
#define RIGHT_1              8 //¡ú
#define ATTACK_1             16


#define UP_2                 32   //w
#define DOWN_2               64	   // s
#define LEFT_2              128		 //a
#define RIGHT_2             256		//d
#define ATTACK_2            512

class TankGame
{
public:
	TankGame();
	~TankGame();
	void start();
	bool FirstDeath; 
	MyTimer Time;
private:
	IMAGE bkimg,bksimg;	
	IMAGE DeadBomb[12];
	Tank play[3];
	void PutTank(int who,int x,int y,int dir);
	void running();
	void Tank_move(int who,int dir,int flag);
	void Tank_turn(int who,int turn);
	void SignTank(int dx,int dy,int flag);
	void KillTank(int who,int i,int fromwho);
	void MoveBullet(int who,int i);
	int FindNewDir(int x,int y ,int direction);
	void EndOfGame(int who,int fromwho);
	void Revive(int who);
	int  Getcommand();
	void DispatchCommand(int _cmd);
};



#endif