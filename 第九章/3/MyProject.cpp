// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。


#include <iostream>
#include <queue>
#include "MersenneTwister.h" 


#pragma warning (disable: 4996) 

using namespace std;

MTRand g_ac; //全局量以产生更加随机的随机数，#include "MersenneTwister.h" 

//地图中格子类型枚举
enum E_MAPNODE_TYPE
{
	e_SN_PASS,  //可通行
	e_SN_OBST,  //障碍（无法通行）
	//....其他类型可以在这里继续增加
};

//地图每个节点相关
struct MapNode
{
	//初始化数据
	void Init(int tmpx, int tmpy, E_MAPNODE_TYPE tmptype)
	{
		x = tmpx;
		y = tmpy;
		type = tmptype;
	}

	//节点位置
	int x;
	int y;
	E_MAPNODE_TYPE type; //格子的类型
	bool sign; //用于标记某个事务
};

//产生随机地图
class CGenRandMap
{
public:
	CGenRandMap(int tmplinecount, int tmpcolcount, int tmpobjCount)//构造函数
	{
		linecount = tmplinecount; //地图行数（其实就是高度）
		colcount = tmpcolcount; //地图列数（其实就是宽度）
		mapobsCount = tmpobjCount; //障碍图块数量

		//确定游戏中心点位置
		mapCenterX = linecount / 2;
		mapCenterY = colcount / 2;
	}
	~CGenRandMap() //析构函数
	{
		//释放内存
		if (m_pmapNode != nullptr)
		{
			//需要释放
			for (int i = 0; i < linecount; ++i)
			{
				delete[] m_pmapNode[i];
			}
			delete[] m_pmapNode;
		}
	}

public:
	//初始化地图信息
	void InitMapInfo()
	{
		int failtimescount = 0; //失败计数
		//动态创建二维数组代表地图（并保存地图数据）
		m_pmapNode = new MapNode * [linecount];
		for (int i = 0; i < linecount; ++i)
		{
			m_pmapNode[i] = new MapNode[colcount];
		}
		for (int i = 0; i < linecount; ++i) //行数
		{
			for (int j = 0; j < colcount; ++j) //列数
			{
				m_pmapNode[i][j].Init(i, j, e_SN_PASS);  //开始时先全部给成可以通行的
			}
		}
		//生成mapobsCount这么多障碍物
		int iCurrObjCount = 0; //当前已经生成的障碍物数量
		for (int i = 0; i < mapobsCount; ++i)  //循环这么多次来尝试生成障碍，即便中间有生成失败的情形也没所谓
		{
			//随机生成障碍的位置
			unsigned int randx = g_ac.randInt() % linecount;
			unsigned int randy = g_ac.randInt() % colcount;

			if (m_pmapNode[randx][randy].type == e_SN_OBST) //不可以是个障碍
				continue;

			if (randx == mapCenterX && randy == mapCenterY) //不可以是地图中间点
				continue;

			//先假设这个点是个障碍（如果测试不行，后续会把这个点修改回非障碍）
			m_pmapNode[randx][randy].type = e_SN_OBST;
			iCurrObjCount++; //因为上面这行假设是个障碍，所以这里假设障碍物的数量就+1

			//判断增加了这个障碍后地图不可行走的数量是不是只减少了1（表示地图可通行）
			if (MapIsFullyAccessible(iCurrObjCount) == false)
			{
				//这个点做障碍会导致地图无法通行，所以把这个点恢复回可通行状态，不用它做障碍点
				m_pmapNode[randx][randy].type = e_SN_PASS; //恢复为可通行
				iCurrObjCount--; //前面假设的障碍计数也要减回去			
				failtimescount++; //统计失败次数				
			}
			else
			{
				//不需要做什么
			}//end if			
		} //end for i
		return;
	}

	//显示地图中的节点信息，障碍图块用1表示，可行走区域用0表示
	void DispMap()
	{
		for (int i = 0; i < linecount; ++i) //行数
		{
			for (int j = 0; j < colcount; ++j) //列数
			{
				if (m_pmapNode[i][j].type == e_SN_PASS)
					cout << 0 << "   ";
				else
					cout << 1 << "   ";
			}
			cout << endl;//换行
		}
		return;
	}

private:

	//判断当前地图是不是完全可通行
	//iCurrObjCount：当前已经生成的障碍物数量
	bool MapIsFullyAccessible(int iCurrObjCount)
	{
		//标记该格子是否已经遍历过。false：没有，true：有
		for (int i = 0; i < linecount; ++i) //行数
		{
			for (int j = 0; j < colcount; ++j) //列数
			{
				m_pmapNode[i][j].sign = false; //该点没被检测过
			}
		}

		//保存可以行走的格子的队列
		std::queue<MapNode*> myqueue; //可行走的位置会保存在这里
		//从中心点开始
		myqueue.push(&m_pmapNode[mapCenterX][mapCenterY]); //中心点先入队列
		m_pmapNode[mapCenterX][mapCenterY].sign = true; //标记中心点已经被遍历过
		int canWalkPosCount = 1; //可以行走的位置统计，因为中心点肯定可以行走，所以这里先给1
		while (myqueue.size() > 0)
		{
			MapNode* firstem = myqueue.front(); //返回队列中的第一个元素
			myqueue.pop();// 删除队列第一个元素

			//获取当前格子上下左右四个方向的格子信息（四邻域填充算法）
			int currposx, currposy;
			currposx = firstem->x;
			currposy = firstem->y;

			//上(x-1,y)			
			//左(x,y-1)
			//右(x,y+1)			
			//下(x+1,y)
			int procposx, procposy;
			for (int i = 0; i < 4; ++i)
			{
				if (i == 0) //处理上
				{
					procposx = currposx - 1;
					procposy = currposy;
				}
				else if (i == 1) //处理左
				{
					procposx = currposx;
					procposy = currposy - 1;
				}
				else if (i == 2) //处理右
				{
					procposx = currposx;
					procposy = currposy + 1;
				}
				else //处理下
				{
					procposx = currposx + 1;
					procposy = currposy;
				}

				//判断是否是个合法位置
				if (procposx < 0 || procposy < 0) //非法点
					continue;
				if (procposx >= linecount || procposy >= colcount) //非法点
					continue;

				//没有被检测过的瓦片，且不是障碍物
				if (m_pmapNode[procposx][procposy].sign == false && m_pmapNode[procposx][procposy].type == e_SN_PASS)
				{
					m_pmapNode[procposx][procposy].sign = true; //标记为检测过
					canWalkPosCount++; //可行走位置数+1					
					myqueue.push(&m_pmapNode[procposx][procposy]);//将该位置增加到队列，
				}
			} //end for
		} //end while

		//参数iCurrObjCount：当前已经生成的障碍物数量		
		unsigned int canwalkpos = linecount * colcount - iCurrObjCount;//可以行走的格子（位置）数量

		//canWalkPosCount：目前实际可以行走的位置
		if (canwalkpos == canWalkPosCount) //如果可以行走的数量 和 上面统计的可行走位置数量相等，则表示增加了这个障碍后，地图依旧可通行
			return true;
		return false;
	}

private:
	int linecount; //地图行数（高度）
	int colcount;  //地图列数（宽度）
	MapNode** m_pmapNode = nullptr; //保存地图数据的动态二维数组	

	//地图中心点位置x、y值，该点不可以有障碍物，该点用于洪水填充算法的判断
	int mapCenterX;
	int mapCenterY;
	int mapobsCount; //障碍图块数量
};


int main()
{

	//第二节 用洪水填充算法(Flood Fill Algorithm)实现通畅的随机地图
	//（1）洪水填充算法基本概念和实现通畅随机地图原理
	//（1.1）洪水填充算法基本概念
	//（1.2）洪水填充算法实现通畅随机地图原理
	//（2）洪水填充算法实现通畅随机地图代码







	//障碍物数量百分比，比如50代表障碍物数量占整个图块的50%；
	int obspercent = 50;
	int mapLines = 50;   //地图的行数
	int mapColumns = 50; //地图的列数
	int obsCount = mapLines * mapColumns * obspercent / 100; //障碍图块的数量；	
		
	CGenRandMap cmobj(mapLines, mapColumns,obsCount);
	cmobj.InitMapInfo(); //初始化地图信息
	cout << "生成的随机地图如下 :" << endl;
	cmobj.DispMap(); //显示生成障碍后的地图，1表示障碍位置，0表示可行走位置

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












//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口