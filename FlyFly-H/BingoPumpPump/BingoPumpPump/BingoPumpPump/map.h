#include <Windows.h>

//定义二维数组六种状态，表示不同的水果
#define BINGO_ZERO 0
#define BINGO_APPLE 1
#define BINGO_LEMON 2
#define BINGO_WATEMALON 3
#define BINGO_BLUEBERRY 4
#define BINGO_STRAWBERRY 5


//游戏坐标
typedef struct _GAME_COORD
{
	short x;
	short y;
}GAME_COORD, *PGAME_COORD;

//全局变量 
int map[7][7]; //表示图
GAME_COORD boundary;

 //初始化二维数组
void initmap();

//设置坐标的状态
void setFruit(int, int);

// 设置边界坐标
void SetBoundary(int x, int y);

// 获取边界坐标
PGAME_COORD GetBoundary();

//消除相同的水果，对整个二维数组进行遍历
int clear();

//填充水果，上面的掉下后空出来的部分填充
void fill();


//交换两个坐标的状态
void swap(POINT, POINT);



#pragma once
