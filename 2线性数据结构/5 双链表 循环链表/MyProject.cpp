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
	//双链表中每个节点的定义
	template <typename T> //T代表数据元素类型
	struct DblNode
	{
		T data; //数据域，用来存放数据元素
		DblNode<T>* prior; //前趋指针，指向前一个同类型（和本节点类型相同）的节点
		DblNode<T>* next; //后继指针，指向下一个同类型（和本节点类型相同）的节点
	};

	template <typename T>
	class DblLinkList
	{
	public:
		DblLinkList(); //构造函数
		~DblLinkList(); //析构函数

	public:
		bool ListInsert(int i, const T& e);  //在第i个位置插入指定元素e
		bool ListDelete(int i);              //删除第i个位置的元素


		bool GetElem(int i, T& e);           //获得第i个位置的元素值
		int  LocateElem(const T& e);         //按元素值查找其在双链表中第一次出现的位置

		void DispList();                     //输出双链表中的所有元素
		int  ListLength();                   //获取双链表的长度
		bool Empty();                        //判断双链表是否为空

		bool InsertPriorNode(DblNode<T>* pcurr, DblNode<T>* pnewnode)
		{
			//在节点pcurr之前插入新节点pnewnode，请自行添加代码......

			//return true;
		}

		bool DeleteNode(DblNode<T>* pdel)
		{
			//删除pdel所指向的节点，请自行添加相关代码
		}


	private:
		DblNode<T>* m_head; //头指针（指向链表第一个节点的指针，如果链表有头结点则指向头结点）
		int m_length;    //双链表当前长度（当前有几个元素），为编写程序更加方便和提高程序运行效率而引入，但不是必须引入
	};

	//通过构造函数对双链表进行初始化
	template <typename T>
	DblLinkList<T>::DblLinkList()
	{
		m_head = new DblNode<T>; //先创建一个头结点
		m_head->next = nullptr; //该值暂时为nullptr，因为还没有后继节点
		m_head->prior = nullptr; //该值一直为nullptr
		m_length = 0;  //头结点不计入双链表的长度		
	}

	//在第i个位置（位置编号从1开始）插入指定元素e
	template <typename T>
	bool DblLinkList<T>::ListInsert(int i, const T& e)
	{
		//判断插入位置i是否合法，i的合法值应该是1到length+1之间
		if (i < 1 || i >(m_length + 1))
		{
			cout << "元素" << e << "插入的位置" << i << "不合法，合法的位置是1到" << m_length + 1 << "之间!" << endl;
			return false;
		}

		DblNode<T>* p_curr = m_head;

		//整个for循环用于找到第i-1个节点
		for (int j = 0; j < (i - 1); ++j)//j从0开始，表示p_curr刚开始指向的是第0个节点（头结点）
		{
			p_curr = p_curr->next; //pcurr会找到当前要插入的位置，比如要在第2个位置插入，pcurr会指向第1个位置(节点)
		}

		DblNode<T>* node = new DblNode<T>;
		node->data = e;
		node->next = p_curr->next;//让新节点链上后续链表，因为pcurr->next指向后续的链表节点

		node->prior = p_curr;
		if (p_curr->next != nullptr)
			p_curr->next->prior = node;

		p_curr->next = node;//让当前位置链上新节点，因为node指向新节点

		cout << "成功在位置为" << i << "处插入元素" << e << "!" << endl;
		m_length++;	        //实际表长+1
		return true;
	}
	//输出双链表中的所有元素，时间复杂度为O(n)
	template<class T>
	void DblLinkList<T>::DispList()
	{
		DblNode<T>* p = m_head->next;
		while (p != nullptr) //这里采用while循环或者for循环书写都可以
		{
			cout << p->data << " ";  //每个数据之间以空格分隔
			p = p->next;
		}
		cout << endl; //换行
	}

	//通过析构函数对双链表进行资源释放
	template <typename T>
	DblLinkList<T>::~DblLinkList()
	{
		DblNode<T>* pnode = m_head->next;
		DblNode<T>* ptmp;
		while (pnode != nullptr) //该循环负责释放数据节点
		{
			ptmp = pnode;
			pnode = pnode->next;

			delete ptmp;
		}
		delete m_head;    //释放头结点
		m_head = nullptr; //非必须
		m_length = 0;     //非必须
	}

	//删除第i个位置的元素
	template < typename T>
	bool DblLinkList<T>::ListDelete(int i)
	{
		if (m_length < 1)
		{
			cout << "当前双链表为空，不能删除任何数据!" << endl;
			return false;
		}
		if (i < 1 || i > m_length)
		{
			cout << "删除的位置" << i << "不合法，合法的位置是1到" << m_length << "之间!" << endl;
			return false;
		}

		DblNode<T>* p_curr = m_head;

		//整个for循环用于找到第i-1个节点
		for (int j = 0; j < (i - 1); ++j)//j从0开始，表示p_curr刚开始指向的是第0个节点（头结点）
		{
			p_curr = p_curr->next; //pcurr会找到当前要删除的位置所代表的节点的前一个节点的位置，比如要删除第2个位置的节点，pcurr会指向第1个位置(节点)
		}

		DblNode<T>* p_willdel = p_curr->next; //p_willdel指向待删除的节点
		DblNode<T>* p_willdelNext = p_willdel->next; //p_willdelNext指向待删除节点的下一个节点
		p_curr->next = p_willdel->next; //第i-1个节点的next指针指向第i+1个节点
		if (p_willdelNext != nullptr)
			p_willdelNext->prior = p_curr;//第i+1个节点的prior指针指向第i-1个节点

		cout << "成功删除位置为" << i << "的元素，该元素的值为" << p_willdel->data << "!" << endl;
		m_length--;       //实际表长-1
		delete p_willdel;
		return true;
	}
};


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//（2）双链表：增加了前趋指针的链表称为双链表。
	//(2.1)双链表的类定义、初始化操作
	//(2.2)双链表元素插入操作
	//(2.3)双链表元素删除操作
	//(2.4)双链表的特点
	   //a)因为存在前趋节点指针，所以寻找前趋节点时间复杂度为O(1)。
	   //b)p->prior->next = p->ndex->prior = p;
	   //c)存放前趋指针要额外消耗存储空间
	   //d)如果在单/双链表中引入last指针用于始终指向链表尾节点，那么在链表尾部插入数据就会非常简单。
	      // 对于双链表，按位置查找某个节点时，若位置不超过链表长度（m_length）的一半，就可以利用head
	      //  指针从左到右查找，而如果位置超过了链表的一半，就可以利用last指针辅助prior指针从右到左查找。

	//（3）循环链表:分为  单（单向）循环链表和  双（双向）循环链表。
	//(3.1)单循环链表
	   //传统的单循环链表
	   //把链表的头指针修改为尾指针  不再使用m_head， 引入一个尾指针m_tail,那么m_tail->next指向头节点
	      //如果需要频繁的在链表头或者链表尾进行数据操作的话，可以考虑引入m_tail表尾指针。
	      //引入尾指针的另外一个好处就是可以迅速的降两个单循环链表连接起来形成一个更大的单循环链表。
	        //p1head = m_tail1->next;  //先把单循环链表1的头节点暂存起来
	        //m_tail1->next = m_tail2->next->next; //让单循环链表1的尾节点指向单循环链表2的头节点之后的节点（第一个数据节点，也就是a11)。
	        //p2head = m_tail2->next; //再把单循环链表2的头节点暂存起来
	        //m_tail2->next = p1head; //让单循环链表2的为节点的next域指向单循环链表1的头结点。
	        //其他代码略：包括重新设置单循环链表2的长度，让单循环链表2的头指针的next指向自己。
	                 //而对于单循环链表2的头结点的释放，其实是在CirLinlist类的析构函数中进行的。

	//(3.2)双循环链表(循环双链表)

	







	_nmsp1::DblLinkList<int> sdbllinkobj;
	sdbllinkobj.ListInsert(1, 12);
	sdbllinkobj.ListInsert(1, 24);
	sdbllinkobj.ListInsert(3, 48);
	sdbllinkobj.ListInsert(2, 100);
	sdbllinkobj.DispList();

	sdbllinkobj.ListDelete(4);
	sdbllinkobj.ListDelete(2);
	sdbllinkobj.DispList();

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

