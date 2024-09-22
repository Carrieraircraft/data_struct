// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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

//B树每个节点的定义
template <typename T,int M> //T代表数据元素的类型，M代表B树的阶
struct BTreeNode
{
	T data[M]; //数据/关键字
	BTreeNode<T,M>	*childs[M + 1]; //子节点指针数组
	BTreeNode<T, M>* parent; //父节点指针
	int size; //节点中实际数据个数

	BTreeNode() //构造函数
	{
		size = 0;
		for (int i = 0; i < M; ++i)
		{
			data[i] = -1; //随便给个比较特殊的值-1，这样跟踪调试时也好观察和辨认
		}
		for (int i = 0; i < (M + 1); ++i)
		{
			childs[i] = nullptr;
		}
		parent = nullptr;
	}
};

//B树的定义
template <typename T,int M>
class BTree
{
public:
	BTree() //构造函数
	{
		root = nullptr;
	}

	~BTree() //析构函数
	{
		ReleaseNode(root);
	}
private:
	void ReleaseNode(BTreeNode<T, M>* pnode)
	{
		if (pnode != nullptr)
		{
			for (int i = 0; i < (pnode->size + 1); ++i)
			{
				if (pnode->childs[i] != nullptr)
				{
					ReleaseNode(pnode->childs[i]);
				}
			}
		}
		delete pnode;
	}

private:
	BTreeNode<T, M>* root; //树根指针
};




int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//第三节  多路查找树
	//（1）B树：多路平衡查找树，B-
	//（1.1）基本概念、定义及基础实现代码
	//引入B树的主要目的：减少磁盘的IO操作
	//（1.2）B树的插入操作及实现代码
	//创建4阶B树：11，12，6，5，13，7，3，4，2，1，9，8，10
	//说明：a)4阶B树每个节点最少有一个数据，最多有3个数据
	      //b)新插入的数据总会落在最底层的叶子节点上。



	   







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


