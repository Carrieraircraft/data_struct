// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
#include <assert.h>
#include <queue>

#ifdef _DEBUG   //只在Debug（调试）模式下
#ifndef DEBUG_NEW
#define DEBUG_NEW new(_NORMAL_BLOCK,__FILE__,__LINE__) //重新定义new运算符
#define new DEBUG_NEW
#endif
#endif

//#include <boost/type_index.hpp>
using namespace std;
#pragma warning(disable : 4996) 

//------------------------------
namespace _nmsp1
{
	void scalc(int n)
	{
		int i, sum = 0;
		for (i = 1; i <= n; ++i)
		{
			sum = sum + 1;
		}
		cout << sum << endl;
	}

	void scalc2(int n)
	{
		int* array = new int[n];
		for (int i = 1; i <= n; ++i) //4n+4
		{
			array[i] = 2 * i;
		}
		//记得释放内存
		delete[] array;
	}

	void scalc21(int n)  //12*n   = O(n)
	{
		int i, j;
		if (n > 1)
			scalc21(n - 1);
		cout << "n=" << n << endl;
	}

	void scalc22(int n) //递归调用n次，n+(n-1)+(n-2)+....+1。等差数列求和公式 = n(n+1) /2 = n^2/2 + n/2
	{                   //O(n^2)
		int* p = new int[n];
		if (n > 1)
			scalc21(n - 1);
		cout << "n=" << n << endl;
		delete[]p;
	}

	void scalc3(int n) //空间复杂度O(n)
	{
		//注意这里的动态二维数组的初始化代码
		int** array;
		array = new int* [n]; //4n
		for (int i = 0; i < n; ++i)
			array[i] = new int[n]; //每执行一次占用4n个字节。一共占用的是4n*n = 4n^2个字节的内存

		//注意动态二维数组的内存释放代码
		for (int i = 0; i < n; i++)
		{
			delete[] array[i];
		}
		delete[] array;
	}
}

int main()
{		
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口
	
	//第1章 基本概念、算法复杂度、编程环境介绍
	//第二节 算法的效率度量
	//（2）算法的空间复杂度分析:运行时所需要的存储空间与问题规模之间的增长关系。
	//大O空间复杂度表示法：有公式S(n) = O(f(n))。
	//a)O(1)：常数阶空间复杂度。需要固定大小内存空间的情形也叫做算法原地工作。
	//b)O(n)：线性阶空间复杂度。 
	   //如果每次递归调用所需要的内存空间大小固定不变，那么算法的空间复杂度一般都等于递归调用深度。
	//c)O(n^2)：平方阶空间复杂度表示法
	// 
	//一般如果没有刻意指明是时间复杂度还是空间复杂度时，一般指的都是时间复杂度。

	//第三节 C++编程环境介绍
	//Visual Studio ,不建议Visual Studio 2005更老。
	//Visual Studio 2019集成开发环境
	//（1）C++编程环境搭建说明
	//（2）创建最基本的能运行的C++程序
	//“Viusla Studio 2019创建新C++项目”，控制台
	  //ctrl+F5
	//（3）Visual Studio中程序的调试方法
	//1. 普通的断点调试（跟踪调试
	//F9 ：加/减断点
	//F5： 执行程序，执行到断点停止
	//F10：从当前停下来的程序代码行开始运行
	//F11：跳入到函数中继续跟踪调试，Shift+F11跳回到该函数的调用处继续往下跟踪调试
	//2. 学会调试时查看内存中的内容
	//alt+6
	//3. 快速监视窗口
	//shift+F9




	_nmsp1::scalc21(5);
	
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


