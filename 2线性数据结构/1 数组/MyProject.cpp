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

#define InitSize 10 //动态数组的初始尺寸
#define IncSize  5   //当动态数组存满数据后每次扩容所能多保存的数据元素数量

//------------------------------
namespace _nmsp1
{
	//typedef struct
	//{
	//	int m_data[10]; //静态数组来保存顺序表中的元素，一共10个位置（最多存入10个元素）
	//	int m_length;  //顺序表中当前实际长度（当前顺序表中已经存入了多少个元素）
	//}SeqList;

	//typedef struct
	//{
	//	int* m_data;  //顺序表中的元素保存再m_data所指向的动态数组内存中。
	//	int m_length;  //顺序表中当前实际长度
	//	int  m_maxsize; //动态数组最大容量，因为动态数组可以扩容，因此要记录该值。
	//}SeqList;

	template <typename T> //T代表数组中元素的类型
	class SeqList
	{
	public:
		SeqList(int length = InitSize); //构造函数，参数可以有默认值
		~SeqList();      //析构函数

	public:
		bool ListInsert(int i, const T& e); //在第i个位置插入指定元素
		bool ListDelete(int i);  //删除第i个位置的元素
		bool GetElem(int i, T& e);  //获得第i个位置的元素值
		int LocateElem(const T& e); //按元素值查找其在顺序表中第一次出现的位置

		void DispList(); //输出顺序表中的所有元素
		int ListLength(); //获取顺序表长度
		void ReverseList();  //翻转顺序表

	private:
		void IncreaseSize();  //当顺序存满数据后可以调用此函数为顺序表扩容

	private:
		T* m_data;  //存放顺序表中的元素
		int m_length;  //顺序表中当前实际长度(当前有几个元素)
		int  m_maxsize; //动态数组最大容量
	};

	//通过构造函数对顺序表进行初始化
	template <typename T>
	SeqList<T>::SeqList(int length)
	{
		m_data = new T[length]; //为一维数组动态分配内存
		m_length = 0; //顺序表当前实际长度为0，表示还未向其中存入任何数据元素
		m_maxsize = length; //顺序表最多可以存储m_maxsize个数据元素
	}
	//通过析构函数对顺序表进行资源释放
	template <typename T>
	SeqList<T>::~SeqList()
	{
		delete[] m_data;
		m_length = 0; //非必须
	}

	//在第i个位置（位置编号从1开始）插入指定元素e，时间复杂度O(n)，时间开销主要是缘于元素的移动。
	template <typename T>
	bool SeqList<T>::ListInsert(int i, const T& e)
	{
		//如果顺序表已经存满数据，则不允许再插入数据了
		if (m_length >= m_maxsize)
		{
			cout << "顺序表已满，不能再进行插入操作了！" << endl;
			return false;
		}
		//判断插入位置i是否合法，i的和合法值应该是从1到m_length+1之间
		if (i < 1 || i >(m_length + 1))
		{
			cout << "元素" << e << "插入位置" << i << "不合法，合法的位置是1到" << m_length+1 << "之间!" << endl;
			return false;
		}
		//从最后有一个元素 开始向前遍历到要插入新元素的第i个位置，分别将这些位置中原有的元素向后移动一个位置
		for (int j = m_length; j >= i; --j) //O(1),O(n), 1/(n+1)
			                               //后移次数平均值=(1+2+3+...+n)/(n+1) = (n(n+1)/2)/(n+1)
		{
			m_data[j] = m_data[j - 1];
		}
		m_data[i - 1] = e; //在指定位置i处插入元素e，因为数组下标从0开始，所以这里用i-1表示插入位置所对应的数组下标。
		cout << "成功在位置为" << i << "处插入元素" << m_data[i - 1] << "!" << endl;
		m_length++; //表长度+1
		return true;
	}
}

int main()
{		
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口
	
	//第2章 线性表:线性结构，保存的数据象线一样按顺序排列，数据之间一对一的关系。
	//第一节 线性表概述:具有相同数据类型的n(n>=0)个数据的有限序列。n：线性表长度。
	   //一般线性表表示为：(a1,a2,......ai,a i+1,....,an）；
	   //直接前趋，直接后继。
	   //线性表：数组、链表、栈、队列等都属于线性表的一种（或者理解为 数组，链表，栈，队列都可以用来表达线性表）。
	    //非线性表：一对多
	//第二节 线性表的顺序存储:指的是用一段连续的内存空间一次存储线性表中的数据。
	 //线性表的顺序存储一般就会采用一维数组来实现。STL,vecotr。
	  //采用一维数组实现的线性表也被称为顺序表。
	   //随机访问：通过数组首地址和所给元素下标可以最快的找到任意数组元素。而且这种通过下标随机访问数组元素的时间复杂度仅仅O(1)
	    //a[i]的地址 = 数组元素的首地址+下标*sizeof(整型）； ---->a[2] = 1000 + 2*4 = 1008
	    //插入或者删除数据时效率会很低。

	//（1）顺序表
	//(1.1)顺序表的类定义、初始化和释放操作
	//(1.2)顺序表元素插入操作








	_nmsp1::SeqList<int> seqobj(10);
	seqobj.ListInsert(1, 15);
	seqobj.ListInsert(2, 10);
	seqobj.ListInsert(30, 8);
	

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


