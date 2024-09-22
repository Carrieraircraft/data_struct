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
	//链式栈中每个节点的定义
	template <typename T> //T代表数据元素的类型
	struct StackNode
	{
		T  data; //数据域，存放数据元素
		StackNode<T>* next; //指针域，指向下一个同类型（和本节点类型相同）节点
	};

	//链式栈的定义
	template <typename T>
	class LinkStack
	{
	public:
		LinkStack(); //构造函数
		~LinkStack(); //析构函数

	public:
		bool Push(const T& e); //入栈元素e
		bool Pop(T& e); //出栈（删除数据）操作，也就是删除栈顶数据
		bool GetTop(T& e); //读取栈顶元素，但该元素并没有出栈而是依旧在栈中

		void DispList(); //输出链式栈中的所有元素
		int ListLength(); //获取链式栈的长度
		bool Empty(); //判断链式栈是否为空

	private:
		StackNode<T>* m_top; //栈顶指针
		int  m_length; //链式栈当前长度
	};

	//构造函数，通过构造函数对链式栈进行初始化
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

	//出栈（删除数据），也就是删除栈顶数据，时间复杂度O(1)
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

	//输出链式栈中的所有元素，时间复杂度O(n)
	template <typename T>
	void LinkStack<T>::DispList()
	{
		if (Empty() == true) //链式栈为空
			return;

		StackNode<T>* p = m_top;
		while (p != nullptr)
		{
			cout << p->data << " "; //每个数据之间以空格分隔
			p = p->next;
		}
		cout << endl; //换行
	}

	//获取链式栈的长度，时间复杂度O(1)
	template <typename T>
	int LinkStack<T>::ListLength()
	{
		return m_length;
	}

	//判断链式栈是否为空，时间复杂度O(1)	
	template <typename T>
	bool LinkStack<T>::Empty()
	{
		if (m_top == nullptr)		
			return true;
		
		return false;
	}

	//通过析构函数对链式栈进行资源释放
	template <typename T>
	LinkStack<T>::~LinkStack()
	{
		T tmpnousevlaue = { 0 };
		while (Pop(tmpnousevlaue) == true){} //把栈顶元素删光，while循环也就退出了，此时也就是空栈了
	}

	
}
namespace _nmsp2
{
	//求两个数字相加的和值
	int Add(int tmpa, int tmpb)
	{
		int sum = 0;
		sum = tmpa + tmpb;
		return sum;
	}

}
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口
	
	//第2章 线性表
	//第四节    栈
	//（2）栈的链式存储（链式栈 / 链栈）:ListInsert。ListDelete
	 //就是单链表：受限的单链表，一般不需要带头结点。
	//如果要存储的数据数量无法提前预估，一般考虑用链式栈，如果数据的数量比较固定，可以考虑使用顺序栈。
	//（3）栈存在的意义和应用举例
	//（3.1）保存临时数据
	//函数调用栈，栈帧
	//（3.2）利用栈来进行括号匹配的检验
	//   ()   ,[] ,{} 
	//可以嵌套使用：{[]()}，{[()][]}, [({}){}]，正确
	//{[](})，{([)][]}、[({}{)}]，不正确
	//（3.3）计算表达式结果
	//先算乘除后算加减，有括号先算括号中的值
	// 3+(2+5)*4-1+18/3  = 3+7*4-1+6 = 3+28-1+6 = 36
	//中缀表达式：运算符在操作数中间,
	//利用栈把中缀表达式转换成后缀表达式（逆波兰表达式） ,然后再次利用栈对这个后缀表达式求值得到最终结果。
	//"C++利用栈计算算数表达式"。






	_nmsp1::LinkStack<int> slinkobj;
	slinkobj.Push(12);
	slinkobj.Push(24);
	slinkobj.Push(48);
	slinkobj.Push(100);
	slinkobj.DispList();

	int eval = 0;
	slinkobj.Pop(eval);
	slinkobj.DispList();

	//--------------
	int a1 = 15;
	int a2 = 6;
	int result = 0;
	result = _nmsp2::Add(a1, 100);
	cout << "和值为" << result << endl;

	//-------------------------
	bool ifMatchSucc = true; //是否匹配成功的标志，先标记匹配成功。
	_nmsp1::LinkStack<char> slinkobjprocKH; //保存左括号的栈
	//string strExp = "[({}){}]";
	string strExp = "[({}){]}";
	for (size_t i = 0; i < strExp.size(); ++i)
	{
		if (strExp[i] == '(' ||   //左括号全部入栈
			strExp[i] == '[' ||
			strExp[i] == '{'
			)
		{
			slinkobjprocKH.Push(strExp[i]);
		}
		else
		{
			//当前是个右括号，则从栈顶取出一个左括号
			char tmptopchar;
			if (slinkobjprocKH.Pop(tmptopchar) == false) //从栈顶取出数据失败
			{
				ifMatchSucc = false;
				break;
			}
			//取得了栈顶的一个左括号，看一看是否匹配
			if (
				(strExp[i] == ')' && tmptopchar == '(') ||
				(strExp[i] == ']' && tmptopchar == '[') ||
				(strExp[i] == '}' && tmptopchar == '{')
				)
			{
				continue;
			}
			else
			{
				//括号不匹配
				ifMatchSucc = false;
				break;
			}
		} //end if
	} //end for
	//扫描完成，还要确定slinkobjprocKH为空才可以
	if (ifMatchSucc == true && slinkobjprocKH.Empty() == false)
	{
		ifMatchSucc = false;
	}
	if (ifMatchSucc == true)
	{
		cout << "\"" << strExp << "\"格式合法，括号配对数量和顺序都正确" << endl;
	}
	else
	{
		cout << "\"" << strExp << "\"格式非法，括号配对数量或顺序不正确" << endl;
	}

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


