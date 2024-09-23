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
		~LinkList(); //析构函数

	public:
		bool ListInsert(int i, const T& e); //在第i个位置插入指定元素e

		bool InsertPriorNode(Node<T>* pcurr, const T& e);

		bool ListDelete(int i); //删除第i个位置的元素
		bool DeleteNode(Node<T>* pdel); 

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

	//删除第i个位置的元素
	template<typename T>
	bool LinkList<T>::ListDelete(int i)
	{
		if (m_length < 1)
		{
			cout << "当前单链表为空，不能删除任何数据!" << endl;
			return false;
		}
		if (i < 1 || i > m_length)
		{
			cout << "删除位置" << i << "不合法，合法的位置是1到" << m_length << "之间!" << endl;
			return false;
		}

		Node<T>* p_curr = m_head;
		//整个for循环用于找到第i-1个节点
		for (int j = 0; j < (i - 1); ++j) //j从0开始，表示p_curr刚开始指向额的是第0个节点（头节点）
		{
			p_curr = p_curr->next; //p_curr会找到当前要删除的位置所代表的节点的前一个节点的位置
		}
		Node<T>* p_willdel = p_curr->next; //p_willdel指向待删除的节点
		p_curr->next = p_willdel->next; //第i-1个节点的next指针指向了第i+1个节点
		cout << "成功删除位置为" << i << "的元素，该元素的值为" << p_willdel->data << "!" << endl;
		m_length--; //实际表长-1
		delete p_willdel;
		return true;
	}

	template<typename T>
	bool LinkList<T>::DeleteNode(Node<T>* pdel)
	{
		//删除pdel所指向的节点，请自行添加相关代码......
		//特别注意书写和测试删除最后一个节点时可能遇到的问题....
	}

	//获得第i个位置的元素值
	template<typename T>
	bool LinkList<T>::GetElem(int i, T& e) 
	{
		if (m_length < 1)
		{
			cout << "当前单链表为空，不能获取任何数据!" << endl;
			return false;
		}
		if (i < 1 || i > m_length)
		{
			cout << "获取元素的位置" << i << "不合法，合法的位置是1到" << m_length << "之间!" << endl;
			return false;
		}
		Node<T>* p_curr = m_head;
		for (int j = 0; j < i; ++j)
		{
			p_curr = p_curr->next;
		}
		e = p_curr->data;
		cout << "成功获取位置为" << i << "的元素，该元素的值为" << e << "!" << endl;
		return true;
	}

	
	//按元素值查找其在单链表中第一次出现的位置
	template<typename T>
	int LinkList<T>::LocateElem(const T& e)
	{
		Node<T>* p_curr = m_head;
		for (int i = 1; i <= m_length; ++i)
		{
			if(p_curr->next->data == e)
			{
				cout << "值为" << e << "的元素在单链表中第一次出现的位置为" << i << "!" << endl;
				return i;
			}
			p_curr = p_curr->next;
		}
		cout << "值为" << e << "的元素在单链表中没有找到！" << endl;
		return  -1; //返回-1表示查找失败
	}

	//输出单链表中的所有元素，时间复杂度O(n)
	template<typename T>
	void LinkList<T>::DispList()
	{
		Node<T>* p = m_head->next;
		while (p != nullptr) //这里采用while循环或者for循环书写都可以
		{
			cout << p->data << " "; //每个数据之间以空格分隔
			p = p->next;
		}
		cout << endl; //换行
	}

	//获取单链表的长度，O(1)
	template<typename T>
	int LinkList<T>::ListLength()
	{
		return m_length;
	}

	//判断单链表是否为空
	template<typename T>
	bool LinkList<T>::Empty()
	{
		if (m_head->next == nullptr) //单链表为空（如果是不带头节点的单链表if(m_head == nullptr)来判断是否为空。
		{
			return true;
		}
		return false;
	}

	//翻转单链表
	template<typename T>
	void LinkList<T>::ReverseList()
	{
		if (m_length <= 1)
		{
			//如果顺序表中没有元素或者只有一个元素，那么就不用做任何操作
			return;
		}

		//至少有两个节点才会走到这里
		Node<T>* pothersjd = m_head->next->next; //指向从第二个节点开始的后续节点
		m_head->next->next = nullptr; //把第一个节点的指针域先置空。

		Node<T>* ptmp;
		while (pothersjd != nullptr)
		{
			//比如a1,a2,a3,a4共4个节点，第一次执行该循环时指向：注意下面代码注释
			ptmp = pothersjd;  //ptmp代表a2
			pothersjd = pothersjd->next; //pothersjd指向a3

			ptmp->next = m_head->next;  //a2指向a1
			m_head->next = ptmp;  //头节点指向a2
		}
	}

	//析构函数
	template<typename T>
	LinkList<T>::~LinkList()
	{		
		Node<T>* pnode = m_head->next;
		Node<T>* ptmp;
		while (pnode != nullptr) //该循环负责释放数据节点
		{
			ptmp = pnode;
			pnode = pnode->next;

			delete ptmp;
		}
		delete m_head; //释放头结点
		m_head = nullptr; //非必须
		m_length = 0; //非必须
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
	//(1.3)单链表元素删除操作
	//(1.4)单链表元素获取操作
	//(1.5)单链表元素的其他常用操作
	//(1.6)单链表的释放操作
	//(1.7)单链表的特点及代码书写和测试建议
	  //特点总结：
	   //a)不需要大量连续存储空间存放数据元素，扩容方便
	   //b)插入和删除节点方便。O(n)。链表与数组比，更适合插入、删除 操作频繁的场景。
	   //c)存放后继指针要额外消耗内存空间。体现了利用空间换取时间来提高算法时间的编程思想。
	     //但对于内存紧张的硬件设备，就要考虑单链表是否合适。
	   //d)内存空间不连续所以无法实现随机访问链表中元素。沿着链逐个查找元素。O(n)
	//代码书写测试建议：
	  //a)多通过图来理解逻辑并书写出自己认为正确的代码
	  //b)链表为空时，测试代码能否正常工作。
	  //c)当链表只有一个数据节点时，测试代码能否正常工作。
	  //d)分别测试在处理链表中第一个和最后一个节点时代码能否正常工作。
	  //e)发现程序执行异常并百思不得其解时，通过设置断点对代码进行调试，逐行跟踪并观察代码的执行情况就是必须的解决问题的手段。
	  





	_nmsp1::LinkList<int> slinkobj;
	slinkobj.ListInsert(1, 12);
	slinkobj.ListInsert(1, 24);
	slinkobj.ListInsert(3, 48);
	slinkobj.ListInsert(2, 100);

	slinkobj.ListDelete(4);
	int eval = 0;
	slinkobj.GetElem(3, eval); //如果GetElem返回true，则eval中保存着获取到的元素值
	int findvalue = 100; //在单链表中要找的元素值
	slinkobj.LocateElem(findvalue);

	slinkobj.DispList();
	slinkobj.ReverseList();
	slinkobj.DispList();



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


