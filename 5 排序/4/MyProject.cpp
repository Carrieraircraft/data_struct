// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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

//简单选择排序（从小到大）
template <typename T>
void SmpSelSort(T myarray[], int length)
{
	for (int i = 0; i < length - 1; ++i) //一共要进行length-1趟
	{
		int minidx = i; //保存最小元素位置

		//在myarray[i]到myarry[length-1]中选择最小值
		for (int j = i + 1; j < length; ++j)
		{
			if (myarray[j] < myarray[minidx])
				minidx = j; //保存最小元素值位置
		} //end for j

		if (minidx != i)
		{
		T temp = myarray[i];
		myarray[i] = myarray[minidx];
		myarray[minidx] = temp;
		}
	} //end for i
	return;
}

#define INT_MAX_MY 2147483647 //整型能够保存的最大数值，作为标记使用
//属性选择排序（从小到大）
template <typename T>
void TreeSelSort(T myarray[], int length)
{
	//ceil是系统函数：返回的是大于或者等于x的最小整数
	int treelvl = (int)ceil(log(length) / log(2)) + 1; //5：完全二叉树高度（含有n个叶子节点的完全二叉树高度是logn向上取整 + 1

	//treelvl高的完全二叉树最多有nodecount个节点，如果有nodecount个节点，此时的完全二叉树其实就是满二叉树
	int nodecount = (int)pow(2, treelvl) - 1; //31:满二叉树是指一棵高度为h，且含有2h-1个节点的二叉树

	//treelvl-1高的完全二叉树最多有nodecount2个节点
	int nodecount2 = (int)pow(2, treelvl - 1) - 1; //15

	int* pidx = new int[nodecount]; //保存节点

	//叶子节点保存元素下标值（就等于保存了元素的值）
	for (int i = 0; i < length; ++i)
	{
		pidx[nodecount2 + i] = i; //pidx[15] = 0; pidx[16] = 1.....;pidx[24]=9;
	} //end for

	//给多余的叶子节点赋予一个最大值作为标记
	for (int i = nodecount2 + length; i < nodecount; ++i) //i = 25~30
	{
		pidx[i] = INT_MAX_MY; //pidx[25] = MAX;pidx[26] = MAX;.....pidx[30] = MAX
	}

	int tmpnode2 = nodecount2; //15
	int tmpnode = nodecount; //31

	//现在要开始给非叶子节点赋值了，非叶子节点下标是[0]~[14]
	//第一趟排序要给非叶子节点赋值，还要两两进行节点比较，所以 要单独处理
	while (tmpnode2 != 0)
	{

		for (int i = tmpnode2; i < tmpnode; i += 2)
		{
			if (pidx[i] != INT_MAX_MY && pidx[i + 1] != INT_MAX_MY)  //如果pidx[i]和pidx[i+1都是正常值，那自然是可以比较
			{
				if (myarray[pidx[i]] <= myarray[pidx[i + 1]])
				{
					pidx[(i + 1) / 2 - 1] = pidx[i];
				}
				else
				{
					pidx[(i + 1) / 2 - 1] = pidx[i + 1];
				}
			}
			else if (pidx[i] != INT_MAX_MY) //pidx[i]是正常值，因为有上个if在，说明pidx[i+1]不是正常值
			{
				pidx[(i + 1) / 2 - 1] = pidx[i];
			}
			else //说明pidx[i + 1]是正常值或者是INT_MAX_MY值
			{
				pidx[(i + 1) / 2 - 1] = pidx[i + 1];
			}
		} //end for i

		tmpnode = tmpnode2;
		tmpnode2 = (tmpnode2 - 1) / 2;
	} //end while 

	T* ptmparray = new T[length]; //临时保存排好序的数据

	for (int i = 0; i < length; i++)
	{
		ptmparray[i] = myarray[pidx[0]]; //将当前最小值赋给ptmparray[i]临时保存

		int leafidx = 0;

		//沿着树根找最小值节点在叶子中的序号
		for (int j = 1; j < treelvl; j++)
		{
			if (pidx[2 * leafidx + 1] == pidx[leafidx])
			{
				leafidx = 2 * leafidx + 1;
			}
			else
			{
				leafidx = 2 * leafidx + 2;
			}
		}//end for j

		//此时的leafidx就是完全二叉树叶子节点中的那个最小值的下标
		pidx[leafidx] = INT_MAX_MY;

		while (leafidx)
		{
			leafidx = (leafidx + 1) / 2 - 1; //序号为leafidx的节点的双亲节点序号
			if (pidx[2 * leafidx + 1] != INT_MAX_MY && pidx[2 * leafidx + 2] != INT_MAX_MY) //如果pidx[i]和pidx[i+1]都是正常值，那自然可以比较
			{
				if (myarray[pidx[2 * leafidx + 1]] <= myarray[pidx[2 * leafidx + 2]])
				{
					pidx[leafidx] = pidx[2 * leafidx + 1];
				}
				else
				{
					pidx[leafidx] = pidx[2 * leafidx + 2];
				}
			}	
			else if (pidx[2 * leafidx + 1] != INT_MAX_MY)
			{
				pidx[leafidx] = pidx[2 * leafidx + 1];
			}
			else
			{
				pidx[leafidx] = pidx[2 * leafidx + 2];
			}
		} //end while
	} //end for i

	//把数据从ptmparray拷贝回myarray
	for (int i = 0; i < length; i++)
	{
		myarray[i] = ptmparray[i];
	} //end for i

	//释放内存
	delete[] ptmparray;
	delete[] pidx;
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

	//（4）表插入排序（Table Insertion Sort）
	//时间复杂度：O(n^2)
	//空间复杂度：O(n)，空间换时间。
	//稳定算法

	//总结插入类排序：
	//最好情况时间复杂度O(n)，最坏情况时间复杂度O(n^2)，平均：O(n^2)。稳定算法

	//（5）希尔排序（Shell Sort）：缩小增量排序（Diminishing Increment Sort）。
	//思想：先追求元素的部分有序，然后再逐渐逼近全局有序。
	 //做法：先将整个待排序记录序列（数组元素）分割成若干个子序列分别进行直接插入排序，等到整个序列中的记录基本有序时，再对所有记录进行一次直接插入排序。
	 //多趟排序。
	//{1,2,10,16,18,45,23,99,42,67}
	//空间复杂度O(1)
	//平均时间复杂度O(nlogn)。说明希尔排序算法优于直接插入排序算法
	//不稳定算法

	//第三节 交换类排序
	//（1）冒泡排序（Bubble Sort）:起泡排序
	//{16,1,45,23,99,2,18,67,42,10}, {1,16,23,45,2,18,67,42,10,99}，大的数据往下沉，小的数据自然往上冒
	//{1, 16, 23, 2, 18, 45,42,10, 67, 99}
	//空间复杂度O(1)
	//最好情况时间复杂度O(n)。最坏情况时间复杂度O(n^2)。平均情况时间复杂度O(n^2)。
	//稳定算法

	//（2）快速排序（Quick Sort）
	//（2.1）快速排序概述及实现代码;qsort
	//选取任意一个元素作为枢轴（基准元素）。引入两个指针，low，high
	//（2.2）快速排序算法效率分析
	//时间复杂度O(n*递归调用深度),最好情况时间复杂度O(nlogn)。最坏情况时间复杂度O(n^2)。平均情况时间复杂度O(nlogn)
	//空间复杂度O(递归调用深度），最好情况空间复杂度O(logn)。最坏情况空间复杂度O(n)，平均情况空间复杂度O(nlogn)。
	//如果给定数组原本就是有序的，此时快速排序算法性能最差，退化成了冒泡排序算法。
	//不稳定算法：稳定性：{3，2，2}，{2，2，3}

	//第四节 选择类排序:就是每趟在待排序的元素中选择关键字最小（或者最大）的元素加入到有序子序列中。
	//（1）简单选择排序（Simple Selection Sort）:需要多趟排序才能得到最终结果。
	//时间复杂度O(n^2)，空间复杂度O(1)。
	//不稳定

	//（2）树形选择排序（Tree Selection Sort）
	//又叫锦标赛排序（Tournament Sort)。对简单排序的改进。
	//时间复杂度O(nLogn)。
	//空间复杂度O(n)。
	//稳定的算法。











	int arr[] = { 16, 1, 45, 23, 99, 2, 18, 67, 42, 10 };	
	int length = sizeof(arr) / sizeof(arr[0]); //数组中元素个数	
	//SmpSelSort(arr, length); //对数组元素进行简单选择排序
	TreeSelSort(arr, length); //对数组元素进行树形选择排序
	
	cout << "树形选择排序最终结果为：";
	for (int i = 0; i < length; ++i)
		cout << arr[i] << "  ";
	cout << endl;
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



