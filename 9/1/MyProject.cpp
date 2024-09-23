// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
#include <map>

using namespace std;
#pragma warning(disable : 4996) 

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//第9章 高级实用算法
	//第一节 用A* 搜索算法实现游戏中的寻路功能(A Star Pathfinding Algorithm)
	//（1）A* 寻路算法的基本概念描述
	//（2）A* 寻路算法的细节阐述
	//a)寻路消耗公式：f代表寻路消耗。g代表离起点距离。h代表离终点距离(计算h用到的公式叫曼哈顿距离)。
	// f = g+h，  寻路消耗 = 离起点距离 + 离终点距离
	//b)开启和关闭列表：用容器vector或者list来保存算法实现过程中的一些重要点的信息
	//c)当前点（格子）的父节点（用于确定最终的寻路路径）













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




