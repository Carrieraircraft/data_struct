// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
#include <assert.h>

#ifdef _DEBUG   //只在Debug（调试）模式下
#ifndef DEBUG_NEW
#define DEBUG_NEW new(_NORMAL_BLOCK,__FILE__,__LINE__) //重新定义new运算符
#define new DEBUG_NEW
#endif
#endif

//#include <boost/type_index.hpp>
using namespace std;
#pragma warning(disable : 4996) 
//#pragma warning(disable : 6386) 

//------------------------------
namespace _nmsp1
{	
	//冒泡排序（从小到大）
	template<typename T>
	void BubbleSort(T myarray[], int length)
	{
		if (length <= 1) //不超过1个元素的数组，没必要排序
			return;
				
		//外层循环只控制排序的趟数
		for (int i = 0; i < length - 1; ++i)
		{
			bool cgflag = false; //表本趟冒泡排序是否发生过记录交换，false：无；true：有
			//内层循环控制元素的大小比较和交换位置
			for (int j = 0; j < length - i - 1; ++j) //每趟比较的次数都会减少
			{
				if (myarray[j] > myarray[j + 1])  //前面的数据如果比后面的数据大
				{
					//交换元素位置
					T temp = myarray[j + 1];
					myarray[j + 1] = myarray[j];
					myarray[j] = temp;

					cgflag = true; //标记本趟冒泡排序发生过记录交换(可能1次或者多次)
				}
			} //end for j
			if (cgflag == false) //本趟冒泡排序没有发生过记录交换，表示整个冒泡排序结束
				break; 

			//每走一趟显示一下结果
			cout << "第" << i+1 << "趟冒泡排序结果为： ";
			for (int i = 0; i < length; ++i) cout << myarray[i] << "  ";
			cout << endl;
		} //end for i
		return;
	}
	
	//
	//分割函数：一趟快速排序的实现函数。该函数是快速排序算法实现的核心函数，返回枢轴位置下标
	template<typename T>
	int Partition(T myarray[], int low, int high) //low：低位置。high：高位置
	{	
		static int icount = 0;
		icount++;
		cout << "【当前Partition调用的次数是： " << icount << "】" << endl;

		//选取枢轴，就用最低位置指向的元素（首元素）作为枢轴即可
		T pivot = myarray[low]; //把枢轴保存起来				

		while (low < high )
		{			
			//先从高位置来
			while (low < high && myarray[high].data >= pivot.data) 
				high--;

			if (low == high) //如果原始集合已经是从小到大排序，这个条件就会成立
				break;

			if(low < high)
				myarray[low] = myarray[high];

			//再从低位来
			while (low < high && myarray[low].data < pivot.data)
				low++;

			if (low == high) //如果原始集合已经是从大到小排序，这个条件就会成立
				break;

			if (low < high)
				myarray[high] = myarray[low];

		} //end while (low < high)

		myarray[low] = pivot; //此时low与high相等
		return low;
	}

	template<typename T>
	void QuickSort(T myarray[], int low, int high,int length,int lvl=1) //lvl用于统计递归调用深度
	{
		//断言low值一定是小于high值的
		assert(low < high); //记得#include <assert.h>

		//调用者要保证low < high		
		cout << "【当前QuickSort递归调用深度是： " << lvl << "层】" ;
						
		int pivotpos = Partition(myarray, low, high);  //分割函数
		//输出中间结果看看：
		cout << "low = " << low << ";high = " << high << ";枢轴位置 = " << pivotpos << "。本趟快排结果为： ";
		for (int i = 0; i < length; ++i)
			cout << myarray[i].data << "【" << myarray[i].idx << "】   ";
		cout << endl;
		
		if(low < (pivotpos - 1))
			QuickSort(myarray, low, pivotpos - 1,length,lvl+1);//枢轴左侧子表做快速排序，即继续分割	

		if((pivotpos + 1) < high)
			QuickSort(myarray, pivotpos + 1, high,length,lvl+1);//枢轴右侧子表做快速排序，即继续分割
		
		return;
	}

	//快速排序（从小到大）
	template<typename T>
	void QuickSort(T myarray[], int length)
	{
		if (length <= 1) //不超过1个元素的数组，没必要排序
			return;

		int low = 0;  //低位置
		int high = length - 1; //高位置

		//调用重载函数
		QuickSort(myarray, low, high, length); //传递length值是为了显示中间的输出结果方便
	}	
}

struct tempstruc
{
	int data;    //值
	int idx;      //序号
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//tempstruc arr[] = {{10, 0}, { 10,1 }, {2,2}};
	//tempstruc arr[] = { {1, 0}, { 3,1 }, {3,2},{4,3},{5,4},{2,5} };
	tempstruc arr[] = { {1, 0}, { 3,1 }, {3,2},{3,3},{5,4},{5,5},{5,6},{4,7},{4,8},{4,9},{6,10},{6,11} };

	//int arr[] = {16,1,45,23,99,2,18,67,42,10};
	//int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	// 
	//int arr[] = { 10,9,8,7,6,5,4,3,2,1 };
	//int arr[] = { 10,10,2 };

	int length = sizeof(arr) / sizeof(arr[0]);   //数组中元素个数
	//_nmsp1::BubbleSort(arr, length);//对数组元素进行冒泡排序
	_nmsp1::QuickSort(arr, length);//对数组元素进行快速排序

	//cout << "冒泡排序结果为：";
	cout << "快速排序结果为：";
	for (int i = 0; i < length; ++i)
	{
		cout << arr[i].data << "【" << arr[i].idx << "】   ";
	}
	cout << endl; //换行
	
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件




