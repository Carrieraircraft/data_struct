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


#define MaxVertices_Size 100 //最大顶点数大小
#define INT_MAX_MY 2147483647 //整型能够保存的最大数值，用以表示两个顶点之间不存在边
template<typename T> //T代表顶点类型
class GraphMatrix //邻接矩阵代表的图
{
public:
	GraphMatrix() //构造函数，空间复杂度O(n)+O(n^2) = O(n^2)
	{
		m_numVertices = 0;
		m_numEdges = 0;
		pm_VecticesList = new T[MaxVertices_Size];
		pm_Edges = new int* [MaxVertices_Size];
		for (int i = 0; i < MaxVertices_Size; ++i)
		{
			pm_Edges[i] = new int[MaxVertices_Size];
		} //end for
		for (int i = 0; i < MaxVertices_Size; ++i)
		{
			for (int j = 0; j < MaxVertices_Size; ++j)
			{
				if (i == j)
				{
					//顶点自己到自己对应的边的权值应该用0标记
					pm_Edges[i][j] = 0;
				}
				else
				{
					pm_Edges[i][j] = INT_MAX_MY; //开始时矩阵中不记录边信息，即边与边之间的权值信息给成最大值IN_MAX_MY
				}
			} //end j
		} //end i
	}

	~GraphMatrix() //析构函数
	{
		delete[] pm_VecticesList;
		for (int i = 0; i < MaxVertices_Size; ++i)
		{
			delete[] pm_Edges[i];
		} //end for
		delete[] pm_Edges;
	}

public:
	//插入顶点
	bool InsertVertex(const T& tmpv)
	{
		if (m_numVertices >= MaxVertices_Size) //顶点空间已满
		{
			cout << "顶点空间已满" << endl;
			return false;
		}
		if (GetVertexIdx(tmpv) != -1) //该顶点已经存在
		{
			cout << "顶点 " << tmpv << " 已经存在！" << endl;
			return false;
		}
		pm_VecticesList[m_numVertices] = tmpv;
		m_numVertices++;
		return true;
	}

	//插入边
	//在tmpv1和tmpv2两个顶点之间插入一条边，注意权值也要插入进来。weight代表边与边之间的权值
	bool InsertEdge(const T& tmpv1, const T& tmpv2, int weight)
	{
		int idx1 = GetVertexIdx(tmpv1);
		int idx2 = GetVertexIdx(tmpv2);
		if (idx1 == -1 || idx2 == -1) //某个顶点不存在，不可以插入边
		{
			return false;
		}
		if (pm_Edges[idx1][idx2] != INT_MAX_MY) //边重复
		{
			return false;
		}
		pm_Edges[idx1][idx2] = pm_Edges[idx2][idx1] = weight; //无向图是一个对称矩阵，tmpv1到tmpv2之间插入边就等于tmpv2到tmpv1之间插入了边
		m_numEdges++; //边数量增加1
		return true;
	}

	//显示图信息，其实就是显示矩阵信息
	void DispGraph()
	{
		cout << "   "; //为了凑一些对齐关系，所以先输出三个空格
		//输出图中的顶点，其实就是矩阵的最顶上一行的顶点名信息
		for (int i = 0; i < m_numVertices; ++i)
		{
			printf("%5c", pm_VecticesList[i]); //5：不够5位的右对齐
		}
		cout << endl; //换行
		//输出对应的邻接矩阵
		for (int i = 0; i < m_numVertices; ++i) //注意循环结束条件是真实的顶点个数
		{
			//输出矩阵左侧的顶点名
			cout << pm_VecticesList[i] << "  ";
			for (int j = 0; j < m_numVertices; ++j)
			{
				if (pm_Edges[i][j] == INT_MAX_MY)
				{
					printf("%5s", "∞"); //两个顶点之间没有边
				}
				else
				{
					printf("%5d", pm_Edges[i][j]);
				}
			} //end j
			cout << endl; //换行
		} //end i
		cout << endl; //换行
	}

	//判断某个idx值是否位于最小生成树顶点下标数组中
	bool IfInMstVertIdxArray(int curridx, int* p_inMstVertIdxArray, int in_MstVertCount)
	{
		for (int i = 0; i < in_MstVertCount; ++i)
		{
			if (p_inMstVertIdxArray[i] == curridx) //这个idx位于最小生成树顶点下标数组中
				return true;
		} //end for
		return false; //这个idx不在最小生成树顶点下标数组中
	}

	//用普里姆算法（Prim）创建最小生成树
	bool CreateMinSpanTree_Prim(const T& tmpv) //tmpv作为创建最小生成树时的起始顶点
	{
		int idx = GetVertexIdx(tmpv);
		if (idx == -1) //顶点不存在
			return false;
		int in_MstVertCount = 1; //已经增加到生成树【最小生成树】中的顶点数量，刚开始肯定是要把起始顶点放进去所以这里给1
		int* p_inMstVertIdxArray = new int[m_numVertices]; //已经增加到生成树中的顶点下标会保存在该数组中
		p_inMstVertIdxArray[0] = idx; //起始顶点下标
		int minWeight = INT_MAX_MY; //用来记录当前的最小权值，先给成最大值

		int minTmpStartVertIdx = -1; //临时存放一个开始顶点的下标值（一个边的开始顶点）
		int minTmpEndVertIdx = -1; //临时存放一个目标顶点的下标值（一个边的末端顶点）

		while (true)
		{
			if (in_MstVertCount == m_numVertices) //生成树中的顶点数量等于了整个图的顶点数量，最小生成树创建完毕
				break;

			minWeight = INT_MAX_MY; //权值先给成最大值
			for (int iv = 0; iv < in_MstVertCount; ++iv) //遍历所有生成树中已有的顶点，从其中找到以该顶点开始的边中权值最小的边所对应的目标顶点
			{
				int tmpidx = p_inMstVertIdxArray[iv]; //拿到该位置的信息【顶点索引】
				for (int i = 0; i < m_numVertices; ++i) //遍历所有顶点以找到所有以tmpidx顶点为起点的边
				{
					if (pm_Edges[tmpidx][i] != 0 && pm_Edges[tmpidx][i] != INT_MAX_MY) //当前顶点与目标顶点不是同一个顶点（否则权值==0）并且与目标顶点之间有连线（否则权值==INT_MAX_MY）
					{
						//在以iv顶点为起点的所有边中找权值最小的边
						//权值最小的边所对应的目标顶点不在最小生成树顶点下标数组中，说明是个新顶点
						if (pm_Edges[tmpidx][i] < minWeight &&
							IfInMstVertIdxArray(
								i,
								p_inMstVertIdxArray,
								in_MstVertCount
							) == false)
						{
							minWeight = pm_Edges[tmpidx][i];
							minTmpStartVertIdx = tmpidx; //记录边对应的开始顶点下标
							minTmpEndVertIdx = i;
						}
					}					
				} //end for i
			} //end for iv
			//走到这里，肯定找到了个新顶点，输出最小生成树的边信息
			cout << pm_VecticesList[minTmpStartVertIdx] << "--->" << pm_VecticesList[minTmpEndVertIdx] << " : 权值=" << minWeight << endl;
			p_inMstVertIdxArray[in_MstVertCount] = minTmpEndVertIdx; //将新顶点增加到最小生成树的下标数组中
			in_MstVertCount++;
		} //end while(true)
		delete[]p_inMstVertIdxArray;
		return true;
	}

	//用普里姆（prim）算法创建最小生成树的第二种方法
	bool CreateMinSpanTree_Prim2(const T& tmpv) //tmpv作为创建最小生成树时的起始顶点
	{
		int idx = GetVertexIdx(tmpv);
		if (idx == -1) //顶点不存在
			return false;

		int lowcost[MaxVertices_Size]; //保存权值的数组，采用new动态分配也可以
		int veridx[MaxVertices_Size]; //保存顶点下标的数组，采用new动态分配也可以
		for (int i = 0; i < m_numVertices; ++i)
		{
			lowcost[i] = pm_Edges[idx][i]; //保存开始顶点的权值信息
			veridx[i] = idx; //保存开始顶点的下标信息
		}  //end for

		int minTmpStartVertIdx = -1;
		int minTmpEndVertIdx = -1;
		for (int i = 0; i < m_numVertices - 1; ++i) //循环“顶点数-1”次即可创建出最小生成树
		{
			//在lowcost数组中找权值最小的顶点
			int minWeight = INT_MAX_MY;
			for (int w = 0; w < m_numVertices; ++w) //遍历lowcost数组，找到其中权值最小的
			{
				if (lowcost[w] != 0 && minWeight > lowcost[w])
				{
					minWeight = lowcost[w];
					minTmpEndVertIdx = w;
				}
			} //end for w
			minTmpStartVertIdx = veridx[minTmpEndVertIdx];
			cout << pm_VecticesList[minTmpStartVertIdx] << "--->" << pm_VecticesList[minTmpEndVertIdx] << " : 权值=" << minWeight << endl; //显示边和权值信息
			lowcost[minTmpEndVertIdx] = 0; //权值设置为0表示该顶点被放入了最小生成树中
			//通过最新寻找到的顶点来修改lowcost数组和veridx数组中的内容
			for (int v = 0; v < m_numVertices; ++v)
			{
				if (lowcost[v] > pm_Edges[minTmpEndVertIdx][v])
				{
					lowcost[v] = pm_Edges[minTmpEndVertIdx][v];
					veridx[v] = minTmpEndVertIdx;
				}
			} //end for v
		} //end for i
		return true;
	}

private:
	//获取顶点下标
	int GetVertexIdx(const T& tmpv)
	{
		for (int i = 0; i < m_numVertices; ++i)
		{
			if (pm_VecticesList[i] == tmpv)
				return i;
		}
		return -1; //不存在的顶点
	}


private:
	int m_numVertices; //当前顶点数量
	int m_numEdges; //边数量
	T* pm_VecticesList; //顶点列表
	int** pm_Edges; //边信息，二维数组
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
	//时间复杂度：O(|V|^2)， O(n^2)。


	GraphMatrix<char> gm;
	//向图中插入顶点
	gm.InsertVertex('A');
	gm.InsertVertex('B');
	gm.InsertVertex('C');
	gm.InsertVertex('D');
	gm.InsertVertex('E');
	gm.InsertVertex('F');
	//向图中插入边
	gm.InsertEdge('A', 'B', 100);
	gm.InsertEdge('A', 'C', 15);
	gm.InsertEdge('A', 'D', 20);

	gm.InsertEdge('B', 'C', 40);
	gm.InsertEdge('B', 'E', 65);

	gm.InsertEdge('C', 'D', 25);
	gm.InsertEdge('C', 'E', 70);
	gm.InsertEdge('C', 'F', 80);

	gm.InsertEdge('D', 'F', 30);
	gm.InsertEdge('E', 'F', 40);

	gm.DispGraph();
	gm.CreateMinSpanTree_Prim('A');
	cout << "------------------" << endl;
	gm.CreateMinSpanTree_Prim2('E');


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



