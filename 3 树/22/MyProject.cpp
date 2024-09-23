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
		/*m_front = nullptr;
		m_rear = nullptr;*/
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
	//红黑树中每个节点的定义
	template <typename T> //T代表数据元素类型
	class RBNode
	{
		T   data;
		RBNode* leftChild; //左子节点指针
		RBNode* rightChild; //右子节点指针
		RBNode* parentNd; //父节点指针，引入方便操作。
		bool isRed; //是否是红色节点，true：是。false：不是（而是黑色节点）
	};

	//红黑树的定义
	template <typename T>
	class RBTree
	{
	public:
		RBTree() //构造函数
		{
			root = nullptr;
		}
		~RBTree() //析构函数
		{
			ReleaseNode(root);
		}

		//层序遍历二叉树，方便显示
		void levelOrder()
		{
			levelOrder(root);
		}
		//获取某个节点的高度（根高度为1，往下高度依次+1），用于显示节点时换行的目的
		int getNodeLevel(RBNode<T>* tNode)
		{
			int icurlvl = 0;
			while (tNode != nullptr)
			{
				tNode = tNode->parentNd;
				icurlvl++;
			}
			return icurlvl;
		}

		void levelOrder(RBNode<T>* tNode)
		{
			if (tNode != nullptr) //若二叉树非空
			{
				RBNode<T>* tmpnode;
				_nmsp0::LinkQueue< RBNode<T>* > lnobj; //注意：队列的元素类型为“节点指针”类型。
				lnobj.EnQueue(tNode); //先把根节点指针入队
				int currdislvl = 1; //当前显示第几层，根算第一层
				const char* pr = "[红]";
				const char* pb = "[黑]";
				char* ptmp;
				while (!lnobj.IsEmpty()) //循环判断队列是否为空
				{
					lnobj.DeQueue(tmpnode); //出队列
					int lvl = getNodeLevel(tmpnode);
					if (lvl != currdislvl) //用于换行
					{
						currdislvl = lvl;
						cout << endl;
					}
					if (tmpnode->isRed == false)
						ptmp = (char*)pb;
					else
						ptmp = (char*)pr;

					cout << tmpnode->data << ptmp << "    ";
					if (tmpnode->leftChild != nullptr)
						lnobj.EnQueue(tmpnode->leftChild); //左孩子入队

					if (tmpnode->rightChild != nullptr)
						lnobj.EnQueue(tmpnode->rightChild); //右孩子入队
				} //end while				
			} //end if
		}

		//插入元素
		void InsertElem(const T& e) //不可以指定插入位置，程序内部会自动确定插入位置
		{
			InsertElem(root, e);
		}
		void InsertElem(RBNode<T>*& tNode, const T& e) //注意第一个参数类型
		{
			RBNode<T>* point = tNode; //从指向根节点开始
			RBNode<T>* parent = nullptr; //保存父亲节点，根节点的父亲节点肯定为nullptr；
			//通过一个while循环寻找要插入的节点的位置，同时还要把插入路径上所经过的所有节点保存到栈中，因为
			   //这些节点的平衡因子可能需要调整
			while (point != nullptr)
			{
				if (e == point->data)
					return; //要插入的数据与当前树中某节点数据相同，则不允许插入，直接返回

				parent = point; //记录父节点，因为后序子节点要往下走，找合适自己的位置
				if (e > point->data)
					point = point->rightChild;
				else
					point = point->leftChild;
			} //end while

			//走到这里，point等于nullptr，该生成新节点了
			point = new RBNode<T>;
			point->data = e;
			point->leftChild = nullptr;
			point->rightChild = nullptr;
			point->parentNd = nullptr;
			point->isRed = true; //缺省插入的节点先给红色

			if (parent == nullptr)
			{
				//创建的是根节点
				point->isRed = false; //根节点是黑色
				tNode = point;
				return;
			}
			//走到这里表示创建的不是根节点，那么就要把孩子链到父亲上
			if (e > parent->data)
				parent->rightChild = point; //在父节点的右树链入
			else
				parent->leftChild = point; //在父节点的左树链入
			point->parentNd = parent; //记录父节点的指针
			if (parent->isRed == false) //父节点为黑色，不需要做什么
				return;

			//能走到这里，要插入的节点肯定是至少在第三层
			//父节点为红色才能走下来（当前节点也是红色的）
			BalanceTune(point, parent);
			root->isRed = false; //根节点颜色无条件给黑色 
		}

		//平衡性调整
		void BalanceTune(RBNode<T>* point, RBNode<T>* parent) //point:当前节点，parent：当前节点的父亲节点
		{
			//....
		}

	private:
		void ReleaseNode(RBNode<T>* pnode)
		{
			if (pnode != nullptr)
			{
				ReleaseNode(pnode->leftChild);
				ReleaseNode(pnode->rightChild);
			}
			delete pnode;
		}

	private:
		RBNode<T>* root; //树根指针
	};


	
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//第3章 树
	//第二节  二叉树
	//（11）红黑树（Red - Black Tree）
	//（11.1）基本概念、定义及基础实现代码
	//“平衡性调整”
	//“非严格平衡二叉树”：
	//红黑树（Read-Black Tree)，R-B树。是一种高效的二叉查找树。
	//发明者：Rudolf Bayer   1972年发明，当时被称为  对称/平衡二叉B树。
	//1978年由 Leo J.Guibas和Robert Sedgewick修改为了  红黑树。
	//相对平衡：任一节点左子树和右子树高度之差很可能会超过1.
	//红黑树性质：
	//a)每个节点要么是黑色，要么是红色，而根节点必须是黑色。
	//b)每个叶子节点都是黑色的空节点（Nil），这一点和其他树不同。
	     //也就是说叶子节点不存储数据。Nil可以（一般）不绘制出来。
	//c)任何相邻节点（用线条连接起来的节点比如当前节点的父或者子节点）不能同时为红色（红色节点不能相邻）；
		//理解：c.1)红节点是被黑色节点分隔开的   ；c.2)红色节点的两个孩子节点或者父亲节点必须是黑色的。
	       //c.3)从叶节点到根的所有路径上不可以有两个连续的红色节点。
	//d)红黑树左右子树高度差很可能会超过1甚至超过更多。红黑树的平衡性是指的是对于每个节点，从该节点到达其所能够
	     //到达的叶子节点的所有路径都包含相同数量的黑色节点（黑色节点数量称为 黑高度 或者 黑高，用于保证黑色节点的平衡性)。

	//总结：红黑树：a)黑色的根.b)黑色的叶子;c)红色节点不相邻（红色节点的父亲和孩子都是黑色节点）;
	      //d)当前节点到其所有叶节点包含的黑色节点数量相同。
	//为什么有AVL树还需要引入红黑树：a)AVL平衡性调整效率比较低。b)平衡性调整旋转次数少甚至不需要旋转只需要调整颜色（红色修改为黑色）。
	       //c)插入删除红黑树更快。    换句话说，但从搜索角度，AVL树更快。如果频繁进行插入和删除操作，因为红黑树需要
	           //更少的旋转，无疑效率会更高（红黑树的查找、插入、删除操作性能稳定）。

	//红黑树从根节点到叶子的最长路径不超过最短路径的两倍。
	//红黑树的高度大概2logn。红黑树的高度只比AVL树高1倍，在执行效率上差不太多。因为上面提到的优势，所以性能更好。

	//红黑树编程问题：
	//a)往往不需要考虑叶子节点，也就是那个黑色的空节点（nil）。
	//b)红黑树节点查找操作同二叉查找树的节点查找操作（SearchElem成员函数）完全一样，大家可以参考前面已经实现的代码。
	
	//（11.2）红黑树插入操作后的平衡性调整及实现代码
	//通过节点变色或者旋转来实现平衡性调整。
	//失衡：插入节点，删除节点
	//插入节点操作一般分为几种情况：
	//a)对于没有任何节点的空树那么直接创建一个黑色节点作为根节点。
	//b)对于非空的树，查找插入位置并插入一个红色节点（不会增加黑色高度以尽量减少平衡性调整），
	    //然后要判断该节点的父节点：b.1)如果父节点为黑色，此时不需要做什么。
	          //b.2)如果父节点为红色，会违背红黑树性质3，此时必须进行平衡性调整。
	//平衡性调整情况1：如图3.2.11_7 ，父节点是爷爷节点的左孩子，叔叔节点存在且为红色。
	// 	   爷爷节点为黑色，父亲节点为红色，有叔叔节点且为红色，父亲节点是爷爷节点的左孩子
	//调整方法为：将父亲节点和叔叔节点变成黑色，将爷爷节点变成红色，如果爷爷节点是整个红黑树的根，
	      //则要将爷爷节点恢复为黑色。如图3.2.11_8 。
	//平衡性调整情况2：如图3.2.11_12 ，父亲接单是爷爷节点的左孩子，新节点是父亲节点的左孩子，叔叔节点不存在或者存在但为黑色
	       //爷爷节点为黑色，父亲节点为红色，没叔叔节点或有叔叔节点且为黑色，父亲节点是爷爷节点的左孩子，插入的新红色节点是父亲节点的左孩子
	//调整方法为：以爷爷节点为根向右旋转。接着将原父亲节点变为黑色，原爷爷节点变为红色。
	//平衡性调整情况3：如图3.2.11_14 ，父亲节点是爷爷节点的左孩子，新节点是父亲节点的右孩子，叔叔节点不存在或者存在但为黑色。
	//调整方法为：先父亲节点为根左旋，再以爷爷节点为根右旋。接着原来的新节点变为黑色，原来的爷爷节点变为红色。
	//平衡性调整情况4，5，6。



	


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




