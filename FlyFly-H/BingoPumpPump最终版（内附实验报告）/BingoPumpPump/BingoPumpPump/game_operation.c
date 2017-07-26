#include <windows.h>
#include <time.h>
#include "map.h"
#include "game_operation.h"

POINT point1, point2;


// 设置边界坐标
void SetBoundary(int x, int y)
{
	boundary.x = x;
	boundary.y = y;
}

// 获得边界坐标
PGAME_COORD GetBoundary()
{
	return &boundary;
}
//游戏的初始化
void CreateGame(HWND hwnd, int x, int  y)
{
	srand(time(0));//srand和rand不要在一层，会生成相同的
	initmap();
	SetBoundary(x, y);
}