// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>


#ifdef _DEBUG   //只在Debug（调试）模式下
#ifndef DEBUG_NEW
#define DEBUG_NEW new(_NORMAL_BLOCK,__FILE__,__LINE__) //重新定义new运算符
#define new DEBUG_NEW
#endif
#endif

//#include <boost/type_index.hpp>
using namespace std;
#pragma warning(disable : 4996) 


//----------------------------
namespace _nmsp1
{
	//平衡二叉树中每个节点的定义
	template <typename T> //T代表数据元素的类型
	struct TreeNode
	{
		T        data;
		TreeNode<T>* leftChild,   //左子节点指针
			   * rightChild;  //右子节点指针
		int    height;        //当前节点高度，叶子节点高度为1，往上一
	};

	//平衡二叉树的定义
	template <typename T>
	class AVLTree
	{
	public:
		AVLTree()  //构造函数		
		{
			root = nullptr;
		}
		~AVLTree() //析构函数
		{
			ReleaseNode(root);
		}
		void ReleaseNode(TreeNode<T>* pnode)
		{
			if (pnode != nullptr)
			{
				ReleaseNode(pnode->leftChild);
				ReleaseNode(pnode->rightChild);
			}
			delete pnode;
		}
	public:
		void InsertElem(const T& data)
		{
			InsertElem( &root, data);
		}

	private:
		void InsertElem(TreeNode<T>** tNode, const T& data)
		{			
			if (*tNode == nullptr)
			{				
				(*tNode) = new TreeNode<T>;
				(*tNode)->data = data;
				(*tNode)->height = 0;
				(*tNode)->leftChild = nullptr;
				(*tNode)->rightChild = nullptr;
			}
			else if (data < (*tNode)->data)
			{
				InsertElem(&(*tNode)->leftChild, data);

				//拿到当前节点左右子树高度
				int lHeight = getHeight((*tNode)->leftChild);
				int rHeight = getHeight((*tNode)->rightChild);
				//判断高度差
				if (lHeight - rHeight == 2)
				{
					if (data < (*tNode)->leftChild->data)
					{
						//LL调整
						llRotation(*tNode, tNode);
					}
					else
					{
						//LR调整
						rrRotation((*tNode)->leftChild, &(*tNode)->leftChild);
						llRotation(*tNode, tNode);
					}
				}
			}
			else if (data > (*tNode)->data)
			{
				InsertElem(&(*tNode)->rightChild, data);

				//拿到当前节点左右子树高度
				int lHeight = getHeight((*tNode)->leftChild);
				int rHeight = getHeight((*tNode)->rightChild);
				//判断高度差
				if (rHeight - lHeight == 2)
				{
					if (data > (*tNode)->rightChild->data)
					{
						//RR调整
						rrRotation(*tNode, tNode);
					}
					else
					{
						//RL调整
						llRotation((*tNode)->rightChild, &(*tNode)->rightChild);
						rrRotation(*tNode, tNode);
					}
				}
			}
			//更新高度
			(*tNode)->height = max(getHeight((*tNode)->leftChild), getHeight((*tNode)->rightChild)) + 1;
			
		}	
		//求节点高度
		int getHeight(TreeNode<T>* node)
		{
			return node ? node->height : 0;
		}
		//求最大值 
		int max(int a, int b)
		{
			return a > b ? a : b;
		}

		//右右旋转
		void rrRotation(TreeNode<T>* node, TreeNode<T>** root)
		{
			TreeNode<T>* temp = node->rightChild;
			node->rightChild = temp->leftChild;
			temp->leftChild = node;
			node->height = max(getHeight(node->leftChild), getHeight(node->rightChild)) + 1;
			temp->height = max(getHeight(temp->leftChild), getHeight(temp->rightChild)) + 1;
			*root = temp;
		}
		//左左旋转    ，右旋转
		void llRotation(TreeNode<T>* node, TreeNode<T>** root)
		{
			TreeNode<T>* temp = node->leftChild;
			node->leftChild = temp->rightChild;
			temp->rightChild = node;
			node->height = max(getHeight(node->leftChild), getHeight(node->rightChild)) + 1;
			temp->height = max(getHeight(temp->leftChild), getHeight(temp->rightChild)) + 1;
			*root = temp;
		}
	private:
		TreeNode<T>* root; //树根指针	
	};
		
}

int main()
{	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口
	
	_nmsp1::AVLTree<int> mybtr;


	//int array[] = { 95,60,40};
	//int array[] = { 95,60,120,40,70,20 };
	//int array[] = { 95,60,120,40,70,50 };
	//int array[] = { 95,60,120,40,20 };
	// 
	//综合演示数据
	int array[] = { 12,4,1,3,7,8,10,9,2,11,6,5 };
	int acount = sizeof(array) / sizeof(int);

	for (int i = 0; i < acount; ++i)	
		mybtr.InsertElem(array[i]);

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


