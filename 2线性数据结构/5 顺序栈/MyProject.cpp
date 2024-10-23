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
#define InitSize 10 //动态数组的初始尺寸
#define IncSize  5 //当动态数组存满数据后每次扩容所能多保存的数据元素数量

	template <typename T> //T代表数组中元素的类型
	class SeqStack
	{
	public:
		SeqStack(int length = InitSize); //构造函数，参数可以默认值
		~SeqStack();   //析构函数

	public:
		bool Push(const T& e); //入栈（增加数据）
		bool Pop(T& e);        //出栈（删除数据），也就是删除栈顶数据
		bool GetTop(T& e);     //读取栈顶元素，但该元素并没有出栈而是依旧在栈中

		void DispList(); //输出顺序栈中所有元素
		int ListLength(); //获取顺序栈的长度（实际拥有的元素数量）

		bool IsEmpty(); //判断顺序栈是否为空
		bool IsFull();  //判断顺序栈是否已满
	private:
		void IncreaseSize(); //当顺序栈存满数据后可以调用此函数为顺序栈扩容

	private:
		T* m_data;  //存放顺序栈中的元素
		int m_maxsize; //动态数组最大容量
		int m_top;  //栈顶指针（用作数组下标），指向栈顶元素，该值为-1表示空栈
	};

	//通过构造函数对顺序栈进行初始化
	template <typename T>
	SeqStack<T>::SeqStack(int length)
	{
		m_data = new T[length]; //为一维数组动态分配内存，该值和算法空间复杂度无关，空间复杂度一般指算法额外需要的存储空间。
		m_maxsize = length; //顺序栈最多可以存储m_maxsize个数据元素
		m_top = -1; //空栈
	}

	//通过析构函数对顺序栈进行资源释放
	template <typename T>
	SeqStack<T>::~SeqStack()
	{
		delete[] m_data;
	}

	//入栈（增加数据），通常时间复杂度为O(1)，但一旦需要扩容，时间复杂度就会变成O(n)了
	template <typename T>
	bool SeqStack<T>::Push(const T& e)
	{
		if (IsFull() == true)
		{
			//cout << "顺序栈已满，不能再进行入栈操作了！" << endl;
			//return false;
			IncreaseSize(); //扩容
		}

		m_top++; //栈顶指针向后走
		m_data[m_top] = e; //和上行代码合并写成 m_data[++m_top] = e;
		return true;
	}

	//当顺序栈存满数据后可以调用此函数为顺序栈扩容，时间复杂度为O(n)
	template <typename T>
	void SeqStack<T>::IncreaseSize()
	{
		T* p = m_data;
		m_data = new T[m_maxsize + IncSize]; //重新为顺序栈分配更大的内存空间
		for (int i = 0; i <= m_top; ++i)
		{
			m_data[i] = p[i]; //将数据复制到新区域
		}
		m_maxsize = m_maxsize + IncSize; //顺序栈最大长度增加IncSize
		delete[] p; //释放原来的内存空间
	}

	//出栈（删除数据），也就是删除栈顶数据，时间复杂度O(1)
	template <typename T>
	bool SeqStack<T>::Pop(T& e)
	{
		if (IsEmpty() == true)
		{
			cout << "当前顺序栈为空，不能进行出栈操作！" << endl;
			return false;
		}
		e = m_data[m_top]; //栈顶元素值返回到e中。有的实现版本不会在Pop成员函数中返回栈顶元素，此时要取得栈顶元素需要用到GetTop()成员函数。
		m_top--; //本行和上行代码可以合并  e= m_data[m_top--];
		return true;
	}

	//读取栈顶元素，但该元素并没有出栈而是依旧在栈顶中，因此m_top值不会发生改变，时间复杂度O(1)
	template <typename T>
	bool SeqStack<T>::GetTop(T& e)
	{
		if (IsEmpty() == true)
		{
			cout << "当前顺序栈为空，不能进行读取栈顶元素！" << endl;
			return false;
		}
		e = m_data[m_top]; //栈顶元素返回到e中
		return true;
	}

	//输出顺序栈中所有元素，时间复杂度O(n）
	template <typename T>
	void SeqStack<T>::DispList()
	{
		//按照从栈顶到栈底的顺序来显示数据：
		for (int i = m_top; i >= 0; --i)
		{
			cout << m_data[i] << "  ";  //每个数据之间以空格分隔
		}
		cout << endl; //换行
	}

	//获取顺序栈的长度（实际拥有的元素数量），时间复杂度O(1)
	template <typename T>
	int SeqStack<T>::ListLength()
	{
		return m_top + 1;
	}

	//判断顺序栈是否为空，复杂度O(1)
	template <typename T>
	bool SeqStack<T>::IsEmpty()
	{
		if (m_top == -1)
			return true;
		return false;
	}

	//判断顺序栈是否已满，复杂度O(1)
	template <typename T>
	bool SeqStack<T>::IsFull()
	{
		if (m_top >= m_maxsize -1)
			return true;
		return false;
	}

}
namespace _nmsp2
{
	//共享栈
	template <typename T> //T代表数组中元素的类型
	class ShareStack
	{
	public:
		ShareStack(int length = InitSize) //构造函数，参数可以有默认值
		{
			m_data = new T[length]; //为一组数组动态分配内存
			m_maxsize = length; //共享栈最多可以存储m_maxsize个数据元素
			m_top1 = -1; //顺序栈1的栈顶指针为-1，表示空栈
			m_top2 = length; //顺序栈2的栈顶指针为length，表示空栈
		}
		~ShareStack() //析构函数
		{
			delete[] m_data;
		}

	public:
		bool IsFull() //判断共享栈是否已满
		{
			if (m_top1 + 1 == m_top2)
				return true;
			return false;
		}

		bool Push(int stackNum, const T& e) //入栈（增加数据），参数stackNum用于表示栈1还是栈2
		{
			if (IsFull() == true)
			{
				//共享栈满了，可以自己增加代码支持共享栈的扩容，但这里，老师简单处理，直接返回false;
				cout << "共享栈已满，不能再进行入栈操作了！" << endl;
				return false;
			}
			if (stackNum == 1)
			{
				//要入的是顺序栈1
				m_top1++; //栈顶指针向后走
				m_data[m_top1] = e;
			}
			else
			{
				//要入的是顺序栈2
				m_top2--;
				m_data[m_top2] = e;
			}
			return true;
		}

		bool Pop(int stackNum, T& e) //出栈（删除数据），也就是删除栈顶数据
		{
			if (stackNum == 1)
			{
				//要从顺序栈1出栈
				if (m_top1 == -1)
				{
					cout << "当前顺序栈1为空，不能进行出栈操作！" << endl;
					return false;
				}
				e = m_data[m_top1]; //栈顶元素值返回到e中
				m_top1--;
			}
			else
			{
				//要从顺序栈2出栈
				if (m_top2 == m_maxsize)
				{
					cout << "当前顺序栈2为空，不能进行出栈操作！" << endl;
					return false;
				}
				e = m_data[m_top2]; //栈顶元素值返回到e中
				m_top2++;
			}
			return true;
		}

	private:
		T* m_data; //存放共享栈中的元素
		int m_maxsize; //动态数组最大容量
		int m_top1; //顺序栈1的栈顶指针
		int m_top2; //顺序栈2的栈顶指针
	};
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口
	
	//第2章 线性表
	//第四节    栈 (Stack)
	// 只能在一端进行插入和删除操作：先进后出，后进先出。理解为一种受限的线性表。
	// 	两端：允许进行插入和删除操作的一端称为栈顶——桶口（表尾）。
	// 	      栈底——桶底（线性表表头）
	// 	   插入数据：进栈（入栈）。
	// 	   删除元素：出栈
	// 	   空栈：不包含任何数据（空线性表）。
	// 	   也称为后进先出（Last In First Out: LIFO)的线性表：最后放入栈中的数据（插入数据）只能最先被从栈中拿出来（删除数据）
	// 	   栈包含的操作：线性表的子集——创建、入栈（增加数据）、出栈（删除数据）、获取栈顶元素（查找数据），判断栈是否为空或者是否已满。
	// 	   STL：stack
	// 
	//（1）栈的顺序存储（顺序栈）：用一段连续的内存口空间依次存储栈中的数据。
	   //两种保存数据的方案：a)通过为一维数组静态分配内存的方式来保存数据。
	                      //b)通过为一维数组动态分配内存的方式来保存数据。 ***
	   //为了考虑到元素存取的方便性，将数组下标为0的一端作为栈底最合适。
	   //(1.1)顺序栈的类定义、初始化和释放操作
	   //(1.2)顺序栈的入栈、出栈、获取栈顶元素、显示元素等操作
	   //(1.3)共享栈:两个顺序栈共享存储空间
	   //共享栈使用的意义：对两个顺序栈存储空间需求正好相反时，使用共享栈意义才比较大。
	     //也就是说：当一个栈进行入栈操作时，另一个栈同时进行出栈操作（此消彼长）。



	_nmsp1::SeqStack<int> seqobj(10);
	seqobj.Push(150);
	seqobj.Push(200);
	seqobj.Push(300);
	seqobj.Push(400);
	seqobj.DispList();

	int eval = 0;
	seqobj.Pop(eval);
	seqobj.Pop(eval);
	cout << "-----" << endl;
	seqobj.DispList();
	
	seqobj.Push(8100);
	seqobj.DispList();

	//-------------
	_nmsp2::ShareStack<int> sharesobj(10);
	sharesobj.Push(1, 150);
	sharesobj.Push(2, 200);
	int eval2;
	sharesobj.Pop(1, eval2);
	sharesobj.Pop(1, eval2);

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


