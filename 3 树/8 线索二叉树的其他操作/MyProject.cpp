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
	//树中每个节点的定义
	template <typename T> //T代表数据元素的类型
	struct BinaryTreeNode
	{
		T   data; //数据域，存放数据元素
		BinaryTreeNode* leftChild, //左子节点指针
						*rightChild;  //右子节点指针

		//BinaryTreeNode* parent; //父节点指针，可以根据需要决定是否引入

		int8_t      leftTag;  //左标记 = 0，表示leftChild指向的是左子节点，=1表示leftChild指向的是前趋节点（线索）
		int8_t      rightTag;  //右标记 = 0，表示rightChild指向的是右子节点，=1表示rightChild指向的是后继节点（线索）
	};

	//线索二叉树的定义
	template <typename T>
	class ThreadBinaryTree
	{
	public:
		ThreadBinaryTree(); //构造函数
		~ThreadBinaryTree(); //析构函数
	public:
		//利用扩展二叉树的前序遍历序列来创建一棵二叉树
		void CreateBTreeAccordPT(char* pstr);
		//利用扩展二叉树的前序遍历序列创建二叉树的递归函数
		void CrerateBTreeAccordPTRecu(BinaryTreeNode<T>*& tnode, char*& pstr); //参数为引用类型，
		                                                   //确保递归调用中对参数的改变会影响到调用者

	public:
		//在二叉树中根据中序遍历序列创建线索
		void CreateThreadInBTreeAccordIO();
		void CreateThreadInBTreeAccordPO();
		void CreateThreadInBTreeAccordPOSTO();
	private:
		void CreateThreadInBTreeAccordIO(BinaryTreeNode<T>*& tnode, BinaryTreeNode<T>*& pre);//参数为引用类型
		void CreateThreadInBTreeAccordPO(BinaryTreeNode<T>*& tnode, BinaryTreeNode<T>*& pre);//参数为引用类型
		void CreateThreadInBTreeAccordPOSTO(BinaryTreeNode<T>*& tnode, BinaryTreeNode<T>*& pre);//参数为引用类型

		//找线索二叉树（中序线索化）的第一个节点
		BinaryTreeNode<T>* GetFirst_IO()
		{
			return GetFirst_IO(root);
		}
		BinaryTreeNode<T>* GetFirst_IO(BinaryTreeNode<T>* root)
		{
			//中序遍历是“左根右顺序”
			//一直找真正的左孩子
			if (root == nullptr)
				return nullptr;
			BinaryTreeNode<T>* tmpnode = root;
			while (tmpnode->leftTag == 0) //指向的是真正的左子节点
			{
				tmpnode = tmpnode->leftChild;
			}
			return tmpnode;
		}

		//找线索二叉树（中序线索化）的最后一个节点
		BinaryTreeNode<T>* GetLast_IO()
		{
			return GetLast_IO(root);
		}
		BinaryTreeNode<T>* GetLast_IO(BinaryTreeNode<T>* root)
		{
			//中序遍历是“左根右顺序”
			//一直找真正的右孩子即可
			if (root == nullptr)
				return nullptr;
			BinaryTreeNode<T>* tmpnode = root;
			while (tmpnode->rightTag == 0) //指向的是真正的右子节点
			{
				tmpnode = tmpnode->rightChild;
			}
			return tmpnode;
		}
		//找线索二叉树（中序线索化）中当前节点的后继节点
		BinaryTreeNode<T>* GetNextPoint_IO(BinaryTreeNode<T>* currnode)
		{
			if (currnode == nullptr)
				return nullptr;
			if (currnode->rightTag == 1) //rightChild指向的是后继节点（线索）
				return currnode->rightChild;

			//如果该节点的rightChild指向的是真正的右孩子节点，那么该怎样获得该节点的后继节点呢？
			//考虑到中序遍历的顺序是“左根右”，那么当前节点（看成根）的右子树的第一个节点就是：
			return GetFirst_IO(currnode->rightChild); //在右子树中查找第一个要访问的节点。			
		}

		//找线索二叉树（中序线索化）中当前节点的前趋节点
		BinaryTreeNode<T>* GetPriorPoint_IO(BinaryTreeNode<T>* currnode)
		{
			if (currnode == nullptr)
				return nullptr;
			if (currnode->leftTag == 1) //leftChild指向的是前趋节点（线索）
				return currnode->leftChild;

			//如果该节点的leftChild指向的是真正的左孩子节点，那么该怎样获得该节点的前趋节点呢？			
			return GetLast_IO(currnode->leftChild); //在左子树中查找最后一个要访问的节点。	
		}

		//找线索二叉树（前序线索化）中当前节点的后继节点
		BinaryTreeNode<T>* GetNextPoint_PO(BinaryTreeNode<T>* currnode)
		{
			//根左右
			if (currnode == nullptr)
				return nullptr;
			if (currnode->rightTag == 1)
				return currnode->rightChild;

			//该节点有右孩子才能走到这里
			//那么：如果改节点有左孩子，则该节点的后继节点必然是左孩子的第一个节点，根据根左右顺序，就是该左孩子节点
			if (currnode->leftTag == 0) //有左孩子
				return currnode->leftChild;
			//没有左孩子，而且前面已经确定了有右孩子，则根据根左右顺序
			return currnode->rightChild;
		}

		//找线索二叉树（前序线索化）中当前节点的前趋节点
		BinaryTreeNode<T>* GetPriorPoint_PO(BinaryTreeNode<T>* currnode)
		{
			if (currnode == nullptr)
				return nullptr;
			if (currnode->leftTag == 1)
				return currnode->leftChild;

			//根左右
			//有左孩子，但此时是无法找到当前节点的前趋节点的，除非重新进行一次前序遍历
			//但是如果是三叉链表，也就是说可以找到当前节点的父节点，那么就可以分几种情况：
			//(1)如果当前节点没有父节点（当前节点是根节点）则根据“根左右”规则，当前节点没有前趋节点。
			//(2)如果当前节点是 父节点 的 左孩子，那么根据“根左右”规则，当前节点的前趋节点就是父节点。
			//(3)如果当前节点是 父节点 的 右孩子，并且当前节点的左兄弟不存在，那么根据“根左右”规则，当前节点的前趋节点就是父节点
			//(4)如果当前节点是 父节点 的 右孩子，并且当前节点的左兄弟存在，那么根据“根左右”规则，当前节点的前趋节点
							//一定是其左兄弟这棵子树中的（按照前序遍历序列最后 一个被访问到的）节点。
			   //那么如何在“左兄弟这棵子树中”找到最后一个被访问到的节点呢？因为左兄弟节点是“左兄弟这棵子树”的根，所以：
				//(4.1)从根节点开始，如果有右子树，则右子树中的节点肯定最后被访问。所以从根节点开始，
			            //尽可能向右子树方向找右下节点，因为这个节点是最后被访问到的。
			    //(4.2)如果最右下角的节点还是左子树，则尽可能向左子树方向找左下的节点，这个节点是最后被访问到的。
			    //(4.3)如果这个节点又有右子树，则尽可能向右子树方向找右下节点，
						//因为这个节点是最后被访问到的。。。。，这样就回到了(4.1)
				//(4.4)直至找到最下面一个节点，这个节点就是前序遍历中的  子树最后 一个被访问到的节点。

			//....相关代码略，大家有兴趣可以自行实现。
		}

		//找线索二叉树（后序线索化）中当前节点的后继节点
		BinaryTreeNode<T>* GetNextPoint_POSTO(BinaryTreeNode<T>* currnode)
		{
			//左根右
			if (currnode == nullptr)
				return nullptr;

			if (currnode->rightTag == 1)
				return currnode->rightChild;

			//有右孩子，但此时是无法找到当前节点的后继节点的，除非重新进行一次后序遍历。
			//但是如果是三叉链表，也就是说可以找到当前节点的父节点，那么就可以分几种情况
			//(1)如果当前节点没有父节点（当前节点是根节点）则根据“左右根”规则，当前节点没有后继节点
			//(2)如果当前节点是 父节点的  右孩子，那么根据左右根规则，当前节点是该节点所代表的
						//子树中最后被访问到的节点，所以，当前节点的后继节点就是父节点。
			//(3)如果当前节点是 父节点的  左孩子，并且当前节点的右兄弟不存在，那么根据左右根规则，
						//当前节点的后继节点就是父节点。
			//(4)如果当前节点是 父节点的  左孩子，并且当前节点的右兄弟存在，那么根据左右根规则，
						//当前节点的后继节点一定是右兄弟这棵子树中（按照后序遍历顺序第一个被访问到的）节点
				//那么如何在“右兄弟这棵子树中”找到第一个被访问到的节点呢？因为右兄弟节点是
						//“右兄弟这棵子树”的根，所以：
				//(4.1)从根节点开始，尽可能向左子树方向找左下的节点，因为这个节点是最先被访问到的
				//(4.2)如果最左下角的节点还有右子树，则尽可能向右子树方向找右下的节点，这个节点是最先被访问到的。
				//(4.3)如果这个节点又有左子树，则尽可能向左子树方向找左下的节点，因为这个节点是最先被访问到的。。。
						//这就回到了(4.1)。
				
			//......相关代码略，大家有兴趣可以自己实现。
		}

		//找线索二叉树（后序线索化）中当前节点的前趋节点
		BinaryTreeNode<T>* GetPriorPoint_POSTO(BinaryTreeNode<T>* currnode)
		{
			if (currnode == nullptr)
				return nullptr;
			if (currnode->leftTag == 1)
				return currnode->leftChild;

			//有左孩子，但是否有右孩子并不确定
			if (currnode->rightTag == 0)
			{
				//有右孩子，则是右子树中按照后序遍历得到的最后一个节点，该节点就是这个右孩子
				return currnode->rightChild;
			}

			//没有右孩子，那么按照左根右的顺序，则左子树中按照后序遍历得到的最后一个节点，该节点就是这个左孩子
			return currnode->leftChild;
		}



	private:
		void ReleaseNode(BinaryTreeNode<T>* pnode);

	private:
		BinaryTreeNode<T>* root; //树根指针
	};

	//构造函数
	template<class T>
	ThreadBinaryTree<T>::ThreadBinaryTree()
	{
		root = nullptr;
	}
	//析构函数
	template <class T>
	ThreadBinaryTree<T>::~ThreadBinaryTree()
	{
		ReleaseNode(root);
	}

	//释放二叉树节点
	template <class T>
	void ThreadBinaryTree<T>::ReleaseNode(BinaryTreeNode<T>* pnode)
	{
		if (pnode != nullptr)
		{
			if (pnode->leftTag == 0)
			{
				ReleaseNode(pnode->leftChild); //只有真的需要delete的节点，才会递归调用ReleaseNode
			}
			if (pnode->rightTag == 0)
			{
				ReleaseNode(pnode->rightChild); //只有真的需要delete的节点，才会递归调用ReleaseNode
			}			
		}
		delete pnode;
	}

	//利用扩展二叉树的前序遍历序列来创建一棵二叉树
	template <class T>
	void  ThreadBinaryTree<T>::CreateBTreeAccordPT(char* pstr)
	{
		CrerateBTreeAccordPTRecu(root, pstr);
	}

	//利用扩展二叉树的前序遍历序列创建二叉树的递归函数
	template <class T>
	void ThreadBinaryTree<T>::CrerateBTreeAccordPTRecu(BinaryTreeNode<T>*& tnode, char*& pstr)
	{
		if (*pstr == '#')
		{
			tnode = nullptr;
		}
		else
		{
			tnode = new BinaryTreeNode<T>; //创建根节点
			tnode->leftTag = tnode->rightTag = 0; //标志先给0
			tnode->data = *pstr;
			CrerateBTreeAccordPTRecu(tnode->leftChild, ++pstr); //创建左子树
			CrerateBTreeAccordPTRecu(tnode->rightChild, ++pstr); //创建右子树
		}
	}

	//在二叉树中根据中序遍历序列创建线索
	template <class T>
	void ThreadBinaryTree<T>::CreateThreadInBTreeAccordIO()
	{
		BinaryTreeNode<T>* pre = nullptr; //记录当前所指向的节点的前趋节点（刚开始的节点没有前驱，所以设置为nullptr)
		CreateThreadInBTreeAccordIO(root, pre);

		//注意处理最后一个节点的右孩子，因为这个右孩子没处理：
		pre->rightChild = nullptr; //这里之所以直接给nullptr，是因为中序遍历访问顺序是 左根右
		                         //，所以最后一个节点不可能有右孩子，否则最后一个访问的节点就会是他的右孩子。
		                          //其实就算不执行这句，pre->rightChild也已经是等于nullptr了的。
		pre->rightTag = 1; //线索化
	}

	template <class T>
	void ThreadBinaryTree<T>::CreateThreadInBTreeAccordIO(BinaryTreeNode<T>*& tnode, BinaryTreeNode<T>*& pre)
	{
		if (tnode == nullptr)
			return;

		//中序遍历序列（左根右），递归顺序非常类似于中序遍历
		CreateThreadInBTreeAccordIO(tnode->leftChild, pre);

		if (tnode->leftChild == nullptr) //找空闲的指针域进行线索化
		{
			tnode->leftTag = 1; //线索
			tnode->leftChild = pre; 
		}

		//这个前趋节点的后继节点肯定是当前这个节点tnode
		if (pre != nullptr && pre->rightChild == nullptr)
		{
			pre->rightTag = 1; //线索
			pre->rightChild = tnode;			
		}
		pre = tnode; //前趋节点指针指向当前节点

		CreateThreadInBTreeAccordIO(tnode->rightChild, pre);
	}

	//--------------
	//在二叉树中根据前序遍历序列创建线索
	template <class T>
	void ThreadBinaryTree<T>::CreateThreadInBTreeAccordPO()
	{
		BinaryTreeNode<T>* pre = nullptr; 
		CreateThreadInBTreeAccordPO(root, pre);				
		pre->rightChild = nullptr;
		pre->rightTag = 1;
	}

	template <class T>
	void ThreadBinaryTree<T>::CreateThreadInBTreeAccordPO(BinaryTreeNode<T>*& tnode, BinaryTreeNode<T>*& pre)
	{
		if (tnode == nullptr)
			return;

		//前序遍历序列（根左右），递归顺序非常类似于前序遍历
		if (tnode->leftChild == nullptr) //找空闲的指针域进行线索化
		{
			tnode->leftTag = 1; //线索
			tnode->leftChild = pre;
		}

		//这个前趋节点的后继节点肯定是当前这个节点tnode
		if (pre != nullptr && pre->rightChild == nullptr)
		{
			pre->rightTag = 1; //线索
			pre->rightChild = tnode;
		}
		pre = tnode; //前趋节点指针指向当前节点


		if(tnode->leftTag == 0) //当leftChild是真正的子节点而不是线索化后的前趋节点时
			CreateThreadInBTreeAccordPO(tnode->leftChild, pre);

		if(tnode->rightTag == 0) //当rightChild是真正的子节点而不是线索化后的后继节点时
			CreateThreadInBTreeAccordPO(tnode->rightChild, pre);
	}

	//--------------
	//在二叉树中根据后序遍历序列创建线索
	template <class T>
	void ThreadBinaryTree<T>::CreateThreadInBTreeAccordPOSTO()
	{
		BinaryTreeNode<T>* pre = nullptr;
		CreateThreadInBTreeAccordPO(root, pre);

		if (pre->rightChild == nullptr)
			pre->rightTag = 1;
	}

	template <class T>
	void ThreadBinaryTree<T>::CreateThreadInBTreeAccordPOSTO(BinaryTreeNode<T>*& tnode, BinaryTreeNode<T>*& pre)
	{
		if (tnode == nullptr)
			return;

		//后序遍历序列（左右根），递归顺序非常类似于后序遍历		
		CreateThreadInBTreeAccordPOSTO(tnode->leftChild, pre);
		CreateThreadInBTreeAccordPOSTO(tnode->rightChild, pre);


		if (tnode->leftChild == nullptr) //找空闲的指针域进行线索化
		{
			tnode->leftTag = 1; //线索
			tnode->leftChild = pre;
		}

		//这个前趋节点的后继节点肯定是当前这个节点tnode
		if (pre != nullptr && pre->rightChild == nullptr)
		{
			pre->rightTag = 1; //线索
			pre->rightChild = tnode;
		}
		pre = tnode; //前趋节点指针指向当前节点		
	}


}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//第3章 树
	//第二节  二叉树
	
	//（8）线索二叉树（Threaded Binary Tree）
	//（8.1）基本概念:有n个节点的二叉树。指针域有2n根指针。这些指针域只是用了n-1个，剩余n+1个指针域没有被使用。
	//中序遍历序列是：DGBHEACF。
	//把指向前趋节点和后继节点的指针称为线索。
	//把加上了线索的二叉树称为线索二叉树。
	//对二叉树进行某种序列的遍历使其成为一棵线索二叉树的过程称为二叉树的线索化
	//线索二叉树分前序，中序，后序，层序。
	//以往的二叉链表，在增加了线索之后称为 线索链表
	//（8.2）二叉树的线索化
	//(1)用中序遍历线索化二叉树
	//    a)创建线索二叉树：a.1)用任何方法创建二叉树。 a.2)将该二叉树根据前、中、后序遍历序列创建线索。
	//(2)用前序遍历序列线索化二叉树
	//(3)用后序遍历序列线索化二叉树
	//（8.3）线索二叉树的操作
	//(1)找线索二叉树的第一个和最后一个节点
	//(2)找线索二叉树中某个节点的前趋和后继节点
		//总结一下：
		//如果用二叉链表作为二叉树的存储结构，那么：
			//对于中序化的线索二叉树，既可以找到前趋节点又可以找到后继节点。
			//对于前序化的线索二叉树，可以找到后继节点但无法找到前趋节点。
			//对于后序化的线索二叉树，可以找到前趋节点但无法找到后继节点。
		//如果用三叉链表作为二叉树的存储结构，则找前趋和后继节点都是可以做到的。如果不采用
			//三叉链表作为二叉树的存储结构，则只能用以往二叉树遍历的方式来寻找前趋和后继节点了。








	_nmsp1::ThreadBinaryTree<int> mythreadTree;
	mythreadTree.CreateBTreeAccordPT((char*)"ABD#G##EH###C#F##"); //利用扩展二叉树的前序遍历序列创建二叉树

	//对二叉树进行线索化（根据中序遍历序列创建线索）
	//mythreadTree.CreateThreadInBTreeAccordIO();
	//mythreadTree.CreateThreadInBTreeAccordPO();
	mythreadTree.CreateThreadInBTreeAccordPOSTO();
	




	

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




