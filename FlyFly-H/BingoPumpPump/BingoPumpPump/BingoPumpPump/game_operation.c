#include <windows.h>
#include <time.h>
#include "map.h"
#include "game_operation.h"

POINT point1, point2;

//游戏的初始化
void CreateGame(HWND hwnd, int x, int  y)
{
	srand(time(0));//srand和rand不要在一层，会生成相同的
	initmap();
	SetBoundary(x, y);
}

//处理鼠标信息,只有鼠标操控
//void OnMouse(POINT point1,POINT  point2)
//{
//		swap(point1, point2);
//		if (clear() == 0)
//		{
//			swap(point1, point2);
//		}
//		else
//		{
//			fill();
//		}
//}