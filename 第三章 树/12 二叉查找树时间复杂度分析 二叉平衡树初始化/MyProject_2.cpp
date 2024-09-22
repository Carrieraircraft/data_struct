// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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
	//平衡二叉树中每个节点的定义
	template <typename T> //T代表数据元素的类型
	struct AVLNode
	{
		T   data; 
		AVLNode* leftChild; //左子节点指针
		AVLNode* rightChild; //右子节点指针
		int  balfac; //平衡因子
	};

	//平衡二叉树的定义
	template <typename T>
	class AVLTree
	{
	public:
		AVLTree()//构造函数
		{
			root = nullptr;
		}
		~AVLTree() //析构函数
		{
			ReleaseNode(root);
		}
	private:
		void ReleaseNode(AVLNode<T>* pnode)
		{
			if (pnode != nullptr)
			{
				ReleaseNode(pnode->leftChild);
				ReleaseNode(pnode->rightChild);
			}
			delete pnode;
		}
	private: 
		AVLNode<T>* root; //树根指针
	};
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//第3章 树
	//第二节  二叉树
	//（10）平衡二叉树（Balanced Binary Tree）:平衡二叉搜索树，简称AVL树（平衡树），Adelson-Velsky   Landis。
	//（10.1）基本概念、定义及基础实现代码
	//平衡二叉树，首先是一棵二叉查找树，在构建这棵二叉查找树的过程中进行平衡化的处理形成二叉平衡树
	 //性质：a)他的左子树和右子树都是平衡二叉树。b)任一节点的左子树和右子树的高度之差不超过1.
	//引入平衡因子BF（Balance Factor)概念：该节点的左子树高度减去他的右子树高度（或右子树高度减去左子树高度）。
	  //那么作为一棵平衡二叉树上任一节点的平衡因子只能是-1、0、1三个值中的一个。即：
		//节点的平衡因子 = 左子树高度 - 右子树高度。




	


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




