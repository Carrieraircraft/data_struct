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
//#pragma warning(disable : 4996) 

namespace _nmsp1
{
	//单循环链表中每个节点的定义
	template <typename T> //T代表数据元素的类型
	struct Node
	{
		T        data;  //数据域，存放数据元素
		Node<T>* next;  //指针域，指向下一个同类型（和本节点类型相同）节点
	};

	//单循环链表的定义
	template <typename T>
	class CirLinkList
	{
	public:
		CirLinkList();      //构造函数，参数可以有默认值
		~CirLinkList();     //析构函数

	public:
		bool ListInsert(int i, const T& e);  //在第i个位置插入指定元素e
		bool ListDelete(int i);              //删除第i个位置的元素

		bool GetElem(int i, T& e);           //获得第i个位置的元素值
		int  LocateElem(const T& e);         //按元素值查找其在单循环链表中第一次出现的位置

		void DispList();                     //输出单循环链表中的所有元素
		int  ListLength();                   //获取单循环链表的长度
		bool Empty();                        //判断单循环链表是否为空		


	private:
		Node<T>* m_head; //头指针（指向链表第一个节点的指针，如果链表有头结点则指向头结点）
		int m_length;    //单循环链表当前长度（当前有几个元素），为编写程序更加方便和提高程序运行效率而引入，但不是必须引入
	};

	//通过构造函数对单循环链表进行初始化
	template <typename T>
	CirLinkList<T>::CirLinkList()
	{
		m_head = new Node<T>; //先创建一个头结点
		//m_head->next = nullptr;
		m_head->next = m_head;
		m_length = 0;  //头结点不计入单循环链表的长度		
	}

	//在第i个位置（位置编号从1开始）插入指定元素e
	template <typename T>
	bool CirLinkList<T>::ListInsert(int i, const T& e)
	{
		//判断插入位置i是否合法，i的合法值应该是1到length+1之间
		if (i < 1 || i >(m_length + 1))
		{
			cout << "元素" << e << "插入的位置" << i << "不合法，合法的位置是1到" << m_length + 1 << "之间!" << endl;
			return false;
		}

		Node<T>* p_curr = m_head;

		//整个for循环用于找到第i-1个节点
		for (int j = 0; j < (i - 1); ++j)//j从0开始，表示p_curr刚开始指向的是第0个节点（头结点）
		{
			p_curr = p_curr->next; //pcurr会找到当前要插入的位置，比如要在第2个位置插入，pcurr会指向第1个位置(节点)
		}

		Node<T>* node = new Node<T>;
		node->data = e;
		node->next = p_curr->next;//让新节点链上后续链表，因为pcurr->next指向后续的链表节点
		p_curr->next = node;//让当前位置链上新节点，因为node指向新节点

		cout << "成功在位置为" << i << "处插入元素" << e << "!" << endl;
		m_length++;	        //实际表长+1
		return true;
	}


	//删除第i个位置的元素
	template < typename T>
	bool CirLinkList<T>::ListDelete(int i)
	{
		if (m_length < 1)
		{
			cout << "当前单循环链表为空，不能删除任何数据!" << endl;
			return false;
		}
		if (i < 1 || i > m_length)
		{
			cout << "删除的位置" << i << "不合法，合法的位置是1到" << m_length << "之间!" << endl;
			return false;
		}

		Node<T>* p_curr = m_head;

		//整个for循环用于找到第i-1个节点
		for (int j = 0; j < (i - 1); ++j)//j从0开始，表示p_curr刚开始指向的是第0个节点（头结点）
		{
			p_curr = p_curr->next; //pcurr会找到当前要删除的位置所代表的节点的前一个节点的位置，比如要删除第2个位置的节点，pcurr会指向第1个位置(节点)
		}

		Node<T>* p_willdel = p_curr->next; //p_willdel指向待删除的节点
		p_curr->next = p_willdel->next; //第i-1个节点的next指针指向第i+1个节点
		cout << "成功删除位置为" << i << "的元素，该元素的值为" << p_willdel->data << "!" << endl;
		m_length--;       //实际表长-1
		delete p_willdel;
		return true;
	}

	//获得第i个位置的元素值
	template<class T>
	bool CirLinkList<T>::GetElem(int i, T& e)
	{
		if (m_length < 1)
		{
			cout << "当前单循环链表为空，不能获取任何数据!" << endl;
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

	//按元素值查找其在单循环链表中第一次出现的位置
	template<class T>
	int CirLinkList<T>::LocateElem(const T& e)
	{
		Node<T>* p_curr = m_head;
		for (int i = 1; i <= m_length; ++i)
		{
			if (p_curr->next->data == e)
			{
				cout << "值为" << e << "的元素在单循环链表中第一次出现的位置为" << i << "!" << endl;
				return i;
			}
			p_curr = p_curr->next;
		}
		cout << "值为" << e << "的元素在单循环链表中没有找到!" << endl;
		return -1;  //返回-1表示查找失败
	}

	//输出单循环链表中的所有元素，时间复杂度为O(n)
	template<class T>
	void CirLinkList<T>::DispList()
	{
		Node<T>* p = m_head->next;
		while (p != m_head) //这里采用while循环或者for循环书写都可以
		{
			cout << p->data << " ";  //每个数据之间以空格分隔
			p = p->next;
		}
		cout << endl; //换行
	}

	//获取单循环链表的长度，时间复杂度为O(1)
	template<class T>
	int  CirLinkList<T>::ListLength()
	{
		return m_length;
	}

	//判断单循环链表是否为空，时间复杂度为O(1)
	template<class T>
	bool CirLinkList<T>::Empty()
	{
		if (m_head->next == m_head) //单循环链表为空
		{
			return true;
		}
		return false;
	}


	//通过析构函数对单循环链表进行资源释放
	template <typename T>
	CirLinkList<T>::~CirLinkList()
	{
		Node<T>* pnode = m_head->next;
		Node<T>* ptmp;
		while (pnode != m_head) //该循环负责释放数据节点
		{
			ptmp = pnode;
			pnode = pnode->next;

			delete ptmp;
		}
		delete m_head;    //释放头结点
		m_head = nullptr; //非必须
		m_length = 0;     //非必须
	}


}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	_nmsp1::CirLinkList<int> slinkobj;
	slinkobj.ListInsert(1, 12);
	slinkobj.ListInsert(1, 24);
	slinkobj.ListInsert(3, 48);
	slinkobj.ListInsert(2, 100);
	slinkobj.DispList();

	slinkobj.ListDelete(4);

	int eval = 0;
	slinkobj.GetElem(3, eval); //如果GetElem()返回true，则eval中保存着获取到的元素值
	int findvalue = 100; //在单循环链表中要找的元素值
	slinkobj.LocateElem(findvalue);
	slinkobj.DispList();
	cout << "单循环链表的长度为：" << slinkobj.ListLength() << endl;
	
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

