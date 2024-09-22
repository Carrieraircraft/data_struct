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

//链式队列相关代码
namespace _nmsp1
{
	//哈夫曼树节点
	struct HFMTreeNode
	{
		int weight;
		int parent; //父亲（数组下标值）
		int lchild; //左孩子（数组下标值）
		int rchild; //右孩子（数组下标值）
	};

	//哈夫曼树 ：用一个数组来保存哈夫曼树
	class HFMTree
	{
	public:
		//nodecount代表要创建的哈夫曼树的叶子节点数量
		//pweight叶子节点的权重数组
		HFMTree(int nodecount, int* pweight) //构造函数
		{
			m_length = nodecount;
			int iMaxNodeCount = 2 * m_length - 1;

			m_data = new HFMTreeNode[iMaxNodeCount]; //哈夫曼树节点总数2n-1（n代表哈夫曼树叶子节点数量）
			for (int i = 0; i < iMaxNodeCount; ++i)
			{
				m_data[i].parent = -1; //-1标记未被使用
				m_data[i].lchild = -1;
				m_data[i].rchild = -1;
			}

			for (int i = 0; i < m_length; ++i)
			{
				m_data[i].weight = pweight[i];
			}
		}

		~HFMTree() //析构函数
		{
			delete[] m_data;
		}


		//真正开始创建哈夫曼树
		void CreateHFMTree()
		{
			int idx1 = 0;
			int idx2 = 0;
			int iMaxNodeCount = 2 * m_length - 1; //整个哈夫曼树的节点数量

			int initlength = m_length;
			for (int i = initlength; i < iMaxNodeCount; ++i)
			{
				SelectTwoMinValue(idx1, idx2);
				m_data[i].weight = m_data[idx1].weight + m_data[idx2].weight; //新节点权值等于左右孩子
				m_data[i].lchild = idx1;
				m_data[i].rchild = idx2;

				m_data[idx1].parent = i;
				m_data[idx2].parent = i;
				m_length++; //SelectTwoMinValue()函数要 用到该值
			}
			return;
		}
		//前序遍历二叉树（根左右）
		void preOrder(int idx)
		{
			if (idx != -1)
			{
				cout << m_data[idx].weight << "  ";
				preOrder(m_data[idx].lchild);
				preOrder(m_data[idx].rchild);
			}
		}

		int GetLength()
		{
			return m_length;
		}

		//生成哈夫曼编码
		bool CreateHFMCode(int idx) //idx用于保存哈夫曼树的数组某个节点的下标
		{
			//调用这个函数时，m_length应该已经等于整个哈夫曼树的节点数量，那么哈夫曼树的叶子节点数量应该这样求；
			int leafNodeCount = (m_length + 1) / 2;
			if (idx < 0 || idx >= leafNodeCount)
			{
				//只允许对叶子节点求其哈夫曼编码
				return false;
			}
			string result = ""; //保存最终生成的哈夫曼编码
			int curridx = idx;
			int tmpparent = m_data[curridx].parent;
			while (tmpparent != -1) //沿着叶子向上回溯
			{
				if (m_data[tmpparent].lchild == curridx)
				{
					//前插0
					result = "0" + result;
				}
				else
				{
					//前插1
					result = "1" + result;
				}
				curridx = tmpparent;
				tmpparent = m_data[curridx].parent;
			} //end while

			cout << "下标为【" << idx << "】,权值为" << m_data[idx].weight << "的节点的哈夫曼编码是" << result << endl;
			return true;
		}

	private:
		//先择两个根权重最小的节点，通过引用返回这个节点所在的下标
		void SelectTwoMinValue(int& rtnIdx1, int& rtnIdx2)
		{
			int minval1 = INT_MAX;
			int minval2 = INT_MAX;

			//找最小值
			for (int i = 0; i < m_length; ++i)
			{
				if (m_data[i].parent == -1) //父标记未被使用
				{
					if (minval1 > m_data[i].weight)
					{
						minval1 = m_data[i].weight; //记录最小值
						rtnIdx1 = i; //记录下标
					}
				}
			} //end for

			//找第二个最小值
			for (int i = 0; i < m_length; ++i)
			{
				if (m_data[i].parent == -1 && i != rtnIdx1) //父标记未被使用，注意&&后的条件，目的是把第一个找到的最小权值的节点排除
				{
					if (minval2 > m_data[i].weight)
					{
						minval2 = m_data[i].weight; //记录最小值
						rtnIdx2 = i; //记录下标
					}
				}
			} //end for
			return;
		}

	private:
		HFMTreeNode* m_data;
		int m_length; //记录当前树有多少个节点【数组中多少个节点被使用了】
	};

}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口


	//（12）哈夫曼树（Huffman Tree）：霍夫曼树/最优二叉树
	// （12.1）基本术语、概念
	    //a)节点的权值：节点的数字
		//b)从根节点到某节点的路径长度：经过的段数。
		//c)节点的带权路径长度(WPL)：从根节点到该节点的路径长度*该节点的权值。
		//d)树的带权路径长度：树中所有叶子节点的带权路径长度之和。
		//1：WPL=38
		//2：WPL=32
		//3：WPL=50
		//4：WPL=51
		//e)哈夫曼树：WPL值最小的那棵。在含有n个带权叶节点的二叉树中，其中带权路径长度（WPL）最小的二叉树称为哈夫曼树（最优二叉树）。
	
	//（12.2）哈夫曼树的构造及相关的代码实现
		//如果给定n个叶子节点，如何构造包含这n个节点的哈夫曼树，步骤：。。。
	    //哈夫曼树特性：
		//a)初始给的节点都作为哈夫曼树的叶子节点
		//b)权值越大的叶子节点到根的路径长度越小。权值越小的叶子节点到根的路径长度越大。
	    //c)哈夫曼树最终节点是n+(n-1)=2n-1。n是叶子节点数量
	    //d)每个节点都有左右子树，所以没有度为1的节点。
		//e)哈夫曼的子树仍旧是 一棵哈夫曼树。
		//f)哈夫曼树并不唯一,但相同叶子节点的哈夫曼树的WPL值一定是相等的。
		// 
	//（12.3）哈夫曼编码及相关的代码实现
	 //哈夫曼编码：是一种可以用于数据压缩的编码方式。哈夫曼编码的构造过程需要用到哈夫曼树
	//AFDBCFBDEFDF
	//12%,15%,9%,24%,8%,32%.
	//哈夫曼编码是可变长编码（36，29）
	//对于可变长度编码，设计的时候必须要保证 任何一个字母的编码都不可以是另一个字母编码的前缀。
	//前缀编码：编码方案中，任何一个编码都不是其他任何编码的前缀（最左子串），则称该编码为前缀编码。
	//哈夫曼编码是用构造哈夫曼树的方式来确定字符集的一种编码方案，属于一种前缀编码，解码时可以保证解出的内容的唯一性。
	//哈夫曼树具有不唯一性（左右叶子节点交换）=》哈夫曼编码也不唯一。


	//int weighLst[] = { 1,2,2,4,8 }; //权值列表（数组），数组中数据顺序无所谓
	int weighLst[] = { 12,15,9,24,8,32 };
	_nmsp1::HFMTree hfmtobj(
					sizeof(weighLst) / sizeof(weighLst[0]), //权值列表中元素个数
					weighLst
					);
	hfmtobj.CreateHFMTree(); //创建哈夫曼树
	hfmtobj.preOrder(hfmtobj.GetLength() - 1); //遍历哈夫曼树，参数其实就是根节点的下标（数组最后一个有效位置的下标）

	//求哈夫曼编码
	cout << "----------------" << endl;
	for (int i = 0; i < sizeof(weighLst) / sizeof(weighLst[0]); ++i)
	{
		hfmtobj.CreateHFMCode(i);
	} //end for
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




