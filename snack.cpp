// snack.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
 
//游戏功能列表
//1.贪吃蛇上下左右移动
//2.贪吃蛇吃食物长大
//3.贪吃蛇撞墙、吃到自己
//4.游戏结束，打印得分
      
//定义地图的大小
#define MAP_WIDTH 60
#define MAP_HEIGHT 20
void DrawChar(int x,int y,char ch);
typedef struct Position
{
	//x坐标
	int x;

	//y坐标
	int y;
}position;

//贪吃蛇结构体
typedef struct Snack
{
	//贪吃蛇的长度
	int size;

	Position pos[MAP_WIDTH*MAP_HEIGHT];
}Snack;

Snack g_snack;
//食物
Position g_food;

void InitFood()
{
	srand((unsigned)time(NULL ));

	g_food.x = rand() % MAP_WIDTH;
	g_food.y = rand() % MAP_HEIGHT;

	DrawChar(g_food.x,g_food.y,'#');
}

//游戏开始贪吃蛇的大小
void InitSnack()
{
	g_snack.size = 3;
	g_snack.pos[0].x = MAP_WIDTH/2;
	g_snack.pos[0].y = MAP_HEIGHT/2;

	g_snack.pos[1].x = MAP_WIDTH/2-1;
	g_snack.pos[1].y = MAP_HEIGHT/2;

	g_snack.pos[2].x = MAP_WIDTH/2-2;
	g_snack.pos[2].y = MAP_HEIGHT/2;
}
//绘制贪吃蛇
void DrawSnack()
{
	for(int i = 0;i <g_snack.size;i++)
	{
		if(i==0)
		{
		DrawChar(g_snack.pos[i].x,g_snack.pos[i].y,'*');
		}
		else
		{
		DrawChar(g_snack.pos[i].x,g_snack.pos[i].y,'#');
		}
	}

}

//在x，y绘制字符ch
//DrawChar(30,10,'#');
void DrawChar(int x,int y,char ch)
{
	COORD pos;
	pos.X=x;
	pos.Y=y;
	//设置光标位置
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
	putchar(ch);
}
void InitMap()
{
	//一行一行
	for(int i=0;i<=MAP_HEIGHT;i++)
	{
		for(int j=0;j<=MAP_WIDTH;j++)
		{
		
			if(j == MAP_WIDTH)
			{
				//右边框
				printf("|\n");
			}
			else if(i == MAP_HEIGHT)
			{
				//底边
		
		    printf("-");
		}
			else
		{
        	printf(" ");
		}
	}
	}
}
void Init()
{
	//绘制地图
	InitMap();
	//初始化贪吃蛇
	InitSnack();
	InitFood();
}
void UpdateScreen()
{
	DrawSnack();

}
//w 上
//s 下
//a 左
//d 右
void SnackMove(int key)
{
	int delta_x = 0;
	int delta_y = 0;


	if(key == 'w' || key =='W')//w 上
	{
		 delta_x = 0;
	     delta_y = -1;
	}
	else if(key == 's' || key =='S')//s 下
	{
		 delta_x = 0;
	     delta_y = 1;
	}
	else if(key == 'a' || key =='A')//a 左
	{
		 delta_x = -1;
	     delta_y = 0;
	}
	else if(key == 'd' || key =='D')//d 右
	{
		 delta_x = 1;
	     delta_y = 0;
	}
	else
	{
		//无效按键
		return;
	}
	//删除掉尾节点
	DrawChar(g_snack.pos[g_snack.size - 1].x, g_snack.pos[g_snack.size - 1].y,' ');

	//后一个节点等于前一个节点的坐标
	//g_snack.size - 1;最后一个节点的坐标
	//i>0不包括头节点
	for (int i = g_snack.size - 1;i>0;i--)
	{
		g_snack.pos[i].x = g_snack.pos[i-1].x;
		g_snack.pos[i].y = g_snack.pos[i-1].y;
	}
	g_snack.pos[0].x += delta_x;
	g_snack.pos[0].y += delta_y;
}
//头节点跟食物的坐标相同
void EatFood()
{
	if(g_snack.pos[0].x == g_food.x &&
		g_snack.pos[0].y == g_food.y)
	{
		g_snack.size++;
		//新的尾节点跟食物的坐标一致
		g_snack.pos[g_snack.size -1].x = g_food.x;
		g_snack.pos[g_snack.size -1].y = g_food.y;
	}
}
void GameLoop()
{
	int key = 0;
	while(1)
	{

		//处理键盘输入

		//检测是否有按键输入
		if(_kbhit())
		{
	     	key =_getch();
		}
		//按q退出游戏
		if(key == 'q'||key =='Q')
		{
			return;
		}
		//键盘移动贪吃蛇
		SnackMove(key);

		//处理撞墙等事件
		EatFood();
		//更新画面
		UpdateScreen();

	
		//延时
		Sleep(100);
	}
}
void Score()
{
}
int main(int argc, char* argv[])
{
	//初始化，画地图
	Init();
	//游戏的主循环，按键处理，游戏画面刷新，处理撞墙等事件
	GameLoop();
	//打印得分
	Score();
	return 0;
}

