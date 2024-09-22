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

#define MaxVertices_size 10  //最大顶点数大小

template<typename T> //T代表顶点类型
class GraphMatrix //邻接矩阵代表的图
{
public:
	GraphMatrix() //构造函数，空间复杂度O(|V|) + O( |V|^2) = O( |V|^2) 
	{
		m_numVertices = 0;
		m_numEdges = 0;
		pm_VecticesList = new T[MaxVertices_size];
		pm_Edges = new int* [MaxVertices_size];
		for (int i = 0; i < MaxVertices_size; ++i)
		{
			pm_Edges[i] = new int[MaxVertices_size];
		} //end for

		for (int i = 0; i < MaxVertices_size; ++i)
		{
			for (int j = 0; j < MaxVertices_size; ++j)
			{
				pm_Edges[i][j] = 0; //矩阵中元素值初始都给0，表示顶点之间目前还没有边存在
			} //end for j
		} //end for i
	}

	~GraphMatrix() //析构函数
	{
		delete[] pm_VecticesList;
		for (int i = 0; i < MaxVertices_size; ++i)
		{
			delete[] pm_Edges[i];
		} //end for i
		delete[] pm_Edges;
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
			cout << "顶点" << tmpv << "已经存在!" << endl;
			return false;
		}

		pm_VecticesList[m_numVertices] = tmpv;
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
		if (pm_Edges[idx1][idx2] != 0) //边重复
			return false;

		pm_Edges[idx1][idx2] = pm_Edges[idx2][idx1] = 1; //无向图是对称矩阵.tmpv1到tmpv2之间插入边就等于tmpv2到tmpv1之间插入了边
		m_numEdges++; //边数量增加1
		return true;
	}

	//删除边
	bool DeleteEdge(const T& tmpv1, const T& tmpv2)
	{
		int idx1 = GetVertexIdx(tmpv1);
		int idx2 = GetVertexIdx(tmpv2);
		if (idx1 == -1 || idx2 == -1) //某个顶点不存在，不可以删除边		
			return false;
		if (pm_Edges[idx1][idx2] == 0) //没边不能删除
			return false;

		pm_Edges[idx1][idx2] = pm_Edges[idx2][idx1] = 0;
		m_numEdges--; //边数量减少1
		return true;
	}

	//删除顶点
	bool DeleteVertex(const T& tmpv)
	{
		int idx = GetVertexIdx(tmpv);
		if (idx == -1) //顶点不存在
			return false;
		int deledges = 0; //要删除的边数统计（顶点被删除，相关的边则肯定也不存在了）

		//统计一下矩阵中该顶点对应的边数
		for (int i = 0; i < m_numVertices; ++i)
		{
			if (pm_Edges[idx][i] != 0)
			{
				deledges++;
			}
		}
		//该顶点在矩阵中所载行和列都要删除
		//(1)下面的行先覆盖上面的行
		for (int i = idx; i < (m_numVertices - 1); ++i) //行数
		{
			for (int j = 0; j < m_numVertices; ++j) //列数
			{
				pm_Edges[i][j] = pm_Edges[i + 1][j];
			}
		}
		//(2)右面的列再覆盖左面的列
		for (int i = 0; i < (m_numVertices - 1); ++i) //行数，因为上面的处理，行数已经少了1了
		{
			for (int j = idx; j < (m_numVertices - 1); ++j) //列数
			{
				pm_Edges[i][j] = pm_Edges[i][j+1];
			}
		}

		//从顶点列表里把顶点删除，注意，观察的顺序还是保持的，比如观察顺序是A,B,C,D,E,F，如果
		 //删除了C，则观察顺序应该保持为A,B,D,E,F。
		for (int i = idx; i < (m_numVertices - 1); ++i)
		{
			pm_VecticesList[i] = pm_VecticesList[i + 1];
		}
		m_numVertices--;//顶点数减少
		m_numEdges -= deledges; //边数减少
		return true;
	}

	void DispGraph() //显示图信息，其实就是显示矩阵信息
	{
		cout << "   "; //为了凑一些对齐关系，所以先输出三个空格
		//输出图中的顶点，其实就是矩阵的最顶上一行的顶点名信息
		for (int i = 0; i < m_numVertices; ++i)
		{
			cout << pm_VecticesList[i] << " ";
		}
		cout << endl; //换行
		//输出对应的邻接矩阵
		for (int i = 0; i < m_numVertices; ++i) //注意循环结束条件是真实的顶点个数
		{
			//输出矩阵左侧的顶点名
			cout << pm_VecticesList[i] << " ";
			for (int j = 0; j < m_numVertices; ++j)
			{
				cout << pm_Edges[i][j] << " ";//每个数据之间以空格分隔
			} //end for j
			cout << endl; //换行
		} //end for i
		cout << endl; //换行
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
	int m_numEdges;  //边数量
	T* pm_VecticesList; //顶点列表
	int** pm_Edges; //边信息，二维数组

};


int main()
{	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//第4章 图
	//第一节 图的基本概念、术语
	//第二节 图的存储结构及基本操作
	//（1）邻接矩阵(数组表示法)：顶点，边（弧）
	//邻接矩阵法：有边（弧）的地方标记为1，否则标记为0。
	//时间复杂度从O(|V|^2)就会变成O(|V|)。如果只做删除标记，则时间复杂度为O(1)。
	//空间复杂度：O( |V|^2) ： |V|表示图中顶点个数

	//邻接矩阵适合存储稠密图（边比较多）

	


	GraphMatrix<char> gm;
	//向图中插入顶点
	gm.InsertVertex('A');
	gm.InsertVertex('B');
	gm.InsertVertex('C');
	gm.InsertVertex('D');
	gm.InsertVertex('E');
	gm.InsertVertex('F');

	//向图中插入边
	gm.InsertEdge('A', 'B');
	gm.InsertEdge('A', 'C');
	gm.InsertEdge('A', 'D');
	gm.InsertEdge('B', 'E');
	gm.InsertEdge('B', 'F');
	gm.InsertEdge('C', 'F');
	gm.InsertEdge('D', 'F');
	gm.DispGraph();
	//删除图中的边
	gm.DeleteEdge('A', 'D');
	gm.DispGraph();
	//删除图中的顶点
	gm.DeleteVertex('C');
	gm.DispGraph();


	

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



