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

	////孩子兄弟表示法作为树存储结构时，树的节点结构定义
	//template <typename T> //T代表数据元素类型
	//struct TreeNode
	//{
	//	T data; //数据域
	//	TreeNode* firstchild; //指针域，指向第一个孩子节点
	//	TreeNode* rightbro; //指针域，指向右兄弟节点
	//};

	////树的前序遍历伪代码：
	//void preOrder(TreeNode* tNode) //前序遍历树
	//{
	//	if (tNode != nulptr) // 若非空树
	//	{
	//		//根左右顺序
	//		visit(tNode); //访问根节点，比如输出节点的数据域的值
	//		while (tNode节点有下一个子树TNodeChild)//访问TNode的各个子节点
	//			preOrder(TNodeChild); //递归方式前序遍历子树
	//	}
	//}
	////树的后序遍历伪代码：
	//void postOrder(TreeNode* tNode) //后序遍历树
	//{
	//	if (tNode != nulptr) // 若非空树
	//	{
	//		//左右根顺序	
	//		while (tNode节点有下一个子树TNodeChild)
	//			postOrder(TNodeChild); //递归方式后序遍历子树
	//		visit(tNode); //访问根节点，比如输出节点的数据域的值
	//	}
	//}

	//void levelOrder(TreeNode* tNode) //层序遍历树
	//{
	//	if (tNode != nullptr) //若二叉树非空
	//	{
	//		TreeNode* tmpnode;
	//		LinkQueue<TreeNode*> lnobj; //使用队列进行层序遍历
	//		lnobj.EnQueue(tNode); //先把根节点指针入队
	//		while (!lnobj.IsEmpty()) //循环判断队列是否为空
	//		{
	//			lnobj.Dequeue(tmpnode); //出队列
	//			cout << (char)tmpnode->data << "  "; //显示结点数据
	//			while (tNode节点有下一个子树TNodeChild)
	//			{
	//				lnobj.EnQueue(TNodeChild);
	//			} //end while
	//		} //end while
	//	} //end if
	//}
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
	//（13.2）树转换为二叉树
	// a)加线 b)去线 c）调整方向
	//（13.3）森林及森林转换为二叉树
	//a)将森林中的每棵树都转换成二叉树   b)第一棵二叉树不动，从第二棵二叉树开始依次把后一棵
	                         //二叉树的根节点作为前一棵二叉树根节点的右孩子用线连接起来
	//c)调整方向：以根节点为轴心，将树顺时针（右）旋转一定角度，这样，整棵树看起来就是一棵二叉树了。

	//（13.4）二叉树转换为树
	//a）加线  b)去线  c)调整方向
	//（13.5）二叉树转换为森林
	//a)查看该二叉树的树根是否有右孩子，如果有，则把根与右孩子节点的连线删除。
	//b)将每棵分离的二叉树转换为树
	
	//（13.6）树的遍历
	//前序遍历，后序遍历，层序遍历 。树没有中序遍历。
	//前序遍历：不难验证，树的前序遍历序列与其对应的二叉树的前序遍历序列相同。
	// 
	//后序遍历：不难验证，树的后序遍历序列与其对应的二叉树的中序遍历序列相同。

	//层序遍历： a)将节点出队列并显示数据元素  b)如果节点有孩子节点，则将这些孩子节点全部入队列。c)重复a,b这两个步骤一直到队列为空。

	//（13.7）森林的遍历
	//前序遍历：从第一棵树开始，依次前序遍历森林中的每棵树。
	//			当然，也可以把森林转成相应二叉树后对该二叉树进行前序遍历，结果一样。
	//后序遍历：从第一棵树开始，依次后序遍历森林中的每棵树。
	//			当然，也可以把森林转成相应二叉树后对该二叉树进行中序遍历，结果一样。



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




