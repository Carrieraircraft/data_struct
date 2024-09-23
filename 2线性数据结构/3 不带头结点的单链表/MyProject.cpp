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

//------------------------------
namespace _nmsp1
{
	//单链表中每个节点的定义
	template <typename T> //T代表数据元素的类型
	struct Node
	{
		T   data; //数据域，存放数据元素
		Node <T>* next; //指针域，指向下一个同类型（和本类型相同）节点。
	};

	//单链表的定义
	template <typename T>
	class LinkList
	{
	public:
		LinkList();  //构造函数
		~LinkList() {} //析构函数

	public:
		bool ListInsert(int i, const T& e); //在第i个位置插入指定元素e

		bool InsertPriorNode(Node<T>* pcurr, const T& e);

		bool ListDelete(int i); //删除第i个位置的元素

		bool GetElem(int i, T& e); //获得第i个位置的元素值
		int LocateElem(const T& e); //按元素值查找其在单链表中第一次出现的位置

		void DispList(); //输出单链表中的所有元素
		int ListLength(); //获取单链表的长度
		bool Empty();   //判断单链表是否为空
		void ReverseList(); //翻转单链表
	private:
		Node<T>* m_head;  //头指针（指向链表第一个节点的指针，如果链表有头节点，则指向头结点）
		int m_length; //单链表当前长度（当前有几个元素），为编写程序更方便和提高程序运行效率而引入，但不是必须引入。
	};
	
	//通过构造函数对单链表进行初始化
	template <typename T>
	LinkList<T>::LinkList()
	{
		m_head = new Node<T>; //先创建一个头节点
		m_head->next = nullptr;
		m_length = 0; //头节点不计入单链表的长度。

		////如果对于不带头的单链表：
		//m_head = nullptr;
		//m_length = 0;
	}


	//在第i个位置（位置编号从1开始）插入指定元素e
	template <typename T>
	bool LinkList<T>::ListInsert(int i, const T& e)
	{
		//判断插入位置i是否合法，i的合法值应该是从1到m_length+1之间
		if (i < 1 || i >(m_length + 1))
		{
			cout << "元素" << e << "插入的位置" << i << "不合适，合法的位置是1到"
				<< m_length + 1 << "之间!" << endl;
			return false;
		}
		Node<T>* p_curr = m_head;

		//整个for循环用于找到第i-1个节点
		for (int j = 0; j < (i - 1); ++j) //j从0开始，表示p_curr刚开始指向的是第0个节点（头节点）
		{
			p_curr = p_curr->next; //pcurr会找到当前要插入的位置，比如要在第2个位置插入，pcurr会指向第1个位置
		}

		Node<T>* node = new Node<T>;  //(1)
		node->data = e;  //(2)
		node->next = p_curr->next; //(3) 让新节点链上后续链表，因为pcurr->next指向后续的链表节点。
		p_curr->next = node; //(4)让当前位置链上新节点，因为node指向新节点

		cout << "成功在位置为" << i << "处插入元素" << e << "!" << endl;
		m_length++;  //实际表长+1
		return true;
	}

	////在第i个位置（位置编号从1开始）插入指定元素e【不带头节点版本】
	//template <typename T>
	//bool LinkList<T>::ListInsert(int i, const T& e)
	//{
	//	//判断插入位置i是否合法，i的合法值应该是从1到m_length+1之间
	//	if (i < 1 || i >(m_length + 1))
	//	{
	//		cout << "元素" << e << "插入的位置" << i << "不合适，合法的位置是1到"
	//			<< m_length + 1 << "之间!" << endl;
	//		return false;
	//	}

	//	if (i == 1) //插入到第一个位置与插入到其他位置不同，要单独处理
	//	{
	//		Node<T>* node = new Node<T>;
	//		node->data = e;
	//		node->next = m_head;
	//		m_head = node; //头指针指向新插入的第一个节点
	//		cout << "成功在位置为" << i << "处插入元素" << e << "!" << endl;
	//		m_length++;  //实际表长+1
	//		return true;
	//	}

	//	//插入的不是第一个位置则程序流程向下走
	//	Node<T>* p_curr = m_head;
	//	//整个for循环用于找到第i-1个节点
	//	for (int j = 1; j < (i - 1); ++j) //j从1开始，表示p_curr刚开始指向的是第1个节点
	//	{
	//		p_curr = p_curr->next; //pcurr会找到当前要插入的位置，比如要在第2个位置插入，pcurr会指向第1个位置（节点）
	//	}
	//	Node<T>* node = new Node<T>;
	//	node->data = e;
	//	node->next = p_curr->next; //让新节点链上后续链表，因为p_curr->next指向后序的链表节点
	//	p_curr->next = node; //当前位置链上新节点，因为node指向新节点
	//	cout << "成功在位置为" << i << "处插入元素" << e << "!" << endl;
	//	m_length++;  //实际表长+1
	//	return true;
	//}

	template<typename T>
	bool LinkList<T>::InsertPriorNode(Node<T>* pcurr, const T& e)
	{
		//在节点pcurr之前插入新节点，新节点数据域元素值为e，请大家自行添加相关代码。。。。
	}
}

int main()
{		
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口
	
	//第2章 线性表:线性结构，保存的数据象线一样按顺序排列，数据之间一对一的关系。
	//第三节 线性表的链式存储
	//（1）单链表
	//用链式存储方式实现的线性表称为链表。链表又可以分为a)单链表、b)双链表、c)循环链表、d)静态链表。
	 //节点：每个存储数据元素的内存空间被称为一个节点。
	  //单链表中，每个节点都包含 数据域 和指针域。
	   //头节点（哨兵节点）
	//不带头节点的单链表和带头节点的单链表有什么不同：
	//a)不带头链表初始化时不创建任何节点。带头链表初始化时要把头结点创建出来（可以把该头节点看成第0个节点）。
    //b)带头节点的单链表中的头结点不存放任何实际元素数据。头结点之后的下一个节点才开始存放数据。
	//c)不带头结点的单链表在编写基本操作代码（插入，删除等）时更繁琐，往往需要对第一个或者最后一个数据节点进行单独处理。
	//(1.1)单链表的类定义、初始化操作
	//(1.2)单链表元素插入操作
	//更好的插入操作实现方式：
	//已知a2，要求往a2之前插入a5，简单方法是：
	 //a)往a2之后插入a5
	 //b)把a2和a5数据域交换
	//如果频繁的向单链表末尾插入新节点，可以考虑引入一个表尾指针。该指针在单链表为空时指向头节点。
	  //在单链表非空时要注意保持其指向最后一个节点。





	_nmsp1::LinkList<int> slinkobj;
	slinkobj.ListInsert(1, 12);
	slinkobj.ListInsert(1, 24);
	slinkobj.ListInsert(3, 48);
	slinkobj.ListInsert(2, 100);

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


