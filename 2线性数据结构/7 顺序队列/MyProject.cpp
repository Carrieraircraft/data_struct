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

	#define MaxSize 10 //数组的尺寸

	template<typename T>  //T代表数组中元素类型
	class SeqQueue
	{
	public:
		SeqQueue(); //构造函数
		~SeqQueue(); //析构函数
	public:
		bool EnQueue(const T& e); //入队列（增加数据）
		bool DeQueue(T& e); //出队列（删除数据）
		bool GetHead(T& e); //读取对头元素，但元素并没有出队列而是依旧在队列中
		void ClearQueue(); //将队列清空

		void DispList(); //输出顺序队列中的所有元素
		int ListLength(); //获取顺序队列的长度（实际拥有的元素数量）

		bool IsEmpty(); //判断顺序队列是否为空
		bool IsFull();  //判断顺序队列是否已满

	private:
		T* m_data; //促进方顺序队列中的元素
		int m_front; //队头指针（数组下标），允许删除的一端，如果队列不为空，则指向队列头元素
		int m_rear;  //队尾指针（数组下标），允许插入的一端，如果队列不为空，则指向队列尾元素的下一个位置
	};

	//通过构造函数对顺序队列进行初始化
	template <typename T>
	SeqQueue<T>::SeqQueue()
	{
		m_data = new T[MaxSize]; //为一维数组动态分配内存

		//空队列约定m_front 和m_rear都为0
		m_front = 0;
		m_rear = 0;
	}

	//通过析构函数对顺序队列进行资源释放
	template <typename T>
	SeqQueue<T>::~SeqQueue()
	{
		delete[] m_data;
	}

	//入队列（增加数据），也就是从队尾增加数据
	template <typename T>
	bool SeqQueue<T>::EnQueue(const T& e)
	{
		if (IsFull() == true)
		{
			cout << "顺序队列已满，不能再进行入队操作了!" << endl;
			return false;
		}

		m_data[m_rear] = e; //将数据放入队尾
		//m_rear++; //队尾指针向后走
		m_rear = (m_rear + 1) % MaxSize; //队尾指针加1并取余，这样m_data的下标就控制在0 ~ (MaxSize-1)之间了。

		//m_tag = 1; //入队 
		return true;
	}

	//出队列（删除数据），也就是删除对头数据
	template <typename T>
	bool SeqQueue<T>::DeQueue(T& e)
	{
		if (IsEmpty() == true)
		{
			cout << "顺序队列为空，不能进行出队操作!" << endl;
			return false;
		}
		e = m_data[m_front]; //队头元素值返回到e中
		//m_front++; 
		m_front = (m_front + 1) % MaxSize; //对头指针加1并取余。
		//m_tag = 0; //出队 
		return true;
	}
	//读取对头元素，但该元素并没有出队列而是依旧在队列中
	template <typename T>
	bool SeqQueue<T>::GetHead(T& e)
	{
		if (IsEmpty() == true)
		{
			cout << "顺序队列为空，不能进行读取队头元素!" << endl;
			return false;
		}
		e = m_data[m_front]; //队头元素值返回到e中		
		return true;
	}

	//输出顺序队列中所有元素，时间复杂度O(n)
	template <typename T>
	void SeqQueue<T>::DispList()
	{
		//按照从队头到队尾的顺序来显示数据
		//for (int i = m_front; i < m_rear; ++i)
		for(int i = m_front; i != m_rear;)
		{
			cout << m_data[i] << " "; //每个数据之间以空格分隔。

			i = (i + 1) % MaxSize;
		}
		cout << endl; //换行
	}

	//获取顺序队列的长度（实际拥有的元素数量），时间复杂度O(n)
	template <typename T>
	int SeqQueue<T>::ListLength()
	{
		//return m_rear - m_front;
		return (m_rear + MaxSize - m_front) % MaxSize;
	}

	//判断顺序队列是否为空，时间复杂度O(1)
	template <typename T>
	bool SeqQueue<T>::IsEmpty()
	{
		if (m_front == m_rear)
			//if (m_front == m_rear && m_tag = 0)
		{
			return true;
		}
		return false;
	}

	//判断队列是否已满，时间复杂度O(1)
	template <typename T>
	bool SeqQueue<T>::IsFull()
	{
		//if(m_rear >= MaxSize) //队尾指针和数组容量做比较
		if((m_rear + 1) % MaxSize == m_front)
			//if(m_front == m_rear && m_tag = 1)  return true;
		{
			return true;
		}
		return false;
	}

	//将队列清空
	template <typename T>
	void SeqQueue<T>::ClearQueue()
	{
		m_front = m_rear = 0;
	}
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口
	
	//第五节  队列
	//允许插入的一端叫队尾，允许删除的一端叫队头。
	//入队。出队。空队列。 
	//队列也叫先进先出（First In First Out:FIFO）的线性表。
	//操作：创建，入队，出队，获取对头元素，判断队列是否为空，以及队列是否为满
	//STL（标准模板库）中，queue容器。
	//分为：顺序存储和链式存储
	//（1）队列的顺序存储（顺序队列）:用一段连续的内存空间依次存储。
	//(1.1)基础实现代码
	//(1.2)循环队列
	//其他判断队列是否满的方法：
	//a)引入int，m_size，初值 = 0；入队m_size自加1，出队成功，m_size自减1.
	  //m_size == 0为空，m_size == MaxSize满。
	//b)引入一个char，变量叫m_tag = 0； 
	   //出队，m_tag = 0。入队，m_tag = 1。 标记最近执行了删除还是插入操作。
	     //只有出队操作才会导致队列为空，只有入队操作才会导致队列变满。


	_nmsp1::SeqQueue<int> seqobj; 
	seqobj.EnQueue(150);
	seqobj.EnQueue(200);
	seqobj.EnQueue(300);
	seqobj.EnQueue(400);
	seqobj.DispList();

	cout << "-----------" << endl;
	int eval = 0;
	seqobj.DeQueue(eval);
	seqobj.DeQueue(eval);
	seqobj.DispList();

	cout << "-----------" << endl;
	seqobj.EnQueue(500);
	seqobj.EnQueue(600);
	seqobj.EnQueue(700);
	seqobj.EnQueue(800);
	seqobj.EnQueue(900);
	seqobj.DispList();


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


