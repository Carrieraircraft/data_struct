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

using namespace std;


int main()
{
	//（2）B + 树
	//（2.1）基本概念,
	//B+树与B树的不同点：
	 //a)B+树的所有非叶子节点中的数据都会包含在叶子节点中。
	 //b)B+树的所有叶子节点相连，从而构成了一个数据从小到大排列的链表。
	 // 
	//（2.2）B + 树的插入操作
	//创建一棵4阶的B+树： 11,12,6,5,13,7,3,4,2,1,9,8,10

	//（2.3）B + 树的删除操作
	//明确一下一棵B+树每个节点有多少个数据，以一棵5阶B+树为例
	 //a)一棵5阶B+树，每个节点最多有4个数据。
	 //b)根节点可以只有1个数据，非根节点至少有2个数据。



	
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误nm,
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件



