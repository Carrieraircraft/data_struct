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
namespace _nmsp1
{
	//红黑树中每个节点的定义
	template <typename T> //T代表数据元素类型
	struct RBNode
	{
		T   data;
		RBNode* leftChild; //左子节点指针
		RBNode* rightChild; //右子节点指针
		RBNode* parentNd; //父节点指针，引入方便操作。
		bool isRed; //是否是红色节点，true：是。false：不是（而是黑色节点）
	};

	//红黑树的定义
	template <typename T>
	class RBTree
	{
	public:
		RBTree() //构造函数
		{
			root = nullptr;
		}
		~RBTree() //析构函数
		{
			ReleaseNode(root);
		}

		//层序遍历二叉树，方便显示
		void levelOrder()
		{
			levelOrder(root);
		}
		//获取某个节点的高度（根高度为1，往下高度依次+1），用于显示节点时换行的目的
		int getNodeLevel(RBNode<T>* tNode)
		{
			int icurlvl = 0;
			while (tNode != nullptr)
			{
				tNode = tNode->parentNd;
				icurlvl++;
			}
			return icurlvl;
		}

		//红黑树遍历操作，增加了是否是合法红黑树的判断
		void levelOrder(RBNode<T>* tNode)
		{
			if (root != nullptr && root->isRed == true)
			{
				cout << "红黑树根节点不应该为红色" << endl;
				return;
			}
			int blackheight = -1; //计算黑高，从而确定是一个有效的红黑树
			bool ifaRBTree = true; //标记是否是一棵红黑树，缺省：是

			if (tNode != nullptr) //若二叉树非空
			{
				RBNode<T>* tmpnode;
				_nmsp0::LinkQueue< RBNode<T>* > lnobj; //注意：队列的元素类型为“节点指针”类型。
				lnobj.EnQueue(tNode); //先把根节点指针入队
				int currdislvl = 1; //当前显示第几层，根算第一层
				const char* pr = "[红]";
				const char* pb = "[黑]";
				char* ptmp;
				while (!lnobj.IsEmpty()) //循环判断队列是否为空
				{
					lnobj.DeQueue(tmpnode); //出队列
					int lvl = getNodeLevel(tmpnode);
					if (lvl != currdislvl) //用于换行
					{
						currdislvl = lvl;
						cout << endl;
					}
					if (tmpnode->isRed == false)
						ptmp = (char*)pb;
					else
						ptmp = (char*)pr;

					cout << tmpnode->data << ptmp << "    ";

					//判断黑高
					int tmpvalue = Calc_BH(tmpnode);
					if (tmpvalue != -1)
					{
						//这个黑高值有效
						if (blackheight == -1) //黑高值从来没拿过
						{
							blackheight = tmpvalue;
						}
						else
						{
							//黑高已经有值，判断黑高值是否相等
							if (blackheight != tmpvalue)
							{
								ifaRBTree = false; //不是红黑树
								cout << "末端节点的黑高值不相等:(" << blackheight << "," << tmpvalue << ")，不是红黑树了！" << endl;
								break; //直接退出循环
							}
						}
					}
					if (tmpnode->isRed == true && tmpnode->parentNd != nullptr)
					{
						if (tmpnode->parentNd->isRed == true)
						{
							//父子关系的两个红黑树节点颜色都为红色，不可以
							cout << endl;
							cout << "红黑树红色节点(" << tmpnode->data << ")的父节点(" << tmpnode->parentNd->data << ")也是红色，这已经不是一棵红黑树了!" << endl;
							break;
						}
					}

					if (tmpnode->leftChild != nullptr)
						lnobj.EnQueue(tmpnode->leftChild); //左孩子入队

					if (tmpnode->rightChild != nullptr)
						lnobj.EnQueue(tmpnode->rightChild); //右孩子入队
				} //end while				
			} //end if
		}

		//插入元素
		void InsertElem(const T& e) //不可以指定插入位置，程序内部会自动确定插入位置
		{
			InsertElem(root, e);
		}
		void InsertElem(RBNode<T>*& tNode, const T& e) //注意第一个参数类型
		{
			RBNode<T>* point = tNode; //从指向根节点开始
			RBNode<T>* parent = nullptr; //保存父亲节点，根节点的父亲节点肯定为nullptr；
			//通过一个while循环寻找要插入的节点的位置，同时还要把插入路径上所经过的所有节点保存到栈中，因为
			   //这些节点的平衡因子可能需要调整
			while (point != nullptr)
			{
				if (e == point->data)
					return; //要插入的数据与当前树中某节点数据相同，则不允许插入，直接返回

				parent = point; //记录父节点，因为后序子节点要往下走，找合适自己的位置
				if (e > point->data)
					point = point->rightChild;
				else
					point = point->leftChild;
			} //end while

			//走到这里，point等于nullptr，该生成新节点了
			point = new RBNode<T>;
			point->data = e;
			point->leftChild = nullptr;
			point->rightChild = nullptr;
			point->parentNd = nullptr;
			point->isRed = true; //缺省插入的节点先给红色

			if (parent == nullptr)
			{
				//创建的是根节点
				point->isRed = false; //根节点是黑色
				tNode = point;
				return;
			}
			//走到这里表示创建的不是根节点，那么就要把孩子链到父亲上
			if (e > parent->data)
				parent->rightChild = point; //在父节点的右树链入
			else
				parent->leftChild = point; //在父节点的左树链入
			point->parentNd = parent; //记录父节点的指针
			if (parent->isRed == false) //父节点为黑色，不需要做什么
				return;

			//能走到这里，要插入的节点肯定是至少在第三层
			//父节点为红色才能走下来（当前节点也是红色的）
			BalanceTune(point, parent);
			root->isRed = false; //根节点颜色无条件给黑色 
		}

		//平衡性调整
		void BalanceTune(RBNode<T>* point, RBNode<T>* parent) //point:当前节点，parent：当前节点的父亲节点
		{
			RBNode<T>* parentBroNode = nullptr; //叔叔节点，有为空的可能性，此时表示没叔叔节点
			RBNode<T>* grandFatherNode = nullptr; //爷爷节点，不会为空的，因为父亲节点为红色，红色不能做根，所致至少都是根节点做爷爷节点。

			while (true)
			{
				parentBroNode = (parent->parentNd != nullptr) ? (getBrotherNode(parent)) : nullptr; //叔叔
				grandFatherNode = point->parentNd->parentNd; //爷爷
				if (grandFatherNode == nullptr) //爷爷节点不可以为空
					break;

				//如果叔叔节点不为空并且叔叔节点为红色（这个代码很统一，只需要变色，集中写在这里）
				if (parentBroNode != nullptr && parentBroNode->isRed == true)
				{
					//这种情况只需要变色
					//(1)父亲和叔叔变为黑色，爷爷变为红色
					parent->isRed = false;
					parentBroNode->isRed = false;
					grandFatherNode->isRed = true;

					//(2)如果爷爷节点是整个二叉树的根节点，跳出循环，根节点颜色在循环外进行设置为黑色的处理
					if (grandFatherNode == root)
						break;

					//(3)往上走继续调整
					point = grandFatherNode; //当前节点指向爷爷，从爷爷节点（红）开始继续向上调整
					parent = point->parentNd; //设置父亲节点

					if (parent == nullptr)
					{
						assert(false); //#include <assert.h>
					}

					if (parent->isRed == false) //如果这个新父节点为黑色，认为调整完毕就不继续向上调整
						break;

					continue;
				} //end if

				//上面代码下不来，下来的，不会满足if (parentBroNode != nullptr && parentBroNode->isRed == true)条件
				//因为 如果叔叔节点不为空并且叔叔节点为红色的情况上面处理完了下不来了，所以走到下面的，都属于
				  //叔叔节点为空或者叔叔节点不为空但是为黑色的情况

				//旋转变色之前确定一些信息，这是通用代码，所以放在这里
				RBNode<T>* gff = grandFatherNode->parentNd;
				int sign = 0; //标记：1表示grandFatherNode是其父亲的左孩子。2表示grandFatherNode是其父亲的右孩子
				if (gff != nullptr)
				{
					if (gff->leftChild == grandFatherNode)
						sign = 1;
					else
						sign = 2;
				} //end if
				//----------------------------
				if (grandFatherNode->leftChild == parent) //第一种情形，父亲是爷爷节点的左孩子
				{
					//开始旋转和变色以调整平衡
					if (parent->leftChild == point) //新节点是父亲节点的左孩子
					{
						//右旋转
						RotateRight(grandFatherNode);
					}
					else //新节点是父亲节点的右孩子
					{
						//先左旋后右旋
						RotateLeftRight(grandFatherNode);
					} //end if (parent->leftChild == point) 

					//旋转变色之后一些公用代码

					//变色
					grandFatherNode->isRed = false; //新根设置为黑色
					grandFatherNode->rightChild->isRed = true; //新右叶子设置为红色
				}
				else //第二种情况，父亲是爷爷节点的右孩子
				{
					//开始旋转和变色以调整平衡
					if (parent->rightChild == point) //新节点是父亲节点的右孩子
					{
						//左旋转
						RotateLeft(grandFatherNode);
					}
					else
					{
						//先右后左旋转
						RotateRightLeft(grandFatherNode);
					} //end if (parent->rightChild == point) 

					//旋转变色之后一些公用代码

					//变色
					grandFatherNode->isRed = false; //新根设置为黑色
					grandFatherNode->leftChild->isRed = true; //新左叶子设置为红色
				}

				//------------------------------------
				//一些通用代码放这里
				//根已经改变了，所以有奥设置一些节点指向信息
				if (gff == nullptr)
				{
					//根要变了吧
					root = grandFatherNode;
				}
				else if (sign == 1)
				{
					gff->leftChild = grandFatherNode;
				}
				else if (sign == 2)
				{
					gff->rightChild = grandFatherNode;
				}
				break; //应该不用往上走继续调整，所以break;
			} //end while (true)
			return;
		}

		//获取兄弟节点指针
		RBNode<T>* getBrotherNode(RBNode<T>* p)
		{
			//由调用者确定p->parent一定不为nullptr
			if (p->parentNd->leftChild == p) //父亲的左二字是不是自己
				return p->parentNd->rightChild; //返回父亲的右儿子
			return p->parentNd->leftChild; //返回父亲的左儿子
		}

		//左旋转（代码与AVL左旋其实是一样的，但要注意parent指针的设置）
		void RotateLeft(RBNode<T>*& pointer) //注意参数类型
		{
			//      4     ----左旋-----        6
			//   /     \                   /      \
			//   3      6                 4       7 
			//         / \              /   \
			//        5   7             3    5
			RBNode<T>* ptmproot = pointer; //让ptmproot指向4
			pointer = ptmproot->rightChild; //让point指向6
			pointer->parentNd = ptmproot->parentNd; //设置6的父亲指向4的父亲
			ptmproot->rightChild = pointer->leftChild; //让4的右孩子不再指向6，而是指向5
			if (pointer->leftChild)
				pointer->leftChild->parentNd = ptmproot; //设置5的父亲是4
			pointer->leftChild = ptmproot; //让6的左孩子指向4
			ptmproot->parentNd = pointer; //设置4的父亲是6、
		}

		//右旋转
		void RotateRight(RBNode<T>*& pointer) //注意参数类型
		{
			//       6  -------右旋-------    4      
			//     /   \                   /     \   
			//    4     7                 3       6 
			//   / \                            /   \
			//  3   5                          5     7
			RBNode<T>* ptmproot = pointer; //让ptmproot指向6
			pointer = ptmproot->leftChild; //让pointer指向4
			pointer->parentNd = ptmproot->parentNd; //设置4的父亲指向6的父亲
			ptmproot->leftChild = pointer->rightChild; //让6的左孩子不再指向4，而是指向5
			if (pointer->rightChild)
				pointer->rightChild->parentNd = ptmproot; //设置5的父亲是6
			pointer->rightChild = ptmproot; //让4的右孩子指向6
			ptmproot->parentNd = pointer; //设置6的父亲是4
		}

		//先左后右旋转
		void RotateLeftRight(RBNode<T>*& pointer)
		{
			//如下图 不全，只是示意
			//    6    -----先左旋----  6       -----再右旋----   5
			//  /  \                  /    \                   /    \
			// 4    7                5     7                  4     6 
			//   \                 /                                  \
			//    5               4                                   7

			RBNode<T>* ptmproot = pointer; //让ptmproot指向6
			RBNode<T>* ptmproot_lf = ptmproot->leftChild; // 让ptmproot_lf指向4
			pointer = ptmproot_lf->rightChild; //让pointer指向5，5是旋转后最终的根
			RBNode<T>* orgparent = ptmproot->parentNd; //把老父亲保存起来，后面要用
			//先左旋转
			ptmproot->leftChild = pointer; //6的左孩子指向5，其实后面会覆盖的，所以这个赋值其实没用，但为了清晰醒目，留着
			pointer->parentNd = ptmproot; //5的父亲指向6，上行没啥用，所以这行其实也没啥用

			ptmproot_lf->rightChild = pointer->leftChild; //4的右孩子指向5的左孩子
			if (pointer->leftChild)
				pointer->leftChild->parentNd = ptmproot_lf; //5的左孩子的父亲指向4
			pointer->leftChild = ptmproot_lf; //5的左孩子指向4
			ptmproot_lf->parentNd = pointer; //4的父亲指向5

			//再右旋转
			ptmproot->leftChild = pointer->rightChild; //6的左孩子指向5的右孩子
			if (pointer->rightChild)
				pointer->rightChild->parentNd = ptmproot; //5的右孩子的父亲指向6
			pointer->rightChild = ptmproot; //5的右孩子指向6
			ptmproot->parentNd = pointer; //6的父亲指向5

			//再处理根节点的父亲指向
			pointer->parentNd = orgparent;
		}

		//先右后左旋转
		void RotateRightLeft(RBNode<T>*& pointer)
		{
			//     6     ----先右旋---      6        ----再左旋----      7
			//  /    \                    /    \                       /   \
			// 4      8                  4      7                     6     8 
			//      /                            \                  /
			//     7                              8                4

			RBNode<T>* ptmproot = pointer; //让ptmproot指向6
			RBNode<T>* ptmproot_rg = ptmproot->rightChild; //让ptmproot_rg指向8
			pointer = ptmproot_rg->leftChild; //让pointer指向7，7是旋转后最终的根
			RBNode<T>* orgparent = ptmproot->parentNd; //把老父亲保存起来，后面要用

			//先右旋转
			ptmproot->rightChild = pointer; //6的右孩子指向7，其实后面会覆盖，但为了醒目，留着
			pointer->parentNd = ptmproot; //7的父亲指针指向6，上行没啥用，所以这行其实也没啥用
			ptmproot_rg->leftChild = pointer->rightChild; //8的左孩子指向7的右孩子
			if (pointer->rightChild)
				pointer->rightChild->parentNd = ptmproot_rg; //7的有孩子的父亲指向7
			pointer->rightChild = ptmproot_rg;//7的右孩子指向8
			ptmproot_rg->parentNd = pointer; //8的父亲指向7

			//再左旋转
			ptmproot->rightChild = pointer->leftChild; //6的右孩子指向7的左孩子
			if (pointer->leftChild)
				pointer->leftChild->parentNd = ptmproot; //7的左孩子的父亲指向6
			pointer->leftChild = ptmproot; //7的左孩子指向6
			ptmproot->parentNd = pointer; //6的父亲指向7

			//再处理根节点的父亲指向
			pointer->parentNd = orgparent;
		}

		//删除某个节点
		void DeleteElem(const T& e)
		{
			return DeleteElem(root, e);
		}

		void DeleteElem(RBNode<T>*& tNode, const T& e)  //注意第一个参数类型
		{
			RBNode<T>* ptmp = tNode; //要删除的节点
			RBNode<T>* parent = nullptr; //保存父亲节点，根节点的父节点肯定先为nullptr

			while (ptmp != nullptr) //通过while循环尝试让ptmp指向要被删除的节点
			{
				if (ptmp->data == e)
					break;
				parent = ptmp; //记录父节点
				if (ptmp->data > e)
					ptmp = ptmp->leftChild;
				else
					ptmp = ptmp->rightChild;
			} //end while
			if (ptmp == nullptr)//没有找到要删除的节点
				return;

			//找到了要删除的节点，删除节点分几种情况：
			RBNode<T>* q = nullptr;         //临时指针变量
			if (ptmp->leftChild == nullptr && ptmp->rightChild == nullptr)
			{
				//如果要删除的节点左子树和右子树都为空（叶节点）
				BlackLeaf_TuneBanance(ptmp);

				if (parent != nullptr)
				{
					if (parent->leftChild == ptmp) //要删除的节点是其父的左孩子
						parent->leftChild = nullptr;
					else
						parent->rightChild = nullptr;
				}
			}
			else if (ptmp->leftChild != nullptr && ptmp->rightChild != nullptr)
			{
				//如果要删除的节点左子树和右子树都不为空，则把对当前节点的删除转换为对当前节点左子树的最右下节点的删除
				//这里涉及到的问题是要记录最终真删除的节点的路径
				//删除举例：比如删除如下的D节点，最后会转变成删除F节点。ptmp指向的是F节点
				//        *
				//    D              *
				//  *        *         *
				//*   F        *
				//(1)该入栈的节点入栈
				parent = ptmp;  //记录父节点,parent是实际要删除的节点的父节点
				//(2)找到这个要删除节点的左子树的最右下节点（也可以找这个要删除节点右子树的最左下节点）,将该节点的值替换到要删除的节点上；
				q = ptmp->leftChild;
				while (q->rightChild != nullptr)
				{
					parent = q;
					q = q->rightChild;
				}
				ptmp->data = q->data;
				ptmp = q; //让ptmp指向真正删除的节点，也就是把删除一个既有左子树右有右子树的节点转化为删除一个叶子节点。

				//上面找到这个节点肯定没有右子树，因为找的是左子树的最右下节点嘛！
				if (ptmp->leftChild != nullptr)
				{
					//平衡性调整：删除仅有左子树或者仅有右子树的黑色节点
					if (ptmp->isRed == false)
					{
						assert(ptmp->leftChild->isRed == true);  //黑色节点的子节点必须有且是红色
						ptmp->leftChild->isRed = false;  //要删除节点的子节点从红色修改为黑色即可
					}
				}
				else
				{
					//删除的是叶子节点，平衡性调整在这里搞
					BlackLeaf_TuneBanance(ptmp);
				}

				if (parent != nullptr)
				{
					if (parent->leftChild == ptmp)
					{
						parent->leftChild = ptmp->leftChild;
						if (ptmp->leftChild)
							ptmp->leftChild->parentNd = parent;
					}
					else
					{
						parent->rightChild = ptmp->leftChild;
						if (ptmp->leftChild)
							ptmp->leftChild->parentNd = parent;
					}
				}
			}
			else
			{
				//如果要删除的节点的左子树为空或者右子树为空(两者肯定有一个为空才能走到这个分支)，让q指向不空的孩子节点
				if (ptmp->leftChild != nullptr)
					q = ptmp->leftChild;
				else
					q = ptmp->rightChild;
				if (parent != nullptr)
				{
					//把被删除的节点的子节点链接到被删除节点的父节点上去
					if (parent->leftChild == ptmp) //要删除的节点是其父的左孩子
						parent->leftChild = q;
					else
						parent->rightChild = q;
				}
				q->parentNd = parent; //被删除节点的 不空的孩子节点 的 父节点指针 指向 被 删除节点的 父节点

				//平衡性调整：删除仅有左子树或者仅有右子树的黑色节点
				if (ptmp->isRed == false)
				{
					assert(q->isRed == true);  //黑色节点的子节点必须有且是红色
					q->isRed = false;  //从红色修改为黑色即可
				}
			}
			//--------------------------------------------------------------
			//parent不为空的情况上面都处理了，这里处理parent为空的情况,parent为空删除的肯定是根节点
			if (parent == nullptr) //有些代码可以合并，但为了方便理解，笔者并没有合并，读者可以自行合并
			{
				if (ptmp->leftChild == nullptr && ptmp->rightChild == nullptr)//这棵树就一个根节点并且删除的就是这个根节点
					tNode = nullptr;
				else if (ptmp->leftChild == nullptr || ptmp->rightChild == nullptr) //要删除这棵树的根节点并且这棵树根的左子树为空或者右子树为空
					tNode = q;
				else
				{
					//这个else条件应该一直不会成立
					assert(false);
				}
			}
			delete ptmp; //释放掉被删除节点所占用的内存
			root->isRed = false; //根节点颜色无条件给黑色
			return;
		}

		//专门针对待删除节点是黑色叶子节点的平衡性调整，非黑的非叶子的直接return;
		void BlackLeaf_TuneBanance(RBNode<T>* pDelNode) //pDelNode代表要删除的节点
		{
			if (pDelNode->isRed == true) return; //非黑节点不处理
			if (pDelNode->leftChild != nullptr || pDelNode->rightChild != nullptr) return; //非叶子节点不处理

			RBNode<T>* pParentNode = pDelNode->parentNd;  //P节点
			if (pParentNode == nullptr)
				return;

			RBNode<T>* pGrandNode = pParentNode->parentNd; //爷爷节点（父亲的父亲），也就是P节点的父亲
			int sign = 0;  //0：代表父亲没爷爷   1：代表父亲是爷爷的左孩子     2：代表父亲是爷爷的右孩子
			if (pGrandNode != nullptr)
			{
				if (pGrandNode->leftChild == pParentNode)
					sign = 1;    //P节点是其父亲（爷爷）的左孩子
				else
					sign = 2;    //P节点是其父亲（爷爷）的右孩子
			}

			RBNode<T>* pBroNode = getBrotherNode(pDelNode);

			//(1)（可以是左节点也可以是右节点），其父节点为红色，兄弟节点为黑色且不带孩子。
			if (
				pParentNode->isRed == true &&     //父为红色
				pBroNode != nullptr && pBroNode->isRed == false &&    //兄弟黑色
				pBroNode->leftChild == nullptr && //兄弟不带孩子
				pBroNode->rightChild == nullptr)
			{
				pParentNode->isRed = false; //父亲节点变成黑色
				pBroNode->isRed = true;     //兄弟节点变成红色
			}


			//(2).a 待删除节点是左节点，其父节点为红色，兄弟节点为黑色且只带红色的左孩子
			else if (
				pParentNode->leftChild == pDelNode &&      //待删节点是左节点
				pParentNode->isRed == true &&            //父为红色
				pBroNode != nullptr && pBroNode->isRed == false &&            //兄弟黑色
				pBroNode->leftChild != nullptr && pBroNode->leftChild->isRed == true && //兄弟只带红色左孩子
				pBroNode->rightChild == nullptr)
			{
				RotateRightLeft(pParentNode);
				pParentNode->isRed = false; //新根是“S左孩子”,S左孩子变成黑色
				pParentNode->rightChild->isRed = true; //新根的右孩子是原来的兄弟，兄弟变成红色
			}


			//(2).b待删除节点是右节点，其父节点为红色，兄弟节点为黑色且只带红色的右孩子
			else if (
				pParentNode->rightChild == pDelNode &&     //待删节点是左节点
				pParentNode->isRed == true &&            //父为红色
				pBroNode != nullptr && pBroNode->isRed == false &&            //兄弟黑色
				pBroNode->rightChild != nullptr && pBroNode->rightChild->isRed == true && //兄弟只带红色右孩子
				pBroNode->leftChild == nullptr)
			{
				RotateLeftRight(pParentNode);
				pParentNode->isRed = false; //新根是“S右孩子”,S右孩子变成黑色
				pParentNode->leftChild->isRed = true; //新根的左孩子是原来的兄弟，兄弟变成红色
			}

			//(3).a 待删除节点是左节点，其父节点为红色，兄弟节点为黑色且只带红色的右孩子
			else if (
				pParentNode->leftChild == pDelNode &&     //待删节点是左节点
				pParentNode->isRed == true &&            //父为红色
				pBroNode != nullptr && pBroNode->isRed == false &&            //兄弟黑色
				pBroNode->rightChild != nullptr && pBroNode->rightChild->isRed == true && //兄弟只带红色右孩子
				pBroNode->leftChild == nullptr)
			{
				RotateLeft(pParentNode);
				pParentNode->isRed = true; //新根设置为红色
				pParentNode->leftChild->isRed = false; //新根的左孩子设置为黑色
				pParentNode->rightChild->isRed = false; //新根的右孩子设置为黑色
			}

			//(3).b待删除节点是右节点，其父节点为红色，兄弟节点为黑色且只带红色的左孩子
			else if (
				pParentNode->rightChild == pDelNode &&     //待删节点是右节点
				pParentNode->isRed == true &&            //父为红色
				pBroNode != nullptr && pBroNode->isRed == false &&            //兄弟黑色
				pBroNode->leftChild != nullptr && pBroNode->leftChild->isRed == true && //兄弟只带红色左孩子
				pBroNode->rightChild == nullptr)
			{
				RotateRight(pParentNode);
				pParentNode->isRed = true; //新根设置为红色
				pParentNode->leftChild->isRed = false; //新根的左孩子设置为黑色
				pParentNode->rightChild->isRed = false; //新根的右孩子设置为黑色
			}


			//(4).a 待删除节点是左节点，其父节点颜色随意，兄弟节点为黑色，兄弟节点的左孩子节点可以没有（如果有肯定是红色，否则会违背红黑树性质4），兄弟节点的右孩子为红色
			else if (
				pParentNode->leftChild == pDelNode &&    //待删节点是左节点	
				pBroNode != nullptr && pBroNode->isRed == false &&     //兄弟黑色
				//(pBroNode->leftChild == nullptr || pBroNode->leftChild->isRed == true) && //没有或者红色左孩子（不用判断，因为如果不是红色左孩子则不会是红黑树了）
				pBroNode->rightChild != nullptr && pBroNode->rightChild->isRed == true  //红色右孩子
				)
			{
				bool colorP = pParentNode->isRed;
				bool colorS = pBroNode->isRed;
				pParentNode->isRed = colorS;  //把节点P和节点S的颜色对调
				pBroNode->isRed = colorP;     //把节点P和节点S的颜色对调   
				RotateLeft(pParentNode); //以P节点为根向左旋转
				pParentNode->rightChild->isRed = false; //新根的右孩子变成黑色
			}
			//(4).b 待删除节点是右节点，其父节点为红色，兄弟节点为黑色且带有两个红色的孩子
			else if (
				pParentNode->rightChild == pDelNode &&    //待删节点是右节点
				pBroNode != nullptr && pBroNode->isRed == false &&     //兄弟黑色
				//(pBroNode->rightChild == nullptr || pBroNode->rightChild->isRed == true) && //没有或者红色右孩子（不用判断，因为如果不是红色右孩子则不会是红黑树了）
				pBroNode->leftChild != nullptr && pBroNode->leftChild->isRed == true //红色左孩子
				)
			{
				bool colorP = pParentNode->isRed;
				bool colorS = pBroNode->isRed;
				pParentNode->isRed = colorS;  //把节点P和节点S的颜色对调
				pBroNode->isRed = colorP;     //把节点P和节点S的颜色对调   
				RotateRight(pParentNode); //以P节点为根向右旋转
				pParentNode->leftChild->isRed = false; //新根的左孩子变成黑色
			}

			//(5).a 待删除节点是左节点，其父节点为黑色，兄弟节点为黑色，兄弟节点只带红色左孩子。
			else if (
				pParentNode->leftChild == pDelNode &&      //待删节点是左节点
				pParentNode->isRed == false &&            //父为黑色
				pBroNode != nullptr && pBroNode->isRed == false &&     //兄弟黑色
				pBroNode->rightChild == nullptr && pBroNode->leftChild != nullptr //兄弟节点只带红色左孩子(显然左孩子不可能为黑色，否则黑高不一致不是红黑树)
				)
			{
				RotateRightLeft(pParentNode); //先右后左旋
				pParentNode->isRed = true;    //新根搞成黑色
			}

			//(5).b 待删除节点是右节点，其父节点为黑色，兄弟节点为黑色，兄弟节点只带红色右孩子。
			else if (
				pParentNode->rightChild == pDelNode &&      //待删节点是右节点
				pParentNode->isRed == false &&              //父为黑色
				pBroNode != nullptr && pBroNode->isRed == false &&     //兄弟黑色
				pBroNode->leftChild == nullptr && pBroNode->rightChild != nullptr //兄弟节点只带红色右孩子
				)
			{
				RotateLeftRight(pParentNode); //先左后右旋
				pParentNode->isRed = true;    //新根搞成黑色
			}

			//(6).a 待删除节点是左节点，其父节点为黑色，兄弟节点为红色且带有两个黑色的孩子(兄弟节点右孩子可以有任意红色孩子，兄弟节点左孩子不可以有孩子)。
			else if (
				pParentNode->leftChild == pDelNode &&      //待删节点是左节点
				pParentNode->isRed == false &&            //父为黑色
				pBroNode != nullptr && pBroNode->isRed == true &&     //兄弟红色
				pBroNode->leftChild != nullptr && pBroNode->leftChild->isRed == false &&  //黑色左孩子
				pBroNode->leftChild->leftChild == nullptr && pBroNode->leftChild->rightChild == nullptr && //且“黑色左孩子”不可以有孩子
				pBroNode->rightChild != nullptr && pBroNode->rightChild->isRed == false  //黑色右孩子，至于是否下面还有孩子不关心，有肯定是红色，否则就不是红黑树了
				)
			{
				RotateLeft(pParentNode); //左旋
				pParentNode->isRed = false; //新根（原兄弟）变成黑色
				pParentNode->leftChild->rightChild->isRed = true; //新根的左孩子的右孩子变成红色
			}

			//(6).a 扩展 待删除节点是左节点，其父节点为黑色，兄弟节点为红色且带2个黑色子节点。兄弟右孩子可以有任意红色孩子，兄弟左孩子至少带一个孩子
			else if (
				pParentNode->leftChild == pDelNode &&      //待删节点是左节点
				pParentNode->isRed == false &&            //父为黑色
				pBroNode != nullptr && pBroNode->isRed == true &&     //兄弟红色
				pBroNode->leftChild != nullptr && pBroNode->leftChild->isRed == false &&  //黑色左孩子				
				pBroNode->rightChild != nullptr && pBroNode->rightChild->isRed == false && //黑色右孩子，至于是否下面还有孩子不关心，有肯定是红色，否则就不是红黑树了
				!(pBroNode->leftChild->leftChild == nullptr && pBroNode->leftChild->rightChild == nullptr) //兄弟左孩子至少带一个孩子，注意前面的!
				)
			{
				RotateLeft(pParentNode); //左旋
				pParentNode->isRed = false; //新根（原兄弟）变成黑色
				pParentNode->leftChild->isRed = true; //新根的左孩子变成红色

				RBNode<T>* p = pParentNode->leftChild;
				RBNode<T>* sleftchild = p->rightChild;   //S左孩子节点，就看这个节点的孩子情况
				if (sleftchild->rightChild != nullptr) //右孩子不为空，左孩子是否为空不用理
				{
					RotateLeft(p); //以P节点为根向左旋转，p是旋转后的新根(也就是s左孩子)
				}
				else  //前面判断了左孩子至少带一个孩子，而上面又判断了右孩子不为空，所以是右孩子为空，表示左孩子肯定不为空
				{
					//左孩子不为空，右孩子为空
					RotateRightLeft(p);
				}
				pParentNode->leftChild = p; //让父亲指向这个旋转后的新孩子
				pParentNode->leftChild->isRed = true;
				if (pParentNode->leftChild->leftChild != nullptr)
					pParentNode->leftChild->leftChild->isRed = false;
				if (pParentNode->leftChild->rightChild != nullptr)
					pParentNode->leftChild->rightChild->isRed = false;
			}

			//(6).b 待删除节点是右节点，其父节点为黑色，兄弟节点为红色且带有两个黑色的孩子(兄弟节点左孩子可以有任意红色孩子，兄弟节点右孩子不可以有孩子)。
			else if (
				pParentNode->rightChild == pDelNode &&    //待删节点是右节点
				pParentNode->isRed == false &&            //父为黑色
				pBroNode != nullptr && pBroNode->isRed == true &&     //兄弟红色
				pBroNode->leftChild != nullptr && pBroNode->leftChild->isRed == false && //黑色左孩子
				pBroNode->rightChild != nullptr && pBroNode->rightChild->isRed == false &&//黑色右孩子
				pBroNode->rightChild->leftChild == nullptr && pBroNode->rightChild->rightChild == nullptr //且“黑色右孩子”不可以有孩子
				)
			{
				RotateRight(pParentNode); //右旋
				pParentNode->isRed = false; //新根（原兄弟）变成黑色
				pParentNode->rightChild->leftChild->isRed = true; //新根的右孩子的左孩子变成红色
			}

			//(6).b.扩展 待删除节点是右节点，其父节点为黑色，兄弟节点为红色且带有两个黑色的孩子，兄弟节点左孩子可以有任意红色孩子，兄弟节点右孩子至少带一个孩子
			else if (
				pParentNode->rightChild == pDelNode &&    //待删节点是右节点
				pParentNode->isRed == false &&            //父为黑色
				pBroNode != nullptr && pBroNode->isRed == true &&     //兄弟红色
				pBroNode->leftChild != nullptr && pBroNode->leftChild->isRed == false && //黑色左孩子
				pBroNode->rightChild != nullptr && pBroNode->rightChild->isRed == false &&//黑色右孩子
				!(pBroNode->rightChild->leftChild == nullptr && pBroNode->rightChild->rightChild == nullptr) //兄弟右孩子至少带一个孩子，注意前面的!
				)
			{
				RotateRight(pParentNode); //右旋
				pParentNode->isRed = false; //新根（原兄弟）变成黑色
				pParentNode->rightChild->isRed = true; //新根的右孩子变成红色

				RBNode<T>* p = pParentNode->rightChild;
				RBNode<T>* srightchild = p->leftChild;   //S右孩子节点，就看这个节点的孩子情况

				if (srightchild->leftChild != nullptr) //左孩子不为空，右孩子是否为空不用理
				{
					RotateRight(p);  //注意以P为根
				}
				else
				{
					//左孩子为空，右孩子就不会为空
					RotateLeftRight(p);
				}

				pParentNode->rightChild = p; //让父亲指向这个旋转后的新孩子
				pParentNode->rightChild->isRed = true;
				if (pParentNode->rightChild->leftChild != nullptr)
					pParentNode->rightChild->leftChild->isRed = false;
				if (pParentNode->rightChild->rightChild != nullptr)
					pParentNode->rightChild->rightChild->isRed = false;
			}

			//(7).ab 待删除节点是左（右）节点【代码通用】，其父节点为黑色，兄弟节点为黑色且不带孩子
			//这个很特殊，这个会动爷爷节点的父亲，所以sign如果不为0则把它设置为0，后面不再调整父亲的父亲节点指向
			else if (
				pParentNode->isRed == false &&            //父为黑色
				pBroNode != nullptr && pBroNode->isRed == false &&     //兄弟黑色
				pBroNode->leftChild == nullptr && pBroNode->rightChild == nullptr  //兄弟节点不带孩子
				)
			{
				pBroNode->isRed = true;  //S节点变为红色

				while (true) //方便跳出去，用了这个
				{
					if (pParentNode->parentNd == nullptr)  //pParentNode->parentNd是100节点
						break; //break;表示没有父亲，不用继续调整后面的根调整照常会被执行到

					//---------------------
					int subsign = 0; //0：代表父亲没爷爷   1：代表父亲是爷爷的左孩子     2：代表父亲是爷爷的右孩子
					RBNode<T>* pParentNodeP = pParentNode->parentNd;   //100节点，这个可能随着调整要变，代表树的根   **********pParentNodeP:代表树的根，注意更新

					bool leftorright = 0;   //0,这个子树是整个红黑树的左边部分，1，这个子树是整个红黑树的右边部分
					if (pParentNodeP->rightChild == pParentNode)
						leftorright = 1; //这个子树是整个红黑树的右边部分

					RBNode<T>* pParentNodePP = pParentNodeP->parentNd; //100节点的父亲
					if (pParentNodePP != nullptr)
					{
						if (pParentNodePP->leftChild == pParentNodeP)
							subsign = 1;   //左孩子
						else
							subsign = 2;   //右孩子
					}
					//---------------------
					//这个树是整个红黑树的一部分，则这个树的parent节点（P节点）一定有兄弟节点（120），但这个兄弟节点是红色还是黑色不确定
					RBNode<T>* pParentBro = getBrotherNode(pParentNode); //获得P节点（父亲）的兄弟节点 :120
					assert(pParentBro != nullptr); //断言120这个节点肯定不为空，不然红黑树无法平衡吧
					assert(pParentBro->leftChild != nullptr && pParentBro->rightChild != nullptr); //断言这个节点肯定有两个孩子110，130，不然红黑树无法平衡吧

					// (7).a
					if (pParentBro->isRed == false) //120是黑色节点
					{
						//120节点的左右孩子都是黑色的，120节点的父亲是黑色的
						//细分1
						if (pParentBro->leftChild->isRed == false && pParentBro->rightChild->isRed == false && pParentBro->parentNd->isRed == false)
						{
							pParentBro->isRed = true; //直接把120变红
						}
						//细分2，3走这个else
						else//这里就要分左右了，因为左右处理是不同的
						{
							//细分2、3走这里
							if (leftorright == 0) //0,这个子树是整个红黑树的左边部分
							{
								//120节点的左孩子是红色的，右孩子是黑色的
								//细分2
								if (pParentBro->leftChild->isRed == true && pParentBro->rightChild->isRed == false)
								{
									RotateRight(pParentBro); //pParentBro原=120，pParentBro新=110
									pParentNodeP->rightChild = pParentBro; //让100的右孩子指向110
									pParentBro->isRed = false; //110节点给黑色
									pParentBro->rightChild->isRed = true; //120节点给红色

									RotateLeft(pParentNodeP);//pParentNodeP原=100，pParentNodeP新=110 ,至于原来100的父亲现在该父亲要指向110，这个调整代码在后面统一处理
									if (pParentNodeP->leftChild->isRed == false)//100节点如果为黑色	，则120要给回黑色（因为前面把该节点给红色了）						
										pParentBro->rightChild->isRed = false;//120节点给黑色

								}
								//120节点右孩子是红色(左孩子颜色随意)
								//细分3
								else if (pParentBro->rightChild->isRed == true)
								{
									RotateLeft(pParentNodeP);//pParentNodeP原=100，pParentNodeP新=120
									if (pParentNodeP->leftChild->isRed == false) //100节点如果为黑色
										pParentNodeP->rightChild->isRed = false; //130节点给黑色
								}
							}
							//细分2、3【反】走这里
							else  //1，这个子树是整个红黑树的右边部分
							{
								//80节点的右孩子是红色的，左孩子是黑色的
								if (pParentBro->rightChild->isRed == true && pParentBro->leftChild->isRed == false)
								{
									RotateLeft(pParentBro);//pParentBro原=80，pParentBro新=90
									pParentNodeP->leftChild = pParentBro;//让100左孩子指向90
									pParentBro->isRed = false; //90节点给黑色
									pParentBro->leftChild->isRed = true; //80节点给红色

									RotateRight(pParentNodeP);//pParentNodeP原=100，pParentNodeP新=90
									if (pParentNodeP->rightChild->isRed == false)//100节点如果为黑色
										pParentBro->leftChild->isRed = false; //80节点给黑色
								}
								//80节点左孩子是红色(右孩子颜色随意)
								else if (pParentBro->leftChild->isRed == true)
								{
									RotateRight(pParentNodeP);//pParentNodeP原=100，pParentNodeP新=80
									if (pParentNodeP->rightChild->isRed == false) //100节点如果为黑色
										pParentNodeP->leftChild->isRed = false;//60节点给黑色
								}
							} //end if (leftorright == 0) 
						} //end if
					}

					// (7).b
					else //120是红色节点，上边的100和孩子110，130都得是黑色的，否则就是红色连接到一起的。
					{
						if (leftorright == 0) //0,这个子树是整个红黑树的左边部分
						{
							//细分1、2、3走这里
							//细分1
							if (pParentBro->leftChild != nullptr &&  //110存在
								pParentBro->leftChild->leftChild != nullptr && pParentBro->leftChild->leftChild->isRed == false &&    //105存在且黑
								pParentBro->leftChild->rightChild != nullptr && pParentBro->leftChild->rightChild->isRed == false)//115存在且黑
							{
								//细分1，2，3的通用步骤代码，但不可提前，否则上面这些if判断条件就都要修改了
								RotateLeft(pParentNodeP); //以100为根旋转，pParentNodeP原=100，pParentNodeP新=120
								pParentNodeP->isRed = false; //120给黑色
								pParentNodeP->leftChild->isRed = true; //100给红色

								//注意：pParentNodeP新=120
								pParentNodeP->leftChild->isRed = false; //100又给黑色
								pParentNodeP->leftChild->rightChild->isRed = true;//110给红色。
							}
							//细分2
							else if (pParentBro->leftChild != nullptr &&  //110存在
								pParentBro->leftChild->leftChild != nullptr && pParentBro->leftChild->leftChild->isRed == true &&  //105存在且红
								pParentBro->leftChild->rightChild != nullptr && pParentBro->leftChild->rightChild->isRed == false)//115存在且黑
							{
								//细分1，2，3的通用步骤代码，但不可提前，否则上面这些if判断条件就都要修改了
								RotateLeft(pParentNodeP); //以100为根旋转，pParentNodeP原=100，pParentNodeP新=120
								pParentNodeP->isRed = false; //120给黑色
								pParentNodeP->leftChild->isRed = true; //100给红色

								//注意：pParentNodeP新=120
								RBNode<T>* point110 = pParentNodeP->leftChild->rightChild; //110
								RotateRight(point110); //110为根右旋，此时point110指向了105
								pParentNodeP->leftChild->rightChild = point110; //让100右孩子指向105

								point110->isRed = false; //105给黑色
								point110->rightChild->isRed = true; //110给红色

								RBNode<T>* point100 = pParentNodeP->leftChild; //100
								RotateLeft(point100); //此时point100指向了105

								pParentBro->leftChild = point100;  //120左孩子指向105
							}
							//细分3
							else if (pParentBro->leftChild != nullptr &&  //110存在
								pParentBro->leftChild->rightChild != nullptr && pParentBro->leftChild->rightChild->isRed == true)//115存在且红
							{
								//细分1，2，3的通用步骤代码，但不可提前，否则上面这些if判断条件就都要修改了
								RotateLeft(pParentNodeP); //以100为根旋转，pParentNodeP原=100，pParentNodeP新=120
								pParentNodeP->isRed = false; //120给黑色
								pParentNodeP->leftChild->isRed = true; //100给红色

								//注意：pParentNodeP新=120
								RBNode<T>* point100 = pParentNodeP->leftChild; //100									
								RotateLeft(point100); //100为根左旋，此时point100指向了110
								pParentNodeP->leftChild = point100; //120左孩子指向110;
							}
							else
							{
								//走到这里表示没被处理，程序不识别的情况，需要做出警告并添加代码处理未识别的情形
								assert(false);
							}
						}
						else  //1，这个子树是整个红黑树的右边部分
						{
							//细分1、2、3【反】走这里
							//细分1【反】pParentBro == 80
							if (pParentBro->rightChild != nullptr &&  //90存在
								pParentBro->rightChild->rightChild != nullptr && pParentBro->rightChild->rightChild->isRed == false &&    //95存在且黑
								pParentBro->rightChild->leftChild != nullptr && pParentBro->rightChild->leftChild->isRed == false)//85存在且黑
							{
								//细分1，2，3【反】的通用步骤代码，但不可提前，否则上面这些if判断条件就都要修改了
								RotateRight(pParentNodeP); //以100为根右旋转，pParentNodeP原=100，pParentNodeP新=80
								pParentNodeP->isRed = false; //80给黑色
								pParentNodeP->rightChild->isRed = true; //100给红色

								//注意：pParentNodeP新=80
								pParentNodeP->rightChild->isRed = false;  //100又给黑色
								pParentNodeP->rightChild->leftChild->isRed = true;//90给红色。
							}
							//细分2【反】
							else if (pParentBro->rightChild != nullptr &&  //90存在
								pParentBro->rightChild->rightChild != nullptr && pParentBro->rightChild->rightChild->isRed == true &&  //95存在且红
								pParentBro->rightChild->leftChild != nullptr && pParentBro->rightChild->leftChild->isRed == false)//85存在且黑
							{

								//细分1，2，3【反】的通用步骤代码，但不可提前，否则上面这些if判断条件就都要修改了
								RotateRight(pParentNodeP); //以100为根旋转，pParentNodeP原=100，pParentNodeP新=80
								pParentNodeP->isRed = false; //80给黑色
								pParentNodeP->rightChild->isRed = true; //100给红色

								//注意：pParentNodeP新=80
								RBNode<T>* point90 = pParentNodeP->rightChild->leftChild; //90							
								RotateLeft(point90); //90为根左旋，此时point90指向了95
								pParentNodeP->rightChild->leftChild = point90; //让100左孩子指向95

								point90->isRed = false; //95给黑色
								point90->leftChild->isRed = true; //90给红色

								RBNode<T>* point100 = pParentNodeP->rightChild; //100
								RotateRight(point100); //此时point100指向了95

								pParentBro->rightChild = point100;  //80右孩子指向95									
							}

							//细分3【反】
							else if (pParentBro->rightChild != nullptr &&  //90存在
								pParentBro->rightChild->leftChild != nullptr && pParentBro->rightChild->leftChild->isRed == true)//85存在且红
							{
								//细分1，2，3【反】的通用步骤代码，但不可提前，否则上面这些if判断条件就都要修改了
								RotateRight(pParentNodeP); //以100为根旋转，pParentNodeP原=100，pParentNodeP新=80
								pParentNodeP->isRed = false; //80给黑色
								pParentNodeP->rightChild->isRed = true; //100给红色

								//注意：pParentNodeP新=80
								RBNode<T>* point100 = pParentNodeP->rightChild; //100									
								RotateRight(point100); //100为根右旋，此时point100指向了90
								pParentNodeP->rightChild = point100; //80右孩子指向90;
							}
							else
							{
								//走到这里表示没被处理，程序不识别的情况，需要做出警告并添加代码处理未识别的情形
								assert(false);
							}
						}
					} //end if(pParentBro->isRed == false)

					//根或者父指针的调整相关
					if (subsign == 0)//根要变了吧
						root = pParentNodeP;
					else if (subsign == 1)  //父亲是爷爷的左孩子
						pParentNodePP->leftChild = pParentNodeP;
					else
						pParentNodePP->rightChild = pParentNodeP;

					return; //不用调整根的问题了,也就是不希望后面的if(sign ==0)....代码执行了
				}//end while (true)
			}

			else
			{
				//走到这里表示没被处理，程序不识别的情况，需要做出警告并添加代码处理未识别的情形
				assert(false);
			}

			//调整根的问题
			//根已经改变了，所以要设置一些节点指向信息
			if (sign == 0)
			{
				//根要变了吧
				root = pParentNode;
			}
			else if (sign == 1)  //父亲是爷爷的左孩子
			{
				pGrandNode->leftChild = pParentNode;
			}
			else //父亲是爷爷的右孩子
			{
				pGrandNode->rightChild = pParentNode;
			}
		}

	public:
		//计算节点的黑高，返回-1表示该节点不需要计算黑高
		int Calc_BH(RBNode<T>* currnode)
		{
			if (currnode->leftChild != nullptr && currnode->rightChild != nullptr)
				return -1; //只有叶子节点或者一个孩子的节点才需要计算黑高

			int blackheight = 0; //计算黑高
			RBNode<T>* tmpnode = currnode;
			while (tmpnode != nullptr)
			{
				if (tmpnode->isRed == false)
					blackheight++; //黑色节点
				tmpnode = tmpnode->parentNd;
			} //end while
			return blackheight;
		}


	private:
		void ReleaseNode(RBNode<T>* pnode)
		{
			if (pnode != nullptr)
			{
				ReleaseNode(pnode->leftChild);
				ReleaseNode(pnode->rightChild);
			}
			delete pnode;
		}

	private:
		RBNode<T>* root; //树根指针
	};



}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//第3章 树
	//第二节  二叉树
	//（11）红黑树（Red - Black Tree）
	//（11.1）基本概念、定义及基础实现代码
	//“平衡性调整”
	//“非严格平衡二叉树”：
	//红黑树（Read-Black Tree)，R-B树。是一种高效的二叉查找树。
	//发明者：Rudolf Bayer   1972年发明，当时被称为  对称/平衡二叉B树。
	//1978年由 Leo J.Guibas和Robert Sedgewick修改为了  红黑树。
	//相对平衡：任一节点左子树和右子树高度之差很可能会超过1.
	//红黑树性质：
	//a)每个节点要么是黑色，要么是红色，而根节点必须是黑色。
	//b)每个叶子节点都是黑色的空节点（Nil），这一点和其他树不同。
		 //也就是说叶子节点不存储数据。Nil可以（一般）不绘制出来。
	//c)任何相邻节点（用线条连接起来的节点比如当前节点的父或者子节点）不能同时为红色（红色节点不能相邻）；
		//理解：c.1)红节点是被黑色节点分隔开的   ；c.2)红色节点的两个孩子节点或者父亲节点必须是黑色的。
		   //c.3)从叶节点到根的所有路径上不可以有两个连续的红色节点。
	//d)红黑树左右子树高度差很可能会超过1甚至超过更多。红黑树的平衡性是指的是对于每个节点，从该节点到达其所能够
		 //到达的叶子节点的所有路径都包含相同数量的黑色节点（黑色节点数量称为 黑高度 或者 黑高，用于保证黑色节点的平衡性)。

	//总结：红黑树：a)黑色的根.b)黑色的叶子;c)红色节点不相邻（红色节点的父亲和孩子都是黑色节点）;
		  //d)当前节点到其所有叶节点包含的黑色节点数量相同。
	//为什么有AVL树还需要引入红黑树：a)AVL平衡性调整效率比较低。b)平衡性调整旋转次数少甚至不需要旋转只需要调整颜色（红色修改为黑色）。
		   //c)插入删除红黑树更快。    换句话说，但从搜索角度，AVL树更快。如果频繁进行插入和删除操作，因为红黑树需要
			   //更少的旋转，无疑效率会更高（红黑树的查找、插入、删除操作性能稳定）。

	//红黑树从根节点到叶子的最长路径不超过最短路径的两倍。
	//红黑树的高度大概2logn。红黑树的高度只比AVL树高1倍，在执行效率上差不太多。因为上面提到的优势，所以性能更好。

	//红黑树编程问题：
	//a)往往不需要考虑叶子节点，也就是那个黑色的空节点（nil）。
	//b)红黑树节点查找操作同二叉查找树的节点查找操作（SearchElem成员函数）完全一样，大家可以参考前面已经实现的代码。

	//（11.2）红黑树插入操作后的平衡性调整及实现代码
	//通过节点变色或者旋转来实现平衡性调整。
	//失衡：插入节点，删除节点
	//插入节点操作一般分为几种情况：
	//a)对于没有任何节点的空树那么直接创建一个黑色节点作为根节点。
	//b)对于非空的树，查找插入位置并插入一个红色节点（不会增加黑色高度以尽量减少平衡性调整），
		//然后要判断该节点的父节点：b.1)如果父节点为黑色，此时不需要做什么。
			  //b.2)如果父节点为红色，会违背红黑树性质3，此时必须进行平衡性调整。
	//平衡性调整情况1：如图3.2.11_7 ，父节点是爷爷节点的左孩子，叔叔节点存在且为红色。
	// 	   爷爷节点为黑色，父亲节点为红色，有叔叔节点且为红色，父亲节点是爷爷节点的左孩子
	//调整方法为：将父亲节点和叔叔节点变成黑色，将爷爷节点变成红色，如果爷爷节点是整个红黑树的根，
		  //则要将爷爷节点恢复为黑色。如图3.2.11_8 。
	//平衡性调整情况2：如图3.2.11_12 ，父亲接单是爷爷节点的左孩子，新节点是父亲节点的左孩子，叔叔节点不存在或者存在但为黑色
		   //爷爷节点为黑色，父亲节点为红色，没叔叔节点或有叔叔节点且为黑色，父亲节点是爷爷节点的左孩子，插入的新红色节点是父亲节点的左孩子
	//调整方法为：以爷爷节点为根向右旋转。接着将原父亲节点变为黑色，原爷爷节点变为红色。
	//平衡性调整情况3：如图3.2.11_14 ，父亲节点是爷爷节点的左孩子，新节点是父亲节点的右孩子，叔叔节点不存在或者存在但为黑色。
	//调整方法为：先父亲节点为根左旋，再以爷爷节点为根右旋。接着原来的新节点变为黑色，原来的爷爷节点变为红色。
	//平衡性调整情况4，5，6。

	//（11.3）红黑树删除操作后的平衡性调整及实现代码
	//平衡二叉树删除：a)查找要删除的节点。b)对节点进行相关删除操作；c)平衡性调整（旋转）
	//节点删除分几种情况：a)要删除的是叶子节点。b)要删除的节点有左子树或右子树（单分支节点）。
						  //c)要删除的节点的左子树和右子树都不为空。
	//对于被删除的节点，最终删除也只分两种情况：a)删除的是叶子节点。b)删除的是仅有左子树或者仅有右子树的节点。
	//先记住以下两点：a)如果最终删除的是一个红色节点，则不需要进行平衡性调整。
					//b)如果最终删除的是一个黑色节点，则因为黑色节点的删除会导致黑高度的变化，
					  //从而违法红黑树的性质4，使红黑树失衡，因此必须进行平衡性调整。
			   //c)红黑树根节点必须设置为黑色。不要忘记
	//删除黑色节点会分两种情况：a)删除的是仅有左子树或者仅有右子树的节点。b)删除的是叶子节点。
	//(1)删除的是仅有左子树或者右子树的黑色节点：
	   //a)节点10删除，让节点10的父节点的相应孩子指针指向节点6或节点12，同时让节点6,或12的父节点指针指向节点10的父节点。
	   //b)将节点6或12颜色从红修改为黑。

	//调整平衡有两件事特别重要：a)调整的子树根节点若为黑，调整平衡后一定不要把他变成红色，否则就面临不断循环向上调整直接遇到黑色节点的情形。
	// 	                      //b)调整完成后，子树黑高度不能发生变化。
	//(2)删除的是黑色叶子节点：最复杂：
		   //待删节点用D表示。  待删节点的兄弟节点用S表示。待删节点的父节点用P。
	//(2.1)待删节点可以是左节点，也可以是右节点，其父亲为红色，兄弟节点为黑色且不带孩子。
		//操作步骤：a)把节点D删除。b)将节点P变成黑色，将节点S变成红色。
	//(2.2)待删节点是左节点，其父节点为红色，兄弟节点为黑色且只带红色的左孩子。
		//操作步骤：a)把节点D删除。b)以S节点为根向右旋转。c)S节点变红，S左孩子变黑。d）以P节点为根左旋转。
	//(2.2)反：
		//操作步骤：a)把节点D删除。b)以S节点为根向左旋转。c)S节点变红，S右孩子变黑。d）以P节点为根右旋转

	//(2.3)待删节点是左节点，其父节点为红色，兄弟节点为黑色且只带红色的右孩子。
		//操作步骤：a)把节点D删除。b)以节点P为根左旋。c)把节点S变成红色，S的所有孩子变成黑色（非必须步骤）。
	//(2.3)反：
		//操作步骤：a)把节点D删除。b)以节点P为根右旋。c)把节点S变成红色，S的所有孩子变成黑色（非必须步骤）

	//(2.4)提前说明：八边形表示颜色随意(可红可黑)，红色三角形表示该节点可以没有，但如果有则必然为红色
	//     待删节点是左节点，其父节点颜色随意，兄弟节点为黑色，兄弟的左孩子可以没有（若有必然为红），兄弟节点右孩子为红色。
		//操作步骤：a)把节点D删除。b)把节点P和节点S颜色对调（对调后P颜色肯定为黑，而S取决于原来P的颜色）
				  //c)以P节点为根左旋。 d)将S右孩子节点设置为黑色。
	//(2.4）反：
	//     待删节点是右节点，其父节点颜色随意，兄弟节点为黑色，兄弟的右孩子可以没有（若有必然为红），兄弟节点左孩子为红色。
		//操作步骤：a)把节点D删除。b)把节点P和节点S颜色对调（对调后P颜色肯定为黑，而S取决于原来P的颜色）
				  //c)以P节点为根右旋。 d)将S左孩子节点设置为黑色。

	//(2.5)待删节点是左节点，其父节点为黑色，兄弟节点为黑色，兄弟节点只带红色左孩子
		//操作步骤：a)把节点D删除。b)以S节点为根向右旋转。C)以P为根先左旋转，D)把S左孩子节点变成黑色。
	//(2.5）反：
	//     待删节点是右节点，其父节点为黑色，兄弟节点为黑色，兄弟节点只带红色右孩子
	//操作步骤：a)把节点D删除。b)以S节点为根向左旋转。C)以P为根先右旋转，D)把S右孩子节点变成黑色。
	//(2.6)待删节点是左节点，其父节点为黑色，兄弟节点为红色且带有两个黑色的孩子（兄弟节点右孩子可以有任意红色孩子），
		 //兄弟节点的左孩子不可以有孩子。
	//操作步骤：a)把节点D删除。b)以P节点为根向左旋转。S节点变成黑色，S左孩子变成红色。
	//(2.6）反：
	// 待删节点是右节点，其父节点为黑色，兄弟节点为红色且带有两个黑色的孩子（兄弟节点左孩子可以有任意红色孩子），
		 //兄弟节点的右孩子不可以有孩子。
	//操作步骤：a)把节点D删除。b)以P节点为根向右旋转。S节点变成黑色，S右孩子变成红色。
	// 
	//(2.6.1)图3.2.11_31中，兄弟节点左孩子有一个右孩子，也可以有或者没有一个左孩子，那么：
	//操作步骤：a)把节点D删除，b)以P节点为根向左旋转。c)S节点变黑，P节点变红。
			  //d)以P节点为根左旋。e)将S左孩子变成红色，将P和 S左孩子右孙子变成黑色。
	//(2.6.2)图3.2.11_31中，兄弟节点左孩子只有一个左孩子（没有右孩子），那么：
	//操作步骤：a)把节点D删除，b)以P节点为根向左旋转。c)S节点变黑，P节点变红。
			//d)以S左孩子为根向右旋。e)以P为根向左旋转。f) 将P节点变成黑色。
			// 
	//(2.6.1)反：兄弟节点右孩子有一个左孩子，也可以有或者没有一个右孩子，那么：
	//操作步骤：a)把节点D删除，b)以P节点为根向右旋转。c)S节点变黑，P节点变红。
			  //d)以P节点为根右旋。e)将S右孩子变成红色，将P和 S右孩子左孙子变成黑色。
	//(2.6.2)反：兄弟节点右孩子只有一个右孩子（没有左孩子），那么：
	//操作步骤：a)把节点D删除，b)以P节点为根向右旋转。c)S节点变黑，P节点变红。
			//d)以S右孩子为根向左旋。e)以P为根向右旋转。f) 将P节点变成黑色。

	//(2.7)待删节点是做或者右节点都可以。父为黑色，兄弟为黑色且不带孩子。
	//操作步骤：a)把节点D删除，b)把S节点变为红色
	//(2.7.1)120黑色。
		//细分1：120的父亲和全部孩子节点都为黑色。
			//操作步骤，前两步和2.7相同。c)把节点P的兄弟节点120调整为红色。
		//细分2：120的左孩子为红色，右孩子为黑色。图3.2.11_39 
			//操作步骤，前两步和2.7相同。c)以120为根右旋.d)将110和120节点颜色互换
				   //e)以节点100为根左旋，f)将节点120变为黑色
		//细分3：节点120右孩子为红色，左孩子颜色随意。图3.2.11_40 
			//操作步骤，前两步和2.7相同。c)以节点100为根左旋。d）将节点130变为黑色。
		//细分2反：对比图 3.2.11_41 
		//细分3反：对比图3.2.11_42 
	//(2.7.2)120红色。
		//细分1：节点120的父亲肯定黑色。两个孩子110,130肯定是黑，左孩子110带了两个黑色孩子105和115,130下带啥无所谓。
			//操作步骤，前两步和2.7相同。c)以100为根左旋。d)120变黑，100变红。e)100变黑，110变红。
		//细分2：节点105红色，那么105下肯定会带两个黑色节点102,107。115是个黑色节点（其下带不带节点没所谓）
			//操作步骤，前两步和2.7相同。c)以100为根左旋。d)120变黑，100变红。
			 //e)以节点110为根右旋。f)将节点105变为黑色。g)以100为根左旋
		//细分3：115是红色，那么该节点下肯定带两个黑色节点112，117。此时不管105是什么颜色以及带什么子节点。
			//操作步骤，前两步和2.7相同。c)以100为根左旋。d)120变黑，100变红。
			//e)以节点100为根左旋。
		//细分1反：对比图3.2.11_46 
		//细分2反：对比图3.2.11_47 
		//细分3反：对比图3.2.11_48
	//提示：（1）红黑树演示：http://www.cs.usfca.edu/~galles/visualization/RedBlack.html
			//(2)遇到问题解决问题，使代码不断完善

	//（11.4）红黑树合法性测试代码
	//（11.5）红黑树插入和删除操作需要进行的平衡性调整的各种情况总结
	







	_nmsp1::RBTree<int> myrbtr;
	int array[] = { 60,25,90,23,49,86,100,34,58,59,80 };
	int acount = sizeof(array) / sizeof(int);
	for (int i = 0; i < acount; ++i)
	{
		myrbtr.InsertElem(array[i]);
	}
	myrbtr.levelOrder();

	cout << endl;
	cout << "---------" << endl;
	myrbtr.DeleteElem(23);
	myrbtr.levelOrder();


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




