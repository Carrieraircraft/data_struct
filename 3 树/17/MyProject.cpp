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


namespace _nmsp0
{
	//链式栈中每个节点的定义
	template <typename T> //T代表数据元素的类型
	struct StackNode
	{
		T        data;  //数据域，存放数据元素
		StackNode<T>* next;  //指针域，指向下一个同类型（和本节点类型相同）节点
	};

	//链式栈的定义
	template <typename T>
	class LinkStack
	{
	public:
		LinkStack();      //构造函数，参数可以有默认值
		~LinkStack();     //析构函数

	public:
		bool Push(const T& e); //入栈元素e
		bool Pop(T& e);        //出栈（删除数据），也就是删除栈顶数据
		bool GetTop(T& e);     //读取栈顶元素，但该元素并没有出栈而是依旧在栈中

		void DispList();                     //输出链式栈中的所有元素
		int  ListLength();                   //获取链式栈的长度
		bool Empty();                        //判断链式栈是否为空

	private:
		StackNode<T>* m_top;   //栈顶指针
		int               m_length;//链式栈当前长度
	};

	//通过构造函数对链式栈进行初始化
	template <typename T>
	LinkStack<T>::LinkStack()
	{
		m_top = nullptr;
		m_length = 0;
	}

	//入栈元素e，时间复杂度为O(1)
	template <typename T>
	bool LinkStack<T>::Push(const T& e)
	{
		StackNode<T>* node = new StackNode<T>;
		node->data = e;
		node->next = m_top;
		m_top = node;
		m_length++;
		return true;
	}

	//出栈（删除数据），也就是删除栈顶数据，时间复杂度为O(1)
	template <typename T>
	bool LinkStack<T>::Pop(T& e)
	{
		if (Empty() == true) //链式栈为空
			return false;

		StackNode<T>* p_willdel = m_top;
		m_top = m_top->next;
		m_length--;
		e = p_willdel->data;
		delete p_willdel;
		return true;
	}

	//读取栈顶元素，但该元素并没有出栈而是依旧在栈中
	template <typename T>
	bool LinkStack<T>::GetTop(T& e)
	{
		if (Empty() == true) //链式栈为空
			return false;

		e = m_top->data;
		return true;
	}

	//输出链式栈中的所有元素，时间复杂度为O(n)
	template<class T>
	void LinkStack<T>::DispList()
	{
		if (Empty() == true) //链式栈为空
			return;

		StackNode<T>* p = m_top;
		while (p != nullptr)
		{
			cout << p->data << " ";  //每个数据之间以空格分隔
			p = p->next;
		}
		cout << endl; //换行
	}

	//获取链式栈的长度，时间复杂度为O(1)
	template<class T>
	int  LinkStack<T>::ListLength()
	{
		return m_length;
	}

	//判断链式栈是否为空，时间复杂度为O(1)
	template<class T>
	bool LinkStack<T>::Empty()
	{
		if (m_top == nullptr) //链式栈为空
		{
			return true;
		}
		return false;
	}

	//通过析构函数对链式栈进行资源释放
	template <typename T>
	LinkStack<T>::~LinkStack()
	{
		T tmpnousevalue = { 0 };
		while (Pop(tmpnousevalue) == true) {}//把栈顶元素删光，while循环也就退出了，此时也就是空栈了				
	}
}

//------------------------------
namespace _nmsp1
{
	//平衡二叉树中每个节点的定义
	template <typename T> //T代表数据元素的类型
	struct AVLNode
	{
		T   data; 
		AVLNode* leftChild; //左子节点指针
		AVLNode* rightChild; //右子节点指针
		int  balfac; //平衡因子
	};

	//平衡二叉树的定义
	template <typename T>
	class AVLTree
	{
	public:
		AVLTree()//构造函数
		{
			root = nullptr;
		}
		~AVLTree() //析构函数
		{
			ReleaseNode(root);
		}

		//插入元素
		void InsertElem(const T& e) //不可以指定插入位置，程序内部会自动确定插入位置
		{
			InsertElem(root, e);
		}
		void InsertElem(AVLNode<T>*& tNode, const T& e) //注意第一个参数类型
		{
			AVLNode<T>* point = tNode; //从指向根节点开始
			AVLNode<T>* parent = nullptr; //保存父亲节点，根节点的父节点肯定先为nullptr；

			//借助以往实现的栈（链栈）代码保存插入的节点路径信息（用于后面调节平衡因子、调整平衡）
			_nmsp0::LinkStack< AVLNode<T>* > slinkobj;

			//通过一个while循环寻找要插入的节点的位置，同时还要把插入路线上的所经过的所有节点都保存到栈中，
			 //因为这些节点的平衡因子可能需要调整
			while (point != nullptr)
			{
				if (e == point->data)
					return; //要插入的数据与当前树中某节点数据相同，则不允许插入，直接返回。

				parent = point;  //记录父节点，因为后续子节点要往下走，找合适自己的位置
				slinkobj.Push(parent); //入栈（树根在最底下，越往上离要插入的节点越近，最上面元素是要插入的节点的父节点）
				
				if (e > point->data)
					point = point->rightChild;
				else
					point = point->leftChild;
			} //end while
			
			//走到这里，point等于nullptr，该生成新节点了
			point = new AVLNode<T>;
			point->data = e;
			point->leftChild = nullptr;
			point->rightChild = nullptr;
			point->balfac = 0; //插入时肯定是个叶节点，所以平衡因子肯定等于0
			if (parent == nullptr)
			{
				//创建的是根节点
				tNode = point;
				return;
			}

			//走到这里表示创建的不是根接待你，那么要把孩子链到父亲上。
			if (e > parent->data)
				parent->rightChild = point; //在父节点的右树链入
			else
				parent->leftChild = point; //在父节点的左树链入

			//下面即将修改平衡因子 以及 调整平衡，前面栈slinkobj里的节点就是可能要更改平衡因子和做平衡调整的节点
			while (slinkobj.Empty() != true)
			{
				if (slinkobj.Pop(parent) == true) //取栈顶元素到parent中，第一次获取到的是新插入节点的父节点
				{
					//（1）因为插入了孩子，所以调整父的平衡因子
					if (parent->leftChild == point) //插入的是parent的左子节点
						parent->balfac++; //平衡因子+1
					else
						parent->balfac--; //平衡因子-1

					//（2）找最小不平衡子树的根节点并进行平衡性调整
					if (parent->balfac < -1 || parent->balfac > 1)
					{
						//有四种旋转方式，采取那种旋转方式呢？
						// （1）如果这棵最小不平衡子树的根节点和其孩子节点的平衡因子>0，那就是LL情形，要通过有旋转来恢复平衡
						if (parent->balfac > 0 && point->balfac > 0)
						{
							RotateRight(parent);
						}
						//（2）如果这棵最小不平衡子树的根节点和其孩子节点的平衡因子都<0，那就是RR情形，要左旋转来恢复平衡。
						else if (parent->balfac < 0 && point->balfac < 0)
						{
							RotateLeft(parent);
						}

						//（3）如果 这棵最小不平衡子树 的根节点的 平衡因子>0，其孩子节点的平衡因子<0，那就是LR情形，要先左旋再右旋来恢复平衡
						else if (parent->balfac > 0 && point->balfac < 0)
						{
							RotateLeftRight(parent);
						}

						//（4）如果 这棵最小不平衡子树的根节点的平衡因子 <0，其孩子节点的平衡因子都>0，那就是RL情形，要先右旋再左旋来恢复平衡
						else  //if (parent->balfac < 0 && point->balfac > 0)
						{
							RotateRightLeft(parent);
						}

						//根相关指针的调整
						if (slinkobj.Empty() == true)
						{
							//本条件成立，表示本次平衡性调整调整到了整个树最上面的根节点，因为平衡性调整会使树根节点
							  //发生改变，所以这里要更新根节点的指向
							root = parent;
						}
						else
						{
							//本次平衡性调整并没有调整到 整个树最上面的根节点，但 因为平衡性调整会使树根发生改变，所以
							//老根节点的孩子指针应该指向新根节点
							AVLNode<T>* pParentPoint = nullptr;
							slinkobj.GetTop(pParentPoint); //拿到老根的父节点，一定会取得成功，因为栈不为空
							//判断让老根父节点（pParentPoint)的左孩子指针还是右孩子指针指向新根(parent)
							if (pParentPoint->data > parent->data)
								pParentPoint->leftChild = parent;
							else
								pParentPoint->rightChild = parent;
						}						
						
						break; //最小平衡子树调整完成后，其他不平衡节点自然会恢复平衡，所以不需要再向上调整，这里直接break;
					}
					//比如某个节点A有个左子树B1，所有其平衡因子为1，现在如果给其增加一个右子树B2，其平衡因子变为0。
					//此时不要再继续向上调整节点A的父的平衡因子了，否则会把A父亲的平衡因子调整错误。
					else if (parent->balfac == 0)
					{
						//已经平衡，不需要继续回溯调整
						break;
					}
					else
					{
						point = parent; //让point指向父接待你，后续parent的新值要从栈顶获取
					} //end if (parent->balfac < -1 || parent->balfac > 1)
				} //end if (slinkobj.Pop(parent) == true) 
			} //end while (slinkobj.Empty() != true)

		}

		//右旋转（LL插入导致失衡）
		void RotateRight(AVLNode<T>*& pointer) //注意参数类型
		{
			AVLNode<T>* childRight = pointer; //pointer是“最小不平衡子树”的根节点，即 失衡的节点A
			pointer = childRight->leftChild;  //新根（节点B） = 老根（节点A）的左孩子节点
			childRight->leftChild = pointer->rightChild; //如果节点B原来有右孩子，则首先将节点B这个右孩子作为节点A的左孩子
			pointer->rightChild = childRight; //将失衡的节点A作为节点B的右孩子

			//需要变动的 平衡因子的处理，其他节点平衡因子不改变，不需要处理
			pointer->balfac = childRight->balfac = 0; //节点A和节点B的平衡因子恢复为0.
		}

		//左旋转（RR插入导致失衡）
		void RotateLeft(AVLNode<T>*& pointer) //注意参数类型
		{
			AVLNode<T>* childLeft = pointer; //point是“最小不平衡子树”的根接单，即失衡的节点A
			pointer = childLeft->rightChild; //新根（节点B:70） = 老根（节点A：40）的右孩子节点。
			childLeft->rightChild = pointer->leftChild; //如果节点B原来有左孩子，则首先将节点B这个左孩子作为节点A的右孩子。
			pointer->leftChild = childLeft; //将失衡的节点A作为节点B的左孩子

			//需要变动的 平衡因子的处理，其他节点的平衡因子不需要处理
			pointer->balfac = childLeft->balfac = 0;//节点A和节点B的平衡因子恢复为0
		}

		//先左后右旋转（LR插入导致失衡）
		void RotateLeftRight(AVLNode<T>*& pointer)
		{
			//给值，让各个变量指向不同节点
			AVLNode<T>* childRight = pointer; //pointer是“最小不平衡子树”的根节点，即失衡的节点A。
			AVLNode<T>* childLeft = childRight->leftChild;  //节点B = 节点A的左孩子节点

			pointer = childLeft->rightChild; //节点C，就是节点B的右孩子，也是最终 先左后右旋转后的新根

			//进行左旋转
			childLeft->rightChild = pointer->leftChild; //如果节点C原来有左孩子，则将这个左孩子变成节点B的右孩子。
			pointer->leftChild = childLeft; //节点B（childLeft)变成了其原右孩子（节点C：pointer）的左孩子

			//节点B的平衡因子会改变，这主要取决于节点C原来带的是左孩子还是右孩子（或说取决于节点C的平衡因子）
			if (pointer->balfac >= 0) //原来带的是左孩子
				childLeft->balfac = 0; //因为节点C带的左孩子刚好成了节点B的右孩子，节点B原来有个左孩子，所以现在节点B平衡了。
			else //节点C没带左孩子
				childLeft->balfac = 1; //节点B只有一个左孩子，所以节点B平衡因子为1.

			//进行上述左旋转后，新的节点B其实已经是pointer了。而且此时节点C（新根）的平衡因子还保持为老值（1或者-1）；

			//再进行右旋转
			childRight->leftChild  = pointer->rightChild; //如果节点C原来有右孩子，则将这个右孩子变成节点A的左孩子。
			pointer->rightChild = childRight; //将失衡的节点A向右侧旋转作为 新 节点B（pointer)的右孩子。
			if (pointer->balfac == 1) //新节点B原来带的是左孩子 			
				childRight->balfac = -1; //节点A原来有个右孩子，所以节点A平衡因子变成-1。			
			else
				childRight->balfac = 0; //新节点B没带孩子或者带右孩子，这个右孩子会挂到节点A上当左孩子，所以节点A平衡因子变为0.

			//根节点（新节点B）的平衡因子做种调整为0
			pointer->balfac = 0;
		}

		//先右后左旋转（RL插入导致失衡），参考RotateLeftRight书写
		void RotateRightLeft(AVLNode<T>*& pointer)
		{
			AVLNode<T>* childLeft = pointer; //60节点
			AVLNode<T>* childRight = childLeft->rightChild; //120
			pointer = childRight->leftChild; //95

			//进行右旋转
			childRight->leftChild = pointer->rightChild; //120的左孩子设置为100
			pointer->rightChild = childRight; //95的右孩子指向120
			//调整120的平衡因子
			if (pointer->balfac <= 0) //如果95的平衡因子是0，-1（95不带孩子或者带右孩子）
				childRight->balfac = 0; //120的平衡因子就是0
			else //节点95带左孩子
				childRight->balfac = -1; //120的平衡因子是-1

			//再进行左旋转
			childLeft->rightChild = pointer->leftChild; //60的右孩子指向65
			pointer->leftChild = childLeft; //95的左孩子指向60
			//调节60的平衡 因子
			if (pointer->balfac == -1) //如果95的平衡因子是-1（95带右子树）
				childLeft->balfac = 1;
			else //节点95不带子树或者带左子树
				childLeft->balfac = 0;

			pointer->balfac = 0; //95这个节点的平衡因子设置为0
		}

		//中序遍历
		void inOrder()
		{
			inOrder(root);
		}
		void inOrder(AVLNode<T>* tNode)
		{
			if (tNode != nullptr)
			{
				//左根右顺序
				inOrder(tNode->leftChild);
				cout << tNode->data << " ";
				inOrder(tNode->rightChild);
			}
		}


	private:
		void ReleaseNode(AVLNode<T>* pnode)
		{
			if (pnode != nullptr)
			{
				ReleaseNode(pnode->leftChild);
				ReleaseNode(pnode->rightChild);
			}
			delete pnode;
		}
	private: 
		AVLNode<T>* root; //树根指针
	};
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//第3章 树
	//第二节  二叉树
	//（10）平衡二叉树（Balanced Binary Tree）:平衡二叉搜索树，简称AVL树（平衡树），Adelson-Velsky   Landis。
	//（10.1）基本概念、定义及基础实现代码
	//平衡二叉树，首先是一棵二叉查找树，在构建这棵二叉查找树的过程中进行平衡化的处理形成二叉平衡树
	 //性质：a)他的左子树和右子树都是平衡二叉树。b)任一节点的左子树和右子树的高度之差不超过1.
	//引入平衡因子BF（Balance Factor)概念：该节点的左子树高度减去他的右子树高度（或右子树高度减去左子树高度）。
	  //那么作为一棵平衡二叉树上任一节点的平衡因子只能是-1、0、1三个值中的一个。即：
		//节点的平衡因子 = 左子树高度 - 右子树高度。
	//（10.2）平衡二叉树插入操作后的平衡性调整及实现代码
	//插入和删除两种操作会改变平衡二叉树的平衡性
	//最小不平衡子树：这里将以节点70为根的这棵需要进行平衡性调整的子树称为“最小不平衡子树”。
	 //只要将最小不平衡子树进行平衡性调整（高度复原），整个二叉查找树就会恢复平衡。
	//平衡性调整时对二叉树进行“旋转”操作来达成的。
	//四种旋转方式：前两种方式称为“单旋转”。后两种方式称为“双旋转”。
		//a)左旋转   b)右旋转     c)先左后右旋转    d)先右后左旋转
	//对于最小不平衡子树（将该子树命名为A）的产生又分为四种情况：
	   //a)在A的“左孩子的左子树”中插入节点导致A不平衡（简称LL：L代表Left）。此时需要通过“右旋转”调整平衡。
	   //b)在A的“右孩子的右子树”中插入节点导致A不平衡（简称RR：R代表Right）。此时需要通过“左旋转”调整平衡。
	   //c)在A的“左孩子的右子树”中插入节点导致A不平衡（简称LR）。此时需要通过“先左后右旋转”调整平衡。
	   //d)在A的“右孩子的左子树”中插入节点导致A不平衡（简称RL）。此时需要通过“先右后左旋转”调整平衡。
	
	//（1）在A的“左孩子的左子树”中插入节点导致A不平衡（简称LL：L代表Left）。
	//如何通过右旋转（左边长了就向右转）让最小不平衡子树恢复平衡？
	    //将失衡的节点A（95）也就是最上边这个失衡的节点向 右侧旋转来作为节点B（60）的右孩子
	     // （当然，如果节点A有右孩子则该右孩子也要跟着节点A一起旋转），如果节点B原来有右孩子，
	     //则首先将节点B这个右孩子作为节点A的左孩子。
	//几个结论：
	//a)插入新节点导致失衡前 这个子树有多高，调整平衡后这个树就会恢复为多高。
	//b)将一棵最小不平衡子树进行平衡性调整后，会发现这棵调整后的子树的根的平衡因子变为0.
	//c)从写程序的角度来看，当插入一个新节点导致原来平衡二叉树失衡后：
	  //c.1)新插入的节点平衡因子自然是0（因为新插入的节点肯定是叶子节点）
	  //c.2)沿着新插入的节点向上逐个找寻父节点并调整父节点的平衡因子，。。。
	//（2）在A的“右孩子的右子树”中插入节点导致A不平衡（简称RR）
	//如何通过左旋转（右边长了就向左转）让最小不平衡子树恢复平衡？
		//将失衡的节点A（40）也就是最上边的这个失衡的节点向左侧旋转来作为节点B（70）的左孩子。
		  //（当然，如果节点A有左孩子则该左孩子也要跟着节点A一起旋转），如果节点B原来有左孩子，
		  //则首先将节点B这个左孩子作为节点A的右孩子。	 
	//（3）在A的“左孩子的右子树”中插入节点导致A不平衡（LR）
	//如何通过先左后右旋转让最小不平衡子树恢复平衡
		//（3.1）将节点B（节点60)也就是从上向下数第二行的节点向左侧旋转让其向左下方下落（如果节点B有左孩子则该左孩子也要跟着节点B一起旋转）。
			//那么节点B的右子树（以70为根，可以成70这个节点为节点C）就被提起来顶替了节点B的位置。
			//得到的效果就是节点B（节点60）变成了其原右孩子（节点的70）的左孩子。
				//a）如果节点C（节点70）原来有左孩子，则将这个左孩子变成节点B（节点60）的右孩子。
				//b）如果节点C（节点70）原来有右孩子，则将这个右孩子跟着70一起旋转。
		//（3.2）将失衡的节点A（节点95）也就是最上边这个失衡的节点向右侧旋转来作为新节点B（节点70）的右孩子。
				//a)如果节点70原来有右孩子，则将这个右孩子变成95的左孩子。
				//b)如果节点95原来有右孩子，则这个右孩子要跟着95一起旋转。

	//（4）在A的“右孩子的左子树”中插入节点导致A不平衡（RL）
	//如何通过先右后左旋转让最小不平衡子树恢复平衡
		//（4.1）将节点B（节点120）也就是从上向下数第二行的节点向右侧旋转让其向右下方下落（如果（如果节点B有右孩子则该右孩子也要跟着节点B一起旋转）。
			//那么节点B的左子树（以95为根，可以称95这个节点为节点C）就被提起来顶替了节点B的位置。
			//得到的效果就是节点B（节点120）变成了其原左孩子（节点95）的右孩子。
				//a)如果节点C（节点95）原来有左孩子，则这个左孩子要跟着节点95一起旋转。
				//b)如果节点C（节点95）原来有右孩子，则将这个右孩子变成了节点B（节点120）的左孩子。
		//（4.2）将失衡的节点A（节点60）也就是岁上边这个失衡的节点向左旋转来作为新节点B（节点95）的左孩子。
				//a)如果节点95原来有左孩子，则将这个左孩子变成节点60的右孩子。
				//b)如果节点60原来有左孩子，则这个左孩子要跟着节点60一起旋转。
	//给出一组数字以供大家进行综合测试：
	 //这组数据大概会进行7次平衡性调整，分别是LL,LR,LL,RL,RR,RL,LL
	//int array[] = {12,4,1,3,7,8,10,9,2,11,6,5};

	 

				




	_nmsp1::AVLTree<int> mybtr;

	/*
	//测试右旋转用到的数据
	int array[] = { 95,60,120,40,20 };
	int acount = sizeof(array) / sizeof(int);
	for (int i = 0; i < acount; ++i)
	{
		mybtr.InsertElem(array[i]);
	}
	*/

	//测试左旋转用到的数据
	//int array[] = { 40,20,60,95,120 };

	/*
	//测试先左后右旋转用到的数据
	int array[] = { 95,60,120,40,50 };

	int acount = sizeof(array) / sizeof(int);
	for (int i = 0; i < acount; ++i)
	{
		mybtr.InsertElem(array[i]);
	}
	*/
	//测试先右后左旋转用到的数据
	int array[] = { 60,40,70,120,95 };
	int acount = sizeof(array) / sizeof(int);
	for (int i = 0; i < acount; ++i)
	{
		mybtr.InsertElem(array[i]);
	}
		
	mybtr.inOrder();



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




