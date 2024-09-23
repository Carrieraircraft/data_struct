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

using namespace std;
//链式队列相关代码
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

//------------------------------

//B树每个节点的定义
template <typename T,int M> //T代表数据元素的类型，M代表B树的阶
struct BTreeNode
{
	T data[M]; //数据/关键字
	BTreeNode<T,M>	*childs[M + 1]; //子节点指针数组
	BTreeNode<T, M>* parent; //父节点指针
	int size; //节点中实际数据个数

	BTreeNode() //构造函数
	{
		size = 0;
		for (int i = 0; i < M; ++i)
		{
			data[i] = -1; //随便给个比较特殊的值-1，这样跟踪调试时也好观察和辨认
		}
		for (int i = 0; i < (M + 1); ++i)
		{
			childs[i] = nullptr;
		}
		parent = nullptr;
	}
};

//B树的定义
template <typename T,int M>
class BTree
{
public:
	BTree() //构造函数
	{
		root = nullptr;
	}

	~BTree() //析构函数
	{
		ReleaseNode(root);
	}

	//插入数据元素
	void InsertElem(const T& e) //不可以指定插入位置，程序内部会自动确定插入位置
	{
		if (root == nullptr) //空树
		{
			root = new BTreeNode<T, M>;
			root->data[0] = e;
			root->size = 1;
			return;
		}
		//非空的树可以往下走
		BTreeNode<T, M>* currnode = root;
		BTreeNode<T, M>* parent = nullptr;
		while (currnode != nullptr)
		{
			int i = 0;
			while (i < currnode->size)
			{
				if (currnode->data[i] == e)
					return; //要插入的数据与当前B树种某节点数据相同，则不允许插入，直接返回

				if (currnode->data[i] < e)
					++i;
				else
					break;
			} //end while (i < currnode->size)

			//因为新插入的数据总是会落在最底层的叶子节点上，所以能往子树走，就往子树走，这里继续向子树前进
			parent = currnode;
			currnode = currnode->childs[i];
		} //end while (currnode != nullptr)

		//走到这里表示插入数据到一个非空的B树
		currnode = parent; //注意赋值
		InsertDataIntoNode(currnode, e);

		//该阶段包含的数据数量是否在允许的范围内，比如一个4阶的B树只能有3个数据，如果超过3个数据达到了4个，则必须要拆分了
		if (currnode->size < M)
			return; //节点包含的数据数量在允许的范围内

		while (true)
		{
			//走到这里表示要拆分节点，因为节点中数据的数量已经达到了M个。
			int mid = (int)(ceil((float)M / (float)2)); //ceil：返回的是大于x的最小整数
			int mididx = mid - 1; //下标从0开始，因此这里需要减1

			//拆分肯定会导致出现2个新的节点
			//对于4阶B树，假如有5、6、11、12四个数据，拆分的话 一个新节点放5，另一个新节点放11、12
			BTreeNode<T, M>* tmp1 = new BTreeNode<T, M>;
			BTreeNode<T, M>* tmp2 = new BTreeNode<T, M>;

			//给tmp1、tmp2值
			int index = 0;
			for (int k = 0; k < mididx; ++k) //把5放入到第一个新节点
			{
				tmp1->data[index] = currnode->data[k];
				tmp1->size++;
				index++;
			} //end for k
			index = 0;
			for (int k = mididx + 1; k < currnode->size; ++k) //把11、12放入第二个新节点
			{
				tmp2->data[index] = currnode->data[k];
				tmp2->size++;
				index++;
			} //end for k

			//currnode可能是有孩子的，所以拆开成tmp1,tmp2后，currnode的孩子也就成了tmp1和tmp2的孩子
			index = 0;
			for (int k = 0; k < (mididx + 1); ++k)
			{
				tmp1->childs[index] = currnode->childs[k];
				if (currnode->childs[k] != nullptr)
					currnode->childs[k]->parent = tmp1; //所属的父亲要修改
				index++;
			} //end for k
			index = 0;
			for (int k = (mididx + 1); k <= currnode->size; ++k) //节点指针数量要比数据元素数量多1，所以这里是k<=...
			{
				tmp2->childs[index] = currnode->childs[k];
				if (currnode->childs[k] != nullptr)
					currnode->childs[k]->parent = tmp2; //所属的父亲要修改
				index++;
			} //end for k

			//currnode节点里只剩余一个数据
			currnode->data[0] = currnode->data[mididx];
			currnode->childs[0] = tmp1;
			currnode->childs[1] = tmp2;
			tmp1->parent = currnode;
			tmp2->parent = currnode;
			currnode->size = 1; //固定是1，因为currnode节点只有一个数据

			//节点的第1个和第2个指针分别指向他的两个孩子，第3个指针开始全部置空
			for (int k = 2; k <= M; ++k)
			{
				//该节点的其他孩子指针置空
				currnode->childs[k] = nullptr;
			} //end for k

			if (currnode->parent != nullptr)
			{
				//和父节点合并
				BTreeNode<T, M>* par = currnode->parent;
				int k;
				for (k = 0; k < par->size; ++k) //通过循环找到该数据在父节点中的位置，k中得到了位置
				{
					if (par->data[k] < currnode->data[0])
						continue;
					else
						break;
				} //end for k

				for (int k2 = (par->size - 1); k2 >= k; --k2) //后边的数据如果有则向右移动
				{
					par->data[k2 + 1] = par->data[k2];
					//指针也要处理
					par->childs[k2 + 1 + 1] = par->childs[k2 + 1];
				} //end for k2

				//新加进来数据到原来的父节点中
				par->data[k] = currnode->data[0];
				par->size++;
				par->childs[k] = tmp1;
				tmp1->parent = par;
				par->childs[k + 1] = tmp2;
				tmp2->parent = par;
				delete currnode; //删除这个没用的节点

				if (par->size >= M) //节点数量够了，要拆分了
				{
					currnode = par;
					continue;
				}
				else
				{
					break;
				}
			} 
			else
			{
				//没有父节点，不需要合并，比如当前只有一个节点，里边包含4个数据，拆分这4个数据后此条件就会满足
				break;
			} //end if (currnode->parent != nullptr)
		} //end while (true)
		return;
	}

	//向当前节点插入数据
	int InsertDataIntoNode(BTreeNode<T, M>* currnode, const T& e)
	{
		int i;
		for (i = currnode->size - 1; i >= 0; --i)
		{
			if (currnode->data[i] > e)
			{
				currnode->data[i + 1] = currnode->data[i];
			}
			else
			{
				break;
			}
		}//end for i
		currnode->data[i + 1] = e;
		currnode->size++;
		return (i + 1);
	}

	//获取某个节点的高度（根高度为1，往下高度依次+1），用于显示节点时换行的目的
	int getNodeLevel(BTreeNode<T, M>* tNode)
	{
		int icurlvl = 0;
		while (tNode != nullptr)
		{
			tNode = tNode->parent;
			icurlvl++;
		} //end while
		return icurlvl;
	}
	//层序遍历B树，方便显示
	void levelOrder()
	{
		levelOrder(root);
	}
	void levelOrder(BTreeNode<T, M>* tNode)
	{
		if (tNode != nullptr) //若B树非空
		{
			BTreeNode<T, M>* tmpnode = nullptr;
			_nmsp0::LinkQueue<BTreeNode<T, M>* > lnobj; //队列的元素类型是“节点指针”类型
			lnobj.EnQueue(tNode); //先把根节点指针入队

			int currdislvl = 1; //当前显示第几层，根算第1层
			while (!lnobj.IsEmpty()) //循环判断队列是否为空
			{
				lnobj.DeQueue(tmpnode); //出队列
				int lvl = getNodeLevel(tmpnode);
				if (lvl != currdislvl) //用于换行
				{
					currdislvl = lvl;
					cout << endl;
				}
				for (int i = 0; i < tmpnode->size; ++i)
				{
					cout << tmpnode->data[i] << ",";
				}
				cout << "     ";

				for (int i = 0; i < (tmpnode->size + 1); ++i)
				{
					if (tmpnode->childs[i] == nullptr)
						break;

					lnobj.EnQueue(tmpnode->childs[i]);
				} //end for
			} //end while
		} //end if (tNode != nullptr) 
	}

private:
	void ReleaseNode(BTreeNode<T, M>* pnode)
	{
		if (pnode != nullptr)
		{
			for (int i = 0; i < (pnode->size + 1); ++i)
			{
				if (pnode->childs[i] != nullptr)
				{
					ReleaseNode(pnode->childs[i]);
				}
			}
		}
		delete pnode;
	}

private:
	BTreeNode<T, M>* root; //树根指针
};




int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//第三节  多路查找树
	//（1）B树：多路平衡查找树，B-
	//（1.1）基本概念、定义及基础实现代码
	//引入B树的主要目的：减少磁盘的IO操作
	//（1.2）B树的插入操作及实现代码
	//创建4阶B树：11，12，6，5，13，7，3，4，2，1，9，8，10
	//说明：a)4阶B树每个节点最少有一个数据，最多有3个数据
	      //b)新插入的数据总会落在最底层的叶子节点上。

	//（1.3）B树的删除操作及实现代码
	//5阶B树，每个节点最多有4个数据。
	//根节点可以只有1个数据，非根节点至少要有2个数据。

	//5阶B树插入操作：不够4个节点，则直接插入。够了4个节点就要进行拆分。
	//B树的删除操作：删除终端节点；删除非终端节点（则要转换成对终端节点的删除）；
	//对终端节点数据的删除，又分为两种情况：
	//父子换位法。



	   
	/*
	BTree<int, 4> mybtree;
	mybtree.InsertElem(11);
	mybtree.InsertElem(12);
	mybtree.InsertElem(6);
	mybtree.InsertElem(5);
	mybtree.InsertElem(13);
	mybtree.InsertElem(7);
	mybtree.InsertElem(3);
	mybtree.InsertElem(4);

	mybtree.InsertElem(2);
	mybtree.InsertElem(1);
	mybtree.InsertElem(9);
	mybtree.InsertElem(8);
	mybtree.InsertElem(10);

	mybtree.levelOrder();
	*/
	BTree<int, 5> mybtree;
	for (int i = 1; i <= 35; ++i)
	{
		mybtree.InsertElem(i);
	} //end for
	mybtree.levelOrder();






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


