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


//调整以curpos为根的子树为大顶堆（这里要一直向下调整到尾部叶子才能结束）
template<typename T>
void AdjustDown(T myarray[], int length, int curpos) //length:堆中元素个数，curpos：当前开始调整的位置
{
	int i = curpos; //4，当前节点下标
	int j = 2 * i + 1; //9：左子节点下标
	while (j < length) //i有左子节点
	{
		//找左右子节点中值比较大的节点，让j指向该节点
		if (j < length - 1) //i也有右子树
		{
			if (myarray[j] < myarray[j + 1]) //如果左子节点<右子节点值
				j = (j + 1); //让j始终指向值最大的子节点
		}

		if (myarray[i] >= myarray[j]) //父节点保持值最大
			break; //不需要调整直接break;

		//这里到这里表示孩子节点比父亲节点大，那么就要进行父子位置交换了
		T temp = myarray[i];
		myarray[i] = myarray[j];
		myarray[j] = temp;

		//交换数据之后，可能就会影响到下一层了。所以要继续向下调整
		i = j;
		j = 2 * i + 1;
	}//end while
	return;
}

//把最大值从大顶堆中删除掉，把尾元素移动到首部并且继续调整为大顶堆
template<typename T>
void RemoveMaxValue(T myarray[], int length) //length：堆中元素个数
{
	if (length == 0) //就一个元素了，就不需要调整了，本身就认为是堆了
		return;

	T temp = myarray[0]; //该位置元素值最大
	myarray[0] = myarray[length]; //将最后一个元素放到最上面位置，等价于最上面位置元素被删除了
	myarray[length] = temp;

	AdjustDown(myarray, length, 0);
	return;
}

//堆排序（从小到大）
template<typename T>
void HeapSelSort(T myarray[], int length)
{
	//(1)由一个无序序列建成一个大顶堆
	int curpos = length / 2 - 1; //非叶子节点的位置
	while (curpos >= 0)
	{
		//要从当前节点向下调整的
		AdjustDown(myarray, length, curpos);
		curpos--;
	} //end while

	//(2)通过大顶堆来进行排序
	for (int i = 0; i < length; ++i)
	{
		RemoveMaxValue(myarray, length - i - 1); //把最大值从大顶堆中删除掉，并重新整理使之再次变成大顶堆
	} //end for i
	return;
}

//2路归并，该函数是归并排序的核心函数，用于把两个有序子序列归并为一个
//left：指向第一个序列开头元素，mid：指向第一个序列末尾元素，right：指向第二个序列末尾元素。
//通过left,mid,right指定要归并的两个子序列的范围（这两个子序列相邻）
template <typename T>
void Merge(T myarray[], T* pResult, int left, int mid, int right, int length) //length用于显示信息目的
{
	cout << "Merge():left,mid,right=" << left << "," << mid << "," << right;
	cout << "|元素值begin:";
	for (int i = 0; i < length; ++i) cout << myarray[i] << "  ";

	//把myarray指定的left到right范围内的数据先复制到pResult(临时空间)中
	for (int i = left;i <= right; ++i)
	{
		pResult[i] = myarray[i];
	} //end for i

	int curpos1 = left; //第一个序列的开始元素
	int curpos2 = mid + 1; //第二个序列的开始元素
	int curpos3 = left; //最终合并好的序列的开始元素位置
	while (curpos1 <= mid && curpos2 <= right)
	{
		if (pResult[curpos1] <= pResult[curpos2]) //将较小值赋给myarray，这里的比较符可以保证该算法的稳定性
		{
			myarray[curpos3] = pResult[curpos1];
			curpos1++;
		}
		else
		{
			myarray[curpos3] = pResult[curpos2];
			curpos2++;
		}
		curpos3++;
	} //end while

	//如果两个子序列元素数目不同，则这里要单独处理
	while (curpos1 <= mid) //子序列1比子序列2长
	{
		//把子序列1中剩余的内容放入到myarray中去
		myarray[curpos3] = pResult[curpos1];
		curpos1++;
		curpos3++;
	}

	while (curpos2 <= right) //子序列2比子序列1长
	{		
		myarray[curpos3] = pResult[curpos2];
		curpos2++;
		curpos3++;
	}
	cout << "|元素值end:";
	for (int i = 0; i < length; ++i) cout << myarray[i] << "  ";
	cout << endl;
	return;
}

//归并排序重载函数
template <typename T>
void MergingSort(T myarray[], T* pResult, int left, int right, int length) //length用于显示信息目的
{
	if (left >= right)
		return; //递归出口

	int mid = (left + right) / 2; //中间分开

	MergingSort(myarray, pResult, left, mid, length); //对左半部分进行归并排序。
	MergingSort(myarray, pResult, mid+1, right, length); //对左右部分进行归并排序。

	//上面因为左半部分归并排序完成，右半部分归并排序完成，所以下面是合并左半部分和右半部分了
	Merge(myarray, pResult, left, mid, right, length);

	return;
}

//归并排序入口（从小到大排序）
template <typename T>
void MergingSort(T myarray[], int length)
{
	T* pResult = new T[length]; //新数组，用于保存结果

	MergingSort(myarray, pResult, 0, length - 1, length); //调用重载函数

	delete[]pResult;
	return;
}


//非递归程序编写方法
template <typename T>
void MergingSort_noRecu(T myarray[], int length)
{
	if (length <= 1) //不超过1个元素的数组，没必要排序
		return;

	T* pResult = new T[length]; //新数组，用于保存结果

	//标示两个子序列位置用
	int left,mid,right;

	int jianGe = 1; //间隔，开始时元素是紧挨着的两个比较，两个元素之间下标间隔是1
	int subseqTotal = length; //当前子序列数量，开始时一个元素算一个子序列
	int gbts = 0; //归并趟数
	while (subseqTotal > 1) //只要没有最终合并成1个序列，就一直循环
	{
		gbts++;
		cout << "第" << gbts << "趟归并：-----------" << endl;
		for (int i = 0; i < length; i += (jianGe * 2))
		{
			left = i;
			mid = left + jianGe - 1;
			if (mid >= length)
				break;

			right = mid + (mid - left + 1);
			if (right >= length) right = (length - 1); //保证right合法

			//必须要保证left,mid,right都是合理值
			if (left <= mid && right > left && right > mid)
			{
				//肯定是两个序列，能合并
				Merge(myarray, pResult, left, mid, right, length); 
				subseqTotal--; //两个序列合并成一个，这里自然减少1
			}
			else
			{
				//不能合并，这次for循环退出
				break;
			}			 
		}//end for i
		jianGe *= 2;		 
	} //end while;

	delete[]pResult;
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

	//（3）堆排序（Heap Sort）:基于堆
	//（3.1）堆的基本概念：有序的完全二叉树
	//a)大顶堆（大根堆/最大堆）：父节点大于等于子节点的值
	//b)小顶堆（小根堆/最小堆）：父节点小于等于子节点的值
	// 
	//（3.2）堆排序算法
	//如果实现从小到大，则使用大顶堆比较方便。（从大到小，则使用小顶堆比较方便）
	//堆排序：利用堆（大顶堆或者小顶堆）进行排序的方法。
	
	//（3.3）堆中元素的插入和删除
	//a)向大顶堆中插入新元素
	//b)从大顶堆中删除一个元素
	//总结：不管大顶还是小顶堆，插入新元素都是不断向上调整该元素。删除老元素都是不断向下调整被填补的元素。

	//（3.4）堆排序算法效率分析
	//适合排序数据比较多
	//构建初始堆的时间复杂度为O(n)，重新构建堆的时间复杂度是O(nlogn)。
	//总体来说，堆排序时间复杂度为O(nLogn)，比很多时间复杂度为O(n^2)的排序算法要好很多。
	//堆排序空间复杂度为O(1)。
	//不稳定算法。

	//第五节 归并排序（Merging Sort）:把两个或者多个已经有序的序列合并成一个
	// （1）基本概念、实现代码、复杂度分析
	//2路归并排序。3路，4路
	//归并排序算法的时间复杂度是O(nlogn)。空间复杂度O(n+logn) = O(n)。
	//（2）非递归实现方式











	int arr[] = { 16, 1, 45, 23, 99, 2, 18, 67, 42, 10 };	
	int length = sizeof(arr) / sizeof(arr[0]); //数组中元素个数	
	//SmpSelSort(arr, length); //对数组元素进行简单选择排序
	//TreeSelSort(arr, length); //对数组元素进行树形选择排序
	//HeapSelSort(arr, length); 
	//MergingSort(arr, length); //对数组元素进行归并排序
	MergingSort_noRecu(arr, length);//对数组元素进行归并排序(非递归)

	
	//cout << "树形选择排序最终结果为：";
	//cout << "堆排序最终结果为：";
	cout << "归并排序结果为：";
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



