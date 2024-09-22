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
	void calc4(int n)
	{
		int i = 100;
		int j = 15;
		int sum = i + j+n;
		cout << sum << endl;
	}

	void calc5(int n)
	{
		int i = 1;
		while (i <= n)
		{
			i = i * 2; //i=i*3
		}
	}

	void calc6(int n)
	{
		int i = 1;
		for (int count = 0; count < n; ++count)
		{
			while (i <= n)
			{
				i = i * 2; //i=i*3
			}
		}
	}

	void calc7(int n)
	{
		int sum = 0;
		for (int i = 1; i <= n; ++i)
		{
			sum += i;
		}
	}

	void calc8(int n)
	{
		int sum = 0;
		for (int i = 1; i <= n; ++i)
		{
			for (int j = 1; j <= n; ++j)
			{
				sum++;
			}
		}
	}

	void calc81(int n)
	{
		int sum = 0;
		for (int i = 1; i <= n; ++i)
		{
			for (int j = i; j <= n; ++j) //n+(n-1)+(n-2)+....+1   -》    1+2+3+4+...+n :等差数列求和公式
			{                                                  // = n(n+1)/2 = n^2 / 2 + n / 2
				sum++;
			}
		}
	}

	void calc9(int m, int n)
	{
		int sum = 0;
		for (int i = 1; i <= m; ++i)
		{
			for (int j = 1; j <= n; ++j)
			{
				sum++;
			}
		}
	}

	void calc10(int m, int n)
	{
		int sum1 = 0;
		for (int i = 1; i <= m; ++i)
		{
			sum1 += i;
		}

		int sum2 = 0;
		for (int j = 1; j <= n; ++j)
		{
			sum2 += j;
		}
	}

	void calc11(int array[], int n, int x)
	{
		int pos = -1;
		for (int i = 0; i < n; ++i)
		{
			if (array[i] == x)
			{
				pos = i;
				break;
			}
		}
		if (pos == -1)
			cout << "没找到值为" << x << "的元素" << endl;
		else
			cout << "找到了值为" << x << "的元素，其在数组中的位置下标为：" <<pos <<  endl;
	}
}

int main()
{		
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口
	
	//第二节 算法的效率度量
	//（1）算法的时间复杂度分析
	    //3. 常见算法时间复杂度分析
	      //a)O(1)：常数阶时间复杂度
	      //b)O(logn),O(nlogn):
	        //O(logn)：对数阶时间复杂度。
	        //O(nlogn):线性对数阶时间复杂度。
	      //c)O(n)：线性阶时间复杂度。
	      //d)O(n^2)、O(m*n)
	        //O(n^2)：平方阶时间复杂度表示法。
	        //O(m*n)：
	      //e)O(m+n)：
	      //f)最好、最坏、平均情况时间复杂度：
	        //最好情况时间复杂度，最坏情况时间复杂度，平均情况时间复杂度
			// 
		//4. 常见算法时间复杂度总结
	     //a)顺序执行的语句与问题规模n无关，不管1000行还是10000行代码
	     //b)算法中若存在循环语句，只需要挑选循环中某基本语句分析其执行次数与问题规模n的关系。
	     //c)对于嵌套的双重甚至多重循环，只需要关注最深层循环的循环次数就可以了。
	     
	     //常见算法时间复杂度：
	     //O(1)：常数阶
	     //O(logn):对数阶
	     //O(n)：线性阶
	     //O(nlogn)：线性对数阶
	     //O(n^2)：平方阶
	     //O(n^3)：立方阶。由平方阶、立方阶，扩展出k次方阶用O(n^k)表示。
	     //O(2^n)：指数阶
	     //O(n!)：阶乘阶
	     //关系式：常用算法时间复杂度所耗费的时间从小到大（数据量级从小到大）的排列顺序。
	     //O(1) <  O(logn) < O(n) < O(nlogn) < O(n^2) < O(n^3) < O(2^n) < O(n!) < O(n^n)
	     //写出阶数更低的算法是每个开发者都应该追求的目标。
	     //O(2^n) 、O(n!) 、 O(n^n)：非多项式量级的时间复杂度。
	     //O(1) 、  O(logn) 、 O(n) 、 O(nlogn)、 O(n^2) 、 O(n^3)：多项式量级的时间复杂度。
	     //考题：T(n) = O(n^3+n^2logn)；
	        //T(n) = O(n^3) + O(n^2 * logn)
	        //O(n^3) = O(n^2 * n)
	        // O(n) < O(nlogn) 
	        // O(n^2 * logn)的数量级 小于 O(n^3)数量级。
	        //T(n) = O(n ^ 3)
	     
	     
	      


	int asz[5] = { 1,2,3,4,5 };
	_nmsp1::calc11(asz, 5, 3);

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


