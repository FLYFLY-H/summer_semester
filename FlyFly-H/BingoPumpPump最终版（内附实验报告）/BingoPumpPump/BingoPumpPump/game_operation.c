#include <windows.h>
#include <time.h>
#include "map.h"
#include "game_operation.h"

POINT point1, point2;


// ���ñ߽�����
void SetBoundary(int x, int y)
{
	boundary.x = x;
	boundary.y = y;
}

// ��ñ߽�����
PGAME_COORD GetBoundary()
{
	return &boundary;
}
//��Ϸ�ĳ�ʼ��
void CreateGame(HWND hwnd, int x, int  y)
{
	srand(time(0));//srand��rand��Ҫ��һ�㣬��������ͬ��
	initmap();
	SetBoundary(x, y);
}