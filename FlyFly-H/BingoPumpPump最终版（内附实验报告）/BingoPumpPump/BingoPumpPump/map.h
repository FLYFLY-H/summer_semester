#include <Windows.h>



//表示图
int map[7][7]; 

 //初始化二维数组
void initmap();

//设置坐标的状态
void setFruit(int, int);

//消除相同的水果，对整个二维数组进行遍历
int clear();

//填充水果，上面的掉下后空出来的部分填充
void fill();

//交换两个坐标的状态
void swap(POINT, POINT);
