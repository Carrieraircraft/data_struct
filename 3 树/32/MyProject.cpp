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

//链式队列相关代码
namespace _nmsp1
{
//	//双亲表示法作为树存储结构时，树的节点结构定义
//	template <typename T> //T代表数据元素的类型
//	struct TreeNode
//	{
//		T data;  //数据域
//		int parent;  //指针域，父节点在数组中的下标
//	};
//
//#define MaxTreeSize 200 //树中能够保存的最大节点个数
//
//	//树的定义
//	template <typename T>
//	class Tree
//	{
//	public:
//		Tree() //构造函数
//		{
//			for (int i = 0; i < MaxTreeSize; ++i)
//			{
//				m_data[i].parent = -1; //-1表示目前还没有父亲，类似于空指针的作用
//			}
//			m_length = 0;
//		}
//
//	private:
//		TreeNode<T> m_data[MaxTreeSize]; //节点数组
//		int m_length; //树中包含的节点数量
//	};
	
	
	////孩子表示法 方案一作为树的存储结构时，树的节点结构定义
	//template <typename T,int treedeg> //T代表数据元素类型，treedeg代表树的度
	//struct TreeNode
	//{
	//	T data; //数据域
	//	TreeNode* child[treedeg]; //指针数组，其中的每个指针指向一个孩子节点

	//};

	////孩子表示法 方案二作为树存储结构时，树的节点结构定义
	//template <typename T> //T代表数据元素的类型
	//struct TreeNode
	//{
	//	T data; //数据域
	//	int degree; //度域，存放该节点的度
	//	TreeNode** child; //指针的指针
	//public:
	//	TreeNode(int tmpdegree) //构造函数
	//	{
	//		degree = tmpdegree; //该节点的孩子节点数量
	//		child = new TreeNode * [degree]; //相当于定义了degree个指向TreeNode对象的指针
	//		for (int i = 0; i < degree; ++i)
	//		{
	//			child[i] = nullptr;
	//		}
	//	}
	//	~TreeNode() //析构函数
	//	{
	//		delete[] child;
	//	}

	//};

//	//孩子节点结构：一个保存孩子下标的结构
//	struct ChildNode
//	{
//		int child; //孩子下标
//		ChildNode* next; //指向下一个相同的结构
//	};
//
//	//表头（父亲）节点结构
//	template <typename T> //T代表数据元素的类型
//	struct TreeNode
//	{
//		T data; //数据域
//		int parent; //父节点所在Tree结构中的m_data数组下标
//		ChildNode* firstchild;//通过该指针可以找到该节点的第一个孩子；
//	};
//
//#define MaxTreeSize 200 //树中能够保存的最大节点个数
//	template <typename T> //T代表数据元素的类型
//	class Tree
//	{
//	private:
//		TreeNode<T> m_data[MaxTreeSize]; //节点数组
//		int m_length; //树中包含的节点数量
//	};

	//孩子兄弟表示法作为树存储结构时，树的节点结构定义
	template <typename T> //T代表数据元素类型
	struct TreeNode
	{
		T data; //数据域
		TreeNode* firstchild; //指针域，指向第一个孩子节点
		TreeNode* rightbro; //指针域，指向右兄弟节点
	};
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//（13）树、森林与二叉树的转换
	//（13.1）树的存储结构
	//（1）双亲表示法
	//（2）孩子表示法（链式存储方式）:两个方案
	//方案一：节点指针域的个数等于树的度（节点拥有的子树数目成为节点的度，树的度是树内各节点度的最大值）。
	//方案二：节点指针域的个数等于该节点的度
	//（3）孩子兄弟表示法
	//又名：二叉链表表示法



	//_nmsp1::TreeNode<int> treenode1(5);
	//treenode1.data = 15;
	//treenode1.child[0] = new _nmsp1::TreeNode<int>(4); //指向一个含有4个孩子节点的TreeNode对象

	////最后不要忘记释放内存
	//delete treenode1.child[0];

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




