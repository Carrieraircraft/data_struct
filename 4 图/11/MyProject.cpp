// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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

		////对于无向图，tmpv1到tmpv2之间插入边就等于tmpv2到tmpv1之间插入了边，所以接着向下标为idx2对应的顶点的单链表中插入边节点
		//ptmp = new EdgeNode;
		//ptmp->curridx = idx1;
		//ptmp->next = m_VertexArray[idx2].point;
		//m_VertexArray[idx2].point = ptmp;

		//注意：对于无向图，tmpv1到tmpv2之间插入了边就等于tmpv2到tmpv1之间插入了边
		m_numEdges++;//边数量增加1
		return true;
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

	//拓扑排序算法
	bool TopologicalSort()
	{
		int* pInvexDegree = new int[m_numVertices]; //分配空间记录顶点入度
		memset(pInvexDegree, 0, sizeof(int) * m_numVertices); //清0

		//统计各个顶点的入度值
		for (int i = 0; i < m_numVertices; ++i)
		{
			EdgeNode* pEdgenode = m_VertexArray[i].point;
			while (pEdgenode != nullptr)
			{
				pInvexDegree[pEdgenode->curridx]++; //注意[]中内容
				pEdgenode = pEdgenode->next;
			} //end while
		}//end for

		//将入度为0的顶点先入栈
		std::stack<int> tempstack; //#include <stack>
		for (int i = 0; i < m_numVertices; ++i)
		{
			if (pInvexDegree[i] == 0)
			{
				tempstack.push(i);
			}
		}//end for

		int iOutputVexcount = 0; //输出的顶点数量统计
		//栈不为空就循环
		while (tempstack.empty() == false)
		{
			//出栈
			int topidx = tempstack.top(); //获取栈顶元素
			cout << m_VertexArray[topidx].data << "  "; //输出没有前趋的顶点
			iOutputVexcount++; //输出的拓扑顶点数量统计
			tempstack.pop(); // //删除栈顶元素

			//要将topidx对应顶点的各个临界点入度减1，所以要先找到第一条边
			EdgeNode* pEdgenode = m_VertexArray[topidx].point;
			while (pEdgenode != nullptr)
			{
				int tmpidx = pEdgenode->curridx;
				if (pInvexDegree[tmpidx] != 0) //入度已经为0的顶点，不理会
				{
					pInvexDegree[tmpidx]--; //入度值减1
					if (pInvexDegree[tmpidx] == 0) //入读为0的点入栈
						tempstack.push(tmpidx);
				}
				pEdgenode = pEdgenode->next;
			} //end while
		} // end while
		cout << endl; //换行
		delete[] pInvexDegree;

		if (iOutputVexcount != m_numVertices) //拓扑排序失败
		{
			cout << "输出顶点数量：" << iOutputVexcount << ",而图中实际顶点数量:" << m_numVertices << "，说明图中有环，没办法输出所有顶点序列(非AOV网，拓扑排序错误)" << endl;
			return false;
		}
		return true;
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

int main()
{	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//第4章 图
	//第一节 图的基本概念、术语
	//第二节 图的存储结构及基本操作
	//第三节 图的应用之最小生成树
	//生成树：一个无向连通图的生成树是包含图中全部顶点的一个极小连通子图。
	//最小生成树：对于一个带权无向连通图，其生成树不同，树中所有边上的权值之和也可能不同，
		//边上权值之和最小的生成树就是该带权连通无向图的最小生成树（Minimum Spanning Tree：MST）。
	//（1）普里姆（Prim）算法
	//（2）克鲁斯卡尔（Kruskal）算法:挑选出权值最小的一条边。前提是a)这条边以往没被挑选过b)该边对应的两个顶点没有连通。	
	//第四节 图的应用之最短路径
	//最短路径：指的是图中两个顶点之间经过的边上权值之和最小的路径
	//（1）迪杰斯特拉（Dijkstra）算法	
	//（2）弗洛伊德（Floyd）算法：求解每对顶点之间的最短路径。
	//第五节 图的应用之拓扑排序
	//（1）拓扑排序基本概念
	//(1.1)有向无环图（Directed Acyclic Graph:DAG)：有向图，不存在环。
	//(1.2)AOV网（Activity On Vertex Network)：有向图描述工程的计划和实施过程。 活动：子工程。
		//有向图中如果用顶点来表示活动，有向边（弧）表示活动之间的先后关系，这样的有向图称为顶点表示活动的网，简称AOV网。
	    //AOV网是有向无环图。AOV网边不设权值，若存在两个顶点之间顶点边<vi,vj>，则表示i活动必然发生在j活动之前（活动之间存在制约关系）。
	//(1.3)拓扑排序：是对一个有向图构造拓扑序列的过程，也是对有向无环图顶点的一种排序。
		//拓扑排序主要用来解决一个工程能否按顺序进行的问题（能够进行正常的拓扑排序即表示工程能够按顺序进行）。
	   //a)图谱序列中每个顶点出现且仅出现一次。
	   //b)若顶点vi排在顶点vj之前，则图中不会存在从顶点vj到顶点vi的路径。
	   //c)每个AOV网都有一个或者多个拓扑排序序列。
	   //d)拓扑排序，就是用来找做事情合理的先后顺序。
	//（2）拓扑排序和逆拓扑排序算法
	//indegree成员记录顶点的入度。std::stack。
	//邻接表：算法的总时间复杂度O(|V|+|E|)   。若邻接矩阵：O(|V|^2)。



	GraphLink<char> gm2;
	//向图中插入顶点
	gm2.InsertVertex('A');
	gm2.InsertVertex('B');
	gm2.InsertVertex('C');
	gm2.InsertVertex('D');
	gm2.InsertVertex('E');
	gm2.InsertVertex('F');
	gm2.InsertVertex('G');
	gm2.InsertVertex('H');

	//向图中插入边
	gm2.InsertEdge('A', 'C');
	gm2.InsertEdge('A', 'D');
	gm2.InsertEdge('B', 'C');
	gm2.InsertEdge('C', 'E');
	gm2.InsertEdge('D', 'F');
	gm2.InsertEdge('E', 'G');
	gm2.InsertEdge('F', 'G');
	gm2.InsertEdge('G', 'H');
	//gm2.InsertEdge('H', 'G'); //模拟图中有环的情形
	gm2.DispGraph();
	cout << "拓扑排序的结果为：    ";
	gm2.TopologicalSort();

	return 0;
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



