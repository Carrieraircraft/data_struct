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

enum ECCHILDSIGN //节点标记
{
	E_Root, //树根
	E_ChildLeft, //左孩子
	E_ChildRight //右孩子
};

//链式队列相关代码
namespace _nmsp0
{
	//链式队列中每个节点的定义
	template <typename T> //T代表数据元素的类型
	struct QueueNode
	{
		T        data;       //数据域，存放数据元素
		QueueNode<T>* next;  //指针域，指向下一个同类型（和本节点类型相同）节点
	};

	//链式队列的定义
	template <typename T> //T代表数组中元素的类型
	class LinkQueue
	{
	public:
		LinkQueue();                          //构造函数，参数可以有默认值
		~LinkQueue();                         //析构函数

	public:
		bool EnQueue(const T& e);            //入队列（增加数据）		
		bool DeQueue(T& e);                  //出队列（删除数据）
		bool GetHead(T& e);                  //读取队头元素，但该元素并没有出队列而是依旧在队列中		

		void DispList();                     //输出链式队列中的所有元素
		int  ListLength();                   //获取链式队列的长度（实际拥有的元素数量）		

		bool IsEmpty();                      //判断链式队列是否为空		

	private:
		QueueNode<T>* m_front;               //头指针（指向头结点），这一端允许出队（删除）
		QueueNode<T>* m_rear;                //专门引入尾指针以方便入队（插入）操作
		int m_length;                        //记录长度，方便获取长度
	};

	//通过构造函数对链式队列进行初始化
	template <typename T>
	LinkQueue<T>::LinkQueue()
	{
		m_front = new QueueNode<T>; //先创建一个头结点
		m_front->next = nullptr;
		m_rear = m_front;
		m_length = 0;

		//若不带头节点的链式队列初始化代码应该如下，供参考
		//m_front = nullptr;
		//m_rear = nullptr;
	}

	//通过析构函数对链式队列进行资源释放
	template <typename T>
	LinkQueue<T>::~LinkQueue()
	{
		QueueNode<T>* pnode = m_front->next;
		QueueNode<T>* ptmp;
		while (pnode != nullptr) //该循环负责释放数据节点
		{
			ptmp = pnode;
			pnode = pnode->next;
			delete ptmp;
		}
		delete m_front;             //释放头结点		
		m_front = m_rear = nullptr; //非必须
		m_length = 0;               //非必须
	}

	//入队列（增加数据），也就是从队尾增加数据
	template <typename T>
	bool LinkQueue<T>::EnQueue(const T& e)
	{
		QueueNode<T>* node = new QueueNode<T>;
		node->data = e;
		node->next = nullptr;

		m_rear->next = node; //新节点插入到m_rear后面
		m_rear = node;       //更新队列尾指针

		m_length++;
		return true;
	}

	//出队列（删除数据），也就是删除队头数据
	template <typename T>
	bool LinkQueue<T>::DeQueue(T& e)
	{
		if (IsEmpty() == true)
		{
			cout << "当前链式队列为空，不能进行出队操作!" << endl;
			return false;
		}

		QueueNode<T>* p_willdel = m_front->next;
		e = p_willdel->data;

		m_front->next = p_willdel->next;
		if (m_rear == p_willdel) //队列中只有一个元素节点（被删除后，整个队列就为空了）
			m_rear = m_front;  //设置队列为空(尾指针指向头指针)

		delete p_willdel;
		m_length--;
		return true;
	}

	//读取队头元素，但该元素并没有出队列而是依旧在队列中
	template <typename T>
	bool LinkQueue<T>::GetHead(T& e)
	{
		if (IsEmpty() == true)
		{
			cout << "当前链式队列为空，不能读取队头元素!" << endl;
			return false;
		}

		e = m_front->next->data;
		return true;
	}

	//输出链式队列中的所有元素，时间复杂度为O(n)
	template<class T>
	void LinkQueue<T>::DispList()
	{
		QueueNode<T>* p = m_front->next;
		while (p != nullptr)
		{
			cout << p->data << " ";  //每个数据之间以空格分隔
			p = p->next;
		}
		cout << endl; //换行
	}

	//获取链式队列的长度（实际拥有的元素数量），时间复杂度为O(1)
	template<class T>
	int LinkQueue<T>::ListLength()
	{
		return m_length;
	}

	//判断链式队列是否为空，时间复杂度为O(1)
	template<class T>
	bool LinkQueue<T>::IsEmpty()
	{
		if (m_front == m_rear) //当然，换一种判断方式也行：if(m_front->next == nullptr) return true;
		{
			return true;
		}
		return false;
	}
}

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
	};

	//二叉树的定义
	template  <typename T>
	class BinaryTree
	{
	public:
		BinaryTree(); //构造函数
		~BinaryTree(); //析构函数
	public:
		//创建一个树节点
		BinaryTreeNode<T>* CreateNode(BinaryTreeNode<T>* parentnode, ECCHILDSIGN pointSign, const T& e);
		//释放树节点
		void RleaseNode(BinaryTreeNode<T>* pnode);

	public:
		//利用扩展二叉树的前序遍历序列来创建一棵二叉树
		void CreateBTreeAccordPT(char* pstr);
	private:
		//利用扩展二叉树的前序遍历序列创建二叉树的递归函数
		void CreateBTreeAccordPTRecu(BinaryTreeNode<T>*& tnode, char*& pstr); //参数类型为引用，确保递归调用中对参数的改变会影响到调用者
		
	public:
		//前序遍历二叉树 ：根左右
		void preOrder()
		{
			preOrder(root);
		}
	private:
		void preOrder(BinaryTreeNode<T>*& tNode)
		{
			if (tNode != nullptr) //若二叉树非空
			{
				//根左右顺序
				cout << (char)tNode->data << "   "; //输出节点的数据域值，为方便观察，用char以显示字母
				preOrder(tNode->leftChild); //递归方式前序遍历左子树
				preOrder(tNode->rightChild); //递归方式前序遍历右子树
			}
		}

	public:
		//中序遍历二叉树 ：左根右
		void inOrder()
		{
			inOrder(root);
		}
	private:
		void inOrder(BinaryTreeNode<T>*& tNode)
		{
			if (tNode != nullptr) //若二叉树非空
			{
				//左根右顺序
				inOrder(tNode->leftChild); //递归方式中序遍历左子树
				cout << (char)tNode->data << "   "; //输出节点的数据域值				
				inOrder(tNode->rightChild); //递归方式中序遍历右子树
			}
		}

	public:
		//后序遍历二叉树 ：左右根
		void postOrder()
		{
			postOrder(root);
		}
	private:
		void postOrder(BinaryTreeNode<T>*& tNode)
		{
			if (tNode != nullptr) //若二叉树非空
			{
				//左右根顺序
				postOrder(tNode->leftChild); //递归方式后序遍历左子树
				postOrder(tNode->rightChild); //递归方式后序遍历右子树
				cout << (char)tNode->data << "   "; //输出节点的数据域值								
			}
		}

	public:
		//层序遍历二叉树
		void levelOrder()
		{
			levelOrder(root);
		}
	private:
		void levelOrder(BinaryTreeNode<T>* tNode)
		{
			if (tNode != nullptr) //若二叉树非空
			{
				BinaryTreeNode<T>* tmpnode;
				_nmsp0::LinkQueue< BinaryTreeNode<T>* > lnobj; //注意队列的元素类型是“节点指针”类型
				lnobj.EnQueue(tNode); //先把根节点指针入队
				while (!lnobj.IsEmpty()) //循环判断队列是否为空
				{
					lnobj.DeQueue(tmpnode); //出队列
					cout << (char)tmpnode->data << "  ";

					//左子节点不存在，而右子节点存在就不是一棵完全二叉树
					if (tmpnode->leftChild == nullptr && tmpnode->rightChild != nullptr)
					{
						//这棵二叉树不是一棵完全二叉树

					}

					if (tmpnode->leftChild != nullptr)
						lnobj.EnQueue(tmpnode->leftChild); //左孩子入队
					if (tmpnode->rightChild != nullptr)
						lnobj.EnQueue(tmpnode->rightChild); //右孩子入队
				} //end while
			} //end if
		}
		
	private:
		BinaryTreeNode<T>* root; //树根节点
	};

	//构造函数
	template  <typename T>
	BinaryTree<T>::BinaryTree()
	{
		root = nullptr;
	}
	//析构函数
	template  <typename T>
	BinaryTree<T>::~BinaryTree()
	{
		RleaseNode(root);
	}

	//释放二叉树节点
	template  <typename T>
	void BinaryTree<T>::RleaseNode(BinaryTreeNode<T>* pnode)
	{
		if (pnode != nullptr)
		{
			RleaseNode(pnode->leftChild);
			RleaseNode(pnode->rightChild);
		}
		delete pnode;
	}

	//创建一个树节点
	template  <typename T>
	BinaryTreeNode<T>* BinaryTree<T>::CreateNode(BinaryTreeNode<T>* parentnode, ECCHILDSIGN pointSign, const T& e)
	{
		//将新节点创建出来
		BinaryTreeNode<T>* tmpnode = new BinaryTreeNode<T>;
		tmpnode->data = e;
		tmpnode->leftChild = nullptr;
		tmpnode->rightChild = nullptr;

		//把新节点放入正确的位置
		if (pointSign == E_Root)
		{
			//创建的是根节点
			root = tmpnode;
		}
		if (pointSign == E_ChildLeft)
		{
			//创建的是左孩子节点
			parentnode->leftChild = tmpnode;
		}
		else if (pointSign == E_ChildRight)
		{
			//创建的是右孩子节点
			parentnode->rightChild = tmpnode;
		}
		return tmpnode;
	}

	//利用扩展二叉树的前序遍历序列来创建一棵二叉树
	template  <typename T>
	void BinaryTree<T>::CreateBTreeAccordPT(char* pstr)
	{
		CreateBTreeAccordPTRecu(root, pstr);
	}
	//利用扩展二叉树的前序遍历序列创建二叉树的递归函数
	template  <typename T>
	void BinaryTree<T>::CreateBTreeAccordPTRecu(BinaryTreeNode<T>*& tnode, char*& pstr)
	{
		//前序遍历序列:ABD###C#E##
		if (*pstr == '#')
		{
			tnode = nullptr;
		}
		else
		{
			//根左右
			tnode = new BinaryTreeNode<T>; //创建根节点
			tnode->data = *pstr;
			CreateBTreeAccordPTRecu(tnode->leftChild, ++pstr); //创建左子树
			CreateBTreeAccordPTRecu(tnode->rightChild, ++pstr); //创建右子树			
		}
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
	//（7）二叉树链式存储的常用操作
	//(7.1)类定义、初始化和释放操作
	//（7.2）创建树节点操作
	//（7.3）遍历操作（二叉树遍历操作的时间复杂度为O(n)）。




	_nmsp1::BinaryTree<int> mytree;
	//创建一棵二叉树
	_nmsp1::BinaryTreeNode<int>* rootpoint = mytree.CreateNode(nullptr, E_Root, 'A'); //创建树根节点A。
	_nmsp1::BinaryTreeNode<int>* subpoint = mytree.CreateNode(rootpoint, E_ChildLeft, 'B'); //创建树根的左子节点B
	subpoint = mytree.CreateNode(subpoint, E_ChildLeft, 'D');//创建左子节点B下的左子节点D

	subpoint = mytree.CreateNode(rootpoint, E_ChildRight, 'C'); //创建树根的右子节点C
	subpoint = mytree.CreateNode(subpoint, E_ChildRight, 'E'); //创建右子节点C的右子节点E


	//前序遍历序列：ABD###C#E##(给出一个扩展二叉树的前序遍历序列，是能够唯一确定一棵二叉树的)
	_nmsp1::BinaryTree<int> mytree2;
	mytree2.CreateBTreeAccordPT((char*)"ABD###C#E##");

	cout << "前序遍历序列为：";
	mytree2.preOrder(); //前序遍历
	cout << endl; //换行


	cout << "中序遍历序列为：";
	mytree2.inOrder(); //中序遍历
	cout << endl; //换行


	cout << "后序遍历序列为：";
	mytree2.postOrder(); //后序遍历

	cout << endl; //换行
	cout << "层序遍历序列为：";
	mytree2.levelOrder();

	

	
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





/*

//链式栈相关代码
namespace _nmsp_1
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

//链式队列相关代码
namespace _nmsp0
{
	//链式队列中每个节点的定义
	template <typename T> //T代表数据元素的类型
	struct QueueNode
	{
		T        data;       //数据域，存放数据元素
		QueueNode<T>* next;  //指针域，指向下一个同类型（和本节点类型相同）节点
	};

	//链式队列的定义
	template <typename T> //T代表数组中元素的类型
	class LinkQueue
	{
	public:
		LinkQueue();                          //构造函数，参数可以有默认值
		~LinkQueue();                         //析构函数

	public:
		bool EnQueue(const T& e);            //入队列（增加数据）		
		bool DeQueue(T& e);                  //出队列（删除数据）
		bool GetHead(T& e);                  //读取队头元素，但该元素并没有出队列而是依旧在队列中		

		void DispList();                     //输出链式队列中的所有元素
		int  ListLength();                   //获取链式队列的长度（实际拥有的元素数量）		

		bool IsEmpty();                      //判断链式队列是否为空		

	private:
		QueueNode<T>* m_front;               //头指针（指向头结点），这一端允许出队（删除）
		QueueNode<T>* m_rear;                //专门引入尾指针以方便入队（插入）操作
		int m_length;                        //记录长度，方便获取长度
	};

	//通过构造函数对链式队列进行初始化
	template <typename T>
	LinkQueue<T>::LinkQueue()
	{
		m_front = new QueueNode<T>; //先创建一个头结点
		m_front->next = nullptr;
		m_rear = m_front;
		m_length = 0;

		//若不带头节点的链式队列初始化代码应该如下，供参考
		//m_front = nullptr;
		//m_rear = nullptr;
	}

	//通过析构函数对链式队列进行资源释放
	template <typename T>
	LinkQueue<T>::~LinkQueue()
	{
		QueueNode<T>* pnode = m_front->next;
		QueueNode<T>* ptmp;
		while (pnode != nullptr) //该循环负责释放数据节点
		{
			ptmp = pnode;
			pnode = pnode->next;
			delete ptmp;
		}
		delete m_front;             //释放头结点		
		m_front = m_rear = nullptr; //非必须
		m_length = 0;               //非必须
	}

	//入队列（增加数据），也就是从队尾增加数据
	template <typename T>
	bool LinkQueue<T>::EnQueue(const T& e)
	{
		QueueNode<T>* node = new QueueNode<T>;
		node->data = e;
		node->next = nullptr;

		m_rear->next = node; //新节点插入到m_rear后面
		m_rear = node;       //更新队列尾指针

		m_length++;
		return true;
	}

	//出队列（删除数据），也就是删除队头数据
	template <typename T>
	bool LinkQueue<T>::DeQueue(T& e)
	{
		if (IsEmpty() == true)
		{
			cout << "当前链式队列为空，不能进行出队操作!" << endl;
			return false;
		}

		QueueNode<T>* p_willdel = m_front->next;
		e = p_willdel->data;

		m_front->next = p_willdel->next;
		if (m_rear == p_willdel) //队列中只有一个元素节点（被删除后，整个队列就为空了）
			m_rear = m_front;  //设置队列为空(尾指针指向头指针)

		delete p_willdel;
		m_length--;
		return true;
	}

	//读取队头元素，但该元素并没有出队列而是依旧在队列中
	template <typename T>
	bool LinkQueue<T>::GetHead(T& e)
	{
		if (IsEmpty() == true)
		{
			cout << "当前链式队列为空，不能读取队头元素!" << endl;
			return false;
		}

		e = m_front->next->data;
		return true;
	}

	//输出链式队列中的所有元素，时间复杂度为O(n)
	template<class T>
	void LinkQueue<T>::DispList()
	{
		QueueNode<T>* p = m_front->next;
		while (p != nullptr)
		{
			cout << p->data << " ";  //每个数据之间以空格分隔
			p = p->next;
		}
		cout << endl; //换行
	}

	//获取链式队列的长度（实际拥有的元素数量），时间复杂度为O(1)
	template<class T>
	int LinkQueue<T>::ListLength()
	{
		return m_length;
	}

	//判断链式队列是否为空，时间复杂度为O(1)
	template<class T>
	bool LinkQueue<T>::IsEmpty()
	{
		if (m_front == m_rear) //当然，换一种判断方式也行：if(m_front->next == nullptr) return true;
		{
			return true;
		}
		return false;
	}
}

*/
