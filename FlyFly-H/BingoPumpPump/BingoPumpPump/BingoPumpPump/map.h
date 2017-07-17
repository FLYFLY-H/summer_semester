#include <Windows.h>

//�����ά��������״̬����ʾ��ͬ��ˮ��
#define BINGO_ZERO 0
#define BINGO_APPLE 1
#define BINGO_LEMON 2
#define BINGO_WATEMALON 3
#define BINGO_BLUEBERRY 4
#define BINGO_STRAWBERRY 5


//��Ϸ����
typedef struct _GAME_COORD
{
	short x;
	short y;
}GAME_COORD, *PGAME_COORD;

//ȫ�ֱ��� 
int map[7][7]; //��ʾͼ
GAME_COORD boundary;

 //��ʼ����ά����
void initmap();

//���������״̬
void setFruit(int, int);

// ���ñ߽�����
void SetBoundary(int x, int y);

// ��ȡ�߽�����
PGAME_COORD GetBoundary();

//������ͬ��ˮ������������ά������б���
int clear();

//���ˮ��������ĵ��º�ճ����Ĳ������
void fill();


//�������������״̬
void swap(POINT, POINT);



#pragma once
