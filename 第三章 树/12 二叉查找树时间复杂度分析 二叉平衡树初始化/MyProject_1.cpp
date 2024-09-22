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

//------------------------------
namespace _nmsp1
{
	template <typename KEY> //KEY代表键（key）的类型，比如可以是一个int类型
	struct ObjType
	{
		KEY key; //关键字
		//......其他各种必要的数据字段
		//....
	};


	//树中每个节点的定义
	template <typename T> //T代表数据元素的类型
	struct BinaryTreeNode
	{
		T   data;
		BinaryTreeNode* leftChild,  //左子节点指针
			* rightChild;  //右子节点指针
	};

	//二叉查找树的定义
	template <typename T>
	class BinarySearchTree
	{
	public:
		BinarySearchTree() //构造函数
		{
			root = nullptr;
		}
		~BinarySearchTree() //析构函数
		{
			ReleaseNode(root);
		}

		//二叉树中序遍历代码（排序），方便测试时显示节点数据
		void inOrder()
		{
			inOrder(root);
		}
		void inOrder(BinaryTreeNode<T>* tNode)
		{
			if (tNode != nullptr)
			{
				//左根右
				inOrder(tNode->leftChild);
				cout << tNode->data << " ";
				inOrder(tNode->rightChild);
			}
		}

		//插入元素
		void InsertElem(const T& e) //不可以指定插入位置，程序内部会自动确定插入位置
		{
			InsertElem(root, e);
		}
		void InsertElem(BinaryTreeNode<T>*& tNode, const T& e) //注意第一个参数类型
		{
			if (tNode == nullptr) //空树
			{
				tNode = new BinaryTreeNode<T>;
				tNode->data = e;
				tNode->leftChild = nullptr;
				tNode->rightChild = nullptr;
				return;
			}
			if (e > tNode->data)
			{
				InsertElem(tNode->rightChild, e);
			}
			else if (e < tNode->data)
			{
				InsertElem(tNode->leftChild, e);
			}
			else
			{
				//要插入的数据与当前树中某节点数据相同，则不允许插入
				//什么也不做
			}
			return;
		}

		//查找某个节点
		BinaryTreeNode<T>* SearchElem(const T& e)
		{
			return SearchElem(root, e);
		}
		/*
		//递归方式实现查找某个节点
		BinaryTreeNode<T>* SearchElem(BinaryTreeNode<T>* tNode, const T& e)
		{
			if (tNode == nullptr)
				return nullptr;

			if (tNode->data == e)
				return tNode;
			if (e < tNode->data)
				return SearchElem(tNode->leftChild,e); //在左子树上左查找
			else
				return SearchElem(tNode->rightChild,e); //在右子树上左查找
		}
		*/
		//非递归方式实现查找某个节点
		BinaryTreeNode<T>* SearchElem(BinaryTreeNode<T>* tNode, const T& e)
		{
			if (tNode == nullptr)
				return nullptr;

			BinaryTreeNode<T>* tmpnode = tNode;
			while (tmpnode)
			{
				if (tmpnode->data == e)
					return tmpnode;

				if (tmpnode->data > e)
					tmpnode = tmpnode->leftChild;
				else
					tmpnode = tmpnode->rightChild;
			}
			return nullptr;		
		}

		//删除某个节点
		void DeleteElem(const T& e)
		{
			return DeleteElem(root, e);
		}
		void DeleteElem(BinaryTreeNode<T>*& tNode, const T& e)//注意第一个参数类型
		{
			/*
			if (tNode == nullptr)
				return;

			if (e > tNode->data)
			{
				DeleteElem(tNode->rightChild, e);
			}
			else if (e < tNode->data)
			{
				DeleteElem(tNode->leftChild, e);
			}
			else
			{
				//找到了节点，执行删除操作
				if (tNode->leftChild == nullptr && tNode->rightChild == nullptr) //要删除的节点左右子树都为空（叶节点）
				{
					//即将被删除的节点的左右孩子都为空 
					BinaryTreeNode<T>* tmpnode = tNode;
					tNode = nullptr; //这个实际上就是让指向该节点的父节点指向空
					delete tmpnode;
				}
				else if (tNode->leftChild == nullptr) //其实这个else if可以和上个if代码合并，这里为了看的清晰就不合并了
				{
					//即将被删除的节点左孩子为空（右孩子不为空）
					BinaryTreeNode<T>* tmpnode = tNode;
					tNode = tNode->rightChild;
					delete tmpnode;
				}
				else if (tNode->rightChild == nullptr)
				{
					//即将被删除的节点的右孩子为空（左孩子不为空）
					BinaryTreeNode<T>* tmpnode = tNode;
					tNode = tNode->leftChild;
					delete tmpnode;
				}
				else
				{
					//即将被删除的节点的左右孩子都不为空
					//(1)找到这个要删除节点的左子树的最右下节点
					BinaryTreeNode<T>* tmpparentnode = tNode; //tmpparentnode代表要删除的节点的父节点
					BinaryTreeNode<T>* tmpnode = tNode->leftChild; //保存要删除节点左子树的最右下节点
					while (tmpnode->rightChild)
					{
						tmpparentnode = tmpnode;
						tmpnode = tmpnode->rightChild;
					}//end while
					tNode->data = tmpnode->data;
					// 此时，tmpnode指向要删除节点左子树的最右下节点（也即是真正要删除的节点），
					  //tmpparentnode指向真正要删除的节点的父节点
					//(2)删除tmpnode所指向的节点（该接单是真正要删除的节点）
					if (tmpparentnode == tNode)
					{
						//此条件成立，表示上面while循环一次都没执行，也就意味着要删除节点左子树没有右孩子（但可能有左孩子）
						tNode->leftChild = tmpnode->leftChild; //让要删除节点的左孩子 指向 真正要删除节点的左孩子的左孩子
					}
					else
					{
						//此条件成立，表示上面while循环至少执行一次，这意味着要删除节点的左子树有1到多个右孩子，
							//但这个右孩子不可能再有右孩子【因为tmpnode指向的是最后一个右孩子】（最多只能有左孩子）
						tmpparentnode->rightChild = tmpnode->leftChild; //tmpnode不可能有右孩子，最多只可能有左孩子
					}
					//(3)把最右下节点删除
					delete tmpnode;
				}//end if
			}
			*/
			
			if (tNode == nullptr)
				return;

			if (e > tNode->data)
			{
				DeleteElem(tNode->rightChild, e);
			}
			else if(e <tNode->data)
			{
				DeleteElem(tNode->leftChild, e);
			}
			else
			{
				//找到了节点，执行删除操作
				if (tNode->leftChild != nullptr && tNode->rightChild != nullptr)
				{
					BinaryTreeNode<T>* tmpnode = tNode->leftChild; //保存要删除节点左子树的最右下节点
					while (tmpnode->rightChild)
					{
						tmpnode = tmpnode->rightChild;
					} //end while
					tNode->data = tmpnode->data;
					DeleteElem(tNode->leftChild, tmpnode->data); //递归调用，
					     //因为上述是要删除节点左子树（下的最右节点），所以这里第一个参数是leftChild
				}
				else
				{
					BinaryTreeNode<T>* tmpnode = tNode;
					if (tNode->leftChild == nullptr)
						tNode = tNode->rightChild;
					else
						tNode = tNode->leftChild;
					delete tmpnode;
				}
			}
		}

		//查找值最大节点
		BinaryTreeNode<T>* SearchMaxValuePoint()
		{
			return SearchMaxValuePoint(root);
		}
		BinaryTreeNode<T>* SearchMaxValuePoint(BinaryTreeNode<T>* tNode)
		{
			if (tNode == nullptr) //空树
				return nullptr;

			//从根开始往右侧找即可
			BinaryTreeNode<T>* tmpnode = tNode;
			while (tmpnode->rightChild != nullptr)
				tmpnode = tmpnode->rightChild;
			return tmpnode;
		}

		//查找值最小节点
		BinaryTreeNode<T>* SearchMinValuePoint()
		{
			return SearchMinValuePoint(root);
		}
		BinaryTreeNode<T>* SearchMinValuePoint(BinaryTreeNode<T>* tNode)
		{
			if (tNode == nullptr) //空树
				return nullptr;

			//从根开始往左侧找即可
			BinaryTreeNode<T>* tmpnode = tNode;
			while (tmpnode->leftChild != nullptr)
				tmpnode = tmpnode->leftChild;
			return tmpnode;
		}

		//找按中序遍历的二叉查找树中当前节点的前趋节点
		BinaryTreeNode<T>* GetPriorPoint_IO(BinaryTreeNode<T>* findnode)
		{
			if (findnode == nullptr)
				return nullptr;
			BinaryTreeNode<T>* prevnode = nullptr;
			BinaryTreeNode<T>* currnode = root; //当前节点，从根开始找
			while (currnode != nullptr)
			{
				if (currnode->data < findnode->data) //当前节点小
				{
					//（1）从一系列比当前要找的值小的节点中找一个值最大的当前趋节点
					//当前节点值比要找的 节点值小，所以当前节点认为有可能是前趋
					if (prevnode == nullptr)
					{
						//如果前趋节点还为空，那不防把当前节点认为就是前趋
						prevnode = currnode;
					}
					else //prevnode不为空
					{
						//既然是找前趋，那自然是找到比要找的值小的 一系列节点中 值最大的
						if (prevnode->data < currnode->data)
						{
							prevnode = currnode; //前趋节点自然是找一堆 比当前值小的 值中 最大的一个
						}
					}
					//(2)继续逼近要找的节点，一直到找到要找的节点，找到要找的节点后，要找的节点的左节点仍旧可能是前趋
					currnode = currnode->rightChild; //当前节点小，所以往当前节点的右子树转
				}
				else if (currnode->data > findnode->data) //当钱包节点值比要找的值大，所以当前节点肯定不会是要找值的前趋
				{
					//当前节点大，所以往当前节点的左子树转
					currnode = currnode->leftChild;
				}
				else // if (curnode->data == findnode->data)，这个else其实可以和上个else合并，但为了清晰，就不合并了
				{
					//当前节点值 就是要找的节点值，那么前趋也可能在当前节点的左子树中，所以往左子树转继续找看有没有更合适的前趋
					currnode = currnode->leftChild;
				}
			} //end while
			return prevnode;
		}
		//找按中序遍历的二叉查找树中当前节点的后继节点
		BinaryTreeNode<T>* GetNextPoint_IO(BinaryTreeNode<T>* findnode)
		{
			if (findnode == nullptr)
				return nullptr;

			BinaryTreeNode<T>* nextnode = nullptr;
			BinaryTreeNode<T>* currnode = root; //当前节点，从根开始找
			while (currnode != nullptr)
			{
				if (currnode->data > findnode->data) //当前节点大
				{
					//(1)从一系列比当前要找的值大的节点中找一个值最小的当后继节点
					//当前节点值比要找的 节点值大，所以当前节点认为有可能就是后继
					if (nextnode == nullptr)
					{
						//如果后继节点还为空，那不妨就把当前节点认为就是后继
						nextnode = currnode;
					}
					else //nextnode不为空
					{
						//既然是找后继，那自然是找到比要找的值大的一系列节点中值最小的
						if (nextnode->data > currnode->data)
						{
							nextnode = currnode; //后继自然是找一堆 比当前值大的 值中 最小的一个
						}
					}
					//(2)继续逼近要找的节点，一直到找到要找的节点，找到要找的节点后，要找的节点的右节点仍旧可能是后继
					currnode = currnode->leftChild; //当前节点大，所以往当前节点的左子树转
				}
				else if(currnode->data < findnode->data) //当前节点值比要找的值小，所以当前节点肯定不会是要找的值的后继
				{
					//当前节点小，所以往当前节点的右子树转
					currnode = currnode->rightChild;
				}

				else //if(currnode->data == findnode->data)
				{
					//当前节点值 就是要找的节点值，那么后继也可能在当前节点的右子树中，所以往右子树转继续找看有没有更合适的后继
					currnode = currnode->rightChild;
				}
			} //end while
			return nextnode;
		}

	private:
		void ReleaseNode(BinaryTreeNode<T>* pnode)
		{
			if (pnode != nullptr)
			{
				ReleaseNode(pnode->leftChild);
				ReleaseNode(pnode->rightChild);
			}
			delete pnode;
		}
	private:
		BinaryTreeNode<T>* root; //树根指针
	};


}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//第3章 树
	//第二节  二叉树
	//（9）二叉查找树（Binary Search Tree）：又名二叉搜索树(BST)，也称为二叉排序树（Binary Sort Tree）
	//（9.1）基本概念及定义
		//其存在的意义在于实现快速查找，当然也支持快速插入和删除
	//（9.2）常见操作
	//（9.2.1）插入操作
	//（9.2.2）查找操作
	//（9.2.3）删除操作
	//a：要删除的节点左右子树都为空（叶子节点），那么1)直接把这个节点删除；
												//2）指向该被删除节点的父节点的相应孩子指针设置为空。
	//b：要删除的节点的左子树为空或者右子树为空，那么1)把这个节点删除
			//更新指向该被删除节点的父节点的相应孩子指针，让该指针指向要删除节点的非空的子节点即可。
	//c：要删除的节点左子树和右子树都不为空，这种情况最复杂：
		//1：找到这个要删除的节点的左子树的最右下节点（也可以找到这个要删除节点的右子树的最左下节点）；
		//2：将该节点的值替换到要删除的节点上；
		//3：接着把刚刚找到的那个最右下节点删除即可。
	//（9.2.4）查找值最大的和值最小的节点操作
	//（9.2.5）找出中序遍历序列中当前节点的前趋和后继节点
	   //当前二叉查找树的前趋节点一定是比当前节点值小的一系列节点中节点值最大的。
	   //当前二叉查找树的后继节点一定是比当前节点值大的一系列节点中节点值最小的。
	//（9.3）实际应用说明
	//对象中的其他数据叫卫星数据
	//（9.4）二叉查找树如何存储重复节点
	//a)扩充二叉树的每个节点：把每个节点扩充成链表或者动态数组，这样每个节点就可以存储多个key值相同的数据
	//b)插入数据时，如果遇到相同的节点数据，就将该数据当做大于当前已经存在的节点的数据来处理，放入当前已经
	  //存在的节点的rightChild（当做小于，放入当前已经存在的节点的leftChild也可以）。
	//（9.5）二叉查找树时间复杂度分析
	//查找长度：在查找操作中，需要对比的节点次数称为查找长度。查找长度反映了查找操作的时间复杂度。
	//平均查找长度ASL（Average Search Length)，用于衡量整个二叉查找树的查找效率。
	 //ASL=(1*1 + 2*2 + 3*4) /7  = 2.42
	 //ASL=(1*1+2*1+3*1+4*1+5*1+6*1+7*1) / 7 = 4
	//查找节点失败时的平均查找长度又怎么计算？
	//ASL = (3*8) / 8 = 3
	//ASL = (1*1+2*1+3*1+4*1+5*1+6*1+7*2) / 8 = 4.375







	_nmsp1::BinarySearchTree<int> mybtr;
	int myarray[] = { 23,17,11,19,8,12 };
	int acount = sizeof(myarray) / sizeof(int);
	for (int i = 0; i < acount; ++i)
	{
		mybtr.InsertElem(myarray[i]);
	}
	mybtr.inOrder(); //中序遍历	

	int val = 19;
	cout << endl; //换行
	_nmsp1::BinaryTreeNode<int>* tmpp;
	tmpp = mybtr.SearchElem(val);
	if (tmpp != nullptr)
	{
		cout << "找到了值为：" << val << "的节点。" << endl;
	}
	else
	{
		cout << "没找到值为：" << val << "的节点。" << endl;
	}

	mybtr.DeleteElem(val);
	mybtr.inOrder();

	tmpp = mybtr.SearchElem(17);
	tmpp = mybtr.GetPriorPoint_IO(tmpp);


	_nmsp1::BinarySearchTree<_nmsp1::ObjType<int> > mybtr2;



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




