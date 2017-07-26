#include <time.h>
#include <stdlib.h>
#include "map.h"



//��ʼ����ά����
void initmap()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			setFruit(i, j);
		}
	}
	while (clear() != 0)//��ʼ���γɵ�ͼû����������ͼ��
	{
		fill();
	}
}

//���������״̬
void setFruit(int x, int y)
{
	map[x][y] = rand() % 5 + 1;
}

//������ͬ��ˮ������������ά������б���
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
			int flag = 0;//�����˺��������Ͳ�������������

			int temp1 = map[i][j]; //��¼map[i][j]

			//���ŵ�
			int k;
			int q;
			for (k = 1; map[i][j + k] == map[i][j] && (j + k < 7); k++);
			if (k >= 3)
			{
				flag++;
				num += k;
				//�ȰѺ���������������
				for (q = 0; q < k; q++)
				{
					map[i][j + q] = 0;
				}
				//�Ժ�����������ÿһ��map[i][j+h]�ж��Ƿ�������Ч����
				for (int h = 0; h < k; h++)
				{
					int g;
					int temp = 0;//��Ч���ܵ���
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

			//���ŵ�
			for (k = 1; map[i + k][j] == map[i][j]&& (i + k < 7); k++);
			if (k >= 3 && flag == 0)
			{
				num += k;
				//�Ȱ����ŵı��0
				for (int q = 0; q < k; q++)
				{
					map[i + q][j] = 0;
				}
				//��������������ÿһ��map[i][j+h]�ж��Ƿ�������Ч����,���ŵ������������map[i][j]����ұ��쳤����ͺ��ŵ�һ��
				for (int h = 1; h < k; h++)
				{
					int g,g1;
					int q;
					int temp = 0;//��Ч���ܵ���
					//ʮ��
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
					//����߳�����
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
					//���ұ߳�����
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

//���ˮ����������ȵ������ճ����������
void fill()
{
	int i, j;
	for (i = 6; i >= 0; i--)
	{
		for (j = 6; j >= 0; j--)
		{
			while (map[i][j] == 0)
			{
				//���µ�
				for (int k = i; k > 0; k--)
				{
					map[k][j] = map[k-1][j];
				}
				map[0][j] = rand() % 5 + 1;;
			}
		}
	}
}

//�������������״̬
void swap(POINT point1, POINT  point2)
{
	int temp;
	temp = map[point1.x][point1.y];
	map[point1.x][point1.y] = map[point2.x][point2.y];
	map[point2.x][point2.y] = temp;
}


