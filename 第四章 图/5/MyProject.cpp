﻿// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注


#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <assert.h>
#include <sstream>
#include <stack>

#pragma warning (disable: 4996) 
using namespace std;


//广度优先遍历需要借助队列
namespace _nmsp0
{
	//链式队列中每个节点的定义
	template <typename T> //T代表数据元素的类型
	struct QueueNode
	{
		T        data;       //数据域，存放数据元素
		QueueNode<T>* next;  //指针域，指向下一个同类型（和本节点类型相同）节点
	};

	//链式队列的定义
	template <typename T> //T代表数组中元素的类型
	class LinkQueue
	{
	public:
		LinkQueue();                          //构造函数，参数可以有默认值
		~LinkQueue();                         //析构函数

	public:
		bool EnQueue(const T& e);            //入队列（增加数据）		
		bool DeQueue(T& e);                  //出队列（删除数据）
		bool GetHead(T& e);                  //读取队头元素，但该元素并没有出队列而是依旧在队列中		

		void DispList();                     //输出链式队列中的所有元素
		int  ListLength();                   //获取链式队列的长度（实际拥有的元素数量）		

		bool IsEmpty();                      //判断链式队列是否为空		

	private:
		QueueNode<T>* m_front;               //头指针（指向头结点），这一端允许出队（删除）
		QueueNode<T>* m_rear;                //专门引入尾指针以方便入队（插入）操作
		int m_length;                        //记录长度，方便获取长度
	};

	//通过构造函数对链式队列进行初始化
	template <typename T>
	LinkQueue<T>::LinkQueue()
	{
		m_front = new QueueNode<T>; //先创建一个头结点
		m_front->next = nullptr;
		m_rear = m_front;
		m_length = 0;

		//若不带头节点的链式队列初始化代码应该如下，供参考
		/*m_front = nullptr;
		m_rear = nullptr;*/
	}

	//通过析构函数对链式队列进行资源释放
	template <typename T>
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
		delete m_front;             //释放头结点		
		m_front = m_rear = nullptr; //非必须
		m_length = 0;               //非必须
	}

	//入队列（增加数据），也就是从队尾增加数据
	template <typename T>
	bool LinkQueue<T>::EnQueue(const T& e)
	{
		QueueNode<T>* node = new QueueNode<T>;
		node->data = e;
		node->next = nullptr;

		m_rear->next = node; //新节点插入到m_rear后面
		m_rear = node;       //更新队列尾指针

		m_length++;
		return true;
	}

	//出队列（删除数据），也就是删除队头数据
	template <typename T>
	bool LinkQueue<T>::DeQueue(T& e)
	{
		if (IsEmpty() == true)
		{
			cout << "当前链式队列为空，不能进行出队操作!" << endl;
			return false;
		}

		QueueNode<T>* p_willdel = m_front->next;
		e = p_willdel->data;

		m_front->next = p_willdel->next;
		if (m_rear == p_willdel) //队列中只有一个元素节点（被删除后，整个队列就为空了）
			m_rear = m_front;  //设置队列为空(尾指针指向头指针)

		delete p_willdel;
		m_length--;
		return true;
	}

	//读取队头元素，但该元素并没有出队列而是依旧在队列中
	template <typename T>
	bool LinkQueue<T>::GetHead(T& e)
	{
		if (IsEmpty() == true)
		{
			cout << "当前链式队列为空，不能读取队头元素!" << endl;
			return false;
		}

		e = m_front->next->data;
		return true;
	}

	//输出链式队列中的所有元素，时间复杂度为O(n)
	template<class T>
	void LinkQueue<T>::DispList()
	{
		QueueNode<T>* p = m_front->next;
		while (p != nullptr)
		{
			cout << p->data << " ";  //每个数据之间以空格分隔
			p = p->next;
		}
		cout << endl; //换行
	}

	//获取链式队列的长度（实际拥有的元素数量），时间复杂度为O(1)
	template<class T>
	int LinkQueue<T>::ListLength()
	{
		return m_length;
	}

	//判断链式队列是否为空，时间复杂度为O(1)
	template<class T>
	bool LinkQueue<T>::IsEmpty()
	{
		if (m_front == m_rear) //当然，换一种判断方式也行：if(m_front->next == nullptr) return true;
		{
			return true;
		}
		return false;
	}
}

#define MaxVertices_size 10 //最大顶点数大小

//表示边的节点结构
struct EdgeNode
{
	int curridx; //边所对应的顶点下标值
	EdgeNode* next; //指向下一条边
};


//表示顶点的节点结构，其后是一个链表，链表中每个节点都代表着和该顶点相连的边
template <typename T> //T代表顶点类型
struct VertexNode
{
	T data; //顶点中的数据
	EdgeNode* point; //指向第一个边节点的指针
};

//邻接表代表的图
template <typename T>
class GraphLink
{
public:
	GraphLink() //构造函数
	{
		m_numVertices = 0;
		m_numEdges = 0;
		for (int i = 0; i < MaxVertices_size; ++i)
		{
			m_VertexArray[i].point = nullptr; //指针可以率先指向nullptr
		}
	}

	~GraphLink() //析构函数
	{
		for (int i = 0; i < m_numVertices; ++i)
		{
			EdgeNode* ptmp = m_VertexArray[i].point;
			while (ptmp != nullptr)
			{
				m_VertexArray[i].point = ptmp->next;
				delete ptmp;
				ptmp = m_VertexArray[i].point;
			} //end while
			m_VertexArray[i].point = nullptr;
		} //end for
	}

public:
	//插入顶点
	bool InsertVertex(const T& tmpv)
	{
		if (m_numVertices >= MaxVertices_size) //顶点空间已满
		{
			cout << "顶点空间已满" << endl;
			return false;
		}
		if (GetVertexIdx(tmpv) != -1) //该顶点已经存在
		{
			cout << "顶点 " << tmpv << " 已经存在！" << endl;
			return false;
		}
		m_VertexArray[m_numVertices].data = tmpv;
		m_VertexArray[m_numVertices].point = nullptr;
		m_numVertices++;
		return true;
	}

	//插入边
	bool InsertEdge(const T& tmpv1, const T& tmpv2) //在tmpv1和tmpv2两个顶点之间插入一条边
	{
		int idx1 = GetVertexIdx(tmpv1);
		int idx2 = GetVertexIdx(tmpv2);
		if (idx1 == -1 || idx2 == -1) //某个顶点不存在，不可以插入边
			return false;

		//判断是否边重复
		EdgeNode* ptmp = m_VertexArray[idx1].point;
		while (ptmp != nullptr)
		{
			if (ptmp->curridx == idx2)
				return false; //边重复
			ptmp = ptmp->next;
		}

		//可以正常插入，先向下标为idx1对应的顶点的单链表中插入边节点
		ptmp = new EdgeNode;
		ptmp->curridx = idx2;
		ptmp->next = m_VertexArray[idx1].point; //为简化编码和提升代码执行效率，采用头插法将边节点插入到单链表的最前面
		m_VertexArray[idx1].point = ptmp;

		//对于无向图，tmpv1到tmpv2之间插入边就等于tmpv2到tmpv1之间插入了边，所以接着向下标为idx2对应的顶点的单链表中插入边节点
		ptmp = new EdgeNode;
		ptmp->curridx = idx1;
		ptmp->next = m_VertexArray[idx2].point;
		m_VertexArray[idx2].point = ptmp;

		//注意：对于无向图，tmpv1到tmpv2之间插入了边就等于tmpv2到tmpv1之间插入了边
		m_numEdges++;//边数量增加1
		return true;
	}

	//删除边
	bool DeleteEdge(const T& tmpv1, const T& tmpv2)
	{
		int idx1 = GetVertexIdx(tmpv1);
		int idx2 = GetVertexIdx(tmpv2);
		if (idx1 == -1 || idx2 == -1) 
			return false;

		//在第一个节点中查找边信息
		EdgeNode* prev = nullptr; //指向前趋节点方便做删除边节点的操作
		EdgeNode* ptmp = m_VertexArray[idx1].point;
		while (ptmp != nullptr && ptmp->curridx != idx2)
		{
			prev = ptmp; //保存前趋节点方便做删除操作
			ptmp = ptmp->next;
		} //end while
		if (ptmp == nullptr) //两个顶点之间没有边，怎么可以删除呢？
			return false;

		//有边，则可以开始删除边节点
		if (prev == nullptr)
		{
			//删除的是第一个边节点
			m_VertexArray[idx1].point = ptmp->next; //等价于删除头部的节点
		}
		else
		{
			prev->next = ptmp->next;
		}
		delete ptmp; //释放边节点所占用的内存。

		//因为是无向图，所以第二个节点中必然能找到和第一个节点相关的边信息
		prev = nullptr;
		ptmp = m_VertexArray[idx2].point;
		while (ptmp->curridx != idx1) //这里无需判断ptmp != nullptr条件，因为无向图中A到B之间有边，则B到A之间必然有边
		{
			prev = ptmp; //保存前趋节点方便做删除操作
			ptmp = ptmp->next;
		} //end while
		if (prev == nullptr)
		{
			//删除的是第一个边节点
			m_VertexArray[idx2].point = ptmp->next;
		}
		else
		{
			prev->next = ptmp->next;
		}
		delete ptmp;
		m_numEdges--;
		return true;
	}

	//删除顶点，涉及到顶点对应的边也要删除
	bool DeleteVertex(const T& tmpv)
	{
		int idx = GetVertexIdx(tmpv);
		if (idx == -1) //顶点不存在
			return false;

		EdgeNode* ptmp = m_VertexArray[idx].point;
		while (ptmp != nullptr) //先释放该顶点后面链接的各个边节点
		{
			//释放边节点也就等价于删除和当前顶点所连接的边，设想一个如下情形
			/*
			0  A:--->3-->2-->1-->nullptr;
			1  B:--->5-->4-->0-->nullptr;
			2  C:--->5-->0-->nullptr;
			3  D:--->5-->0-->nullptr;
			4  E:--->1-->nullptr;
			5  F:--->3-->2-->1-->nullptr;			
			*/
			//上面情形中，如果要删除顶点C，那么顶点C关联的下标为5、0的边要删除，但删除前
			  //先要在下标为5、0的顶点所关联的边中删除与顶点C（下标为2）关联的边
			int tmpDestIdx = ptmp->curridx; //以删除顶点C为例，tmpDestIdx = 5;
			EdgeNode* ptmpDestPrev = nullptr; //要开始在下标为5的顶点对应的单链表中找出下标为2的边节点进行删除
			EdgeNode* ptmpDest = m_VertexArray[tmpDestIdx].point;
			while (ptmpDest != nullptr && ptmpDest->curridx != idx)
			{
				ptmpDestPrev = ptmpDest; //保存前趋节点方便做删除操作
				ptmpDest = ptmpDest->next;
			} //end while ptmpDest

			if (ptmpDest != nullptr) //两个顶点之间有边，就要删除边
			{
				if (ptmpDestPrev == nullptr)
				{
					//删除的是第一个边节点
					m_VertexArray[tmpDestIdx].point = ptmpDest->next;
				}
				else
				{
					ptmpDestPrev->next = ptmpDest->next;
				}
				delete ptmpDest;
			}

			//顶点指向下一个边节点（第一次while循环所执行的是让C节点指向下标为0的边节点）
			m_VertexArray[idx].point = ptmp->next;
			//可以删除顶点C所关联的下标为5的节点了
			delete (ptmp);
			ptmp = m_VertexArray[idx].point;

			m_numEdges--; //边数减少1
		} //end while ptmp;

		//此时顶点中对应的边信息全部删除了，其他顶点与该被删除顶点相关的边信息也全部删除了
		//此时，针对顶点C的删除，整个邻接表应该是这样：
		/*
			0  A:--->3-->1-->nullptr;
			1  B:--->5-->4-->0-->nullptr;
			2  C:--->nullptr;
			3  D:--->5-->0-->nullptr;
			4  E:--->1-->nullptr;
			5  F:--->3-->1-->nullptr;
			*/

		m_numVertices--; //顶点数减少1，后续用到该值，所以先把该值减1
		//因为要删除C顶点，所以要把末尾的F顶点的数据搬到C的位置
		if (idx != m_numVertices)
		{
			//要删除的不是最后一个顶点，所以把最后一个顶点的数据搬到要删除的顶点处
			m_VertexArray[idx].data = m_VertexArray[m_numVertices].data;
			m_VertexArray[idx].point = m_VertexArray[m_numVertices].point;

			//上面代码执行完毕，相当于这种情形了
			/*
			0  A:--->3-->1-->nullptr;
			1  B:--->5-->4-->0-->nullptr;			
			2  F:--->3-->1-->nullptr;
			3  D:--->5-->0-->nullptr;
			4  E:--->1-->nullptr;
			5  F:----------------------
			*/
			//现在相当于把F的下标从5变成了2，那么所有边节点中，涉及到数字5的，都得变成数字2
			EdgeNode* ptmpnew = m_VertexArray[idx].point; //--->3--->1-->nullptr
			while (ptmpnew != nullptr)
			{
				int tidx = ptmpnew->curridx; //3
				EdgeNode* tp = m_VertexArray[tidx].point; //指向下标3（D节点）对应的边节点的指针，5-->0-->nullptr
				while (tp != nullptr)
				{
					if (tp->curridx == m_numVertices) //在D节点中，找到了下标为5的节点，把该节点下标修改为2
					{
						tp->curridx = idx;
						break; //直接跳出while循环即可
					}
					tp = tp->next;
				} //end while (tp != nullptr)
				ptmpnew = ptmpnew->next;
			} //end while (ptmpnew != nullptr)

			//上面代码执行完毕后，相当于这种情形了
			/*
			0  A:--->3-->1-->nullptr;
			1  B:--->2-->4-->0-->nullptr;
			2  F:--->3-->1-->nullptr;
			3  D:--->2-->0-->nullptr;
			4  E:--->1-->nullptr;			
			*/
		} //end if (idx != m_numVertices)
		m_VertexArray[m_numVertices].point = nullptr;
		return true;
	}

	//获取某个顶点的第一个邻接顶点的下标，返回-1表示获取失败
	int GetFirstNeighbor(int idx) //idx代表顶点下标
	{
		if (idx == -1)
			return -1; //非法
		EdgeNode* pedge = m_VertexArray[idx].point;
		if (pedge != nullptr)
			return pedge->curridx;
		return -1;
	}

	//获取某个顶点（下标为idx1）的邻接顶点（下标为idx2）的下一个邻接顶点的下标，返回-1表示获取失败
	int GetNextNeightbor(int idx1, int idx2)
	{
		if (idx1 == -1 || idx2 == -1)
			return -1;
		EdgeNode* pedge = m_VertexArray[idx1].point;
		while (pedge != nullptr && pedge->curridx != idx2)
		{
			pedge = pedge->next;
		}//end while
		if (pedge != nullptr && pedge->next != nullptr)
		{
			//说明找到idx2这个邻接顶点了
			return pedge->next->curridx;
		}
		return -1;
	}

	void DispGraph() //显示图信息
	{
		for (int i = 0; i < m_numVertices; ++i)
		{
			cout << i << "   " << m_VertexArray[i].data << ":-->"; //输出顶点下标和顶点数据
			EdgeNode* ptmp = m_VertexArray[i].point;
			while (ptmp != nullptr)
			{
				cout << ptmp->curridx << "-->"; //输出顶点相关的边索引（编号）
				ptmp = ptmp->next;
			}
			cout << "nullptr" << endl; //显示指向nullptr并换行
		} //end for
		cout << "图中有顶点" << m_numVertices << "个，边" << m_numEdges << "条!" << endl;
	}

	//深度优先遍历
	void DepthFirstSearch(const T& tmpv) //tmpv代表从该顶点出发开始遍历，即tmpv是开始遍历的起始顶点
	{
		bool vVarray[MaxVertices_size]; //顶点是否被访问过的标记，false表示没有被访问过
		for (int i = 0; i < MaxVertices_size; ++i) //开始时所有顶点都没有被访问过
		{
			vVarray[i] = false;
		}//end for
		int idx = GetVertexIdx(tmpv);
		DepthFirstSearch(idx, vVarray);

		//如果是非连通图，则继续遍历其他子图
		bool iffindnovisited; //是否找到了没被访问的顶点
		int idxnovisited; //没被访问的顶点的下标
	lblloop:
		iffindnovisited = false;
		idxnovisited = -1;
		for (int i = 0; i < m_numVertices; ++i)
		{
			if (vVarray[i] == false)
			{
				iffindnovisited = true; //标记找到了没被访问的顶点
				idxnovisited = i; //记录没被访问的顶点的下标
				break;
			}
		}//end for
		if (iffindnovisited == true) //找到了没被访问的顶点
		{
			DepthFirstSearch(idxnovisited, vVarray);
			goto lblloop;
		}
	}
	void DepthFirstSearch(int idx, bool vVarray[])
	{
		cout << m_VertexArray[idx].data << "-->"; //输出顶点数据（顶点值）
		vVarray[idx] = true; //标记该顶点已经被访问过

		int idx2 = GetFirstNeighbor(idx); //获取第一个邻接顶点的下标，B的第一个邻接顶点是F
		while (idx2 != -1)
		{
			//(1)继续沿着深度访问节点
			if (vVarray[idx2] == false)
			{
				//没访问过，则进行递归访问
				DepthFirstSearch(idx2, vVarray);
			}

			//(2)找其他的邻接顶点（广度方向走）
			idx2 = GetNextNeightbor(idx, idx2); //获取某个顶点（下标idx）的邻接顶点（idx2）的下一个邻接顶点
		} //end while
		return;
	}

	//广度优先遍历
	void BreadthFirstSearch(const T& tmpv) //tmpv代表从该顶点出发开始遍历，即tmpv是开始遍历的起始顶点
	{
		bool vVArray[MaxVertices_size]; //顶点是否被访问过的标记，false表示没有被访问过
		for (int i = 0; i < MaxVertices_size; ++i) //开始时所有顶点都没有被访问过
		{
			vVArray[i] = false;
		}//end for
		int idx = GetVertexIdx(tmpv);
		cout << m_VertexArray[idx].data << "-->";
		vVArray[idx] = true; //标记该顶点已经被访问过

		_nmsp0::LinkQueue<int> lnobj; //借助队列实现遍历
		lnobj.EnQueue(idx); //把起始顶点下标先入队
		while (!lnobj.IsEmpty()) //循环判断队列是否为空
		{
			lnobj.DeQueue(idx); //出队列

			int idx2 = GetFirstNeighbor(idx);
			while (idx2 != -1)
			{
				if (vVArray[idx2] == false)
				{
					//没访问过
					cout << m_VertexArray[idx2].data << "-->";
					vVArray[idx2] = true; //标记该顶点已经被访问过
					lnobj.EnQueue(idx2); //入队
				}
				idx2 = GetNextNeightbor(idx, idx2); //获取某个顶点（下标idx）的邻接顶点（下标为idx2)的下一个邻接顶点的下标				
			} //end while (idx2 != -1)
		} //end while (!lnobj.IsEmpty()) 
		
	}

private:
	//获取顶点下标
	int GetVertexIdx(const T& tmpv)
	{
		for (int i = 0; i < m_numVertices; ++i)
		{
			if (m_VertexArray[i].data == tmpv)
				return i;
		}
		return -1; //不存在的顶点
	}

private:
	int m_numVertices; //当前顶点数量
	int m_numEdges; //边数量
	VertexNode<T> m_VertexArray[MaxVertices_size]; //顶点数组
};

//十字链表
//表示弧的节点结构
struct EdgeNode_cross
{
	int tailidx; //弧尾顶点下标
	int headidx; //弧头顶点下标
	EdgeNode_cross* headlink;//弧头相同的下一个弧
	EdgeNode_cross* taillink; //弧尾相同的下一个弧
	//int weight; //权值，可以根据需要决定是否需要此字段
};

//表示顶点的节点结构
template <typename T>
struct VertexNode_cross
{
	T data; //顶点中的数据
	EdgeNode_cross* firstin; //该顶点作为弧头的第一条弧（入度指针）
	EdgeNode_cross* firstout;//该顶点作为弧尾的第一条弧（出度指针）
};

//邻接多重表
//表示边的节点结构
struct EdgeNode_adjmt
{
	int iidx; //边的第一个顶点下标
	EdgeNode_adjmt* ilink; //指向下一个依附于iidx所代表的顶点的边

	int jidx; //边的第二个顶点下标
	EdgeNode_adjmt* jlink; //指向下一个依附于jidx所代表的顶点的边
	//int weight; //权值，可以根据需要决定是否需要此字段
};

//表示顶点的节点结构
template <typename T>
struct VertexNode_adjmt
{
	T data; //顶点中的数据
	EdgeNode_adjmt* firstedge; //与该顶点相连的第一条边
};

//边集数组
//表示边的结构
struct Edge_esa
{
	int beginidx; //边的起始顶点下标
	int endidx; //边的终止顶点下标
	//int weight; //权值，可以根据需要决定是否需要此字段
};

int main()
{	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//第4章 图
	//第一节 图的基本概念、术语
	//第二节 图的存储结构及基本操作
	//（1）邻接矩阵(数组表示法)：顶点，边（弧）
	//（2）邻接表:对图中的每个顶点建立一个单链表。
	//逆邻接表
	//无向图边节点的数量是2|E|
	//使用邻接表存储无向图所需要的空间复杂度是O(|V|+2|E|)
	//使用邻接表存储有向图所需要的空间复杂度是O(|V|+|E|)
	//图的邻接表表示方式并不唯一（图的邻接矩阵表示方式是唯一的）
	//（3）十字链表
	//使用十字链表存储有向图所需要的空间复杂度是O(|V|+|E|)。
	//（4）邻接多重表
	//存储无向图
	//使用邻接多重表存储有向图所需要的空间复杂度是O(|V|+|E|)。
	//（5）边集数组
	//使用边集数组存储有向图所需要的空间复杂度是O(|V|+|E|)。
	//（6）图各种存储结构的比较
	//(6.1)邻接矩阵：
	//空间复杂度 O(|V|^2)，空间浪费比较多。
	//适用性：稠密图（顶点多边也多）
	//找邻边（有公共顶点的两条边）：需要对行或者列进行遍历，具有O(|V|)的时间复杂度
	//操作便利性：删除边比较容易，删除顶点需要移动许多数据；

	//(6.2)邻接表：
	//空间复杂度：无向图 O(|V|+2|E|)；有向图：O(|V|+|E|)
	//适用性：稀疏图（顶点多边比较少）
	//找邻边：寻找有向图某个顶点的入边（入度）不方便，需要遍历整个邻接表
	//操作便利性：删除无向图的边和顶点并不方便

	//(6.3)十字链表：
	//空间复杂度：O(|V|+|E|)
	//适用性：有向图
	//找邻边：很容易
	//操作便利性：操作比较便利，编程比较复杂

	//(6.4)邻接多重表：
	//空间复杂度：O(|V|+|E|)
	//适用性：无向图
	//找邻边：很容易
	//操作便利性：操作比较便利，编程比较复杂

	//(6.5)边集数组：
	//空间复杂度：O(|V|+|E|)
	//适用性：有向图，无向图
	//找邻边：遍历整个数组
	//操作便利性：不太适合对顶点进行操作的场合。操作比较便利，编程比较简单。

	//(7）图的遍历（以邻接表作为图的存储结构）
	//图的遍历，就是指从图中任意一个顶点出发访遍图中其余顶点，且使每个顶点都被访问且只被访问一次。
	//图的遍历分两种：深度优先遍历，广度优先遍历。
	//1：深度优先遍历（DFS——Depth First Search）:
	  //沿着每一个分支路径进行深入访问。
	//深度优先生成树
	//非连通图，就需要对它的连通分量分别进行深度优先遍历，直到图中所有顶点都被访问。
	//深度优先生成森林
	//2：广度优先遍历（BFS——Breadth First Search）:
	//广度优先生成树
	//广度优先生成森林
	//3：深度与广度优先遍历的空间与时间复杂度：
	//	深度优先遍历，空间复杂度O(|V|)。时间复杂度如果采用邻接表：O(|V|+|E|)，如果采用邻接矩阵：O(|V|^2)。
	//	广度优先遍历，空间复杂度O(|V|)。时间复杂度如果采用邻接表：O(|V|+|E|)，如果采用邻接矩阵：O(|V|^2)。







	GraphLink<char> gm2;
	//向图中插入顶点
	gm2.InsertVertex('A');
	gm2.InsertVertex('B');
	gm2.InsertVertex('C');
	gm2.InsertVertex('D');
	gm2.InsertVertex('E');
	gm2.InsertVertex('F');

	//向图中插入边
	gm2.InsertEdge('A', 'B');
	gm2.InsertEdge('A', 'C');
	gm2.InsertEdge('A', 'D');
	gm2.InsertEdge('B', 'E');
	gm2.InsertEdge('B', 'F');
	gm2.InsertEdge('C', 'F');
	gm2.InsertEdge('D', 'F');
	gm2.DispGraph();

	//gm2.DeleteEdge('A', 'D');
	//gm2.DeleteEdge('E', 'B');
	//gm2.DeleteEdge('E', 'C'); //删除一个不存在的边
	//cout << "------------------" << endl;
	//gm2.DispGraph();
	//gm2.DeleteVertex('C');
	//cout << "------------------" << endl;
	//gm2.DispGraph();
		
	gm2.DepthFirstSearch('B');
	cout << "nullptr" << endl;

	gm2.BreadthFirstSearch('B');
	cout << "nullptr" << endl;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧:  ∞
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误nm,
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件



