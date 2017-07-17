//引用的头文件
#include <windows.h>
#include <math.h>
#include "map.h"
#include "game_operation.h"

#define CELL_PIXEL			20
#define FRUIT_PIXEL         50

//使用的位图
#define BITMAP_FILE_APPLE   "apple_bmp"
#define BITMAP_FILE_LEMON   "lemon_bmp"
#define BITMAP_FILE_WATEMALON   "watermelon_bmp"
#define BITMAP_FILE_BLUEBERRY    "blueberry_bmp"
#define BITMAP_FILE_STRAWBERRY   "strawberry_bmp"  


//初始设置
#define MAX_X		24// 游戏界面大小
#define MAX_Y		42// 游戏界面大小

//全局变量
HINSTANCE hinst; /// HINSTANCE是用来表示程序运行实例的句柄，某些API函数会使用到这个变量。
RECT rectBoundary;
POINT point1, point2;
int flag = 0;
int swapnumber[3] = { 10,15,20 }; //每一关卡交换次数
int removenumber[3] = { 40,90,150 };//每一关卡需消除的个数
int level = 0;



// 函数声明
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LONG CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
void GamePaint(HWND);
void ReSizeGameWnd(HWND);

//WinMain函数
int WINAPI WinMain(HINSTANCE  hinstance, HINSTANCE hPrevlnstance, LPSTR IpCmdline, int nCmdShow)
{
	WNDCLASS wc;
	HWND hwnd;

	MSG msg;
	int fGotMessage;

	hinst = hinstance;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hinstance;
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = "MainMenu";
	wc.lpszClassName = "MainWClass";

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "创建窗口class失败", "错误！", MB_ICONERROR | MB_OK);
		return -1;
	}

	hwnd = CreateWindow(
		"MainWClass",			// 窗口类名，必须是已经注册了的窗口类
		"BingoPumpPump!!",		// title-bar string 
		WS_OVERLAPPEDWINDOW,	// 窗口的style，这个表示为top-level window 
		CW_USEDEFAULT,			// 窗口水平位置default horizontal POINT 
		CW_USEDEFAULT,			// 窗口垂直位置default vertical POINT 
		CW_USEDEFAULT,			// 窗口宽度 default width 
		CW_USEDEFAULT,			// 窗口高度 default height 
		(HWND)NULL,				// 父窗口句柄 no owner window 
		(HMENU)NULL,			// 窗口菜单的句柄 use class menu 
		hinstance,				// 应用程序实例句柄 handle to application instance 
		(LPVOID)NULL);			// 指向附加数据的指针 no window-creation data 

	if (!hwnd)
	{
		MessageBox(NULL, "创建窗口失败", "错误！", MB_ICONERROR | MB_OK);
		return -1;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while ((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0&& fGotMessage != -1)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}



void GamePaint(HWND hwnd)
{
	HDC hdc, hdcmem, hdcFruit, hdcBk, hdcNumber;
	HBITMAP hbmmem;
	BITMAP bmp;
	HBITMAP hbmpApple, hbmpWatermelon, hbmpLemon, hbmpBlueberry, hbmpStrawberry;
	HBITMAP hbmpBk;
	HBITMAP hbmpNumber;
	HFONT hFont, hOldFont;
	//HBITMAP hbmpapple;

	RECT rect;

	GetClientRect(hwnd, &rect);
	hdc = GetDC(hwnd);

	hdcmem = CreateCompatibleDC(hdc);
	hbmmem = CreateCompatibleBitmap(hdc, rect.right - rect.left, rect.bottom - rect.top);
	hdcFruit = CreateCompatibleDC(hdcmem);
	hdcBk = CreateCompatibleDC(hdcmem);
	hdcNumber = CreateCompatibleDC(hdcmem);
	hbmpApple = LoadImage(NULL, "apple.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbmpBlueberry = LoadImage(NULL, "blueberry.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbmpLemon = LoadImage(NULL, "lemon.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbmpStrawberry = LoadImage(NULL, "strawberry.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbmpWatermelon = LoadImage(NULL, "watermelon.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbmpBk = LoadImage(NULL, "BK.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbmpNumber = LoadImage(NULL, "number.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	SelectObject(hdcmem, hbmmem);

	//画背景
	//FillRect(hdcmem, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	SelectObject(hdcBk, hbmpBk);
	GetObject(hbmpBk, sizeof(BITMAP), &bmp);
	StretchBlt(hdcmem,
		rect.left, rect.top,
		rect.right - rect.left, rect.bottom - rect.top,
		hdcBk,
		0, 0,
		bmp.bmWidth, bmp.bmHeight,
		SRCCOPY);

	//贴位图
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)  //用map[j][i]是因为在画图过程中，系统是竖着画的
		{
			if (map[j][i] == 1) 
			{
				GetObject(hbmpApple, sizeof(BITMAP), &bmp);
				SelectObject(hdcFruit, hbmpApple);

				StretchBlt(hdcmem,
					i * FRUIT_PIXEL + rectBoundary.left + 55,
					j* FRUIT_PIXEL + rectBoundary.top + 220,
					FRUIT_PIXEL, FRUIT_PIXEL,
					hdcFruit,
					0, 0, bmp.bmWidth, bmp.bmHeight,
					SRCCOPY);

			}
			if (map[j][i] == 2) 
			{
				//hdcFruit = CreateCompatibleDC(hdcmem);
				//hbmpBlueberry = LoadImage(NULL, "blueberry.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				GetObject(hbmpBlueberry, sizeof(BITMAP), &bmp);
				SelectObject(hdcFruit, hbmpBlueberry);

				StretchBlt(hdcmem,
					i * FRUIT_PIXEL + rectBoundary.left + 55,
					j* FRUIT_PIXEL + rectBoundary.top + 220,
					FRUIT_PIXEL, FRUIT_PIXEL,
					hdcFruit,
					0, 0, bmp.bmWidth, bmp.bmHeight,
					SRCCOPY);

			}
			if (map[j][i] == 3)
			{
				//hdcFruit = CreateCompatibleDC(hdcmem);
				//hbmpLemon = LoadImage(NULL, "lemon.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				GetObject(hbmpLemon, sizeof(BITMAP), &bmp);
				SelectObject(hdcFruit, hbmpLemon);

				StretchBlt(hdcmem,
					i * FRUIT_PIXEL + rectBoundary.left + 55, 
					j* FRUIT_PIXEL + rectBoundary.top + 220,
					FRUIT_PIXEL, FRUIT_PIXEL,
					hdcFruit,
					0, 0, bmp.bmWidth, bmp.bmHeight,
					SRCCOPY);

			}
			if (map[j][i] == 4) 
			{
				//hdcFruit = CreateCompatibleDC(hdcmem);
				//hbmpStrawberry = LoadImage(NULL, "strawberry.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				GetObject(hbmpStrawberry, sizeof(BITMAP), &bmp);
				SelectObject(hdcFruit, hbmpStrawberry);

				StretchBlt(hdcmem,
					i * FRUIT_PIXEL + rectBoundary.left + 55,
					j* FRUIT_PIXEL + rectBoundary.top + 220,
					FRUIT_PIXEL, FRUIT_PIXEL,
					hdcFruit,
					0, 0, bmp.bmWidth, bmp.bmHeight,
					SRCCOPY);

			}
			if (map[j][i] == 5)//蓝色
			{
				//hdcFruit = CreateCompatibleDC(hdcmem);
				//hbmpWatermelon = LoadImage(NULL, "watermelon.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				GetObject(hbmpWatermelon, sizeof(BITMAP), &bmp);
				SelectObject(hdcFruit, hbmpWatermelon);

				StretchBlt(hdcmem,
					i * FRUIT_PIXEL + rectBoundary.left + 55,
					j* FRUIT_PIXEL + rectBoundary.top + 220,
					FRUIT_PIXEL, FRUIT_PIXEL,
					hdcFruit,
					0, 0, bmp.bmWidth, bmp.bmHeight,
					SRCCOPY);

			}
		}
	}

	//计步数
	SelectObject(hdcNumber, hbmpNumber);
	GetObject(hbmpNumber, sizeof(BITMAP), &bmp);
	StretchBlt(hdcmem,
		320, 60,
		FRUIT_PIXEL * 2, FRUIT_PIXEL * 2.3,
		hdcNumber,
		0, 0, bmp.bmWidth, bmp.bmHeight,
		SRCCOPY);
	
	//消灭个数
	SelectObject(hdcNumber, hbmpNumber);
	GetObject(hbmpNumber, sizeof(BITMAP), &bmp);
	StretchBlt(hdcmem,
		200, 60,
		FRUIT_PIXEL * 2, FRUIT_PIXEL * 2.3,
		hdcNumber,
		0, 0, bmp.bmWidth, bmp.bmHeight,
		SRCCOPY);

	//字体
	hFont = CreateFont(33, 0, 0, 0, FW_DONTCARE, 1, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));
	if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
	{
		CHAR szSourceInfo[1024];
		wsprintf(szSourceInfo, "%d", removenumber[level]);
		SetTextColor(hdcmem, RGB(178, 34, 34));
		TextOut(hdcmem, 240, 66, szSourceInfo, lstrlen(szSourceInfo));
		SelectObject(hdcmem, hOldFont);
	}

	hFont = CreateFont(33, 0, 0, 0, FW_DONTCARE, 1, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));
	if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
	{
		CHAR szSourceInfo[1024];
		wsprintf(szSourceInfo, "%d", swapnumber[level]);
		SetTextColor(hdcmem, RGB(178, 34, 34));
		TextOut(hdcmem, 360, 66, szSourceInfo, lstrlen(szSourceInfo));
		SelectObject(hdcmem, hOldFont);
	}
	// 在内存DC中画完，一次输出的窗口DC上。
	BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, hdcmem, 0, 0, SRCCOPY);

	//回收资源，释放GDI对象
	DeleteObject(hbmmem);
	DeleteObject(hbmpNumber);
	DeleteObject(hbmpApple);
	DeleteObject(hbmpBlueberry);
	DeleteObject(hbmpLemon);
	DeleteObject(hbmpStrawberry);
	DeleteObject(hbmpWatermelon);
	DeleteObject(hFont);
	DeleteObject(hOldFont);
	//释放占用的DC等系统资源
	ReleaseDC(hwnd, hdc);
	ReleaseDC(hwnd, hdcmem);
	ReleaseDC(hwnd, hdcFruit);
	ReleaseDC(hwnd, hdcNumber);
}

void ReSizeGameWnd(HWND hwnd)
{
	POINT ptLeftTop;		// 左上角
	POINT ptRightBottom;	// 右下角
	RECT rectWindow;
	PGAME_COORD pCoordBoundary = GetBoundary();

	// 设置游戏边界
	rectBoundary.left = 10;
	rectBoundary.top = 10;
	rectBoundary.right = 10 + CELL_PIXEL*(pCoordBoundary->x + 1);
	rectBoundary.bottom = 10 + CELL_PIXEL*(pCoordBoundary->y + 1);

	// 计算上下左右角的位置
	ptLeftTop.x = rectBoundary.left;
	ptLeftTop.y = rectBoundary.top;
	ptRightBottom.x = rectBoundary.right;
	ptRightBottom.y = rectBoundary.bottom;
	ClientToScreen(hwnd, &ptLeftTop);
	ClientToScreen(hwnd, &ptRightBottom);

	GetWindowRect(hwnd, &rectWindow);
	// 计算好了，设置窗口大小。
	MoveWindow(hwnd,
		rectWindow.left,
		rectWindow.top,
		ptLeftTop.x - rectWindow.left + ptRightBottom.x - rectWindow.left-80, // 保存边界和左右两边边框相等。
		rectBoundary.bottom , //给积分信息留出显示空间。
		TRUE);
}

LONG CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int x, y;
	switch (msg)
	{
	case WM_CREATE:
		CreateGame(hwnd, MAX_X, MAX_Y);
		ReSizeGameWnd(hwnd);
		GamePaint(hwnd);
		break;
	case WM_LBUTTONDOWN:
		if (wParam && MK_LBUTTON&&flag==0)
		{
			x = LOWORD(lParam);
		    y = HIWORD(lParam);
			point1.x = (y - 220) / FRUIT_PIXEL;
			point1.y = (x - 52) / FRUIT_PIXEL;
			flag++;
		}
		else if (wParam && MK_LBUTTON&&flag == 1)
		{
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			point2.x = (y - 220) / FRUIT_PIXEL;
			point2.y = (x - 55) / FRUIT_PIXEL;
			if (point2.x == point1.x&&point2.y == point1.y)
			{
				MessageBox(hwnd, "请单击鼠标，不用双击", "错误！", MB_ICONERROR | MB_OK);
				flag = 0;
				break;
			}
			flag++;
		}
		if (flag == 2)
		{
			if (point1.x == point2.x&&abs(point1.y - point2.y) == 1 ||
				point1.y == point2.y&&abs(point1.x - point2.x) == 1)
			{
				swap(point1, point2);
				swapnumber[level]--;
				GamePaint(hwnd);
				Sleep(800);
				flag = 0;
				int f;
				f = clear();
				removenumber[level] -= f;
				GamePaint(hwnd);
				Sleep(800);
				if (f == 0)
				{
					swap(point1, point2);
					swapnumber[level]++;
					GamePaint(hwnd);
					Sleep(800);
				}
				else
				{
					fill();
					GamePaint(hwnd);
					Sleep(800*2);
					while ((f=clear() )!= 0)
					{
						removenumber[level] -= f;
						GamePaint(hwnd);
						Sleep(800);
						fill();
						GamePaint(hwnd);
						Sleep(800*2);
					}
				}
				if (swapnumber[level] >= 0 && removenumber[level] <= 0)
				{
					if (level == 2)
					{
						MessageBox(0, "You Win!", "Success", 0);
						ExitProcess(0);
						break;
					}
					else
					{ 
						MessageBox(0, "Enter the next pass", "Success", 0);
						level++;
						CreateGame(hwnd, MAX_X, MAX_Y);
						GamePaint(hwnd);
					}
				}
				else if (swapnumber[level] == 0 && removenumber[level] > 0)
				{
					MessageBox(0, "Gameover!", "Faile", 0);
					ExitProcess(0);
					break;
				}
			}
			else
			{
				MessageBox(hwnd, "请点击相邻的水果", "错误！", MB_ICONERROR | MB_OK);
				flag = 0;
			}
		}
		break;
	case WM_PAINT:
		GamePaint(hwnd);
		break;
	case WM_DESTROY:
		ExitProcess(0);
		break;
	default:
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
