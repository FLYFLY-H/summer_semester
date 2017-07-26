#include <time.h>
#include <stdlib.h>
#include "map.h"



//初始化二维数组
void initmap()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			setFruit(i, j);
		}
	}
	while (clear() != 0)//初始化形成的图没有连起来的图标
	{
		fill();
	}
}

//设置坐标的状态
void setFruit(int x, int y)
{
	map[x][y] = rand() % 5 + 1;
}

//消除相同的水果，对整个二维数组进行遍历
int clear()
{
	int num = 0;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (map[i][j] == 0)
			{
				continue;
			}
			int flag = 0;//进行了横向置零后就不进行竖向置零

			int temp1 = map[i][j]; //记录map[i][j]

			//横着的
			int k;
			int q;
			for (k = 1; map[i][j + k] == map[i][j] && (j + k < 7); k++);
			if (k >= 3)
			{
				flag++;
				num += k;
				//先把横着连起来的置零
				for (q = 0; q < k; q++)
				{
					map[i][j + q] = 0;
				}
				//对横着连起来的每一个map[i][j+h]判断是否满足特效条件
				for (int h = 0; h < k; h++)
				{
					int g;
					int temp = 0;//特效不能叠加
					for (g = 1; map[i + g][j + h] == temp1 && (i + g < 7); g++);
					if (g >= 3&&temp==0)
					{
						temp++;
						num += g-1;
						for (q = 1; q < g; q++)
						{
							map[i + q][j + h] = 0;
						}
					}
				}
			}

			//竖着的
			for (k = 1; map[i + k][j] == map[i][j]&& (i + k < 7); k++);
			if (k >= 3 && flag == 0)
			{
				num += k;
				//先把竖着的变成0
				for (int q = 0; q < k; q++)
				{
					map[i + q][j] = 0;
				}
				//对竖着连起来的每一个map[i][j+h]判断是否满足特效条件,竖着的情况不用讨论map[i][j]左边右边伸长，这和横着的一样
				for (int h = 1; h < k; h++)
				{
					int g,g1;
					int q;
					int temp = 0;//特效不能叠加
					//十字
					for (g = 1; map[i + h][j - g] == temp1 && (j - g <j); g++);
					for (g1 = 1; map[i + h][j + g1] == temp1 && (j + g1 < 7); g1++);
					if ((g >= 2 && g1 >= 2) && temp == 0)
					{
						temp++;
						for (q = 1; q < g; q++)
						{
							map[i + h][j - q] = 0;
							num++;
						}
						for (q = 1; q < g1; q++)
						{
							map[i + h][j + q] = 0;
							num++;
						}
					}
					//往左边长出来
					for (g = 1; map[i+h][j - g] == temp1 && (j - g <j); g++);
					if (g >= 3 && temp == 0)
					{
						temp++;
						num += g - 1;
						for (q = 1; q < g; q++)
						{
							map[i+h][j - q] = 0;
						}
					}
					//往右边长出来
					for (g = 1; map[i + h][j + g] == temp1 && (j + g < 7); g++);
					if (g >= 3 && temp == 0)
					{
						temp++;
						num += g - 1;
						for (q = 1; q < g; q++)
						{
							map[i + h][j + q] = 0;
						}
					}
				}
			}
		}
	}
	return num;
}

//填充水果，上面的先掉下来空出来的再填充
void fill()
{
	int i, j;
	for (i = 6; i >= 0; i--)
	{
		for (j = 6; j >= 0; j--)
		{
			while (map[i][j] == 0)
			{
				//往下掉
				for (int k = i; k > 0; k--)
				{
					map[k][j] = map[k-1][j];
				}
				map[0][j] = rand() % 5 + 1;;
			}
		}
	}
}

//交换两个坐标的状态
void swap(POINT point1, POINT  point2)
{
	int temp;
	temp = map[point1.x][point1.y];
	map[point1.x][point1.y] = map[point2.x][point2.y];
	map[point2.x][point2.y] = temp;
}


