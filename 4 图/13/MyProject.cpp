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
	int weight; //权值
	EdgeNode* next; //指向下一条边
};


//表示顶点的节点结构，其后是一个链表，链表中每个节点都代表着和该顶点相连的边
template <typename T> //T代表顶点类型
struct VertexNode
{
	int indegree; //入度
	int outdegree; //出度
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
			m_VertexArray[i].outdegree = 0; //出度先给0
			m_VertexArray[i].indegree = 0; //入度先给0
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
	bool InsertEdge(const T& tmpv1, const T& tmpv2,int weight) //在tmpv1和tmpv2两个顶点之间插入一条边
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

		//可以正常插入
		ptmp = new EdgeNode;
		ptmp->curridx = idx2;
		ptmp->weight = weight;
		ptmp->next = m_VertexArray[idx1].point; //为简化编码和提升代码执行效率，采用头插法将边节点插入到单链表的最前面
		m_VertexArray[idx1].point = ptmp;
		m_VertexArray[idx1].outdegree++; //开始顶点出度数增加
		m_VertexArray[idx2].indegree++; //终止顶点入度数增加
		m_numEdges++;//边数量增加1
		return true;
	}	
	
	void DispGraph() //显示图信息
	{
		for (int i = 0; i < m_numVertices; ++i)
		{
			cout << i << "    入度/出度(" << m_VertexArray[i].indegree << "/" << m_VertexArray[i].outdegree << ")" << " "  <<
				m_VertexArray[i].data << ":-->"; 
			EdgeNode* ptmp = m_VertexArray[i].point;
			while (ptmp != nullptr)
			{
				cout << ptmp->curridx << "(权值:" << ptmp->weight << ")-->";					
				ptmp = ptmp->next;
			}
			cout << "nullptr" << endl; //显示指向nullptr并换行
		} //end for
		cout << "图中有顶点" << m_numVertices << "个，边" << m_numEdges << "条!" << endl;
	}

	//拓扑排序算法
	bool TopologicalSort(int *pPopResult,int *pve)
	{
		int* pInvexDegree = new int[m_numVertices]; //分配空间记录顶点入度
		memset(pInvexDegree, 0, sizeof(int) * m_numVertices); //清0

		////统计各个顶点的入度值
		//for (int i = 0; i < m_numVertices; ++i)
		//{
		//	EdgeNode* pEdgenode = m_VertexArray[i].point;
		//	while (pEdgenode != nullptr)
		//	{
		//		pInvexDegree[pEdgenode->curridx]++; //注意[]中内容
		//		pEdgenode = pEdgenode->next;
		//	} //end while
		//}//end for

		//顶点的入度值先拿过来
		for (int i = 0; i < m_numVertices; ++i)
		{
			pInvexDegree[i] = m_VertexArray[i].indegree;
		} //end for

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
			static int sign = 0;
			if (sign == 0)
			{
				sign = 1;
				cout << "拓扑排序的结果为：   ";
			}

			int topidx = tempstack.top(); //获取栈顶元素
			cout << m_VertexArray[topidx].data << "  "; //输出没有前趋的顶点

			pPopResult[iOutputVexcount] = topidx; //记录出栈的元素顺序

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

				//顺带计算事件的最早发生时间ve供后续CriticalPath计算关键路径使用
				if (pve[tmpidx] < (pve[topidx] + pEdgenode->weight))
				{
					pve[tmpidx] = pve[topidx] + pEdgenode->weight;
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

	//求关键路径
	bool CriticalPath()
	{
		//在AOE网中，只有一个入度为0的顶点，称为开始顶点，也只有一个出度为0的顶点，称为结束顶点
		int iStartVerIdx = -1;
		int iEndVerIdx = -1;
		for (int i = 0; i < m_numVertices; ++i)
		{
			if (m_VertexArray[i].indegree == 0)
			{
				if (iStartVerIdx != -1)
				{
					cout << "图中发现超过1个入度为0的节点，非法的AOE网，不能求关键路径" << endl;
					return false;
				}
				iStartVerIdx =  i;
			} //end if

			if (m_VertexArray[i].outdegree == 0)
			{
				if (iEndVerIdx != -1)
				{
					cout << "图中发现超过1个出度为0的节点，非法的AOE网，不能求关键路径" << endl;
					return false;
				}
				iEndVerIdx = i;
			} //end if
		} //end for i

		//(1)事件的最早发生时间ve分配内存准备开始计算：
		int* pve = new int[m_numVertices];
		memset(pve, 0, sizeof(int) * m_numVertices); //清0

		//整个用来计算后续的vl用的
		int* pPopResult = new int[m_numVertices];
		memset(pPopResult, 0, sizeof(int) * m_numVertices); //清0

		//通过拓扑排序能够得到ve值（当然不通过拓扑排序而是单独计算ve值也可以）：
		if (TopologicalSort(pPopResult, pve) == false)
		{
			//内存不要忘记释放
			delete[] pve;
			delete[] pPopResult;
			return false; //图中有环，直接返回
		}

		//(2)事件的最迟发生时间vl计算，注意vl值是从后向前求的。
		int *pvl = new int[m_numVertices];
		memset(pvl, 0, sizeof(int) * m_numVertices); //清0

		int toppos = m_numVertices - 1; //栈顶位置=9-1=8
		int vexIdx = pPopResult[toppos]; //栈顶位置所代表的顶点的下标值
		toppos--;

		for (int i = 0; i < m_numVertices; ++i)
		{
			//初始化vl值，vl值一般都比最大的ve值（pve[idxTop])小，所以把最大ve值先给vl没问题，后续要进行min判断
			pvl[i] = pve[vexIdx]; 
		} //end for

		while (toppos >= 0) //栈里有数据
		{
			int fromVexIdx = pPopResult[toppos]; //7：出栈
			toppos--;

			EdgeNode* pTmpEdge = m_VertexArray[fromVexIdx].point; //下标7所代表的顶点为H，这里拿到H指向的第一条边
			while (pTmpEdge != nullptr) //遍历顶点H指向的其他边
			{
				int toVexIdx = pTmpEdge->curridx; // 8
				if (pvl[fromVexIdx] > (pvl[toVexIdx] - pTmpEdge->weight))
					pvl[fromVexIdx] = pvl[toVexIdx] - pTmpEdge->weight;

				pTmpEdge = pTmpEdge->next;
			} //end while (pTmpEdge != nullptr)
		} //end while (toppos >= 0) 

		//(3)活动的最早开始时间ee计算，该值需要通过ve求得
		//(4)活动的最晚开始时间el计算，该值需要通过vl求得
		//这里不用分配内存并进行计算，只需要求得ee和el临时值，比较他们是否相等就可以得到关键路径了
		int tmpee, tmpel;
		cout << "关键路径如下：" << endl;
		for (int fromVexIdx = 0; fromVexIdx < m_numVertices; ++fromVexIdx)
		{
			EdgeNode* pTmpEdge = m_VertexArray[fromVexIdx].point; //该顶点指向的边信息
			while (pTmpEdge != nullptr)
			{
				int toVexIdx = pTmpEdge->curridx;
				int toWeight = pTmpEdge->weight;

				tmpee = pve[fromVexIdx]; //活动最早开始时间
				tmpel = pvl[toVexIdx] - toWeight; //活动最晚开始时间

				//活动最早开始时间和活动最晚开始时间相等，这属于关键路径上的活动
				if (tmpee == tmpel)
				{
					//用"<顶点1,顶点2>(权值=?)"的形式表示顶点之间的弧
					cout << "<" << m_VertexArray[fromVexIdx].data << "," <<
						m_VertexArray[toVexIdx].data << ">(权值=" << toWeight << ") ";
				}

				pTmpEdge = pTmpEdge->next;
			}//end while
		} //end for

		//释放内存
		delete[] pve;
		delete[] pvl;
		delete[] pPopResult;
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

	//第六节 图的应用之关键路径
	// （1）基本概念
	 //关键路径解决的是估算完成该工程需要的最短时间（从而想办法提高生产效率）问题。
	//AOE网（Activity On Edge Network）：在一个表示工程的带权有向图中，以顶点表示事件，有向边表示活动，以边上的权值表示
	    //完成该活动的开销或者该活动的持续时间，这样的有向图称为边表示活动的网，简称AOE网。
	//关键路径：最长路径长度。把关键路径上的活动称为关键活动。
	//假设AOE网中顶点用v表示：
	//a)事件vk的最早发生时间ve[k]:从开始顶点v0到顶点vk的最大路径长度。该长度决定了从顶点vk发出的活动能够开工的最早时间（即所有以vk为尾的弧所表示的活动的最早开始时间）。
	//如何计算ve[k]呢？  1:将开始顶点ve[0]的值设置为0（初始值）。2：ve[k]值：
	// ve[0]=0,ve[1] =2,ve[2] = 3,ve[3] = 5,ve[4]=13
	//b)时间vk的最迟发生时间vl[k]:不推迟整个工程完成时间（工期）的前提下，事件vk允许的最晚发生时间。
	//计算vl[k]：vl[n-1] = ve[n-1]
	//vl[4] = 13,vl[3]=5,vl[1]=4,vl[2]=3,vl[0]=0
	//c)活动ai的最早开始时间ee[i]：
	//d)活动ai的最晚开始时间el[i]：
	    //el[0] = vl[1]-2 = 2.

	//（2）关键路径算法实现
	//只有带权有向无环图才能求关键路径。
	//el-ee的差值也称为时间余量，表示在不增加整个工程完成工期的情况下，活动可以拖延的时间。
	  //时间余量为0就表示该活动必须按期完成，这样的活动也就是关键活动。由这些关键活动组成的路径就是关键路径。
	//关键路径算法的时间复杂度是O(|V|+|E|)；



	GraphLink<char> gm2;
	//向图中插入顶点	
	gm2.InsertVertex('B');
	gm2.InsertVertex('C');
	gm2.InsertVertex('D');
	gm2.InsertVertex('E');
	gm2.InsertVertex('F');
	gm2.InsertVertex('G');
	gm2.InsertVertex('H');
	gm2.InsertVertex('I');
	gm2.InsertVertex('A');

	//向图中插入边
	gm2.InsertEdge('A', 'B',6);
	gm2.InsertEdge('A', 'C',4);
	gm2.InsertEdge('A', 'D',5);
	gm2.InsertEdge('B', 'E',1);
	gm2.InsertEdge('C', 'E',1);
	gm2.InsertEdge('D', 'F',2);
	gm2.InsertEdge('E', 'G',9);
	gm2.InsertEdge('E', 'H',7);
	gm2.InsertEdge('F', 'H',4);
	gm2.InsertEdge('G', 'I',2);
	gm2.InsertEdge('H', 'I',4);	
	gm2.DispGraph();	
	gm2.CriticalPath();

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



