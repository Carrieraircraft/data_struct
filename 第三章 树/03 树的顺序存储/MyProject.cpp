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

#define MaxSize 100       //数组的尺寸

enum ECCHILDSIGN  //节点标记
{
	E_Root,       //树根
	E_ChildLeft,  //左孩子
	E_ChildRight  //右孩子
};

//------------------------------
namespace _nmsp1
{
	//树中每个节点的定义
	template <typename T> //T代表数据元素的类型
	struct BinaryTreeNode
	{
		T data;  //数据域，存放数据元素
		bool isValid; //该节点是否有效以应对非完全二叉树(只有保存了实际节点数据的节点才是有效的）
	};

	//二叉树的定义
	template <typename T>
	class BinaryTree
	{
	public:
		BinaryTree() //构造函数
		{
			for (int i = 0; i <= MaxSize; ++i) //注意这里数组大小是MaxSize+1，所以这里i的终止值没问题
			{
				SqBiTree[i].isValid = false; //开始时节点无效，没有保存任何数据
			}
		}
		~BinaryTree() {} //析构函数

	public:
		//创建一个树节点
		int CreateNode(int parindex, ECCHILDSIGN pointSign, const T& e);

		//获取父节点的下标
		int getParentIdx(int sonindex)
		{
			if (ifValidRangeIdx(sonindex) == false) //位置不合理
				return -1;
			if (SqBiTree[sonindex].isValid == false) //不是个合理的节点，不要尝试找父节点
				return -1;
			return int(sonindex / 2); //i的父节点是(i/2)向下取整
		}

		//获取某个节点所在的高度
		//根据二叉树性质5：具有n(n>0)个节点的完全二叉树的高度log(n+1) 向上取整或者  log(n)向下取整 +1。这里的log都是 以2为底
		int getPointLevel(int index)
		{
			if (ifValidRangeIdx(index) == false) //位置不合理
				return -1;
			if (SqBiTree[index].isValid == false) //不是个合理的节点，不要尝试找父节点
				return -1;

			//采用公式计算: log(n)向下取整 +1
			int level = int(log(index) / log(2)) + 1; //c++中的log(n)函数求的是以e(2.71828)为底的对数值，如果要求以数字m为底，则需要log(n) / log(m)。
			return level;
		}

		//获取二叉树的高度/深度
		int getLevel()
		{
			if (SqBiTree[1].isValid == false) //没根
				return 0;

			int i;
			for (i = MaxSize; i >= 1; --i)
			{
				if (SqBiTree[i].isValid == true) //找到了最后一个有效节点
					break;
			} //end for
			return getPointLevel(i);
		}

		//判断是否是个完全二叉树
		bool ifCompleteBT()
		{
			if (SqBiTree[1].isValid == false) //没根
				return false;

			int i;
			for (i = MaxSize; i >= 1; --i)
			{
				if (SqBiTree[i].isValid == true) //找到了最后一个有效节点
					break;
			}
			for (int k = 1; k <= i; ++k)
			{
				if (SqBiTree[k].isValid == false) //所有节点必须都要有效
					return false;
			}
			return true;
		}

		//前序遍历二叉树，其他的遍历方式在二叉树的链式存储中再详细书写代码和讲解
		void preOrder()
		{
			if (SqBiTree[1].isValid == false) //没根
				return;

			preOrder(1); //根节点的数组下标是1，所以这里把根的下标传递进去
		}
		void preOrder(int index)
		{
			if (ifValidRangeIdx(index) == false) //位置不合理
				return;
			if (SqBiTree[index].isValid == false) //不是个合理的节点
				return;

			//根左右顺序
			cout << (char)SqBiTree[index].data << "  ";  //输出节点的数据域的值，为了方便观察，用char以显示字母
			preOrder(2 * index); //递归方式前序遍历左子树
			preOrder(2 * index +1); //递归方式前序遍历右子树
		}
	private:
		bool ifValidRangeIdx(int index) //是否是一个有效的数组下标值
		{
			//位置必须合理
			if (index < 1 || index > MaxSize) //[0]下标留着不用。因定义数组时定义的是MaxSize+1，所以数组最大下标是MaxSize
				return false;
			return true;
		}
		
	private:
		BinaryTreeNode<T> SqBiTree[MaxSize + 1]; //存储二叉树节点的数组，为了写程序方便，下标为[0]的数组元素不使用，因此这里+1
	};

	//创建一个树节点
	template<class T>
	//参数1：父节点所在的数组下标。参数2：标记所创建的是树根，左孩子，右孩子。参数3：插入的数据节点的元素值。
	int BinaryTree<T>::CreateNode(int parindex, ECCHILDSIGN pointSign, const T& e)
	{
		if (pointSign != E_Root) //非根节点，则一定是子节点，要求parindex一定是个合理值
		{
			if (ifValidRangeIdx(parindex) == false) //位置不合理
				return -1;
			if (SqBiTree[parindex].isValid == false) //不是个合理的节点
				return -1;
		}
		int index = -1;
		if (pointSign == E_Root) //根
		{
			index = 1; //根节点固定存储在下标为1的位置
		}
		else if(pointSign == E_ChildLeft) //左孩子
		{
			//创建的是左孩子节点，节点i的左孩子节点的下标是2i。
			index = 2 * parindex;
			if (ifValidRangeIdx(index) == false) //位置不合理
				return -1; //非法下标
		}
		else //右孩子
		{
			//创建的是右孩子节点，节点i的右孩子节点的下标是2i+1。
			index = 2 * parindex +1;
			if (ifValidRangeIdx(index) == false) //位置不合理
				return -1; //非法下标
		}
		SqBiTree[index].data = e;
		SqBiTree[index].isValid = true; //标记该下标中有有效数据
		return index;
	}

}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//第3章 树
	//第二节  二叉树
	//（1）基本概念
	//（2）特殊二叉树	
	//（3）二叉树的性质
	//（4）二叉树的遍历:根出发，依次访问二叉树所有节点。使每个节点都被访问且只被访问一次。	
	//（4.1）前序遍历、中序遍历、后序遍历基本概念
	//（4.2）前序、中序、后序遍历简单范例	
	//（4.4）前序、中序、后序遍历针对普通二叉树的遍历顺序范例及伪代码	
	//（4.5）二叉树遍历的推导以及遍历的一些结论
	//（4.6）扩展二叉树 / 扩充二叉树
	 //a)如果给出一个扩展二叉树的前序或后序遍历序列，是能够唯一确定一棵二叉树的。  前序:ABD###C#E##
	 //b)给出一个扩展二叉树的中序遍历序列，是无法唯一确定一棵二叉树的。
	//（4.7）层序遍历 / 层次遍历（也称为 广度优先遍历/广度优先搜索），一般要借助队列。
	 //从根节点开始，从上到下，从左到右。
	 //已知层序遍历序列是无法唯一确定一棵二叉树的。
	 //已知“层序和中序遍历序列”，是能够唯一确定一棵二叉树的。 层序：ABCDEFGH。中序：DGBHEACF。
	//层序遍历的过程：
	//a)初始化一个队列。
	//b)把二叉树的根节点入队列。
	//c)判断队列是否为空，如果为空，就让队头节点出队（相当于遍历了该节点），
	     //同时要将这个刚刚出队的节点的左孩子和右孩子分别入队（如果该节点有左右孩子）。
	//d)重复c)步骤，一直到队列为空。

	//（5）二叉树的存储结构：基于数组的顺序存储方式， 另一种是链式存储方式。
	//（5.1）顺序存储方式:用一段连续的内存单元（数组）依次从上到下从左到右存储二叉树各个节点元素。
	  //存储就的是完全二叉树。根在数组下标为i = 1。那么左子节点就存储就在下标2*i = 2的位置，
	   //右子节点就存储在2*i+1=3的位置。
	 //顺序存储结构一般用于存储完全二叉树。
	//（5.2）链式存储方式(因为多了左右子节点指针，所以适合存储普通二叉树)。
	  //节点结构：一个数据域，二个指针域。二叉链表（一个节点带两个指针）。
	  //在设计节点结构时再增加一个指针域用于指向其父节点，这种节点结构所得到的二叉树存储结构称为三叉链表（一个节点结构中带三个指针）。
	//（6）二叉树顺序存储的常用操作


	_nmsp1::BinaryTree<int> mytree;
	//创建一棵二叉树
	int indexRoot = mytree.CreateNode(-1, E_Root, 'A'); //创建数根节点A
	int indexNodeB = mytree.CreateNode(indexRoot, E_ChildLeft, 'B'); //创建树根的左子节点B
	int indexNodeC = mytree.CreateNode(indexRoot, E_ChildRight, 'C'); //创建树根的右子节点C

	int indexNodeD = mytree.CreateNode(indexNodeB, E_ChildLeft, 'D'); //创建B的左子节点D

	int indexNodeE = mytree.CreateNode(indexNodeC, E_ChildRight, 'E'); //创建C的右子节点E

	int iParentIndexE = mytree.getParentIdx(indexNodeE); //获取某个节点的父节点的下标
	cout << "节点E的父节点的下标是:" << iParentIndexE << endl;

	int iLevel = mytree.getPointLevel(indexNodeD); //获取某个节点所在的高度
	cout << "节点D所在的高度是:" << iLevel << endl;
	iLevel = mytree.getPointLevel(indexNodeE);
	cout << "节点E所在的高度是:" << iLevel << endl;

	cout << "二叉树的深度是：" << mytree.getLevel() << endl; 
	cout << "二叉树是个完全二叉树吗？" << mytree.ifCompleteBT() << endl;

	cout << "---------------" << endl;
	cout << "前序遍历序列为：";
	mytree.preOrder(); //前序遍历
	

	
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


