﻿// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
#include  <assert.h>

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
	//红黑树中每个节点的定义
	template <typename T> //T代表数据元素类型
	class RBNode
	{
		T   data;
		RBNode* leftChild; //左子节点指针
		RBNode* rightChild; //右子节点指针
		RBNode* parentNd; //父节点指针，引入方便操作。
		bool isRed; //是否是红色节点，true：是。false：不是（而是黑色节点）
	};

	//红黑树的定义
	template <typename T>
	class RBTree
	{
	public:
		RBTree() //构造函数
		{
			root = nullptr;
		}
		~RBTree() //析构函数
		{
			ReleaseNode(root);
		}
	private:
		void ReleaseNode(RBNode<T>* pnode)
		{
			if (pnode != nullptr)
			{
				ReleaseNode(pnode->leftChild);
				ReleaseNode(pnode->rightChild);
			}
			delete pnode;
		}

	private:
		RBNode<T>* root; //树根指针
	};


	
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//第3章 树
	//第二节  二叉树
	//（11）红黑树（Red - Black Tree）
	//（11.1）基本概念、定义及基础实现代码
	//“平衡性调整”
	//“非严格平衡二叉树”：
	//红黑树（Read-Black Tree)，R-B树。是一种高效的二叉查找树。
	//发明者：Rudolf Bayer   1972年发明，当时被称为  对称/平衡二叉B树。
	//1978年由 Leo J.Guibas和Robert Sedgewick修改为了  红黑树。
	//相对平衡：任一节点左子树和右子树高度之差很可能会超过1.
	//红黑树性质：
	//a)每个节点要么是黑色，要么是红色，而根节点必须是黑色。
	//b)每个叶子节点都是黑色的空节点（Nil），这一点和其他树不同。
	     //也就是说叶子节点不存储数据。Nil可以（一般）不绘制出来。
	//c)任何相邻节点（用线条连接起来的节点比如当前节点的父或者子节点）不能同时为红色（红色节点不能相邻）；
		//理解：c.1)红节点是被黑色节点分隔开的   ；c.2)红色节点的两个孩子节点或者父亲节点必须是黑色的。
	       //c.3)从叶节点到根的所有路径上不可以有两个连续的红色节点。
	//d)红黑树左右子树高度差很可能会超过1甚至超过更多。红黑树的平衡性是指的是对于每个节点，从该节点到达其所能够
	     //到达的叶子节点的所有路径都包含相同数量的黑色节点（黑色节点数量称为 黑高度 或者 黑高，用于保证黑色节点的平衡性)。

	//总结：红黑树：a)黑色的根.b)黑色的叶子;c)红色节点不相邻（红色节点的父亲和孩子都是黑色节点）;
	      //d)当前节点到其所有叶节点包含的黑色节点数量相同。
	//为什么有AVL树还需要引入红黑树：a)AVL平衡性调整效率比较低。b)平衡性调整旋转次数少甚至不需要旋转只需要调整颜色（红色修改为黑色）。
	       //c)插入删除红黑树更快。    换句话说，但从搜索角度，AVL树更快。如果频繁进行插入和删除操作，因为红黑树需要
	           //更少的旋转，无疑效率会更高（红黑树的查找、插入、删除操作性能稳定）。

	//红黑树从根节点到叶子的最长路径不超过最短路径的两倍。
	//红黑树的高度大概2logn。红黑树的高度只比AVL树高1倍，在执行效率上差不太多。因为上面提到的优势，所以性能更好。

	//红黑树编程问题：
	//a)往往不需要考虑叶子节点，也就是那个黑色的空节点（nil）。
	//b)红黑树节点查找操作同二叉查找树的节点查找操作（SearchElem成员函数）完全一样，大家可以参考前面已经实现的代码。



	


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




