// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
#include <iomanip>
#include <list>
#include <map>
#include <set>

#pragma warning (disable: 4996) 
using namespace std;


//回溯算法：组合
class CBackTracking_CB
{
public:
	//构造函数
	CBackTracking_CB(int tmpn,int tmpk)
	{
		n = tmpn;
		k = tmpk;
	}

	//递归函数
	//startidx：因为返回范围1到n中所有可能的k个数的组合，所以第一次调用该函数时startidx = 1;
	void MyBackTrack(int startidx)
	{
		if (n < k)
		{
			cout << "n不可以小于k!";
			return;
		}
		//以下内容用于显示目的begin---------------
		static int idiguitimes = 0; //统计递归次数
		cout << "递归" << idiguitimes << "次。startidx=" << startidx << "  n=" << n;
		idiguitimes++;
		if (path.size() == k)
		{
			cout << "  本次是递归出口，path={ ";
			for (auto iter = path.begin(); iter != path.end(); ++iter)
			{
				cout << *iter << "  ";
			}
			cout << "}";
		}
		cout << endl;
		//以上内容用于显示目的end---------------

		//注意仔细寻找递归出口
		if (path.size() == k) //这就是递归出口
		{
			allcombi.push_back(path);
			return;
		}

		//for (int i = startidx; i <= n; ++i)//分别以每个数为开头尝试和后续的数组合
		for (int i = startidx; i <= (n-(k-(int)path.size())+1); ++i) //剪枝优化
		{
			//把第一个数放进去
			path.push_back(i);

			//其余的数字由下面的递归函数放进去，将这些数字放入到allcombi保存也由下面这个递归函数解决
			MyBackTrack(i + 1); //递归，注意传递进去的参数，往树形结构的纵深方向走

			//这是关键的一步：回溯的过程——前面自己放入一个数字，这里自己弹出去，为后续放和其他数字的组合腾出地方
			//比如找到组合[1,2]，必须要把末尾的2弹出去，下次递归才能得到[1,3]，不把末尾的2弹出去，下次就变成了[1,2,3]
			path.pop_back();
		} //end for
	}

	//显示结果
	void DispResult()
	{
		int icount = 0;
		for (auto iter = allcombi.begin(); iter != allcombi.end(); ++iter)
		{
			list<int>* tmplist = &(*iter);
			for (auto iter2 = tmplist->begin(); iter2 != tmplist->end(); ++iter2)
			{
				cout << *iter2 << " ";
			}
			icount++;
			cout << endl; //换行
		} //end for
		cout << "一共输出了(" << icount << ")组数据" << endl;
		return;
	}

private:
	int n;
	int k;
	list < list<int>  >  allcombi; //里边每个元素代表一个组合，所以里面的可能的内容是{1,2} {1,3} {1,4} {2,3} {2,4} {3,4}
	list<int> path; //里边每个元素代表一个组合中的数字，比如{2,4}是一个组合，path中就包含2个元素，分别是2、4
};


//回溯算法：组合2
class CBackTracking_CB2
{
public:
	//递归函数
	void MyBackTrack(int a[], int asize, int target,  //a：数组名，asize：数组元素个数，target：目标数字
		int sum, //统计一个组合的和值，判断其是否等于target
		int startidx //标记数组中当前元素下标（递归的起始位置），也指明下个for循环的搜索位置
	)
	{
		//以下内容用于显示目的begin-------------------------
		static int idiguitimes = 0; //统计递归次数
		cout << "递归" << idiguitimes << "次。startidx=" << startidx;
		idiguitimes++;
		if (sum >= target)
		{
			cout << "   本次是递归出口，sum = " << sum << ",target = " << target << ",path={";
			for (auto iter = path.begin(); iter != path.end(); ++iter)
			{
				cout << *iter << " ";
			}
			cout << "}";
		}
		cout << endl;
		//以上内容用于显示目的end-------------------------

		//注意仔细寻找递归出口
		if (sum > target) //值过大
			return; //递归出口

		if (sum == target) //找到了一组，记录下来
		{
			allcombi.push_back(path);
			return; //递归出口
		}

		//for (int i = startidx; i < asize; ++i)
		for(int i = startidx; i < asize && sum+a[i] <= target; ++i) //剪枝
		{
			path.push_back(a[i]); //元素放进去
			sum += a[i];
			MyBackTrack(a, asize, target,
				sum,
				i //注意下一层的startidx是从i开始（因为元素可以重复使用）
			);

			//递归完成后的回溯
			sum -= a[i];
			path.pop_back();
		}//end for
	}

	//显示结果
	void DispResult()
	{
		int icount = 0;
		for (auto iter = allcombi.begin(); iter != allcombi.end(); ++iter)
		{
			list<int>* tmplist = &(*iter);
			for (auto iter2 = tmplist->begin(); iter2 != tmplist->end(); ++iter2)
			{
				cout << *iter2 << " ";
			}
			icount++;
			cout << endl; //换行
		} //end for
		cout << "一共输出了(" << icount << ")组数据" << endl;
		return;
	}

private:
	list < list<int>  >  allcombi; 
	list<int> path;
};

//回溯算法：切割
class CBackTracking_DIV
{
public:
	//判断是否是回文串
	bool IsPalindrome(string a, int startidx, int endidx) //startidx：开始位置下标；endidx：结束位置下标
	{
		if (startidx >= endidx) //一个字符，肯定是回文
			return true;

		//非一个字符的回文子串判断
		do
		{
			if (a[startidx] != a[endidx])
				return false;

			startidx++;
			endidx--;
		} while (startidx < endidx);
		return true;
	}

	//递归函数
	void MyBackTrack(const string& a,
		int startidx  //控制切割位置
	)
	{
		//以下内容用于显示目的begin-----------
		static int idiguitimes = 0; //统计递归次数
		cout << "递归" << idiguitimes << "次。startidx=" << startidx;
		idiguitimes++;
		if (startidx >= (int)a.size())
		{
			cout << "   本次是递归出口，a.size() =" << a.size() << ",path={";
			for (auto iter = path.begin(); iter != path.end(); ++iter)
			{
				cout << *iter << "  ";
			}
			cout << "}";
		}
		cout << endl;
		//以上内容用于显示目的end-----------

		if (startidx >= (int)a.size()) //切割的位置已经在最后了
		{
			allcombi.push_back(path);
			return; //递归出口
		}

		for (int i = startidx; i < (int)a.size(); ++i)
		{
			if (IsPalindrome(a, startidx, i) == true) //是回文串
			{
				path.push_back(a.substr(startidx, i - startidx + 1)); //把这个区间的子串弄到path数组
			}
			else
			{
				continue;
			}
			MyBackTrack(a, i + 1); //往树形结构纵深方向走 

			//回溯
			path.pop_back();
		}//end for
	}

	//显示结果
	void DispResult()
	{
		int icount = 0;
		for (auto iter = allcombi.begin(); iter != allcombi.end(); ++iter)
		{
			list<string>* tmplist = &(*iter);
			for (auto iter2 = tmplist->begin(); iter2 != tmplist->end(); ++iter2)
			{
				cout << *iter2 << "  ";
			}
			icount++;
			cout << endl; //换行
		}//end for
		cout << "一共输出了(" << icount << ")组数据" << endl;
		return;
	}

private:
	list < list<string>> allcombi;
	list<string> path;
};

//n皇后问题
class CNQueen
{
public:
	CNQueen(int tmpn) //tmpn：代表n皇后
	{
		//初始化数据
		n = tmpn;
		solution.clear();
		path_1_c.clear();
		path_c_1.clear();
		L_Sub_Cset.clear();
		L_Add_Cset.clear();
	}

	//递归函数
	void MyBackTrack(int startidx) //startidx：当前行
	{
		if ((int)(path_1_c.size()) >= n)
		{
			solution.push_back(path_1_c);
			return; //递归出口
		}

		for (int i = 0; i < n; ++i) //控制着列
		{
			if (put_queen(startidx, i) == false) //不能放
				continue;

			//走到这里，能放并且已经放了
			MyBackTrack(startidx + 1);

			//恢复
			back_queen(startidx, i);
		} //end for
	}

	//显示结果
	void DispResult()
	{
		int icount = 0;
		for (auto iter = solution.begin(); iter != solution.end(); ++iter)
		{
			map<int, int >* tmpmap = &(*iter);
			for (auto iter2 = tmpmap->begin(); iter2 != tmpmap->end(); ++iter2)
			{
				cout << "(" << iter2->first << "," << iter2->second << ") ";
			}
			icount++;
			cout << endl; //换行
		}//end for
		cout << "一共输出了(" << icount << ")组数据" << endl;
		return;
	}

private:
	//判断是否能放置皇后，如果能，则放置，并设置相应的各种标记
	//成功放置则返回true，否则返回false
	bool put_queen(int x, int y) //x,y:要放置的皇后的位置
	{
		int cha = x - y;
		int he = x + y;

		if (L_Sub_Cset.find(cha) != L_Sub_Cset.end())
			return false; //该对角线被其他皇后占领了

		if (L_Add_Cset.find(he) != L_Add_Cset.end())
			return false; //该对角线被其他皇后占领了

		if (path_1_c.find(x) != path_1_c.end()) //该x位置（行）被其他皇后占领了
			return false;

		if (path_c_1.find(y) != path_c_1.end()) //该y位置（列）被其他皇后占领了
			return false;

		//设置占领标记
		L_Sub_Cset.insert(cha); //占领 左上/右下方向对角线
		L_Add_Cset.insert(he); //占领 右上/左下方向对角线
		path_1_c[x] = y; //x行被占领，同时，这个的size也标记着成功放置了几个皇后
		path_c_1[y] = x; //y列被占领
		return true;
	}

	//回溯皇后——皇后撤回时要还原一些数据
	void back_queen(int x, int y)
	{
		int cha = x - y;
		int he = x + y;
		
		//占领的 左上/右下方向对角线 还原
		L_Sub_Cset.erase(L_Sub_Cset.find(cha));
		L_Add_Cset.erase(L_Add_Cset.find(he));

		path_1_c.erase(path_1_c.find(x)); //x行被占领 还原
		path_c_1.erase(path_c_1.find(y)); //y列被占领 还原
		return;
	}

private:
	int n; //n皇后问题
	list < map<int, int>> solution; //这里保存着n皇后问题的所有摆放方法
	map<int, int> path_1_c; //保存皇后位置，key = x位置，value=y位置
	map<int, int> path_c_1;//保存皇后位置，key = y位置，value=x位置

	set<int> L_Sub_Cset; //保存已经被占领的 左上/右下方向对角线  的 行下标-列下标差值
	set<int> L_Add_Cset; //保存已经被占领的 右上/左下方向对角线  的 行下标+列下标和值
};

int main()
{	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//第8章 算法设计方法
	//第三节  回溯算法(Back tracking Algorithm)
	//暴力的穷举法来达成目的。回溯的意义在于探求所有可能的解
	//回溯能够解决的问题：组合问题，切割问题，子集问题，排列问题，棋盘问题（n皇后)等。
	//其能解决的问题一般可以抽象为一棵树形结构。
	//（1）组合问题 - LeetCode网站第77题
	//给定两个整数n和k，返回范围1到n中所有可能的k个数的组合
	//输入：n=4,k=2
	//结果：{1,2} {1,3} {1,4} {2,3} {2,4} {3,4}
	//通过回溯解决：回溯算法通过  递归  来控制for循环的嵌套层数（递归中的每一层代表一个for循环，
	    //下一层递归代表下一层for循环）。
	//对于组合问题，回溯算法可以通过 剪枝  操作来对代码进行优化
	//剪枝操作，就是缩小循环变量i的取值范围，目前的有用信息：
	 //a)一共要选取k个数字
	 //b)已经选择了的数字个数等于path.size();
	 //c)剩余还需要选取的数字个数等于k-path.size();
	    //n-(k-path.size()) + 1 ，就代表还需要选取的元素个数至多要从哪开始搜索。
	//（2）组合总和问题 - LeetCode网站第39题
	// 求和值为目标数字的元素组合
	//数组：{2,3,6,7}，目标数字7.结果：{7}，{2,2,3}
	//数组：{2,3,5}，目标数字8，结果：{2,2,2,2} {2,3,3} { 3,5}
	//三件事注意：a)确定好递归的出口代码；b)确定递归调用所提供的参数；c)回溯部分的处理代码
	//（3）分割字符串问题 - LeetCode网站第131题
	//aab，分割子串，使每个子串都是回文串。
	//a|a|b
	//aa|b
	//（4）n皇后问题 - LeetCode网站第51题
	//研究的是如何将n个皇后摆放在n*n的棋盘上并使皇后之间彼此不能攻击（任意两个皇后都不能处于同一行或者同一列或者同一条斜线上）
	//给定一个整数n，返回所有不同的n皇后问题的解决方案（有多少种摆放方式，每种摆放方式是如何摆放）







	//int n = 4;
	////找几个数的组合就是几重循环，这里k=2，所以是2层for循环
	//for (int i = 1; i <= n - 1; ++i)
	//{
	//	for (int j = i + 1; j <= n; ++j)
	//	{
	//		printf("{%d,%d}\n", i, j);
	//	}
	//}


	////给定两个整数n和k，返回范围1到n中所有可能的k歌数的组合
	//CBackTracking_CB myobj(4, 4); //参数1:n，参数2:k
	//myobj.MyBackTrack(1); //返回1到n中所有可能的k个数的组合，所以第一次调用给的参数是1
	//myobj.DispResult();//显示结果

	//int a[] = { 2,3,5 };
	//int asize = sizeof(a) / sizeof(int); //求数组元素个数
	//int target = 8;

	//CBackTracking_CB2 myobj2;
	//myobj2.MyBackTrack(a, asize, target, 0, 0);
	//myobj2.DispResult();

	/*string a = "aab";
	CBackTracking_DIV myobj3;
	myobj3.MyBackTrack(a, 0);
	myobj3.DispResult();*/

	CNQueen myobj4(8); //八皇后
	myobj4.MyBackTrack(0);
	myobj4.DispResult();

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



