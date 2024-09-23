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


namespace _nmsp0
{
	//链式栈中每个节点的定义
	template <typename T> //T代表数据元素的类型
	struct StackNode
	{
		T        data;  //数据域，存放数据元素
		StackNode<T>* next;  //指针域，指向下一个同类型（和本节点类型相同）节点
	};

	//链式栈的定义
	template <typename T>
	class LinkStack
	{
	public:
		LinkStack();      //构造函数，参数可以有默认值
		~LinkStack();     //析构函数

	public:
		bool Push(const T& e); //入栈元素e
		bool Pop(T& e);        //出栈（删除数据），也就是删除栈顶数据
		bool GetTop(T& e);     //读取栈顶元素，但该元素并没有出栈而是依旧在栈中

		void DispList();                     //输出链式栈中的所有元素
		int  ListLength();                   //获取链式栈的长度
		bool Empty();                        //判断链式栈是否为空

	private:
		StackNode<T>* m_top;   //栈顶指针
		int               m_length;//链式栈当前长度
	};

	//通过构造函数对链式栈进行初始化
	template <typename T>
	LinkStack<T>::LinkStack()
	{
		m_top = nullptr;
		m_length = 0;
	}

	//入栈元素e，时间复杂度为O(1)
	template <typename T>
	bool LinkStack<T>::Push(const T& e)
	{
		StackNode<T>* node = new StackNode<T>;
		node->data = e;
		node->next = m_top;
		m_top = node;
		m_length++;
		return true;
	}

	//出栈（删除数据），也就是删除栈顶数据，时间复杂度为O(1)
	template <typename T>
	bool LinkStack<T>::Pop(T& e)
	{
		if (Empty() == true) //链式栈为空
			return false;

		StackNode<T>* p_willdel = m_top;
		m_top = m_top->next;
		m_length--;
		e = p_willdel->data;
		delete p_willdel;
		return true;
	}

	//读取栈顶元素，但该元素并没有出栈而是依旧在栈中
	template <typename T>
	bool LinkStack<T>::GetTop(T& e)
	{
		if (Empty() == true) //链式栈为空
			return false;

		e = m_top->data;
		return true;
	}

	//输出链式栈中的所有元素，时间复杂度为O(n)
	template<class T>
	void LinkStack<T>::DispList()
	{
		if (Empty() == true) //链式栈为空
			return;

		StackNode<T>* p = m_top;
		while (p != nullptr)
		{
			cout << p->data << " ";  //每个数据之间以空格分隔
			p = p->next;
		}
		cout << endl; //换行
	}

	//获取链式栈的长度，时间复杂度为O(1)
	template<class T>
	int  LinkStack<T>::ListLength()
	{
		return m_length;
	}

	//判断链式栈是否为空，时间复杂度为O(1)
	template<class T>
	bool LinkStack<T>::Empty()
	{
		if (m_top == nullptr) //链式栈为空
		{
			return true;
		}
		return false;
	}

	//通过析构函数对链式栈进行资源释放
	template <typename T>
	LinkStack<T>::~LinkStack()
	{
		T tmpnousevalue = { 0 };
		while (Pop(tmpnousevalue) == true) {}//把栈顶元素删光，while循环也就退出了，此时也就是空栈了				
	}
}

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

		//插入元素
		void InsertElem(const T& e) //不可以指定插入位置，程序内部会自动确定插入位置
		{
			InsertElem(root, e);
		}
		void InsertElem(AVLNode<T>*& tNode, const T& e) //注意第一个参数类型
		{
			AVLNode<T>* point = tNode; //从指向根节点开始
			AVLNode<T>* parent = nullptr; //保存父亲节点，根节点的父节点肯定先为nullptr；

			//借助以往实现的栈（链栈）代码保存插入的节点路径信息（用于后面调节平衡因子、调整平衡）
			_nmsp0::LinkStack< AVLNode<T>* > slinkobj;

			//通过一个while循环寻找要插入的节点的位置，同时还要把插入路线上的所经过的所有节点都保存到栈中，
			 //因为这些节点的平衡因子可能需要调整
			while (point != nullptr)
			{
				if (e == point->data)
					return; //要插入的数据与当前树中某节点数据相同，则不允许插入，直接返回。

				parent = point;  //记录父节点，因为后续子节点要往下走，找合适自己的位置
				slinkobj.Push(parent); //入栈（树根在最底下，越往上离要插入的节点越近，最上面元素是要插入的节点的父节点）
				
				if (e > point->data)
					point = point->rightChild;
				else
					point = point->leftChild;
			} //end while
			
			//走到这里，point等于nullptr，该生成新节点了
			point = new AVLNode<T>;
			point->data = e;
			point->leftChild = nullptr;
			point->rightChild = nullptr;
			point->balfac = 0; //插入时肯定是个叶节点，所以平衡因子肯定等于0
			if (parent == nullptr)
			{
				//创建的是根节点
				tNode = point;
				return;
			}

			//走到这里表示创建的不是根接待你，那么要把孩子链到父亲上。
			if (e > parent->data)
				parent->rightChild = point; //在父节点的右树链入
			else
				parent->leftChild = point; //在父节点的左树链入

			//下面即将修改平衡因子 以及 调整平衡，前面栈slinkobj里的节点就是可能要更改平衡因子和做平衡调整的节点
			while (slinkobj.Empty() != true)
			{
				if (slinkobj.Pop(parent) == true) //取栈顶元素到parent中，第一次获取到的是新插入节点的父节点
				{
					//（1）因为插入了孩子，所以调整父的平衡因子
					if (parent->leftChild == point) //插入的是parent的左子节点
						parent->balfac++; //平衡因子+1
					else
						parent->balfac--; //平衡因子-1

					//（2）找最小不平衡子树的根节点并进行平衡性调整
					if (parent->balfac < -1 || parent->balfac > 1)
					{
						//有四种旋转方式，采取那种旋转方式呢？
						//...待增加

						break;
					}
					//比如某个节点A有个左子树B1，所有其平衡因子为1，现在如果给其增加一个右子树B2，其平衡因子变为0。
					//此时不要再继续向上调整节点A的父的平衡因子了，否则会把A父亲的平衡因子调整错误。
					else if (parent->balfac == 0)
					{
						//已经平衡，不需要继续回溯调整
						break;
					}
					else
					{
						point = parent; //让point指向父接待你，后续parent的新值要从栈顶获取
					} //end if (parent->balfac < -1 || parent->balfac > 1)
				} //end if (slinkobj.Pop(parent) == true) 
			} //end while (slinkobj.Empty() != true)

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
	//（10.2）平衡二叉树插入操作后的平衡性调整及实现代码
	//插入和删除两种操作会改变平衡二叉树的平衡性
	//最小不平衡子树：这里将以节点70为根的这棵需要进行平衡性调整的子树称为“最小不平衡子树”。
	 //只要将最小不平衡子树进行平衡性调整（高度复原），整个二叉查找树就会恢复平衡。
	//平衡性调整时对二叉树进行“旋转”操作来达成的。
	//四种旋转方式：前两种方式称为“单旋转”。后两种方式称为“双旋转”。
		//a)左旋转   b)右旋转     c)先左后右旋转    d)先右后左旋转
	//对于最小不平衡子树（将该子树命名为A）的产生又分为四种情况：
	   //a)在A的“左孩子的左子树”中插入节点导致A不平衡（简称LL：L代表Left）。此时需要通过“右旋转”调整平衡。
	   //b)在A的“右孩子的右子树”中插入节点导致A不平衡（简称RR：R代表Right）。此时需要通过“左旋转”调整平衡。
	   //c)在A的“左孩子的右子树”中插入节点导致A不平衡（简称LR）。此时需要通过“先左后右旋转”调整平衡。
	   //d)在A的“右孩子的左子树”中插入节点导致A不平衡（简称RL）。此时需要通过“先右后左旋转”调整平衡。




	


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




