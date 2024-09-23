// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
#include <assert.h>
#include <queue>

#ifdef _DEBUG   //只在Debug（调试）模式下
#ifndef DEBUG_NEW
#define DEBUG_NEW new(_NORMAL_BLOCK,__FILE__,__LINE__) //重新定义new运算符
#define new DEBUG_NEW
#endif
#endif

//#include <boost/type_index.hpp>
using namespace std;
#pragma warning(disable : 4996) 



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
	template <typename T>   //T代表数据元素的类型
	struct RBNode
	{
		T        data;   		
		RBNode* leftChild,   //左子节点指针
			  * rightChild,  //右子节点指针
		      * parentNd;    //父节点指针，引入方便操作
		
		bool     isRed;      //是否是红色节点，true：是，false：不是（而是黑色节点）
	};

	//红黑树的定义
	template <typename T>
	class RBTree
	{
	public:
		RBTree()  //构造函数		
		{
			root = nullptr;
		}
		~RBTree() //析构函数
		{
			ReleaseNode(root);
		}	

		////查找某个节点
		//RBTree<T>* SearchElem(const T& e)
		//{
		//	return SearchElem(root, e);
		//}
		//RBTree<T>* SearchElem(RBTree<T>* tNode, const T& e)
		//{
		//	if (tNode == nullptr)
		//		return nullptr;

		//	BinaryTreeNode<T>* tmpnode = tNode;
		//	while (tmpnode)
		//	{
		//		if (tmpnode->data == e)
		//			return tmpnode;
		//		if (tmpnode->data > e)
		//			tmpnode = tmpnode->leftChild;
		//		else
		//			tmpnode = tmpnode->rightChild;
		//	}
		//	return nullptr;
		//}

		/*
		RBNode<T>* AddNode(RBNode<T>*& myparent, bool ifleft,bool isRed,int data)
		{
			RBNode<T>* point = new RBNode<T>;
			point->parentNd = myparent;
			point->leftChild = point->rightChild = nullptr;
			point->isRed = isRed;
			point->data = data;
			if (ifleft == true)
				myparent->leftChild = point;
			else
				myparent->rightChild = point;
			return point;
		}

		//创建树的特殊代码
		void CreateKXTree()
		{
			root = new RBNode<T>;			
			root->data = 100;
			root->parentNd = nullptr;
			root->leftChild = root->rightChild = nullptr;
			root->isRed = false;

			RBNode<T>* tmpnode;

			tmpnode = AddNode(root, true, false, 90);
			AddNode(tmpnode, true, false, 85);
			AddNode(tmpnode, false, false, 95);

			RBNode<T>* tmpnode120 = AddNode(root, false, true, 120);
			RBNode<T>* tmpnode110 = AddNode(tmpnode120, true, false, 110);
			RBNode<T>* tmpnode130 = AddNode(tmpnode120, false, false, 130);

			RBNode<T>* tmpnode105 = AddNode(tmpnode110, true, true, 105);
			AddNode(tmpnode105, true, false, 102);
			AddNode(tmpnode105, false, false, 107);
			RBNode<T>* tmpnode115 = AddNode(tmpnode110, false, false, 115);

			AddNode(tmpnode130, true, false, 125);
			AddNode(tmpnode130, false, false, 140);
		}*/

		//插入元素
		//change==true表示自动调整平衡，但有时候为了测试目的，我们需要手工构造红黑树，不让其自动调整平衡，此时可以给change传递false
		void InsertElem(const T& e,bool change = true)  //不可以指定插入位置，程序内部会自动确定插入位置
		{
			InsertElem(root, e,change);
		}
		void InsertElem(RBNode<T>*& tNode, const T& e, bool change = true) //注意第一个参数类型
		{
			RBNode<T>* point = tNode;     //从指向根节点开始 
			RBNode<T>* parent = nullptr;  //保存父亲节点，根节点的父节点肯定先为nullptr			

			//通过一个while循环寻找要插入节点的位置，同时还要把插入路线上所经过的所有节点都保存到栈中，因为这些节点的平衡因子可能需要调整
			while (point != nullptr)
			{
				if (e == point->data)
					return;   //要插入的数据与当前树中某节点数据相同，则不允许插入，直接返回

				parent = point; //记录父节点，因为后续子节点要往下走，找合适自己的位置				

				if (e > point->data)
					point = point->rightChild;
				else
					point = point->leftChild;
			} //end while

			//走到这里，point 等于 nullptr，该生成新节点了
			point = new RBNode<T>;
			point->data = e;
			point->leftChild = nullptr;
			point->rightChild = nullptr;
			point->parentNd = nullptr;
			point->isRed = true;  //缺省插入的节点先给红色

			if (parent == nullptr)
			{
				//创建的是根节点
				point->isRed = false; //根节点是黑色
				tNode = point;
				return;
			}

			//走到这里表示创建的不是根节点，那么要把孩子链到父亲上
			if (e > parent->data)
				parent->rightChild = point; //在父节点的右树链入
			else
				parent->leftChild = point; //在父节点的左树链入

			point->parentNd = parent;  //记录父节点指针

			if (parent->isRed == false) //父节点为黑色，不需要做什么
				return;
			
			//能走到这里的，要插入的节点肯定是至少在第三层了。

			//父节点为红色才能走下来（当前节点也是红色的）
			if(change == true)
				BalanceTune(point, parent);
			root->isRed = false; //根节点颜色无条件给黑色
		}
		
		//层序遍历二叉树，方便显示		
		void levelOrder()
		{
			cout << endl; //先换个行，防止多次调用levelOrder看不清楚内容
			cout << endl; //留个空行
			levelOrder(root);
		}

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
			}
			return blackheight;
		}

		//删除某个节点
		void DeleteElem(const T& e)
		{
			return DeleteElem(root, e);
		}
		void DeleteElem(RBNode<T>*& tNode, const T& e)  //注意第一个参数类型
		{
			RBNode<T>* ptmp = tNode; //要删除的节点
			RBNode<T>* parent = nullptr;  //保存父亲节点，根节点的父节点肯定先为nullptr
						
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
				//slinkobj.Push(parent); //入栈
				//(2)找到这个要删除节点的左子树的最右下节点（也可以找这个要删除节点右子树的最左下节点）,将该节点的值替换到要删除的节点上；
				q = ptmp->leftChild;
				while (q->rightChild != nullptr)
				{
					parent = q;
					//slinkobj.Push(parent); //入栈
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
				pBroNode->leftChild != nullptr && pBroNode->leftChild->isRed == true  //红色左孩子
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
				
		lblgoto:  //一个标号，当黑高变少时要回到这里再次执行
				if (pParentNode->parentNd == nullptr)  //pParentNode->parentNd是100节点
					return; //没有父亲，自己就是根了，不用继续调整了

				//---------------------		
				//100节点存在，才走下来
				RBNode<T>* pParentNodeP = pParentNode->parentNd;   //100节点，这个可能随着调整要变，代表树的根   **********pParentNodeP:代表树的根，注意更新

				bool leftorright = 0;   //0,这个子树是整个红黑树的左边部分，1，这个子树是整个红黑树的右边部分
				if (pParentNodeP->rightChild == pParentNode) //看看100节点的右孩子是不是被删除节点的父亲即90节点
					leftorright = 1; //这个子树是整个红黑树的右边部分

				int subsign = 0; //0：代表父亲没爷爷   1：代表父亲是爷爷的左孩子     2：代表父亲是爷爷的右孩子
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
					//2023.2.23发现了代码错误（调整平衡后黑高减少，导致整个二叉树失衡），进行修正。感谢学友心境无痕 提出这个问题。
					//细分1
					if (pParentNodeP->isRed == true) //100节点为红
					{
						//细分1走这里
						RBNode<T>* tmpnode = nullptr;
						if (leftorright == 0) //这个子树[以P为根]是100这个节点的左孩子
						{
							bool ifdo = (pParentBro->leftChild->isRed == true); //120的左孩子110是否为红色先取得，防止后面旋转把信息搞丢了							
							if (ifdo == true) //120的左孩子110为红色,还需要多进行一步调整
							{
								tmpnode = pParentBro->leftChild; //保存要变色的节点
							}
							RotateLeft(pParentNodeP); //100为根左旋
							if (ifdo == true)
							{
								//110为红色，则其必然有两个黑色孩子
								tmpnode->isRed = !(tmpnode->isRed); //110节点变色
								tmpnode->leftChild->isRed = !(tmpnode->leftChild->isRed); //110的左孩子105变色
								tmpnode->rightChild->isRed = !(tmpnode->rightChild->isRed); //110的右孩子115变色
							}							
						}
						//细分1【反】走这里
						else
						{
							bool ifdo = (pParentBro->rightChild->isRed == true); //80的右孩子90是否为红色先取得，防止后面旋转把信息搞丢了
							if (ifdo == true) //120的左孩子110为红色,还需要多进行一步调整
							{
								tmpnode = pParentBro->rightChild; //保存要变色的节点
							}
							RotateRight(pParentNodeP); //100为根右旋
							if (ifdo == true)
							{
								//90为红色，则其必然有两个黑色孩子
								tmpnode->isRed = !(tmpnode->isRed); //90节点变色
								tmpnode->rightChild->isRed = !(tmpnode->rightChild->isRed); //90的右孩子95变色
								tmpnode->leftChild->isRed = !(tmpnode->leftChild->isRed); //90的左孩子85变色								
							}
						}
					}
					else
					{
						//100节点为黑色走这里，这里也是要处理细分2、3、4的地方						
						if (leftorright == 0 &&  //这个子树[以P为根]是100这个节点的左孩子
							pParentBro->leftChild->isRed == true && pParentBro->rightChild->isRed == false) //节点120的左孩子为红色，右孩子为黑色
						{
							//细分2
							RotateRight(pParentBro); //pParentBro原=120，pParentBro新=110
							pParentNodeP->rightChild = pParentBro; //让100的右孩子指向110(因为原来100的右孩子指向120的)
							pParentBro->isRed = !(pParentBro->isRed); //110节点变色						

							RotateLeft(pParentNodeP); //100为根左旋
						}
						else if (leftorright != 0 &&  //这个子树[以P为根]是100这个节点的右孩子
							pParentBro->rightChild->isRed == true && pParentBro->leftChild->isRed == false) //节点80的右孩子为红色，左孩子为黑
						{
							//细分2【反】
							RotateLeft(pParentBro); //pParentBro原=80，pParentBro新=90
							pParentNodeP->leftChild = pParentBro; //让100的左孩子指向90
							pParentBro->isRed = !(pParentBro->isRed); //90节点变色
							
							RotateRight(pParentNodeP);//100为根右旋。pParentNodeP原=100，pParentNodeP新=90
						}

						else if (leftorright == 0 &&  //这个子树[以P为根]是100这个节点的左孩子
							pParentBro->rightChild->isRed == true) //节点120的右孩子为红色
						{
							//细分3
							RotateLeft(pParentNodeP);//100为根左旋。pParentNodeP原=100，pParentNodeP新=120
							pParentNodeP->rightChild->isRed = !(pParentNodeP->rightChild->isRed); //130节点变色

						}
						else if (leftorright != 0 &&  //这个子树[以P为根]是100这个节点的右孩子
							pParentBro->leftChild->isRed == true) //节点80的左孩子为红色
						{
							//细分3【反】
							RotateRight(pParentNodeP);//100为根右旋。pParentNodeP原=100，pParentNodeP新=80
							pParentNodeP->leftChild->isRed = !(pParentNodeP->leftChild->isRed); //60节点变色		
						}
						
						else if (pParentBro->leftChild->isRed == false && pParentBro->rightChild->isRed == false)
						{
							//细分4[不用分左右]
							pParentBro->isRed = !(pParentBro->isRed); //直接把120反色，也就是改为红色

							if (pParentNodeP == root) 
							{
								//此时100是整个红黑树的根节点，则平衡调整完毕。
								//do nothing：这里啥也不用做，因为平衡调整完毕
							}
							else
							{
								//100不是整个红黑树的根，有些麻烦，因为经过调整后，虽然以100为根的这棵子树是平衡的，但是该子树的黑高却从3降为了2
								//黑高的减少意味着必须要向树根的方向继续调整，调整方法：
								//（1）将节点100当做新的P节点
								pParentNode = pParentNodeP;  //100

								//（2）回到 (7).a中的执行流程继续调整
								goto lblgoto;								
							}
						}
						else
						{
							//走到这里表示没被处理，程序不识别的情况，需要做出警告并添加代码处理未识别的情形
							assert(false);
						}
					}//end if (pParentNodeP->isRed == true) //100节点为红
				}
				// (7).b
				else //120是红色节点，上边的100和孩子110，130都得是黑色的，否则就是红色连接到一起的。
				{
					if (leftorright == 0) //0,这个子树是整个红黑树的左边部分
					{
						//细分1、2、3走这里							
						//细分1
						if(pParentBro->leftChild != nullptr &&  //110存在
							pParentBro->leftChild->leftChild != nullptr && pParentBro->leftChild->leftChild->isRed == false &&    //105存在且黑
							pParentBro->leftChild->rightChild != nullptr && pParentBro->leftChild->rightChild->isRed == false )//115存在且黑
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
					} //end if (leftorright == 0) 
				} //end if(pParentBro->isRed == false)

				//根或者父指针的调整相关
				if (subsign == 0)//根要变了吧
					root = pParentNodeP;
				else if (subsign == 1)  //父亲是爷爷的左孩子
					pParentNodePP->leftChild = pParentNodeP;
				else
					pParentNodePP->rightChild = pParentNodeP;

				return; //不用调整根的问题了,也就是不希望后面的if(sign ==0)....代码执行了								
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

	private:	
		//平衡性调整				
		void BalanceTune(RBNode<T>* point, RBNode<T>* parent)//point：当前节点。parent：当前节点的父节点
		{
			RBNode<T>* parentBroNode = nullptr;      //叔叔节点，有为空的可能性，此时表示没叔叔节点
			RBNode<T>* grandFatherNode = nullptr;      //爷爷节点，不会为空的，因为父亲节点为红色，红色不能做根，所以至少都是根节点做爷爷节点。

			while (true)
			{
				parentBroNode = (parent->parentNd != nullptr) ? (getBrotherNode(parent)) : nullptr;  //叔叔
				grandFatherNode = point->parentNd->parentNd;     //爷爷 

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
					point = grandFatherNode;    //当前节点指向爷爷，从爷爷节点（红）开始继续向上调整						
					parent = point->parentNd;   //设置父亲节点

					//这情况不存在，否则前面的if (grandFatherNode == root)就会成立就会return出去，到不了这里						
					//记得#include <assert.h>
					if (parent == nullptr) { assert(false); }  //assert(false);意味着代码不可能执行到这条语句，若执行到了，会报告异常		

					if (parent->isRed == false) //如果这个新父节点为黑色，认为调整完毕不继续向上调整
						break;
					
					continue;
				}

				//上面的代码下不来，下来的，不会满足上面的   if (parentBroNode != nullptr && parentBroNode->isRed == true)条件
				//因为  如果叔叔节点不为空并且叔叔节点为红色的情况上面处理完了下不来了，所以走到下面的，都属于 叔叔节点为空或者叔叔节点不为空但为黑色的情况

				//旋转变色之前确定一些信息，这是通用代码，所以放这里
				RBNode<T>* gff = grandFatherNode->parentNd;
				int sign = 0;  //标记：1表示grandFatherNode是其父亲的左孩子，2表示grandFatherNode是其父亲的右孩子
				if (gff != nullptr)
				{
					if (gff->leftChild == grandFatherNode)
						sign = 1;
					else
						sign = 2;
				}
				//---------------------------------------------------------------------------------
				if (grandFatherNode->leftChild == parent)//第一种情形，父亲是爷爷节点的左孩子
				{
					//开始旋转和变色以调整平衡
					if (parent->leftChild == point)//新节点是父亲节点的左孩子
					{
						//右旋转
						RotateRight(grandFatherNode);
					}
					else //新节点是父亲节点的右孩子
					{
						//先左后右旋
						RotateLeftRight(grandFatherNode);
					} //end if (parent->leftChild == point)

					//旋转变色之后一些公用代码						
					//变色
					grandFatherNode->isRed = false;  //新根设置为黑色
					grandFatherNode->rightChild->isRed = true; //新右叶子设置为红色					
				}
				else   // 第二种情形，父亲是爷爷节点的右孩子
				{
					//开始旋转和变色以调整平衡
					if (parent->rightChild == point)//新节点是父亲节点的右孩子
					{
						//左旋转
						RotateLeft(grandFatherNode);
					}
					else //新节点是父亲节点的左孩子
					{
						//先右后左旋
						RotateRightLeft(grandFatherNode);
					} //end if (parent->rightChild == point)

					//旋转变色之后一些公用代码						
					//变色 
					grandFatherNode->isRed = false;  //新根设置为黑色
					grandFatherNode->leftChild->isRed = true; //新左叶子设置为红色
				}
				//---------------------------------------------------------------------------------
				// 一些通用代码放这里
				//根已经改变了，所以要设置一些节点指向信息
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
			} //end while
			return;
		}
		//获取兄弟节点指针
		RBNode<T>* getBrotherNode(RBNode<T>* p)
		{
			//由调用者确定p->parent一定不为nullptr。
			if (p->parentNd->leftChild == p) //父亲的左儿子是不是自己
				return 	p->parentNd->rightChild; //返回父亲的右儿子
			
			return p->parentNd->leftChild; //返回父亲的左儿子
		}

		//左旋转（代码与AVL左旋其实是一样的，但要注意parent指针的设置）
		void RotateLeft(RBNode<T>*& pointer)//注意参数类型
		{
			//     4      -----左旋----             6
			//  /      \                         /     \
			// 3        6                     4         7
			//         /   \                 /  \
			//        5     7              3     5   
			RBNode<T>* ptmproot = pointer;   //让ptmproot指向4

			pointer = ptmproot->rightChild;  //让pointer指向6
			pointer->parentNd = ptmproot->parentNd; //设置6的父亲指向4的父亲

			ptmproot->rightChild = pointer->leftChild; //让4的右孩子不再指向6，而是指向5
			if (pointer->leftChild)
				pointer->leftChild->parentNd = ptmproot;   //设置5的父亲是4

			pointer->leftChild = ptmproot; //让6的左孩子指向4
			ptmproot->parentNd = pointer;  //设置4的父亲是6
		}

		//右旋转
		void RotateRight(RBNode<T>*& pointer) //注意参数类型
		{
			//         6      -----右旋----             4
			//     /      \                          /     \
			//    4        7                        3       6
			//  /   \                                      /  \
			// 3     5                                    5    7   
			RBNode<T>* ptmproot = pointer;   //让ptmproot指向6

			pointer = ptmproot->leftChild;    //让pointer指向4
			pointer->parentNd = ptmproot->parentNd; //设置4的父亲指向6的父亲

			ptmproot->leftChild = pointer->rightChild;  //让6的左孩子不再指向4，而是指向5
			if(pointer->rightChild)
				pointer->rightChild->parentNd = ptmproot;   //设置5的父亲是6

			pointer->rightChild = ptmproot;             //让4的右孩子指向6
			ptmproot->parentNd = pointer;               //设置6的父亲是4
		}

		//先左后右旋转
		void RotateLeftRight(RBNode<T>*& pointer)
		{
			//如下图不全，只是示意，不要按照这个图写代码否则会造成代码出现bug
			//      6      -----先左旋----    6       -----再右旋----    5
			//   /      \                   /   \                      /    \
			//  4        7                 5     7                    4      6 
			//    \                       /                                    \
			//     5                     4                                      7

			RBNode<T>* ptmproot = pointer;   //让ptmproot指向6
			RBNode<T>* ptmproot_lf = ptmproot->leftChild;  //让ptmproot_lf指向4
			pointer = ptmproot_lf->rightChild;  //让pointer指向5，5是旋转后最终的根
			RBNode<T>* orgparent = ptmproot->parentNd; //把老父亲保存起来，后面要用			

			//先左旋转
			ptmproot->leftChild = pointer; //6的左孩子指向5,其实后面会覆盖，所以这个赋值其实没用，但为了醒目清晰，就留着了
			pointer->parentNd = ptmproot;  //5的父亲指向6，上行没啥用，所以这行其实也没啥用			

			ptmproot_lf->rightChild = pointer->leftChild; //4的右孩子指向5的左孩子
			if(pointer->leftChild)
				pointer->leftChild->parentNd = ptmproot_lf;   //5的左孩子的父亲指向4

			pointer->leftChild = ptmproot_lf; //5的左孩子指向4
			ptmproot_lf->parentNd = pointer;    //4的父亲指向5
			
			//再右旋转			
			ptmproot->leftChild = pointer->rightChild;//6的左孩子指向5的右孩子
			if (pointer->rightChild)  
				pointer->rightChild->parentNd = ptmproot;  //5的右孩子的父亲指向6

			pointer->rightChild = ptmproot;  //5的右孩子指向6
			ptmproot->parentNd = pointer;    //6的父亲指向5

			//再处理根节点的父亲指向
			pointer->parentNd = orgparent;
		}

		//先右后左旋转
		void RotateRightLeft(RBNode<T>*& pointer)
		{
			//      6     -----先右旋----     6       -----再左旋----     7
			//   /     \                   /     \                      /    \
			//  4        8                4       7                    6      8 
			//          /                           \                 /                   
			//         7                             8               4                    
			RBNode<T>* ptmproot = pointer;   //让ptmproot指向6
			RBNode<T>* ptmproot_rg = ptmproot->rightChild;  //让ptmproot_rg指向8
			pointer = ptmproot_rg->leftChild;  //让pointer指向7，7是旋转后最终的根
			RBNode<T>* orgparent = ptmproot->parentNd; //把老父亲保存起来，后面要用	

			
			//先右旋转
			ptmproot->rightChild = pointer; //6的右孩子指向7,其实后面会覆盖，所以这个赋值其实没用，但为了醒目清晰，就留着了
			pointer->parentNd = ptmproot;  //7的父亲指向6，上行没啥用，所以这行其实也没啥用			
			
			ptmproot_rg->leftChild = pointer->rightChild; //8的左孩子指向7的右孩子
			if (pointer->rightChild)
				pointer->rightChild->parentNd = ptmproot_rg;   //7的右孩子的父亲指向7
			
			pointer->rightChild = ptmproot_rg; //7的右孩子指向8
			ptmproot_rg->parentNd = pointer;    //8的父亲指向7
			
			//再左旋转			
			ptmproot->rightChild = pointer->leftChild;//6的右孩子指向7的左孩子
			if (pointer->leftChild)
				pointer->leftChild->parentNd = ptmproot;  //7的左孩子的父亲指向6
			
			pointer->leftChild = ptmproot;  //7的左孩子指向6
			ptmproot->parentNd = pointer;    //6的父亲指向7

			//再处理根节点的父亲指向
			pointer->parentNd = orgparent;			
		}

		void ReleaseNode(RBNode<T>* pnode)
		{
			if (pnode != nullptr)
			{				
				ReleaseNode(pnode->leftChild); 
				ReleaseNode(pnode->rightChild);
			}
			delete pnode;
		}
		
		//获取某个节点的高度（根高度为1，往下高度依次+1），用于显示节点时换行的目的
		int getNodeLevel(RBNode<T>* tNode)
		{
			int icurlvl = 0;
			while (tNode != nullptr)
			{
				tNode = tNode->parentNd;
				icurlvl++;
			} //end while
			return icurlvl;
		}
public:
		//测试目的，设置所有红黑树节点为黑色。设置后是否还是红黑树，可以调用levelOrder()检验
		void setAllBlack()
		{
			RBNode<T>* tNode = root;
			if (tNode != nullptr) //若二叉树非空
			{
				RBNode<T>* tmpnode;
				_nmsp0::LinkQueue<RBNode<T>*> lnobj;//注意，队列的元素类型是“节点指针”类型
				lnobj.EnQueue(tNode); //先把根节点指针入队

				int currdislvl = 1;   //当前显示第几层，根算第一层
				while (!lnobj.IsEmpty()) //循环判断队列是否为空
				{
					lnobj.DeQueue(tmpnode); //出队列
					//int lvl = getNodeLevel(tmpnode);
					//if (lvl != currdislvl) //用于换行
					//{
					//	currdislvl = lvl;
					//	cout << endl;
					//}					
					tmpnode->isRed = false; //设置为黑色节点

					if (tmpnode->leftChild != nullptr)
						lnobj.EnQueue(tmpnode->leftChild);  //左孩子入队
					if (tmpnode->rightChild != nullptr)     //右孩子入队
						lnobj.EnQueue(tmpnode->rightChild);
				} //end while
			} //end if (tNode != nullptr)
			return;
		}

		//测试目的，用于设置某些节点为红色节点，这里需要修改代码来专门设置某些红色节点。设置后是否还是红黑树，可以调用levelOrder()检验
		void setNodeColor__secondfa()
		{
			RBNode<T>* tNode = root;
			if (tNode != nullptr) //若二叉树非空
			{
				RBNode<T>* tmpnode;
				_nmsp0::LinkQueue<RBNode<T>*> lnobj;//注意，队列的元素类型是“节点指针”类型
				lnobj.EnQueue(tNode); //先把根节点指针入队

				int currdislvl = 1;   //当前显示第几层，根算第一层
				while (!lnobj.IsEmpty()) //循环判断队列是否为空
				{
					lnobj.DeQueue(tmpnode); //出队列
					//int lvl = getNodeLevel(tmpnode);
					//if (lvl != currdislvl) //用于换行
					//{
					//	currdislvl = lvl;
					//	cout << endl;
					//}
					if (/*tmpnode->data == 36 ||
						tmpnode->data == 3223 ||
						tmpnode->data == 5453 ||
						tmpnode->data == 6556 ||
						tmpnode->data == 52 ||*/
						tmpnode->data == 3299 ||
						tmpnode->data == 3390 ||
						tmpnode->data == 5500 ||
						tmpnode->data == 3410
						)
					{
						tmpnode->isRed = true; //设置为红色节点
					}
					else
						tmpnode->isRed = false; //设置为黑色节点

					if (tmpnode->leftChild != nullptr)
						lnobj.EnQueue(tmpnode->leftChild);  //左孩子入队
					if (tmpnode->rightChild != nullptr)     //右孩子入队
						lnobj.EnQueue(tmpnode->rightChild);
				} //end while
			} //end if (tNode != nullptr)
			return;
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
				_nmsp0::LinkQueue<RBNode<T>*> lnobj;//注意，队列的元素类型是“节点指针”类型
				lnobj.EnQueue(tNode); //先把根节点指针入队

				int currdislvl = 1;   //当前显示第几层，根算第一层
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
						cout <<  endl;
					}
					if (tmpnode->isRed == false)
						ptmp = (char *)pb;
					else
						ptmp = (char*)pr;
					cout << tmpnode->data <<ptmp << "       ";

					//判断黑高
					int tmpvalue = Calc_BH(tmpnode);
					if (tmpvalue != -1)
					{
						//这个黑高值有效
						if (blackheight == -1) //黑高值从来没拿到过
						{
							blackheight = tmpvalue;//给黑高赋值
						}
						else
						{
							//黑高已经有值，判断黑高是否相等
							if (blackheight != tmpvalue)
							{
								ifaRBTree = false; //不是红黑树
								cout << "末端节点的黑高值不相等:（" << blackheight << "," << tmpvalue << "），不是红黑树了！" << endl;
								break; //直接退出循环吧
							}
						}
					}
					if (tmpnode->isRed == true && tmpnode->parentNd != nullptr)
					{
						if (tmpnode->parentNd->isRed == true)
						{
							//父子关系的两个红黑树节点颜色都为红色，不可以
							cout << endl; //换行
							cout << "红黑树红色节点（" << tmpnode->data << "）的父节点（" << tmpnode->parentNd->data << "）也是红色，这已经不是一棵红黑树了！" << endl;
							break; //直接退出循环吧
						}
					}

					if (tmpnode->leftChild != nullptr)
						lnobj.EnQueue(tmpnode->leftChild);  //左孩子入队
					if (tmpnode->rightChild != nullptr)     //右孩子入队
						lnobj.EnQueue(tmpnode->rightChild);
				} //end while
			} //end if (tNode != nullptr)
		}
	private:
		RBNode<T>* root; //树根指针	
	};	
}

int main()
{		
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口
	
	_nmsp1::RBTree<int> myrbtr;
	//myrbtr.CreateKXTree();
	
	//int array[] = { 40,30,50,10,35,5 };	
	//int array[] = { 100,80,60};
	//int array[] = { 80,50,120,30,60,20,40 ,10};
	//int array[] = { 80,50,30 };
	//int array[] = { 80,50,120,30,10 };
	//---------------------
	//int array[] = { 50,30,40 };
	//综合测试
	//int array[] = { 1,2,3,4,5,6,7 ,8,9,10,11,12 };
	//int array[] = { 60,25,90,23,49,86,100,34,58,101/*,59*/};
	//int array[] = { 60,25,90,23,49,86,100,34,58,59 };
	//int array[] = { 60,25,90,23,49,86,100,34,58,59,80 };
	//int array[] = { 10,9,12 };

	//int array[] = { 100,60,120,110,130,115 };

	//int array[] = { 1212,32,3299,11,52,3223,3390,8,12,35,54,2333,3266,3345,3444 };
	//int array[] = { 1212,36,3444,11,56,2333,5454,8,32,43,545,3223,5453,6556,52,500 };
	//int array[] = { 2,1,3};
	//int array[] = { 100,90,120,85,95,110,130 };
	//int array[] = { 150,100,200,90,120,180,220,85,95,110,130 ,105,115};
	//int array[] = { 100,80,120,60,90,110,130,105,115 };
	//int array[] = { 100,80,120,60,90,110,130};
	//int array[] = { 180,100,220,90,120,210,230,85,95,110,130,205,215,225,235 };
	//int array[] = { 180,100,220,90,120,210,230,85,95,110,130,205,215,225,235,202,207,212,217,222,227,232,237 };
	int array[] = { 1212,32,3444,11,52,3299,5454,8,12,35,54,3223,3345,4000,6556,2333,3266,3322,3390,5500,3380,3400,3410};

	int acount = sizeof(array) / sizeof(int);
	for (int i = 0; i < acount; ++i)
	{
		myrbtr.InsertElem(array[i],false); //false表示不需要插入数据时自动调整平衡
	}

	myrbtr.setAllBlack(); //设置所有红黑树节点为黑色【测试目的】
	myrbtr.setNodeColor__secondfa();//设置某些红黑树节点为红色【测试目的】
	myrbtr.levelOrder(); //显示并确认是一颗红黑树
	myrbtr.DeleteElem(8);	
	myrbtr.levelOrder(); //显示并确认是一颗红黑树	


	void* test;
	int i=10;
	int* p = &i;
	test = (void*)p;
	//((char*)test)++;
	p++;
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


