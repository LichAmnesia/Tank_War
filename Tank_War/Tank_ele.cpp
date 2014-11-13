#include "Tank_ele.h"
#include "TankGame.h"
#include "labyrith.h"



Tank::Tank()
{
	blood = 7;
	bulletnum = 0;
	for (int i = 0; i < 5; i++){
		bullet[i].IsLau = 0;
	}
	Prekillnum = 0;
	Prekilltime = 0;
	Isrevive = 0;
}

Tank::~Tank()
{
}

void Tank::LoadImg(int flag){
	if(flag){// 8������ 1����2�J��3����4�K��5����6�L��7����8�I 1357�����ж�
		loadimage(&img[1], "res\\tank_1\\Tank_1_��.jpg", 30, 60);
		loadimage(&img[2], "res\\tank_1\\Tank_1_�J.jpg", 60, 60);
		loadimage(&img[3], "res\\tank_1\\Tank_1_��.jpg", 60, 30);
		loadimage(&img[4], "res\\tank_1\\Tank_1_�K.jpg", 60, 60);
		loadimage(&img[5], "res\\tank_1\\Tank_1_��.jpg", 30, 60);
		loadimage(&img[6], "res\\tank_1\\Tank_1_�L.jpg", 60, 60);
		loadimage(&img[7], "res\\tank_1\\Tank_1_��.jpg", 60, 30);
		loadimage(&img[8], "res\\tank_1\\Tank_1_�I.jpg", 60, 60);
	}else{
		loadimage(&img[1], "res\\tank_2\\Tank_2_1.jpg", 30, 60);
		loadimage(&img[2], "res\\tank_2\\Tank_2_2.jpg", 60, 60);
		loadimage(&img[3], "res\\tank_2\\Tank_2_3.jpg", 60, 30);
		loadimage(&img[4], "res\\tank_2\\Tank_2_4.jpg", 60, 60);
		loadimage(&img[5], "res\\tank_2\\Tank_2_5.jpg", 30, 60);
		loadimage(&img[6], "res\\tank_2\\Tank_2_6.jpg", 60, 60);
		loadimage(&img[7], "res\\tank_2\\Tank_2_7.jpg", 60, 30);
		loadimage(&img[8], "res\\tank_2\\Tank_2_8.jpg", 60, 60);
	}
}	

void Tank::getdir(int dir){
	direction = dir;
}


