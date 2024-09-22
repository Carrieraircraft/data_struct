﻿// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注


#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <assert.h>
#include <sstream>
#include <stack>

#pragma warning (disable: 4996) 
using namespace std;

//直接插入排序（从小到大排序）
template <typename T> //T代表数组元素类型
void InsertSort(T myarray[], int length) //myarray：要排序的数组元素，length：数组中元素数量。
{
	if (length <= 1) //不超过1个元素的数组，没必要排序
		return;

	for (int i = 1; i < length; ++i) //从第2个元素（下标为1）开始比较
	{
		if (myarray[i] < myarray[i - 1])
		{
			T temp = myarray[i]; //暂存myarray[i]值，防止后续移动元素时值被覆盖掉
			int j;
			for (j = i - 1; j >= 0 && myarray[j] > temp; --j) //检查所有前面排好序的元素
			{
				myarray[j + 1] = myarray[j]; //所有大于temp的元素都向后移动
			} //end for j

			myarray[j + 1] = temp; //复制数据到插入位置，注意j因为被减了1，所以这里加回来
		} //end if
	}//end for i
	return;
}

//折半插入排序（从小到大）
template <typename T> //T代表数组元素类型
void HalfInsertSort(T myarray[], int length)
{
	if (length <= 1) //不超过1个元素的数组，没必要排序
		return;

	for (int i = 1; i < length; ++i) //从第2个元素（下标为1）开始比较
	{
		if (myarray[i] < myarray[i - 1])
		{
			T temp = myarray[i]; //暂存myarray[i]值，防止后续移动元素时值被覆盖掉

			//记录查找的左右区间范围
			int left = 0; 
			int right = i - 1;

			while (left <= right) //注意while结束条件
			{
				//取中间元素
				int mid = (right - left) / 2 + left;
				if (myarray[mid] > temp)
				{
					//待排的元素值更小，将搜索区间缩小到左边的一半区域
					right = mid - 1;
				}
				else
				{
					//待排的元素值更大，将搜索区间缩小到右边的一半区域
					left = mid + 1;
				}
			}//end while

			int j;
			for (j = i - 1; j >= right+1; --j)
			{
				myarray[j + 1] = myarray[j]; 
			} //end for j
			myarray[right + 1] = temp;
		}//end if
	}//end for i
	return;
}

//2路插入排序（从小到大）
template <typename T> //T代表数组元素类型
void TwoWayInsertSort(T myarray[], int length)
{
	if (length <= 1) //不超过1个元素的数组，没必要排序
		return;

	T* pfzarray = new T[length]; //创建辅助数组空间
	pfzarray[0] = myarray[0];//将原始数组空间的第一个元素放入辅助数组空间第1个位置

	int head = 0; //头指针指向第一个位置（下标为0的元素）
	int tail = 0; //尾指针指向第一个位置（下标为0的元素）

	for (int i = 1; i < length; ++i)
	{
		if (myarray[i] < pfzarray[head]) //小于头
		{
			//往头前面插入
			head = (head - 1 + length) % length; //要保证head值在0到(length - 1)之间
			pfzarray[head] = myarray[i];
		}
		else if (myarray[i] > pfzarray[tail]) //大于尾
		{
			tail++;
			pfzarray[tail] = myarray[i];
		}
		else //数据既不小于头，也不大于尾，要往中间插入
		{ 
			//这里要移动数据了
			tail++;
			pfzarray[tail] = pfzarray[tail - 1];
			int j;
			for (j = tail - 1; myarray[i] < pfzarray[(j - 1 + length) % length]; j = (j - 1 + length) % length)
			{
				pfzarray[j] = pfzarray[(j - 1 + length) % length];
			} //end for j
			pfzarray[j] = myarray[i];
		} //end if
	} // end for i

	for (int i = 0; i < length; ++i)
	{
		myarray[i] = pfzarray[head];
		head = (head + 1) % length;
	} //end for i

	delete[] pfzarray;
	return;
}

int main()
{	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//第5章 排序
	//第一节 基本概念
	//排序的目的是为了让查找数据的效率变得更高
	//排序算法的稳定性：指关键字相同的元素在排序后相对位置不变。   
	    //a)不稳定算法  b)有些算法可以稳定，但通过细微调整代码也可以让他不稳定。

	//内部排序（内排序），外部排序（外排序）。
	//两种基本操作：比较，移动。

	//第二节 插入类排序
	//（1）直接插入排序（Straight Insertion Sort）
	//算法思想：每次将一个记录按其关键字的大小插入到已经排好序的序列中，直至全部记录插入完毕。
	//int arr[] = {16,1,45,23,99,2,18,67,42,10}--{1,16,....}--{1,16,45,....}--{1,16,23,45,....}
	//{1,16,23,45,99,....}--{1,2,16,23,45,99,....}--{1,2,16,18,23,45,99,...}--{1,2,16,18,23,45,67,99,...}
	//{1,2,16,18,23,42,45,67,99,...}--{1,2,10,16,18,23,42,45,67,99}
	//空间复杂度O(1)
	//时间复杂度：最好O(n),最坏O(n^2),平均：O(n^2)
	//稳定算法
	//适合：待排序记录数量比较少。
	//（2）折半（二分）插入排序（Binary Insertion Sort）--Binary Search。
	//是在已经排好序的序列（有序区）中，使用折半查找的方式去确定待排序元素的插入位置。
	//减少了关键字的比较次数，但没有减少记录的移动次数，所以时间复杂度仍旧是O(n^2)。
	//稳定算法

	//（3）2路插入排序（Two - Way Insertion Sort)
	//用辅助数组来减少排序中记录的移动次数
	//时间复杂度：O(n^2)
	//空间复杂度：O(n)，空间换时间。
	//稳定算法








	int arr[] = { 16,1,45,23,99,2,18,67,42,10 };
	int length = sizeof(arr) / sizeof(arr[0]); //数组中元素个数
	//InsertSort(arr, length); //对数组元素进行直接插入排序
	//HalfInsertSort(arr, length); //对数组元素进行折半插入排序
	TwoWayInsertSort(arr, length); //对数组元素进行2路插入排序

	//输出排好序的数组中元素内容
	//cout << "直接插入排序结果为：";
	//cout << "折半插入排序结果为：";
	cout << "2路插入排序结果为：";
	for (int i = 0; i < length; ++i)
	{
		cout << arr[i] << "  ";
	}
	cout << endl; //换行
	return 0;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧:  ∞
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误nm,
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件



