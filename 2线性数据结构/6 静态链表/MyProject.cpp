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


#define MaxSize 201   //静态链表的尺寸，可以根据实际需要设定该值，可用数组下标为0-200

//------------------------------
namespace _nmsp1
{
	//节点使用情况枚举标记值
	enum NODEUSE
	{
		//这些枚举值都给负值，以免和数组下标（从0开始的正直）冲突
		e_NOUSE = -1, //未使用(未用)
		e_LAST = -2   //最后一个节点（末尾）
	};

	//静态链表中每个节点的定义
	template<typename T> //T代表数据元素类型
	struct Node
	{
		T   data; //元素数据域，存放数据元素
		int cur;  //游标，记录下个静态链表节点的数组下标
	};
	
	//静态链表的定义
	template<typename T>
	class StaticLinkList
	{
	public:
		StaticLinkList(); //构造函数
		~StaticLinkList() {}; //析构函数

	public:
		int findAnIdlePos(); //找到一个空闲位置用于保存数据
		bool ListInsert(int i, const T& e); //在第i个位置插入指定元素e
		bool ListDelete(int i); //删除第i个位置的元素

		bool GetElem(int i, T& e); //获得第i个位置的元素值
		int LocateElem(const T& e); //按元素值查找其在静态链表中第一次出现的位置

		void DispList();   //输出静态链表中的所有元素
		int ListLength();  //获取静态链表的长度
		bool Empty();   //判断静态链表是否为空

	private:
		Node<T> m_data[MaxSize]; //保存节点数据的数组
		int m_length; //当前长度，也就是当前保存的数据节点数目
	};

	//通过构造函数对静态链表进行初始化
	template<typename T>
	StaticLinkList<T>::StaticLinkList()
	{
		for (int i = 1; i < MaxSize; ++i) //从下标1开始的节点用于保存实际的数据，这些节点的cur有必要设置值，而头结点其实不用给任何值
		{
			m_data[i].cur = e_NOUSE; //标记这些节点都没使用
		}
		m_length = 0; //还未向其中存入任何数据元素
	}

	//在m_data中找到一个空闲位置用于保存数据，若没找到（静态链表满了），则返回-1。
	template<typename T>
	int StaticLinkList<T>::findAnIdlePos()
	{
		for (int i = 1; i < MaxSize; ++i) //因为下标0是头节点，不能用于保存数据，所以循环变量从1开始
		{
			if (m_data[i].cur == e_NOUSE) //未使用
				return i;
		}
		return -1;
	}

	//在第iPos个位置（位置编号从1开始）插入指定元素e
	template<typename T>
	bool  StaticLinkList<T>::ListInsert(int iPos,const T&e)
	{
		if (iPos < 1 || iPos >(m_length + 1))
		{
			cout << "元素" << e << "插入的位置" << iPos << "不合法，合法的位置是1到" << m_length + 1 << "之间!" << endl;
			return false;
		}

		int iIdx;
		if ((iIdx = findAnIdlePos()) == -1) //静态链表满了
		{
			cout << "静态链表已满!" << endl;
			return false;
		}

		//既然需要在第iPos个位置插入元素，那么肯定要找到iPos-1个位置
		int iDataCount = 1; //统计静态链表中元素数量
		int iIdxPrev;  //保存第iPos-1个位置对应的m_data数组的下标

		if (iPos == 1)  //向第一个位置插入元素，要单独处理
		{
			m_data[iIdx].data = e;
			if (m_length == 0) //空表
			{
				m_data[iIdx].cur = e_LAST;
			}
			else //非空表
			{
				m_data[iIdx].cur = m_data[0].cur;
			}
			m_data[0].cur = iIdx;
		}
		else
		{
			int iPosCount = 0; //位置计数
			int tmpcur = m_data[0].cur;

			//前面已经判断过插入位置合法，所以一定可以找到合适的位置，while(true)循环肯定可以正常退出
			while (true)
			{
				iPosCount++;
				if (iPosCount >= (iPos - 1)) //找到了第iPos-1个位置
				{
					iIdxPrev = tmpcur;
					break;
				}
				tmpcur = m_data[tmpcur].cur;				
			}//end while
			int iTmpCurr = m_data[iIdxPrev].cur;
			m_data[iIdxPrev].cur = iIdx;
			m_data[iIdx].data = e;
			m_data[iIdx].cur = iTmpCurr;			
		}
		cout << "成功在位置为" << iPos << "处插入元素" << e << "!" << endl;
		m_length++;
		return true;
	}

	//输出静态链表中所有元素，时间复杂度O(n)
	template<typename T>
	void  StaticLinkList<T>::DispList()
	{
		if (m_length < 1)
			return; //静态链表为空

		int tmpcur = m_data[0].cur;
		while (true)
		{
			cout << m_data[tmpcur].data << "  ";
			if ((tmpcur = m_data[tmpcur].cur) == e_LAST)
				break;
		} //end while
		cout << endl; //换行
	}

	//获取第i个位置的元素值，时间复杂度O(n)
	template<typename T>
	bool  StaticLinkList<T>::GetElem(int i, T& e)
	{
		if (m_length < 1)
		{
			//静态链表为空
			cout << "当前静态链表为空，不能获取任何数据！" << endl;
			return false; 
		}
		if (i < 1 || i > m_length)
		{
			cout << "获取元素的位置" << i << "不合法，合法的位置是1到" << m_length << "之间!" << endl;
			return false;
		}

		int tmpcur = m_data[0].cur;
		int iPos = 0;
		while (true)
		{
			iPos++;
			if (iPos == i)
			{
				e = m_data[tmpcur].data;
				cout << "成功获取位置为" << i << "的元素，该元素的值为" << e << "!" << endl;
				return true;
			}
			tmpcur = m_data[tmpcur].cur;
		}
		return false;
	}
	
	//按元素值查找其在静态链表中第一次出现的位置，时间复杂度O(n)
	template<typename T>
	int StaticLinkList<T>::LocateElem(const T& e)
	{
		if (m_length < 1)
		{
			//静态链表为空
			cout << "当前静态链表为空，不能获取任何数据！" << endl;
			return -1;
		}
		int tmpcur = m_data[0].cur;
		int iPos = 0;
		while (true)
		{
			iPos++;
			if (m_data[tmpcur].data == e && m_data[tmpcur].cur != e_NOUSE)
			{
				cout << "值为" << e << "的元素在静态链表中第一次出现的位置为" << iPos << "!" << endl;
				return tmpcur;
			}
			if (m_data[tmpcur].cur == e_LAST)
			{
				//没找到
				break;
			}
			tmpcur = m_data[tmpcur].cur;
		}
		cout << "值为" << e << "的元素在静态链表中没有找到!" << endl;
		return -1; //-1表示查找失败
	}

	//获取静态链表的长度，时间复杂度O(1)
	template<typename T>
	int StaticLinkList<T>::ListLength()
	{
		return m_length;
	}

	//判断静态链表是否为空，时间复杂度O(1)
	template<typename T>
	bool StaticLinkList<T>::Empty()
	{
		if (m_length < 1)
			return true;
		return false;
	}

	//删除第iPos个位置的元素
	template<typename T>
	bool StaticLinkList<T>::ListDelete(int iPos)
	{
		if (m_length < 1)
		{
			//静态链表为空
			cout << "当前静态链表为空，不能删除任何数据！" << endl;
			return false;
		}
		if (iPos < 1 || iPos > m_length)
		{
			cout << "删除的位置" << iPos << "不合法，合法的位置是1到" << m_length << "之间!" << endl;
			return false;
		}
		int tmpcur = m_data[0].cur; //第一个数据节点的数组下标
		if (iPos == 1) //删除第一个位置元素，要单独处理
		{
			if (m_length != 1)
			{
				//这个静态链表里有多个元素，那么
				m_data[0].cur = m_data[tmpcur].cur; //头节点指向第二个数据节点的数组下标
			}
			m_data[tmpcur].cur = e_NOUSE;
			cout << "成功删除位置为" << iPos << "的元素，该元素的值为" << m_data[tmpcur].data << "!" << endl;
		}
		else
		{
			int iIdxPrev; //第iPos-1个位置对应的m_data数组的下标
			int iPosCount = 0; //位置计数
			//前面已经判断过删除位置合法，所以一定可以找到合适位置，while(true)循环肯定可以正常退出
			while (true)
			{
				iPosCount++;
				if (iPosCount >= (iPos - 1)) //找到了第i-1个位置
				{
					iIdxPrev = tmpcur;
					break;
				}
				tmpcur = m_data[tmpcur].cur;
			} //end while
			int iTmpCurr = m_data[iIdxPrev].cur; //当前要删除的这个节点的数组下标
			m_data[iIdxPrev].cur = m_data[iTmpCurr].cur; //前一个节点的cur指向当前要删除节点的cur
			m_data[iTmpCurr].cur = e_NOUSE; //标记被删除数据节点的数组下标为未用状态
			cout << "成功删除位置为" << iPos << "的元素，该元素的值为" << m_data[iTmpCurr].data << "!" << endl;
		} //end if (iPos == 1)
		m_length--; //实际表厂-1
		return true;
	}
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口
	
	//（4）静态链表：用一维数组描述的链表就称为静态链表。
	   //静态链表在内存中也需要分配一整块连续的内存空间。
	//每个数组元素（链表中的节点）都由两个数据域组成：data（存储链表节点中数据）和cur（存储后继节点所属的数组元素下标）。
	      //cur也称为游标，用来模拟指针。 
	      //下标为0的数组元素可以看成是链表的头节点，其cur域的值用于指示链表第一个数据节点对应的数组下标。      
	//(4.1)静态链表的类定义、初始化操作
	//(4.2)静态链表元素插入操作
	//步骤：a)找到一个空闲位置代表新插入的节点，在其中存入数据元素。
	        //b)从头节点开始，找到待插入位置的前一个（前趋）节点；
	        //c)设置新插入节点的cur值以指向前趋节点所指向的节点，设置前趋节点的cur值以指向这个新插入的节点。
	        //d)如果新插入的节点是最后一个节点，要设置其cur标记为“末尾”。
	//(4.3)静态链表元素显示、获取等操作
	//(4.4)静态链表元素删除操作
	//步骤：a)从头节点开始，找到待删除节点的前一个（前趋）节点；
	       //b)设置前趋节点的cur值等于当前待删除节点的cur值以指向当前节点所指向的节点。
	       //c)设置被删除节点的状态为“未用”状态
	//(4.5)静态链表的使用总结:
	   //不同的静态链表实现方式——将静态链表中的第一个和最后一个节点作为特殊节点来使用（不保存数据）。
	    //第一个节点的cur存放第一个未被使用的节点所对应的数组下标（这些未被使用的节点可以通过cur串起来，构成一个未被使用的节点链）
        //最后一个节点的cur存放第一个有数据的节点对应的数组下标（相当于头结点），该值为0相当于链表为空。
	   //实现代码繁琐，但插入数据时能明显提高寻找空闲节点的效率，时间复杂度从O(n)变为O(1)；

	//插入删除节点方便（不需要移动元素，仅仅需要修改游标）。存取数据时无法随机存取。

	//场合：a)不支持指针的语言  b)所需要的空间比较固定。


	_nmsp1::StaticLinkList<int> slinkobj;
	slinkobj.ListInsert(1, 12);
	slinkobj.ListInsert(1, 24);
	slinkobj.ListInsert(3, 48);
	slinkobj.ListInsert(2, 100);
	slinkobj.ListInsert(5, 190);
	slinkobj.ListInsert(4, 300);
	//24,100,12,300,48,190,

	slinkobj.DispList();
	slinkobj.LocateElem(190);
	slinkobj.LocateElem(24);
	slinkobj.LocateElem(300);

	cout << "--------------" << endl;
	int eval = 0;
	slinkobj.GetElem(0, eval); //如果GetElem()返回true，则eval中保存着获取到的元素值
	slinkobj.GetElem(1, eval);
	slinkobj.GetElem(3, eval);
	slinkobj.GetElem(6, eval);

	cout << "--------------" << endl;
	slinkobj.ListDelete(1);
	slinkobj.ListDelete(5);
	slinkobj.ListDelete(10);
	slinkobj.DispList();

	cout << "--------------" << endl;
	slinkobj.ListInsert(1, 500);
	slinkobj.ListInsert(3, 600);
	slinkobj.ListInsert(4, 700);
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


