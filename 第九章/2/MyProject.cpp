// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
#include <map>

using namespace std;
#pragma warning(disable : 4996) 


//地图中格子类型枚举
enum E_STARNODE_TYPE
{
	e_SN_PASS,  //可通行
	e_SN_OBST,  //障碍（无法通行）
	//....其他类型可以在这里继续增加
};
//A*节点相关
struct AStarNode
{
	//初始化数据
	void Init(int tmppos, E_STARNODE_TYPE tmptype)
	{
		pos = tmppos;
		type = tmptype;
	}
	float f; //寻路消耗
	float g; //离起点距离
	float h; //离终点距离
	AStarNode* parent; //记录父节点
	int pos; //该节点的格子位置，这一个数字中其实就包含这该位置的行值和列值
	E_STARNODE_TYPE type; //格子的类型
};
//A*寻路算法管理器类
class AStarMgr
{
public:
	AStarMgr(int tmplinecount, int tmpcolcount)//构造函数
	{
		linecount = tmplinecount; //地图行数（其实就是高度）
		colcount = tmpcolcount; //地图列数（其实就是宽度）
	}
	~AStarMgr() //析构函数
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

	//初始化地图信息
	void InitMapInfo(int* ptmpmaparray)
	{
		//动态创建二维数组代表地图（并保存地图数据）
		m_pmapNode = new AStarNode * [linecount];
		for (int i = 0; i < linecount; ++i)
		{
			m_pmapNode[i] = new AStarNode[colcount];
		}

		//一行一行的创建地图
		for (int i = 0; i < linecount; ++i) //行数
		{
			for (int j = 0; j < colcount; ++j) //列数
			{
				//cout << *(ptmpmaparray + i * colcount + j) <<""; //等价于ptmpmaparray[i][j]
				int ywnum;
				GetTerr1NumFrom2Num(i, j, ywnum); //将对应的二维数组位置a[i,j]转换成一个位置数字保存到ywnum中，方便存储
				int tmparryvalue; //取得a[i][j]位置的值
				tmparryvalue = *(ptmpmaparray + i * colcount + j);
				if (tmparryvalue == 0)
				{
					//正常通行位置
					m_pmapNode[i][j].Init(ywnum, e_SN_PASS); //初始化该图块
				}
				else
				{
					//障碍位置					
					m_pmapNode[i][j].Init(ywnum, e_SN_OBST);
				}
			} //end for j
			//cout << endl;
		} //end for i
		return;
	}

	//通过给出地图的二维下标（位置），得到地图的1维数字（位置），调用者保证x, y的合理值
	void GetTerr1NumFrom2Num(int posx, int posy, int& yiweinum)
	{
		//假设有一个5*6的地图（五行六列）
		//比如，这里给进来 x = 3, y = 2 要返回的是 8 
		//给进来x = 1,y=4,返回22		
		//[0,0] [0,1] [0,2] [0,3] [0,4] [0,5]
		//[1,0] [1,1] [1,2] [1,3] [1,4] [1,5]
		//[2,0] [2,1] [2,2] [2,3] [2,4] [2,5]
		//[3,0] [3,1] [3,2] [3,3] [3,4] [3,5]
		//[4,0] [4,1] [4,2] [4,3] [4,4] [4,5]		
		//而寻路时，用一维数字来处理，左下角为0，那么应该如此：
		//24     25    26     27    28    29
		//18     19    20     21    22    23
		//12     13    14     15    16    17
		//6      7     8      9     10    11
		//0      1     2      3     4     5
		yiweinum = (linecount - 1 - posx) * (colcount)+posy;
		return;
	}

	//给出1维数字（位置），返回二维下标（位置），调用者保证yiweinum的合理值
	//yiweinum：代表一维的地图位置
	//posx,posy：返回的二维下标
	void GetTerr2NumFrom1Num(int yiweinum, int& posx, int& posy)
	{
		posx = linecount - (yiweinum / colcount) - 1;
		posy = yiweinum % colcount;
		return;
	}

public:
	//寻路算法：
	//startx，starty：开始位置的x,y值
	//endx,endy：结束位置的x,y值
	//listresult寻路路径信息
	bool FindPath(int startx, int starty, int endx, int endy, std::list<int>& listresult)
	{
		int startpos, endpos;
		GetTerr1NumFrom2Num(startx, starty, startpos); //把二维下标转成1个数字，方便保存
		GetTerr1NumFrom2Num(endx, endy, endpos);
		return FindPath(startpos, endpos, listresult); //调用重载函数
	}

	//A*寻路核心算法
	//startPos：寻路开始位置，endPos：寻路结束位置。
	//listresult：寻路路径信息
	//返回true表示找到了路径，否则返回false;
	bool FindPath(int startPos, int endPos, std::list<int>& listresult)
	{
		//判断startPos和endPos是否合法
		int gzcount = linecount * colcount; //地图中的格子数量

		//判断是否是在地图范围内的位置
		if (startPos < 0 || startPos >= gzcount || endPos < 0 || endPos >= gzcount) //位置显然不合法，比如格子数量56，那么位置应该是0~55之间
		{
			cout << "起点或者终点不合法，不能寻路！" << endl;
			return false;
		}
		if (startPos == endPos)
		{
			cout << "起点和终点相同，没必要寻路！" << endl;
			return false;
		}

		int posx1, posy1;
		int posx2, posy2;
		//把1维代表的位置转成2维数组下标，方便操作
		GetTerr2NumFrom1Num(startPos, posx1, posy1); //起点
		GetTerr2NumFrom1Num(endPos, posx2, posy2);   //终点
		if (m_pmapNode[posx1][posy1].type == e_SN_OBST || m_pmapNode[posx2][posy2].type == e_SN_OBST)
		{
			//起点或者终点为障碍点，这是不能寻路的，寻路要求起点和终点必须都是可通行点
			cout << "起点或者终点是障碍点，不能寻路！" << endl;
			return false;
		}

		//清理一些数据，因为FindPath()可能会被多次反复调用，避免上次的数据影响这次的寻路
		//清空开启和关闭列表
		openList.clear();
		closeList.clear();

		//开始运用寻路算法来寻路了
		//寻路开始时，将起点（命名为a点）放入关闭列表中。并且起点没有父节点
		m_pmapNode[posx1][posy1].parent = nullptr;
		m_pmapNode[posx1][posy1].f = m_pmapNode[posx1][posy1].g = m_pmapNode[posx1][posy1].h = 0.0f; //清0，因为孩子的某些值可能要用这些值来参与计算求得
		closeList.push_back(&m_pmapNode[posx1][posy1]); //放入关闭列表

		//下面是个不断循环的过程
		while (true)
		{
			//观察起点格子周围的8个格子,排除障碍点，其他点都放入到开启列表中
			pointToOpenList(posx1 - 1, posy1 - 1, 1.4f, &m_pmapNode[posx1][posy1], posx2, posy2);//左上(x-1,y-1)
			pointToOpenList(posx1 - 1, posy1, 1.0f, &m_pmapNode[posx1][posy1], posx2, posy2);//上(x-1,y)
			pointToOpenList(posx1 - 1, posy1 + 1, 1.4f, &m_pmapNode[posx1][posy1], posx2, posy2);//右上(x-1,y+1)
			pointToOpenList(posx1, posy1 - 1, 1.0f, &m_pmapNode[posx1][posy1], posx2, posy2);//左(x,y-1)
			pointToOpenList(posx1, posy1 + 1, 1.0f, &m_pmapNode[posx1][posy1], posx2, posy2);//右(x,y+1)
			pointToOpenList(posx1 + 1, posy1 - 1, 1.4f, &m_pmapNode[posx1][posy1], posx2, posy2);//左下(x+1,y-1)
			pointToOpenList(posx1 + 1, posy1, 1.0f, &m_pmapNode[posx1][posy1], posx2, posy2);//下(x+1,y)
			pointToOpenList(posx1 + 1, posy1 + 1, 1.4f, &m_pmapNode[posx1][posy1], posx2, posy2);//右下(x+1,y+1)

			if (openList.size() <= 0)
			{
				//if条件成功的可能性1：寻路所有点都找了一遍都从开始列表转移到关闭列表，导致开启列表为空，这表示是死路
				//if条件成功的可能性2：开始点周围8个方向全是障碍，这也代表死路，无法寻路成功
				cout << "死路，寻路失败！" << endl;
				return false;
			}
			//寻找开启列表中f值（消耗）最小的节点，把所选择的节点从开启列表移到关闭列表
			openList.sort(openlistsort);  //按f值从小到大排序
			auto iter = openList.begin();
			AStarNode* ptmpa = (*iter);
			closeList.push_back(ptmpa); //openList是排好序的，开头元素就是f值最小的
			openList.erase(iter); //移除开头元素

			//把所选择的位置一维数字转成二维下标方便比较判断
			int tmpselposx, tmpselposy;
			GetTerr2NumFrom1Num(ptmpa->pos, tmpselposx, tmpselposy);
			//判断一下该选择的点是不是终点
			if (tmpselposx == posx2 && tmpselposy == posy2)
			{
				//找到了终点,A*寻路结束了，回溯把路径信息向listresult里放
				listresult.push_front(ptmpa->pos); //先把终点放入到结果列表中
				while (ptmpa->parent != nullptr) //回溯
				{
					ptmpa = ptmpa->parent;
					listresult.push_front(ptmpa->pos);  //这样压最终起点就在listresult的最上面
				} //end while
				break; //寻路结束，跳出while循环
			}
			//走到这里表示寻路没结束，继续
			posx1 = tmpselposx;
			posy1 = tmpselposy;
		} //end while
		cout << "成功完成寻路！" << endl;
		return true;
	}
private:
	//将一个点放入开启列表：点位置要合法，点必须是可通行位置，必须不在开启和关闭列表中
	//posx1,posy1，要加入到开启列表中的点
	//g：要加入到开启列表的点离起点的距离
	//parent：要加入到开启列表的点的父节点
	//posx2,posy2：寻路到的终点，用于计算h(离终点距离)值
	void pointToOpenList(
		int posx1, int posy1,
		float g,
		AStarNode* parent,
		int posx2, int posy2
	)
	{
		if (posx1 < 0 || posy1 < 0) //非法点
			return;
		if (posx1 >= linecount || posy1 >= colcount) //x或者y值范围不合法
			return;
		if (m_pmapNode[posx1][posy1].type != e_SN_PASS) //不可通行位置不行
			return;

		//不在关闭列表中
		for (auto iter = closeList.begin(); iter != closeList.end(); ++iter)
		{
			if ((*iter) == &m_pmapNode[posx1][posy1]) //已经在关闭列表中，不行
				return;
		}
		for (auto iter = openList.begin(); iter != openList.end(); ++iter)
		{
			if ((*iter) == &m_pmapNode[posx1][posy1]) //已经在开启列表中，不行
				return;
		}
		//计算f值:f = g+h(寻路消耗 = 离起点距离 + 离终点距离)
		m_pmapNode[posx1][posy1].parent = parent; //设置父节点
		m_pmapNode[posx1][posy1].g = parent->g + g; //注意这里的g一定要加上自己父节点的g值
		m_pmapNode[posx1][posy1].h = float(abs(posx2 - posx1) + abs(posy2 - posy1)); //abs()取绝对值函数。曼哈顿距离（Manhattan distance）公式
		m_pmapNode[posx1][posy1].f = m_pmapNode[posx1][posy1].g + m_pmapNode[posx1][posy1].h;

		//保存到开启列表中
		openList.push_back(&m_pmapNode[posx1][posy1]);
		return;
	}

	//开启列表排序相关函数（按f值从小到大排序）
	static bool openlistsort(AStarNode* asn1, AStarNode* asn2)
	{
		if (asn1->f < asn2->f)
			return true;
		return false;
	}

private:

	int linecount; //地图行数（高度）
	int colcount;  //地图列数（宽度）

	std::list<AStarNode*> openList;//开启列表，#include <list>
	std::list<AStarNode*> closeList; //关闭列表

	AStarNode** m_pmapNode = nullptr; //保存地图数据的动态二维数组
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//第9章 高级实用算法
	//第一节 用A* 搜索算法实现游戏中的寻路功能(A Star Pathfinding Algorithm)
	//（1）A* 寻路算法的基本概念描述
	//（2）A* 寻路算法的细节阐述
	//a)寻路消耗公式：f代表寻路消耗。g代表离起点距离。h代表离终点距离(计算h用到的公式叫曼哈顿距离)。
	// f = g+h，  寻路消耗 = 离起点距离 + 离终点距离
	//b)开启和关闭列表：用容器vector或者list来保存算法实现过程中的一些重要点的信息
	//c)当前点（格子）的父节点（用于确定最终的寻路路径）



	//将如下二维数组作为要寻路的地图[实际项目中地图信息应该是从地图或者配置文件中读入]，其中0代表该位置正常通行，1代表是个障碍	
	//定义数组时给了初始值则第一维可以省略
    //行数列数设置为不同值以便更容易发现编程中的错误
	int maparray[][8] = { 
		{0,1,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{1,1,1,1,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0}
	};
	int elmcount = sizeof(maparray) / sizeof(maparray[0][0]); //56：获取二维数组中元素数量
	int linecount = sizeof(maparray) / sizeof(maparray[0]); //7：行数
	int colcount = elmcount / linecount; //8：列数

	AStarMgr asobj(linecount, colcount); //构造A*管理器对象
	asobj.InitMapInfo((int*)&maparray); //初始化地图

	std::list<int> listresult; //寻路结果信息保存到该容器中
	bool iffindapath = asobj.FindPath(4, 2, 0, 0, listresult); //现在寻路路径保存在了listresult中

	//做个输出
	maparray[4][2] = 7;  //寻路开始点和结束点显示成7
	maparray[0][0] = 7;
	cout << "当前的地图情形：" << endl;
	for (int i = 0; i < linecount; ++i) //行数
	{
		for (int j = 0; j < colcount; ++j) //列数
		{
			cout << maparray[i][j] << "";
		}
		cout << endl;//换行
	}

	if (iffindapath == true) //寻路成功，则显示一下寻路到的路径
	{
		//将要寻路的路径位置设置为数字7以便后续显示出来方便观察
		for (auto iter = listresult.begin(); iter != listresult.end(); ++iter)
		{
			int posyiwei = (*iter); //一维的位置
			int posx, posy;   //二维的位置
			asobj.GetTerr2NumFrom1Num(posyiwei, posx, posy); //借助GetTerr2NumFrom1Num成员函数将一维的位置数字转成二维下标
			maparray[posx][posy] = 7; //寻路找到的路径位置显示为7(包括寻路开始点和结束点)
		}
		cout << "寻路路径为：" << endl;
		for (int i = 0; i < linecount; ++i) //行数
		{
			for (int j = 0; j < colcount; ++j) //列数
			{
				cout << maparray[i][j] << "";
			}
			cout << endl;
		}
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




