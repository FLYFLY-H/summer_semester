#include <windows.h>
#include <time.h>
#include "map.h"
#include "game_operation.h"

POINT point1, point2;

//��Ϸ�ĳ�ʼ��
void CreateGame(HWND hwnd, int x, int  y)
{
	srand(time(0));//srand��rand��Ҫ��һ�㣬��������ͬ��
	initmap();
	SetBoundary(x, y);
}

//���������Ϣ,ֻ�����ٿ�
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