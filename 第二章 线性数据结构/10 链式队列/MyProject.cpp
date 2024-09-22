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
	//链式队列中每个节点的定义
	template<typename T> //T代表数据元素的类型
	struct QueueNode
	{
		T   data; //数据域，存放数据元素
		QueueNode<T>* next; //指针域，指向下一个同类型（和本节点类型相同）节点。
	};

	//链式队列的定义
	template<typename T> //T代表数据元素的类型
	class LinkQueue
	{
	public:
		LinkQueue();   //构造函数
		~LinkQueue();  //析构函数

	public:
		bool EnQueue(const T& e); //入队列（增加数据）；
		bool DeQueue(T& e);  //出队列（删除数据）；
		bool GetHead(T& e);  //读取队头元素，但该元素并没有出队列而是依旧在队列中。

		void DispList(); //输出链式队列中的所有元素
		int ListLength(); //获取链式队列的长度（实际拥有的元素数量）

		bool IsEmpty(); //判断链式队列是否为空

	private:
		QueueNode<T>* m_front;  //头指针（指向头节点），这一端允许出队（删除）
		QueueNode<T>* m_rear;  //专门引入尾指针以方便入队（插入）操作
		int m_length; //记录长度，方便长度
	};

	//通过构造函数对链式队列进行初始化
	template<typename T>
	LinkQueue<T>::LinkQueue()
	{
		m_front = new QueueNode<T>; //先创建一个头节点
		m_front->next = nullptr;
		m_rear = m_front;
		m_length = 0;
	}

	//通过析构函数对链式队列进行资源释放
	template<typename T>
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
		delete m_front; //释放头节点
		m_front = m_rear = nullptr; //非必须
		m_length = 0; //非必须
	}

	//入队列（增加数据），也就是从队尾增加数据
	template<typename T>
	bool LinkQueue<T>::EnQueue(const T& e)
	{
		QueueNode<T>* node = new QueueNode<T>;
		node->data = e;
		node->next = nullptr;

		m_rear->next = node; //新节点插入到m_rear后面
		m_rear = node;  //更新队尾指针

		m_length++;
		return true;
	}

	//出队列（删除数据），也就是删除队头数据
	template<typename T>
	bool LinkQueue<T>::DeQueue(T& e)
	{
		if (IsEmpty() == true)
		{
			cout << "当前链式队列为空，不能进行出队操作！" << endl;
			return false;
		}
		QueueNode<T>* p_willdel = m_front->next;
		e = p_willdel->data;

		m_front->next = p_willdel->next;
		if (m_rear == p_willdel) //队列中只有一个元素节点（被删除后，整个队列为空）
		{
			m_rear = m_front; //设置队列为空，尾指针，指向头指针
		}

		delete p_willdel;
		m_length--;
		return true;
	}

	//读取队头元素，但该元素并没有出队列而是依旧在队列中
	template<typename T>
	bool LinkQueue<T>::GetHead(T& e)
	{
		if (IsEmpty() == true)
		{
			cout << "当前链式队列为空，不能读取队头元素！" << endl;
			return false;
		}
		e = m_front->next->data;
		return true;
	}

	//输出链式队列中的所有元素，时间复杂度O(n)
	template<typename T>
	void LinkQueue<T>::DispList()
	{
		QueueNode<T>* p = m_front->next;
		while (p != nullptr)
		{
			cout << p->data << "  "; //每个数据之间以空格分隔
			p = p->next;
		}
		cout << endl; //换行
	}

	//获取链式队列的长度（实际拥有的元素数量）。O(1)
	template<typename T>
	int LinkQueue<T>::ListLength()
	{
		return m_length;
	}

	//判断链式队列是否为空，时间复杂度O(1)
	template<typename T>
	bool LinkQueue<T>::IsEmpty()
	{
		if (m_front == m_rear)
			return true;
		return false;
	}
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//第五节  队列
	//（2）队列的链式存储（链式队列）:操作受限的单链表（尾部插，头部删）。
	//带头节点实现方式；
	//（3）双端队列:允许在两端插入、删除数据。STL，deque 容器
	   //输入受限的双端队列，输出受限的双端队列。






	_nmsp1::LinkQueue<int> lnobj;
	lnobj.EnQueue(150);

	int eval = 0;
	lnobj.DeQueue(eval);
	lnobj.EnQueue(200);
	lnobj.EnQueue(700);
	lnobj.DispList();

	
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


