#include<windows.h>

//ÓÎÏ·×ø±ê
typedef struct _GAME_COORD
{
	short x;
	short y;
}GAME_COORD, *PGAME_COORD;

GAME_COORD boundary;

void CreateGame(HWND, int, int);

void SetBoundary(int, int);

PGAME_COORD GetBoundary();
