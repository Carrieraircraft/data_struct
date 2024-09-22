// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include <iomanip>

using namespace std;
#pragma warning(disable : 4996) 

class FibonacciSeq
{
public:
	//参数n，表示要求第n个斐波那契数，注意n从0开始编号
	int Calc(int n)
	{
		if (n == 0)
			return 0;
		else if (n == 1)
			return 1;

		//定义dp数组，给初值
		int* dp = new int[n + 1]; //因为n从0编号，所以如果n=4，实际开辟的空间就是5个
		dp[0] = 0;
		dp[1] = 1;

		//从前向后给值
		for (int i = 2; i <= n; ++i) //n从0开始，所以这里是 <=n
		{
			dp[i] = dp[i - 1] + dp[i - 2];
		} //end for

		int rtnvalue = dp[n]; //因为内存将释放，把要返回的数据先保存起来

		//可以考虑把dp内容输出看看
		for (int i = 0; i <= n; ++i)
		{
			cout << dp[i] << "  ";
		}
		cout << endl;

		delete[] dp; //释放内存
		return rtnvalue;
	}
};

//0-1背包相关类（二维数组实现）
class BackPack_01
{
public:
	void Calc()
	{
		int wpary_weight[] = { 2,3,4,5 }; //物品重量
		int wpary_price[] = { 3,4,5,8 }; //物品价值

		int wpary_weight_size = sizeof(wpary_weight) / sizeof(int); //物品重量数组大小
		int wpary_price_size = sizeof(wpary_price) / sizeof(int); //物品价值数组大小

		if (wpary_weight_size != wpary_price_size)//物品重量数组中元素数量不可能不等于物品价值数组中元素数量
			return;

		int pkg_capacity = 8; //背包容量

		//定义二维数组大小行数比物品数量大1，列数比背包容量大 1
		int lines = wpary_weight_size + 1; //行数
		int columns = pkg_capacity + 1; //列数
		int* dp = new int[lines * columns]; //这里相当于定义一维数组，后续准备当二维数组用。

		memset(dp, 0, lines * columns * sizeof(int));


#define E(i,j) (ETO(i,j,columns)) //方便把二维数组的下标转化为一维数组的下标

		//双循环给dp值
		//i:1~4，代表行，物品数量
		for (int i = 1; i <= wpary_weight_size; ++i) //注意i,j的初值和终值不要写错
		{
			//j：1~8,代表列，即背包承载量（容量）
			for (int j = 1; j <= pkg_capacity; ++j)
			{
				int ipack_w = j; //背包当前的承重记录下来
				if (wpary_weight[i - 1] > ipack_w)
				{
					//如果物品重量 大于当前背包能够承载的重量，装不下，则
					//根据递推公式：如果第k件物品太重无法放入背包wk > w，则dp(k,w) = dp(k-1,w)：
					//一维数组当二维数组用，比如a[i][j] = a[i *列数+j]
					dp[E(i, j)] = dp[E(i - 1, j)]; 
				}
				else
				{
					//如果第k件物品可以装入背包（wk<=w)，则：
					//根据递推公式： dp(k,w) = max( dp(k-1,w),   dp(k-1 , w - wk) + vk);
					int tmpvalue1 = dp[E(i - 1, j)]; 
					int tmpvalue2 = dp[E(
						(i - 1), (j - wpary_weight[i - 1])
					)]
						+ wpary_price[i - 1];

					dp[E(i, j)] = max(tmpvalue1, tmpvalue2); //取两者中的最大值
				}
			} //end for j
		} //end for i

		//输出一下dp数组信息，看是否是想要的值
		for (int i = 0; i <= wpary_weight_size; ++i) //注意i和j的初值和终值，不要写错，因为是输出所以从0开始
		{
			for (int j = 0; j <= pkg_capacity; ++j)
			{
				cout << setw(5) << dp[E(i, j)]; //setw:保持输出对齐，#include <iomanip>
			}
			cout << endl; //换行
		}

		cout << "背包在承载范围内所装的物品最大价值总和是： " << dp[E(wpary_weight_size, pkg_capacity)] << endl;	
		
		//开始回溯，倒推哪些物品装入了背包中：
		int jendidx = pkg_capacity;
		for (int i = wpary_weight_size; i >= 1; --i) //物品数量倒着推
		{
			if (dp[E(i, jendidx)] == dp[E((i - 1), jendidx)])
			{
				//没有装第i号物品 
				//啥也不用干
			}
			else
			{
				//装了第i号物品
				cout << "编号(从1算起)为" << i << "的物品被装入了背包!" << endl;
				jendidx -= wpary_weight[i - 1]; //把该号物品的重量去掉
			}
		}//end for i

		delete[] dp;
		return;
	}

	//二维数组下标转一维，用以计算
	//i,j：传递进来的二维行和列下标
	//column：一行有多少个元素
	//返回值：一个一维下标
	int ETO(int i, int j, int column)
	{
		return i * column + j;
	}
};


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//第8章 算法设计方法
	//第四节  动态规划算法
	// Dynamic Programming Algorithm：DP
	// 将问题分解成若干子问题并保存子问题的解从而更快速求得原问题的解，记忆化搜索。
	// 用DP算法写出的代码大概分2种：1：自顶向下【递归】。2：自底向上，递推写法。
	// 动态规划算法解题需要的步骤：
	// a)确定dp数组（一维或者二维）以及dp数组下标的含义。这里的dp数组一般称为状态转移数组
	// b)求得dp递推公式（状态转移方程）并确定dp数组初始值；
	//	     其中求dp递推公式是动态规划中的最重点也是最难点。
	// c)确定遍历顺序（从前向后或者从后向前等等）
	// d)必要时输出dp数组内容以确定程序执行结果的正确性。
	// 
	//（1）斐波那契数列 - LeetCode网站第509题
	//F(n)
	//F(0) = 0,F(1) = 1
	//F(n) = F(n-1) + F(n-2)，其中n>1。
	//0,1,1,2,3,5,8,13,21.....
	//给定n，计算F(n)，也就是计算第n个斐波那契数列（注意n从0开始编号）。
	
	//dp[i]表示第i个斐波那契数的值是合适的。
	//dp[i] = dp[i-1]+dp[i-2]。dp[0]=0,dp[1] =1
	//确定遍历顺序：从前向后遍历合适


	//（2）爬楼梯 - LeetCode网站第70题
	//一个楼梯有n级台阶，如果每次只能向上跨1级或者2级台阶，那么走上第n级台阶有多少种走法
	//测试数据：n=1。
	//结果：一种走法，向上迈一步。数组{1}
	
	//测试数据：n=2。
	//结果：二种走法，a)一次跨一级，走2次。
	//                b)直接一次向上跨2几级。
	//{1,1}或者{2}

	//测试数据：n=3。
	//主要问题：是否能够通过n=1和n=2时的情形进行推导。
	//{1,2}——1级台阶的走法法向上跨2级台阶
	//{1,1,1} {2,1}——2级台阶的走法向上跨1级台阶

	//测试数据：n=4。
	//{1, 1,2}或者{ 2,2 }——2级台阶的走法向上跨2级台阶
	//{1,2,1}  {1,1,1,1} {2,1,1}——3级台阶的走法向上跨1级台阶

	//解题步骤：
	//dp数组中的dp[i]表示上到第i级台阶的方法有dp[i]种
	//本案例递推公式dp[i] = dp[i-1]+dp[i-2]
	//       根据初始条件，dp[0]无需初始化（这个值不要用，因为没有意义），
    //        dp[1] = 1,dp[2] = 2；
	//确定遍历顺序：最后一个数字式前两个数字之和，所以从前向后遍历时非常合适的。

		
	//（3）0 - 1背包问题——用二维数组实现
	//问题描述：n种物品,每种物品只有1个，每种物品有自己的重量和自己的价值
	   //    有一个背包，最多能承重的重量（容量）为m。
	   //求：这个背包最多能够装价值为多少的物品。
	//测试数据： 假设背包最多能承重的重量为8，共有4种物品。
	//设：
		//k：共有k种物品可以往背包里放（并不代表这k种物品都已经放入到背包中）。
		//w：背包最多能承重的重量（或表示背包已经装入的重量）
		//dp(k,w)：在背包最多能承载的重量为w，共有k种物品可以往背包里放的前提下，
				   //该背包能装的物品的最大价值
		  //dp（4,8） = 12;
		//编码时可以把dp(k,w)看成是一个二维数组，即定义的大小是dp[k+1][w+1]。

	//现在，反推一下dp(4,8)的值（最大价值）看一看能否得到要装入的物品信息
	          //（有时反推比较容易得到递推公式）
	//a：如果放入第4件物品，那么dp(4,8)就可以转化为dp(3,3)+8
	          //dp(3,3)+8  => dp(4,8)
	//b：如果不放入第4件物品，那么dp(4,8)就可以转化成d[(3,8)

	//c：接着反推左侧分支dp(3,3)+8：
	    // 如果放入第3件物品，那么因为第3件物品重量为4，装不进去，所以结论是无法放入第三件物品
	    //dp(2,3)+8 => dp(3,3)+8
		// 
	//d：推dp(2,3)+8.....

	//针对图8.4.3_3 ：叶节点：
	//dp(1,0) = 0 , dp(1,0） + 4 + 8 = 12
	//dp(0,1) = 0， dp(0,1） + 3 + 8 = 11
	//dp(0,3) = 0， dp(0,3)  + 8 = 8

	//本案例递推公式如下：
	//a）如果第k件物品太重无法放入背包,则：
	//   dp(k,w) = dp(k-1,w);
	//b) 如果第k件物品可以放入背包，则
	//   dp(k,w) = max( dp(k-1,w),   dp(k-1 , w - wk) + vk);
	  //其中：max表示取圆括号中两个数的最大值，wk代表k物品的重量， vk代表k物品的价值。

	//如何初始化dp？







	//FibonacciSeq myobj;
	//int rtnvalue = myobj.Calc(14);
	//cout << "第14个（编号从0开始）斐波那契数是：" << rtnvalue << endl;
	//

	BackPack_01 myobj;
	myobj.Calc();


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




