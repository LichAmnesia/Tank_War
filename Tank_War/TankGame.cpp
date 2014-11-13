#include "labyrith.h"
#include "TankGame.h"
#include "Tank_ele.h"
#include "key_def.h"
#include <time.h>
#include <graphics.h>
using namespace std;
#define TIME_UNIT 80
#define BULL_LEN  30
/*int Wall[34][34];	// 墙壁
int Play1_X;		// 玩家1
int Play1_Y;
int Play2_X;			//玩家2
int Play2_Y;
*/
int mycontrol;
int movdir[9][3] = {{0,0},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}};
clock_t killtime = 0;
TankGame::TankGame()
{
	srand(time(NULL));
	loadimage(&bkimg, "res\\tank_bk.jpg", 60, 60);
	loadimage(&bksimg, "res\\tank_bk.jpg", 20, 20);
	loadimage(&DeadBomb[0], "res\\bongbongbong\\Image 4453.jpg", 60, 60);
	loadimage(&DeadBomb[1], "res\\bongbongbong\\Image 4455.jpg", 60, 60);
	loadimage(&DeadBomb[2], "res\\bongbongbong\\Image 4457.jpg", 60, 60);
	loadimage(&DeadBomb[3], "res\\bongbongbong\\Image 4459.jpg", 60, 60);
	loadimage(&DeadBomb[4], "res\\bongbongbong\\Image 4461.jpg", 60, 60);
	loadimage(&DeadBomb[5], "res\\bongbongbong\\Image 4463.jpg", 60, 60);
	loadimage(&DeadBomb[6], "res\\bongbongbong\\Image 4465.jpg", 60, 60);
	loadimage(&DeadBomb[7], "res\\bongbongbong\\Image 4467.jpg", 60, 60);
	loadimage(&DeadBomb[8], "res\\bongbongbong\\Image 4469.jpg", 60, 60);
	loadimage(&DeadBomb[9], "res\\bongbongbong\\Image 4471.jpg", 60, 60);
	loadimage(&DeadBomb[10], "res\\bongbongbong\\Image 4473.jpg", 60, 60);
	loadimage(&DeadBomb[11], "res\\tank_bk.jpg", 60, 60);
	FirstDeath = 1;
	Time.Reset();
}

TankGame::~TankGame()
{
}

void TankGame::start()
{
	play[1].x = Play1_X;play[1].y = Play1_Y;
	play[2].x = Play2_X;play[2].y = Play2_Y;
	play[1].LoadImg(1);
	play[2].LoadImg(0);

	/*测试TANK图片用
	for(int i = 1; i < 9; i++){
		PutTank(1,play[1].x,play[1].y,i);
		getch();
	}*/ 

	int birdir_1 = rand()%8 + 1;
	int birdir_2 = rand()%8 + 1;

	PutTank(1,play[1].x,play[1].y,birdir_1);
	play[1].getdir(birdir_1);
	SignTank(play[1].x,play[1].y,2);
	
	//play[2]
	PutTank(2,play[2].x,play[2].y,birdir_2);
	play[2].getdir(birdir_2);
	SignTank(play[2].x,play[2].y,3);
	
	/*测试wall的位置 
	IMAGE imge;
	loadimage(&imge, "res\\bk.jpg", 20, 20);
	for (int i = 0; i <= 33; i++)
		for (int j = 0; j <= 33; j++){
			if(Wall[i][j] == 1) 
				putimage(20*i, j * 20 , &imge);
		}
	*/
	while (play[1].blood > 0 && play[2].blood > 0){
		running();
	}


}

// 8个方向 1↑，2↗，3→，4↘，5↓，6↙，7←，8↖ 1357特殊判定
void TankGame::PutTank(int who,int x,int y,int dir){
	if(dir == 1 || dir == 5){
		
		putimage( play[who].x * 20 - 5 , play[who].y * 20 - 20, &play[who].img[dir]);
	}else if(dir == 3 || dir == 7) {
		putimage( play[who].x * 20 - 20 , play[who].y * 20 - 5, &play[who].img[dir]);
	}else {
		putimage( play[who].x * 20 - 20 , play[who].y * 20 - 20, &play[who].img[dir]);
	}
}


void TankGame::running(){
	int control = 0;
	int _cmd;
	play[1].PreTime = clock();
	play[2].PreTime = clock();
	while(play[1].blood > 0 && play[2].blood > 0)
	{
		if (play[1].blood <= 0 || play[2].blood <= 0) continue;
		for (int Who = 1; Who <= 2; Who ++)
			for (int i = 0; i < 5; i++)
				if (play[Who].bullet[i].IsLau){
					MoveBullet(Who,i);
			}
		int Death_1 = clock() - play[1].Killtime;
		int Death_2 = clock() - play[2].Killtime;
		if (Death_1 <= 960){
			SignTank(play[1].x,play[1].y,0);
			putimage(play[1].x * 20 - 20, play[1].y * 20 -20 , &DeadBomb[Death_1/80]); 
			if (Death_1 > 874) {
				play[1].Isrevive = 0;
				SignTank(play[1].x,play[1].y,0);
				play[1].Killtime = 0;
				Revive(1);
			}
		}
		if (Death_2 <= 960){
			SignTank(play[2].x,play[2].y,0);
			putimage(play[2].x * 20 - 20, play[2].y * 20 -20 , &DeadBomb[Death_2/80]);
			/*char s[100];
			sprintf(s,"%d",Death_2);
			outtextxy(760, 200, s);*/
			if (Death_2 > 874){ 
				play[2].Isrevive = 0;
				SignTank(play[2].x,play[2].y,0);
				play[2].Killtime = 0;
				Revive(2);
			}
		}
		_cmd = Getcommand();
		DispatchCommand(_cmd);
		Time.Sleep(TIME_UNIT);
		/*for (int Who = 1; Who <= 2; Who ++)
			for (int i = 0; i < 5; i++)
				if (play[Who].bullet[i].IsLau){
					MoveBullet(Who,i);
			}
		if (play[1].blood <= 0 || play[2].blood <= 0) continue;
		if (killtime !=0 && clock() - killtime > 1000){
			SignTank(play[1].x,play[1].y,2);
			SignTank(play[2].x,play[2].y,3);
		}
		if(kbhit())													// 检测按键
		{
			//clock_t now = clock();
 												
			//while (clock() - now < TIME_UNIT){
				control = getch();	// 从按键获取输入

				if (control == UP_1){
					Tank_move(1,play[1].direction,1);		
				}else if (control == UP_2){
					Tank_move(2,play[2].direction,1);	
				}else if (control == DOWN_1){
					Tank_move(1,play[1].direction,-1);
				}else if (control == DOWN_2){
					Tank_move(2,play[2].direction,-1);
				}else if (control == LEFT_1){
					Tank_turn(1,-1);
				}else if (control == LEFT_2){
					Tank_turn(2,-1);
				}else if (control == RIGHT_1){
					Tank_turn(1,1);
				}else if (control == RIGHT_2){
					Tank_turn(2,1);
				}else if (control == ATTACK_2 && play[2].bulletnum < 4){
					int x = play[2].x + 2 * movdir[play[2].direction][0];
					int y = play[2].y + 2 * movdir[play[2].direction][1];
					int i;
					for (i = 0;i < 5; i ++){
						if (!play[2].bullet[i].IsLau){
							play[2].bullet[i].IsLau = 1;
							break;
						}
					}
					if (i<5) {
						play[2].bullet[i].len = 0;
						play[2].bullet[i].x = x;play[2].bullet[i].y = y;
						play[2].bullet[i].direction = play[2].direction;
						play[2].bulletnum ++;
						if (Wall[play[2].bullet[i].x][play[2].bullet[i].y] == 1){
							KillTank(2,i,2);
						} else if (Wall[play[2].bullet[i].x][play[2].bullet[i].y] == 2){
							KillTank(1,i,2);
						} else if (Wall[play[2].bullet[i].x][play[2].bullet[i].y] == 3){
							
						} else {
							fillcircle(x * 20 + 10, y * 20 + 10, 5);
						}
					}
					//fillcircle(x * 20 + 10, y * 20 + 10, 5);
					//putimage(x * 20 , y * 20 , &bksimg);
					//防止直接打到墙上就直接死
					//play[2].MakeBullet();
					//play[2].
				}else if (control == ATTACK_1 && play[1].bulletnum < 4){
					int x = play[1].x + 2 * movdir[play[1].direction][0];
					int y = play[1].y + 2 * movdir[play[1].direction][1];
					int i;
					for (i = 0;i < 5; i ++){
						if (!play[1].bullet[i].IsLau){
							play[1].bullet[i].IsLau = 1;
							break;
						}
					}
					if (i<5) {
						play[1].bullet[i].len = 0;
						play[1].bullet[i].x = x;play[1].bullet[i].y = y;
						play[1].bullet[i].direction = play[1].direction;
						play[1].bulletnum ++;
						if (Wall[play[1].bullet[i].x][play[1].bullet[i].y] == 1){
							KillTank(1,i,1);
						} else if (Wall[play[1].bullet[i].x][play[1].bullet[i].y] == 2){
							KillTank(2,i,1);
						} else if (Wall[play[1].bullet[i].x][play[1].bullet[i].y] == 3){
							
						} else {
							fillcircle(x * 20 + 10, y * 20 + 10, 5);
						}
					}
					//putimage(x * 20 , y * 20 , &bksimg);
				}
			//}
		}
		else
		{
			Sleep(60);
		}*/
	}	

}


int TankGame::Getcommand(){
	int c = 0;

	if ((GetAsyncKeyState(VK_UP) & 0x8000) && (play[1].Isrevive == 0))		c |= UP_1;
	if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && (play[1].Isrevive == 0))	c |= DOWN_1;
	if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && (play[1].Isrevive == 0))	c |= LEFT_1;
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && (play[1].Isrevive == 0))	c |= RIGHT_1;
	if ((GetAsyncKeyState(VK_RETURN) & 0x8000) && (play[1].Isrevive == 0))	c |= ATTACK_1;

	if ((GetAsyncKeyState(VK_W) & 0x8000) && (play[2].Isrevive == 0))	c |= UP_2;
	if ((GetAsyncKeyState(VK_S) & 0x8000) && (play[2].Isrevive == 0))	c |= DOWN_2;
	if ((GetAsyncKeyState(VK_A) & 0x8000) && (play[2].Isrevive == 0))	c |= LEFT_2;
	if ((GetAsyncKeyState(VK_D) & 0x8000) && (play[2].Isrevive == 0))	c |= RIGHT_2;
	if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && (play[2].Isrevive == 0))	c |= ATTACK_2;
	return c;
}

void TankGame::DispatchCommand(int _cmd){
	if (_cmd & UP_1) Tank_move(1,play[1].direction,1);
	if (_cmd & UP_2) Tank_move(2,play[2].direction,1);	
	if (_cmd & DOWN_1) Tank_move(1,play[1].direction,-1);
	if (_cmd & DOWN_2) Tank_move(2,play[2].direction,-1);
	if (_cmd & LEFT_1) Tank_turn(1,-1);
	if (_cmd & LEFT_2) Tank_turn(2,-1);
	if (_cmd & RIGHT_1) Tank_turn(1,1);
	if (_cmd & RIGHT_2) Tank_turn(2,1);
	if ((_cmd & ATTACK_2) && play[2].bulletnum < 4 && clock() - play[2].PreTime > 100){
		int x = play[2].x + 2 * movdir[play[2].direction][0];
		int y = play[2].y + 2 * movdir[play[2].direction][1];
		int i;
		for (i = 0;i < 5; i ++){
			if (!play[2].bullet[i].IsLau){
				play[2].bullet[i].IsLau = 1;
				break;
			}
		}
		if (i<5) {
			play[2].bullet[i].len = 0;
			play[2].bullet[i].x = x;play[2].bullet[i].y = y;
			play[2].bullet[i].direction = play[2].direction;
			play[2].bulletnum ++;
			if (Wall[play[2].bullet[i].x][play[2].bullet[i].y] == 1){
				KillTank(2,i,2);
			} else if (Wall[play[2].bullet[i].x][play[2].bullet[i].y] == 2){
				KillTank(1,i,2);
			} else if (Wall[play[2].bullet[i].x][play[2].bullet[i].y] == 3){
						
			} else {
				fillcircle(x * 20 + 10, y * 20 + 10, 5);
			}
			play[2].PreTime = clock();
		}
	}
	if ((_cmd & ATTACK_1) && play[1].bulletnum < 4 && clock() - play[1].PreTime > 100){
		int x = play[1].x + 2 * movdir[play[1].direction][0];
		int y = play[1].y + 2 * movdir[play[1].direction][1];
		int i;
		for (i = 0;i < 5; i ++){
			if (!play[1].bullet[i].IsLau){
				play[1].bullet[i].IsLau = 1;
				break;
			}
		}
		if (i<5) {
			play[1].bullet[i].len = 0;
			play[1].bullet[i].x = x;play[1].bullet[i].y = y;
			play[1].bullet[i].direction = play[1].direction;
			play[1].bulletnum ++;
			if (Wall[play[1].bullet[i].x][play[1].bullet[i].y] == 1){
				KillTank(1,i,1);
			} else if (Wall[play[1].bullet[i].x][play[1].bullet[i].y] == 2){
			//	KillTank(2,i,1);
			} else if (Wall[play[1].bullet[i].x][play[1].bullet[i].y] == 3){
				KillTank(2,i,1);		
			} else {
				fillcircle(x * 20 + 10, y * 20 + 10, 5);
			}
			play[1].PreTime = clock();
		}
	}
}
//向前走向后走flag为正负号
void TankGame::Tank_move(int who,int dir,int flag){
	putimage( play[who].x * 20 - 20 , play[who].y * 20 - 20, &bkimg);
	SignTank(play[who].x,play[who].y,0);
	int x = play[who].x; int y = play[who].y;
	int dx = x + flag * movdir[dir][0], dy = y + flag * movdir[dir][1]; 
	//判断dxdy这个中心形成的Tank能不能到达
	if (Wall[dx-1][dy-1] || Wall[dx][dy-1] || Wall[dx+1][dy-1] || Wall[dx-1][dy] || Wall[dx][dy] ||  Wall[dx+1][dy] || Wall[dx-1][dy+1] || Wall[dx][dy+1] || Wall[dx+1][dy+1]){
		dx = x; dy = y;
	}

	play[who].x = dx;
	play[who].y = dy;
	PutTank(who,dx,dy,dir);
	

	SignTank(play[who].x,play[who].y,who+1);
	/*测试Tank所在位置有没有标记成功
	for (int i = 1; i <= 31; i++)
		for (int j = 1; j <= 31; j++){
			if (Wall[i][j] == 2)
				putimage(i*20,j*20,&bksimg);
		}
	*/
}

void TankGame::SignTank(int dx,int dy,int flag){
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

void TankGame::Tank_turn(int who,int turn){
	play[who].direction += turn;
	if (play[who].direction == 0) play[who].direction = 8;
	else if (play[who].direction == 9) play[who].direction = 1;
	putimage( play[who].x * 20 - 20 , play[who].y * 20 - 20, &bkimg);
	PutTank(who,play[who].x,play[who].y,play[who].direction);
} 

void TankGame::KillTank(int who,int i,int fromwho){
	play[fromwho].bullet[i].IsLau = 0;
	play[who].blood --;
	//计算杀人的时间点
	play[who].Isrevive = 1;
	if (who != fromwho){
		play[fromwho].Prekillnum ++;
		if (clock() - play[fromwho].Prekilltime < 25000){
			mciSendString("close movie",NULL,0,NULL);
			switch (play[fromwho].Prekillnum){
			case 1: break;	
			case 2: mciSendString("play  res\\k2.wav", NULL, 0, NULL); break;
			case 3: mciSendString("play  res\\k3.wav", NULL, 0, NULL); break;
			case 4: mciSendString("play  res\\k4.wav", NULL, 0, NULL); break;
			default:
				mciSendString("play  res\\k5.wav", NULL, 0, NULL); break;
			}
		}
		switch (play[fromwho].Prekillnum)
		{
		case 1: case 2: break;
		case 3: mciSendString("play  res\\3.wav", NULL, 0, NULL); break;
		case 4: mciSendString("play  res\\4.wav", NULL, 0, NULL); break;
		case 5: mciSendString("play  res\\5.wav", NULL, 0, NULL); break;
		case 6: mciSendString("play  res\\6.wav", NULL, 0, NULL); break;
		case 7: mciSendString("play  res\\7.wav", NULL, 0, NULL); break;
		case 8: mciSendString("play  res\\8.wav", NULL, 0, NULL); break;
		case 9: mciSendString("play  res\\9.wav", NULL, 0, NULL); break;
		default:
			mciSendString("play  res\\10.wav", NULL, 0, NULL);
			break;
		}
		play[fromwho].Prekilltime = clock();
	}
	play[who].Prekillnum = 0; play[who].Prekilltime = 0;
	if (play[who].blood == 6 && FirstDeath) {
		mciSendString("play  res\\1.wav", NULL, 0, NULL);
		FirstDeath = 0;
	}
	play[fromwho].bulletnum --;
	play[who].Killtime = clock();
	
	//putimage
	if (play[who].blood > 0){
		/*for (int i = 0; i <= 10; i++){
			putimage(play[who].x * 20 - 20, play[who].y * 20 -20 , &DeadBomb[i]);
			Time.Sleep(100);
		}*/
		putimage(play[who].x * 20 - 20 , play[who].y * 20 - 20, &bkimg);
		SignTank(play[who].x,play[who].y,0);
		killtime = clock();
		//Revive(who);
	}else {
		for (int i = 0; i <= 10; i++){
			putimage(play[who].x * 20 - 20, play[who].y * 20 -20 , &DeadBomb[i]);
			Time.Sleep(100);
		}
		EndOfGame(who,fromwho);	
	}
}

void TankGame::Revive(int who){
	putimage(play[who].x * 20 - 20 , play[who].y * 20 - 20, &bkimg);
	int dx = rand() % 31 + 1; 
	int dy = rand() % 31 + 1;
	while (Wall[dx-1][dy-1] || Wall[dx][dy-1] || Wall[dx+1][dy-1] || Wall[dx-1][dy] || Wall[dx][dy] ||  Wall[dx+1][dy] || Wall[dx-1][dy+1] || Wall[dx][dy+1] || Wall[dx+1][dy+1]){
		dx = rand() % 31 + 1;
		dy = rand() % 31 + 1;
	}
	play[who].x = dx;
	play[who].y = dy;
	int newdir = rand()%8 + 1;
	play[who].direction = newdir;
	PutTank(who,play[who].x,play[who].y,play[who].direction);
	SignTank(play[who].x,play[who].y,who+1);
}

void TankGame::MoveBullet(int who,int i){
	int x = play[who].bullet[i].x; int y = play[who].bullet[i].y;
	int dx = play[who].bullet[i].x + movdir[play[who].bullet[i].direction][0];
	int dy = play[who].bullet[i].y + movdir[play[who].bullet[i].direction][1];
	putimage(x * 20, y * 20 , &bksimg);
	if (play[who].bullet[i].len >= BULL_LEN){
		play[who].bullet[i].IsLau = 0;
		play[who].bulletnum --;
		return ;
	}
	if (Wall[dx][dy] == 0){
		play[who].bullet[i].len  ++;
	}else if (Wall[dx][dy] == 1){
		int newdir = FindNewDir(x,y,play[who].bullet[i].direction);
		dx = x + movdir[newdir][0];
		dy = y + movdir[newdir][1];
		play[who].bullet[i].len ++;
		play[who].bullet[i].direction = newdir;
		
	}
	if (Wall[dx][dy] == 2){
		KillTank(1,i,who);
		play[who].bullet[i].IsLau = 0;
		//play[who].bulletnum --;
	}else if (Wall[dx][dy] == 3){
		KillTank(2,i,who);
		play[who].bullet[i].IsLau = 0;
		//play[who].bulletnum --;
	}else {
		fillcircle(dx * 20 + 10, dy * 20 + 10, 5);
	}

	play[who].bullet[i].x = dx;
	play[who].bullet[i].y = dy;
}

int TankGame::FindNewDir(int x,int y,int direction){
	int dx,dy;
	switch (direction)
	{
	case 1: return 5;
	case 2: dx = x + movdir[4][0];dy = y + movdir[4][1];
			if (Wall[dx][dy] != 1) 
				return 4;
			else if (Wall[x+movdir[8][0]][y+movdir[8][1]] != 1)
				return 8;
			else return 6;
	case 3: return 7;
	case 4: if (Wall[x+movdir[6][0]][y+movdir[6][1]] != 1)
				return 6;
			else if (Wall[x+movdir[2][0]][y+movdir[2][1]] != 1)
				return 2;
			else return 8;
	case 5: return 1;
	case 6: if (Wall[x+movdir[8][0]][y+movdir[8][1]] != 1)
				return 8;
			else if (Wall[x+movdir[4][0]][y+movdir[4][1]] != 1)
				return 4;
			else return 2;
	case 7: return 3;
	case 8: if (Wall[x+movdir[6][0]][y+movdir[6][1]] != 1)
				return 6;
			else if (Wall[x+movdir[2][0]][y+movdir[2][1]] != 1)
				return 2;
			else return 4;

	default:
		break;
	}	
}

void TankGame::EndOfGame(int who,int fromwho){
	IMAGE img;
	loadimage(&img, "res\\bk.jpg", 20, 20);
	float H, S, L;
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
	for(int i = 0; i < 15; ++i)					// 绘制提示区域外围框
	{
		putimage(i * 20 + 660, 0, &img);
		putimage(i * 20 + 660, 640, &img);
	}
	for(int i = 0; i < 34; ++i)								
	{
		putimage(940, i * 20 , &img);
	}
	RECT r = {710, 40, 900, 300};
	setbkmode(TRANSPARENT);					// 设置输出文字背景模式为透明
	setcolor(BLUE);							// 设置输出文字颜色
	setfont(18, 0, "楷体");
	outtextxy(760, 400, "游戏结束！");
	outtextxy(730, 450, "按R键重新开始");
	outtextxy(760, 500, "按Q键退出");
	if (play[1].blood <= 0) 
		outtextxy(760, 200, "玩家2获胜");
	else
		outtextxy(760, 200, "玩家1获胜");

	//mycontrol = getch(); 
	while(1){
		if(kbhit())	{
			mycontrol = getch();
			if (mycontrol == 'q' || mycontrol == 'Q' || mycontrol == 'R' || mycontrol == 'r')	
				break;
		}else Sleep(60);
	}
	//if (mycontrol == 'q' || mycontrol == 'Q') return ;
}