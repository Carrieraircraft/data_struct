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
	//树中每个节点的定义
	template <typename T> //T代表数据元素的类型
	struct BinaryTreeNode
	{
		T   data;
		BinaryTreeNode* leftChild,  //左子节点指针
			* rightChild;  //右子节点指针
	};

	//二叉查找树的定义
	template <typename T>
	class BinarySearchTree
	{
	public:
		BinarySearchTree() //构造函数
		{
			root = nullptr;
		}
		~BinarySearchTree() //析构函数
		{
			ReleaseNode(root);
		}

		//二叉树中序遍历代码（排序），方便测试时显示节点数据
		void inOrder()
		{
			inOrder(root);
		}
		void inOrder(BinaryTreeNode<T>* tNode)
		{
			if (tNode != nullptr)
			{
				//左根右
				inOrder(tNode->leftChild);
				cout << tNode->data << " ";
				inOrder(tNode->rightChild);
			}
		}

		//插入元素
		void InsertElem(const T& e) //不可以指定插入位置，程序内部会自动确定插入位置
		{
			InsertElem(root, e);
		}
		void InsertElem(BinaryTreeNode<T>*& tNode, const T& e) //注意第一个参数类型
		{
			if (tNode == nullptr) //空树
			{
				tNode = new BinaryTreeNode<T>;
				tNode->data = e;
				tNode->leftChild = nullptr;
				tNode->rightChild = nullptr;
				return;
			}
			if (e > tNode->data)
			{
				InsertElem(tNode->rightChild, e);
			}
			else if (e < tNode->data)
			{
				InsertElem(tNode->leftChild, e);
			}
			else
			{
				//要插入的数据与当前树中某节点数据相同，则不允许插入
				//什么也不做
			}
			return;
		}

		//查找某个节点
		BinaryTreeNode<T>* SearchElem(const T& e)
		{
			return SearchElem(root, e);
		}
		/*
		//递归方式实现查找某个节点
		BinaryTreeNode<T>* SearchElem(BinaryTreeNode<T>* tNode, const T& e)
		{
			if (tNode == nullptr)
				return nullptr;

			if (tNode->data == e)
				return tNode;
			if (e < tNode->data)
				return SearchElem(tNode->leftChild,e); //在左子树上左查找
			else
				return SearchElem(tNode->rightChild,e); //在右子树上左查找
		}
		*/
		//非递归方式实现查找某个节点
		BinaryTreeNode<T>* SearchElem(BinaryTreeNode<T>* tNode, const T& e)
		{
			if (tNode == nullptr)
				return nullptr;

			BinaryTreeNode<T>* tmpnode = tNode;
			while (tmpnode)
			{
				if (tmpnode->data == e)
					return tmpnode;

				if (tmpnode->data > e)
					tmpnode = tmpnode->leftChild;
				else
					tmpnode = tmpnode->rightChild;
			}
			return nullptr;		
		}

	private:
		void ReleaseNode(BinaryTreeNode<T>* pnode)
		{
			if (pnode != nullptr)
			{
				ReleaseNode(pnode->leftChild);
				ReleaseNode(pnode->rightChild);
			}
			delete pnode;
		}
	private:
		BinaryTreeNode<T>* root; //树根指针
	};


}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//第3章 树
	//第二节  二叉树
	//（9）二叉查找树（Binary Search Tree）：又名二叉搜索树(BST)，也称为二叉排序树（Binary Sort Tree）
	//（9.1）基本概念及定义
		//其存在的意义在于实现快速查找，当然也支持快速插入和删除
	//（9.2）常见操作
	//（9.2.1）插入操作
	//（9.2.2）查找操作





	_nmsp1::BinarySearchTree<int> mybtr;
	int myarray[] = { 23,17,11,19,8,12 };
	int acount = sizeof(myarray) / sizeof(int);
	for (int i = 0; i < acount; ++i)
	{
		mybtr.InsertElem(myarray[i]);
	}
	mybtr.inOrder(); //中序遍历	

	int val = 19;
	cout << endl; //换行
	_nmsp1::BinaryTreeNode<int>* tmpp;
	tmpp = mybtr.SearchElem(val);
	if (tmpp != nullptr)
	{
		cout << "找到了值为：" << val << "的节点。" << endl;
	}
	else
	{
		cout << "没找到值为：" << val << "的节点。" << endl;
	}

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




