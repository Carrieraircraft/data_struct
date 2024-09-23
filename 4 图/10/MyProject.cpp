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
		//pm_Edges[idx1][idx2] = pm_Edges[idx2][idx1] = weight; //无向图是一个对称矩阵，tmpv1到tmpv2之间插入边就等于tmpv2到tmpv1之间插入了边
		pm_Edges[idx1][idx2] = weight; //有向图
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

	//迪杰斯特拉（Dijkstra)算法求最短路径
	bool ShortestPath_Dijkstra(const  T& tmpv) //tmpv:源顶点（起始/源顶点/开始顶点）
	{
		int idx = GetVertexIdx(tmpv);
		if (idx == -1) //顶点不存在
			return false;

		bool* pS = new bool[m_numVertices]; //创建集合S用于保存已经处理过的顶点信息（标记各顶点是否已经找到最短路径）
		int* pdist = new int[m_numVertices]; //存放当前起始点到其他各个顶点的距离（最短路径/权值之和），开始时时只需要
												//把邻接矩阵中该点所在行的数据存存入其中，比如如果从顶点A开始，那么
											    //存入的数据就应该是"0,22,∞,6,∞∞"
		int* ppath = new int[m_numVertices]; //记录每个顶点在最短路径上的前趋节点。其内容需要根据pdist中的内容来得到：
											    //pdist中对应下标位置是∞，则ppath对应位置是-1
												//pdist中对应下标位置有权值，则ppath对应位置是起始点的下标。

		//初始化
		for (int i = 0; i < m_numVertices; ++i)
		{
			pS[i] = false; //表示所有顶点都没有加入到集合S中
			pdist[i] = pm_Edges[idx][i]; //保存起始顶点到其他顶点的权值

			if (i == idx || pdist[i] == INT_MAX_MY)
			{
				ppath[i] = -1;
			}
			else
			{
				ppath[i] = idx;
			}
		}
		pS[idx] = true; //表示下标为idx的顶点加入到了集合S中，也就是先把起始点加入到集合S中。

		//执行完上述初始化后：pS={true,false,false,false,false,false}，pdist = {0,22,∞,6,∞∞}, ppath = {-1,0,-1,0,-1,-1};

		int minpathweight = INT_MAX_MY; //保存最小路径权值
		int minidx = -1;
		for (int i = 0; i < m_numVertices - 1; ++i) //因为每次循环都会向集合S加入一个顶点，S中原来已经有一个顶点了，
													//所以只需要再循环m_numVertices-1次，把所有顶点加入到S中，迪杰斯特拉执行完毕
		{
			//现在：从起始顶点到其他所有顶点的路径中，选一条最短路径保存在minpath中
			minpathweight = INT_MAX_MY;
			for (int j = 0; j < m_numVertices; ++j) //本循环找pdist中权值最小的
			{
				if (pS[j] == false &&  //不在S集合中的顶点
					pdist[j] < minpathweight)
				{
					minpathweight = pdist[j]; //记录最小路径权值
					minidx = j; //下标记录下来
				}
			} //end j

			//找到了最短路径，该路径对应的终点（顶点）下标保存在minidx中，将其放入到S集合中。
			pS[minidx] = true; //根据演示图内容，第一次minidx = 3;代表顶点D

			//i的第一次循环分析如下：
			//现在要看一看加入了顶点D之后，开始顶点【经过顶点D】到其他顶点是不是有更短的路径【也就是看如何更新pdist】，已知：
			//(1)顶点D到其他顶点的权值是：{∞,10,20,0,∞,∞}
			//(2)此时pdist={0,22,∞,6,∞∞}, ppath = {-1,0,-1,0,-1,-1};
			//(3)下面的dest循环执行后，pdist={0,16,26,6,∞,∞},ppath = {-1,3,3,0,-1,-1};
			for (int dest = 0; dest < m_numVertices; ++dest)
			{
				if (
					pS[dest] == false && //到达的目标顶点是不可以包含在集合S中的
					(pm_Edges[minidx][dest] != 0 && pm_Edges[minidx][dest] != INT_MAX_MY) //顶点D到其他顶点（B,C）都有路径而且B、C这两个顶点目前不包含在S中
					)
				{
					//A到D的权值 + D到其他点的权值
					if (minpathweight + pm_Edges[minidx][dest] < pdist[dest]) //A到D的权值+D到B的权值如果要是比原来A到B的权值小，则更新A到B的权值为最小的
					{
						pdist[dest] = minpathweight + pm_Edges[minidx][dest];
						ppath[dest] = minidx;
					}
				}
			} //end for dest
		} //end i

		//显示最短路径信息
		cout << "从源顶点" << pm_VecticesList[idx] << "到其他各顶点的最短路径信息如下（不显示的表示没路径）： " << endl;
		//源顶点下标是idx
		for (int destveridx = 0; destveridx < m_numVertices; ++destveridx)
		{
			if (idx == destveridx)
				continue;

			//源顶点和目标顶点不同，则显示源顶点到目标顶点的最短路径
			int weight = pdist[destveridx]; //源顶点到目标顶点的最短路径长度
			if (weight == INT_MAX_MY) //两个顶点之间没有路径
				continue;

			cout << pm_VecticesList[idx] << "--->" << pm_VecticesList[destveridx] << ": " << "最短路径长度(" << weight << "),最短路径：";
			//借用个标准库中的堆栈保存数据
			std::stack<int> tempstack; //#include <stack>
			tempstack.push(destveridx); //最终顶点下标先扔到堆栈

			int tmpidx = ppath[destveridx];
			while (tmpidx != idx) //不等于源顶点时循环
			{
				tempstack.push(tmpidx);
				tmpidx = ppath[tmpidx];
			} //end while

			tempstack.push(idx); //源顶点扔到堆栈
			while (!tempstack.empty())
			{
				cout << pm_VecticesList[tempstack.top()]; //显示栈顶元素
				tempstack.pop(); //删除栈顶元素
				if (tempstack.size() != 0)
					cout << "->";
			}//end while

			cout << endl; //换行
		} //end for destveridx

		delete[] pdist;
		delete[]ppath;
		delete[] pS;
		return true;
	}

	//弗洛伊德（Floyd)算法 求任意两个顶点之间的最短路径
	bool ShortestPath_Floyd(const T& tmpv1, const T& tmpv2) //tmpv1：开始顶点，tmpv2：结束顶点
	{
		int idx1 = GetVertexIdx(tmpv1);
		if (idx1 == -1) //开始顶点不存在
			return false;

		int idx2 = GetVertexIdx(tmpv2);
		if (idx2 == -1) //结束顶点不存在
			return false;

		if (idx1 == idx2)
		{
			cout << "开始顶点和结束顶点不可以相同！" << endl;
			return false;
		}

		int** pdist = new int* [m_numVertices];
		int** ppath = new int* [m_numVertices];
		for (int i = 0; i < m_numVertices; ++i)
		{
			pdist[i] = new int[m_numVertices];
			ppath[i] = new int[m_numVertices];
		} //end for

		//二维数组初始化
		for (int i = 0; i < m_numVertices; ++i)
		{
			for (int j = 0; j < m_numVertices; ++j)
			{
				pdist[i][j] = pm_Edges[i][j];
				ppath[i][j] = -1;
			}//end for j
		} //end for i

		//用三重循环实现弗洛伊德（Floyd)算法
		for (int v = 0; v < m_numVertices; ++v) //依次把各个顶点放入图中，顶点下标是v
		{
			for (int i = 0; i < m_numVertices; ++i)
			{
				for (int j = 0; j < m_numVertices; ++j)
				{
					if (i == j || v == i || v == j)
						continue;

					if (pdist[i][v] == INT_MAX_MY || pdist[v][j] == INT_MAX_MY) //因为这两个数字将做加法运算，所以每个值都必须不能是INT_MAX_MY
					{
						continue;
					}
					else if (pdist[i][j] > (pdist[i][v] + pdist[v][j]))
					{
						pdist[i][j] = pdist[i][v] + pdist[v][j];
						ppath[i][j] = v;
					}
				}//end for j
			} //end for i
		}//end for v
	
		//下两个顶点之间最短路径信息
		if (pdist[idx1][idx2] == INT_MAX_MY)
		{
			cout << "从顶点" << pm_VecticesList[idx1] << "到顶点" << pm_VecticesList[idx2] << "之间没有路径" << endl;
		}
		else
		{
			cout << "从顶点" << pm_VecticesList[idx1] << "到顶点" << pm_VecticesList[idx2] << "最短路径长度(" <<
				pdist[idx1][idx2] << "),最短路径：";
			Disp_FloydPath(ppath, idx1, idx2); //采用一个递归函数来显示最短路径信息
		}

		//释放内存
		for (int i = 0; i < m_numVertices; ++i)
		{
			delete[] pdist[i];
			delete[] ppath[i];
		} //end for
		delete[] pdist;
		delete[] ppath;
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

	//显示弗洛伊德（Floyd）算法找到的两点之间最小路径（递归函数）
	void Disp_FloydPath(int** ppath, int u, int v)
	{
		if (ppath[u][v] == -1)
		{
			cout << "<" << pm_VecticesList[u] << "->" << pm_VecticesList[v] << ">  ";
		}
		else
		{
			int middle = ppath[u][v];
			Dis_FloydPath(ppath, u, middle);
			Dis_FloydPath(ppath, middle,v);
		}		
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
	//顶点数比较少，边数比较多时该算法构造最小生成树效果比较好。 
	//（2）克鲁斯卡尔（Kruskal）算法:挑选出权值最小的一条边。前提是a)这条边以往没被挑选过b)该边对应的两个顶点没有连通。
	//如果采用WeightSort排序，则排序算法的时间复杂度可能达到O(|E|^2)。
	 //如果采用qsort排序，则排序算法的时间复杂度为O(|E|log|E|)。
	//并查集判断两个顶点是否属于同一个集合，最坏时间复杂度O(Log|V|)。整个while循环时间复杂度O(|V|Log|V|)。
	//采用qsort算法，整个克鲁斯卡尔算法的时间复杂度O(|E|log|E| + |V|Log|V|)
	//图中顶点数比较多，边数比较少时使用该算法构造最小生成树效果比较好。
	//第四节 图的应用之最短路径
	//最短路径：指的是图中两个顶点之间经过的边上权值之和最小的路径
	//（1）迪杰斯特拉（Dijkstra）算法
	//思路1：a)设置一个集合S用于存放已经找到最短路径的顶点。S={A}
	//      b)设置一个叫dist的数组，元素数量等同于图中顶点数量。该数组用于存放当前起始点到其他各个顶点的最短距离（权值最小）,
			  //开始时该数组内容就是就是图4.4_2中源顶点 A所在行的值即{0，22，∞，6，∞,∞}
	//      c)设置一个叫path的数组，元素数量等同于图中顶点数量。该数组用于记录每个顶点在最短路径上的前趋节点，其内容需要根据dist
	          //中的内容得出。dist中对应下标位置是0或者∞，path对应位置是-1，dist中对应下标位置有权值则path对应位置是源顶点的下标。
	          //所以，开始时该数组内容为{-1，0，-1，0，-1，-1}；
	//思路2：开始计算从源顶点A到不在集合S中的顶点的最短路径。
	//    选择A->D，距离是6。并把顶点D放入集合S中表示源顶点A到顶点D的最短路径已经找到）。
	//    S={A,D}
	//    更新后的dist数组{0，16，26，6，∞,∞}，path={-1，3，3，0，-1，-1}

	//整理一下源顶点到其他顶点的距离
	//A->B=16（A->D->B），A->C=26（A->D-C），A->D=6，A->E=∞,A->F=∞;
	//选中A->B=16（A->D->B）,把顶点B放入集合S中：
	//     S={A,D,B}

	//A->E = 6+10+100=116(A->D->B->E路径)
	//dist数组{ 0，16，26，6，116,∞ }
	//path={-1，3，3，0，1，-1}

	//整理一下源顶点到其他顶点的距离
	//A->B=16（A->D->B）,A->C=26（A->D-C），A->D=6，A->E=116(A->D->B->E路径),A->F=∞
	//A->C=26（A->D->C）,把顶点C放入到集合S中：
	//     S={A,D,B,C}
	//A->E = 6+20+40=66（A->D->C->E）
	//A->F = 6+20+10=36(A-D->C->F)
	//dist数组{ 0，16，26，6，66,36 }
	//path={-1，3，3，0，2，2}

	//整理一下源顶点到其他顶点的距离
	//A->B=16（A->D->B）,A->C=26（A->D-C），A->D=6，A->E=66(A->D->C->E路径),A->F=36(A->D->C->F路径)
	//A->F = 36(A->D->C->F路径)
	//     S={A,D,B,C,F}
	//A->E=71 (A->D->C->F->E路径)
	//dist数组{ 0，16，26，6，66,36 }
	//path={-1，3，3，0，2，2}

	//整理一下源顶点到其他顶点的距离
	//A->B=16（A->D->B）,A->C=26（A->D-C），A->D=6，A->E=66(A->D->C->E路径),A->F=36(A->D->C->F路径)
	//A->E=66(A->D->C->E路径)
	//     S={A,D,B,C,F,E}

	//在增加了顶点E到集合后，顶点A（经过顶点E）到其他所有顶点是不是有更短的路径存在呢？没有了，因为顶点E没有到达任何其他顶点。
	//至此，集合S中已经包含了图中所有顶点，所以缔结斯特拉算法结束，此时：
	//dist数组{ 0，16，26，6，66,36 }
	//path={-1，3，3，0，2，2}
	
	//结果：
	//a)如何得到从源顶点A到顶点B的最短路径长度？
	//b)如何得到从源顶点A到顶点E的最短路径长度？

	//算法时间复杂度是O(|V|^2)。
	//算法的实用价值：
	//a)城市A到B如何走距离最短
	//b)城市A到B如何走最节省时间
	//c)城市A到B如何走花费的金钱最少
	//d)地铁站之间如何换乘所需要的换乘次数最少	

	//（2）弗洛伊德（Floyd）算法：求解每对顶点之间的最短路径。
	//a)设置一个叫做dist的二维数组，存储图中任意两个顶点之间当前的最短路径长度信息。
	//设置一个叫做path的二维数组，用于存储两个顶点所在最短路径上的中间点，起始值=-1，表示没有中间点。
	//算法描述：依次向图中加入顶点v，每次加入顶点后都进行这样的操作：
		//遍历上一个阶段得到的dist数组。dist数组的所有下标对(用[i][j]表示)中，如果i!=j并且v!=i,v!=j，
			// 则如果dist[i][j] > ( dist[i][v] + dist[v][j]),则将dist[i][j]的值更新为dist[i][v]+dist[v][j]
				//同时将path[i][j]修改为v。
	//b)开始计算：先把图中第一个顶点A(下标为0，即v=0)加入到有向图中，
	//dist数组中满足i!=j并且v!=i,v!=j 条件的成员只有6个：dist[1][2],[1][3],[2][1],[2][3],[3][1],[3][2]
	//开始分析
	//dist[1][2]=4，而dist[1][0]+dist[0][2] = ∞，忽略。
	// 
	//c)把图中第二个顶点B（下标为1，v=1)加入到有向图中。
	//dist数组中满足i != j并且v != i, v != j 条件的成员只有6个：dist[0][2], [0][3], [2][0], [2][3], [3][0], [3][2]
	//开始分析
	//dist[0][2] =  ∞, 而dist[0][1] + dist[1][2] = 5+4=9，采纳，更新dist[0][2] = 9
	//dist[0][3] = 10, 而dist[0][1] + dist[1][3] = 5+2=7,采纳，更新dist[0][3] = 7
	//dist数组
	//0,5,9,7
	//∞,0,4,2
	//3,3,0,2
	//∞,∞,1,0
	//path数组
	//-1,-1,1,1
	//-1,-1,-1,-1
	//-1,-1,-1,-1
	//-1,-1,-1,-1

	//d)把图中的第三个顶点C（下标为2，v=2)加入到有向图中。
	//dist数组中满足i != j并且v != i, v != j 条件的成员只有6个：dist[0][1], [0][3], [1][0], [1][3], [3][0], [3][1]
	//开始分析
	//dist[1][0] = ∞,而dist[1][2]+dist[2][0]=7,采纳，dist[1][0]=7
	//dist[3][0] = ∞,而dist[3][2]+dist[2][0] = 4,采纳，dist[3][0]=4
	//dist[3][1] = ∞,而dist[3][2]+dist[2][1] = 4，采纳，dist[3][1]=4
	//dist数组
	//0,5,9,7
	//7,0,4,2
	//3,3,0,2
	//4,4,1,0
	//path数组
	//-1,-1,1,1
	//2,-1,-1,-1
	//-1,-1,-1,-1
	//2,2,-1,-1
	//e)把D加入到有向图
	//dist数组
	//0,5,8,7
	//6,0,3,2
	//3,3,0,2
	//4,4,1,0
	//path数组
	//-1,-1,3,1
	//3,-1,3,-1
	//-1,-1,-1,-1
	//2,2,-1,-1
	// 
	//找顶点B（下标1）到顶点A（下标0）的最短路径
	//[1] [3]   [0]
	//path[1][3] = -1 ,表示直接连接的
	//path[3][0] = 2
	//[1] [3]  [2]   [0] -- B,D,C,A
	//path[3] [2] =-1,表示直接连接的
	//path[2] [0] = -1,表示直接连接的
	//弗洛伊德算法的时间复杂度打给为O(|V|^3)。


	GraphMatrix<char> gm;
	gm.InsertVertex('A');
	gm.InsertVertex('B');
	gm.InsertVertex('C');
	gm.InsertVertex('D');
	gm.InsertVertex('E');
	gm.InsertVertex('F');

	//向图中插入边
	gm.InsertEdge('A', 'B', 22); //22代表边的权值
	gm.InsertEdge('A', 'D', 6);
	gm.InsertEdge('B', 'E', 100);
	gm.InsertEdge('C', 'B', 50);
	gm.InsertEdge('C', 'E', 40);
	gm.InsertEdge('C', 'F', 10);
	gm.InsertEdge('D', 'B', 10);
	gm.InsertEdge('D', 'C', 20);
	gm.InsertEdge('F', 'D', 65);
	gm.InsertEdge('F', 'E', 35);

	//显示图形
	gm.DispGraph();
	//gm.ShortestPath_Dijkstra('A');
	gm.ShortestPath_Floyd('A', 'F');

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



