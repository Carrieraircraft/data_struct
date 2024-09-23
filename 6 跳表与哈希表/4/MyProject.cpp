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

#define MAX_HASHTBLSIZE 37  //哈希表最大长度，素数保证分布尽量均匀

//每个节点的定义
template <typename T>
struct ListNode
{
	T   data; //数据
	ListNode<T>* next; //指针
};

//哈希表定义
template <typename T>
class myHashTbl
{
public:
	myHashTbl()//构造函数
	{
		for (int i = 0; i < MAX_HASHTBLSIZE; ++i)
		{
			m_bucketArray[i] = nullptr;
		} //end for
	}
	~myHashTbl() //析构函数
	{
		for (int i = 0; i < MAX_HASHTBLSIZE; ++i)
		{
			if (m_bucketArray[i] == nullptr)
				continue;

			ListNode<T>* pnode = m_bucketArray[i];
			ListNode<T>* ptmp;
			while (pnode != nullptr)
			{
				ptmp = pnode;
				pnode = pnode->next;
				delete ptmp;
			}
		} //end for
	}

	//增加元素
	void add(T key)
	{
		int idx = key % MAX_HASHTBLSIZE; //除留取余法，先得到桶的位置
		if (IfInBucket(m_bucketArray[idx], key)) //检查链表中是否已经存在该键，如果存在，则什么不做
			return;

		//创建节点
		ListNode<T>* tempnode = new ListNode<T>;
		tempnode->data = key; //这里只是把键插入到哈希表中，如果想让程序变得更实用，可以改造代码来插入各种数据到哈希表中
		
		//头插法
		tempnode->next = m_bucketArray[idx];
		m_bucketArray[idx] = tempnode;
	}

	//在哈希表中查找指定键
	bool Find(T key)
	{
		int idx = key % MAX_HASHTBLSIZE; //除留取余法，先得到桶的位置
		bool bfind = IfInBucket(m_bucketArray[idx], key);
		if (bfind == true)
		{
			cout << "在下标为[" << idx << "]的桶中找到了元素" << key << endl;
		}
		else
		{
			cout << "没有找到元素" << key << endl;
		}
		return bfind;
	}

	//从哈希表中删除key代表的项
	void Delete(T key)
	{
		int idx = key % MAX_HASHTBLSIZE;

		if (m_bucketArray[idx] == nullptr) //空桶
			return;

		ListNode<T>* parent = nullptr;
		ListNode<T>* tempnode = m_bucketArray[idx];
		while (tempnode != nullptr)
		{
			if (tempnode->data == key) 
			{
				if (parent == nullptr) //桶中第一个元素就是要找的元素
					m_bucketArray[idx] = tempnode->next;
				else			
					parent->next = tempnode->next;

				delete tempnode;
				break;
			}
			parent = tempnode;
			tempnode = tempnode->next;
		} //end while
		return;
	}

	//判断是否某个key在桶中
	bool IfInBucket(ListNode<T>* head, T key)
	{
		ListNode<T>* tempnode = head;
		while (tempnode)
		{
			if (tempnode->data == key)
				return true;
			tempnode = tempnode->next;
		}
		return false;
	}

	//输出哈希表中元素
	void DispHashList()
	{
		cout << "--------------begin-----------" << endl;
		for (int i = 0; i < MAX_HASHTBLSIZE; ++i)
		{
			if (m_bucketArray[i] == nullptr)
			{
				cout << "[桶下标]:" << i << "]= nullptr" << endl;
				continue;
			}
			cout << "[桶下标:" << i << "]= ";
			ListNode<T>* p = m_bucketArray[i];
			while (p != nullptr)
			{
				cout << p->data << " ";
				p = p->next;
			}
			cout << endl; //换行
		} //end for
		cout << "--------------end-----------" << endl;
	}

private:
	ListNode<T>* m_bucketArray[MAX_HASHTBLSIZE];
};

int main()
{	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//第二节 哈希表 / 散列表（Hash Table）
	//（1）基本概念
	//数组的一种扩展。对查找性能要求高，查找的数据之间彼此没有关系的场合非常合适。

	//根据商品名称获取商品价格。
	//哈希函数，也叫散列函数/杂凑函数。 根据输入数据，生成一个整数。
	 //通过哈希函数，实现了数据（关键字）到存储位置的一对一映射关系。
	//关键字/键（key）：苹果，猕猴桃：用来标识一件商品。
	//哈希函数/散列函数：把键转化为数组下标的函数。
	//哈希值：执行哈希函数得到的数值成为哈希值/散列值/Hash值。

	//（2）哈希函数、哈希算法简介
	//哈希函数设计要求：a)计算结果为非负整数。b)输入参数相同，返回的哈希值应该是相同的整数。
	    //c)输入参数不同，那么返回的哈希值是不同的整数。
	//哈希算法：将任意长度的二进制值映射为较短的固定长度的二进制值（哈希值），这个映射规则就是哈希算法。
	//一般来说：
		//哈希算法应该得到单向哈希值。
		//原始数据哪怕只修改一点，那么得到的哈希值也会大不相同。
	    //生成的哈希值要尽可能随机且均匀分布。 哈希冲突。
		//算法不能太复杂，执行效率要高。

	//哈希函数设计方法：
	//直接定址法： HashFunc(Key) = a *Key +b。
	//除留取余法：最常用的构造哈希函数的方法。 HashFunc(Key) = key % p
	//数字分析法：
	//平方取中法：取关键字的平方值的中间几位作为哈希值。
	//折叠法：

	//设计/采用哈希函数要考虑的因素：计算时间、关键字长度、哈希表尺寸、关键字分布情况、记录查找频率。
	//hash_set，hash_map,hash_multiset,hash_multimap
	//unordered_set(bucket_count()、bucket_size()),unordered_map,unordered_multimap

	//解决哈希冲突的方法
	//a)链表法/拉链法/链地址法（Chaining）
	//b)开放地址/开放寻址/开放定址法（Open Addressing）:如果哈希冲突，就重新寻找一个空闲位置并将数据插入。
		//如何重新寻找一个空闲位置：
		//a)线性探测法（Linear Probing）,最坏情况下，插入、删除、查询时间复杂度会达到O(n)。
		//b)二次探测法（Quadratic probing）：
		//c)双哈希法（Double hashing）/再哈希法/再散列法
		//d)伪随机序列法（Pseudorandom sequence）。
	//适合数据量比较小的情形。
	//c)公共溢出区法（Public Overflow Area)

	//（3）哈希函数算法效率分析
	//装载因子/装填因子（load factor）：表示哈希表中空闲位置的多少。
	 //哈希表的装载因子 = 哈希表中元素个数/哈希表的长度
	//将扩容操作耗费的时间均摊到多次插入操作中。
	//缩容。
	//总结：查询O(1)。扩容或者搬移O(n)。
			//插入：O(1)。

	//（4）哈希表实现源码
	//（5）哈希算法的主要应用领域
	// MD5哈希算法的特点：
	//    a)哈希冲突肯定存在。
	//    b)哪怕对原始数据微小的修改，得到的哈希值也会很不同
	//    c)很难通过md5后的信息反推出原始数据信息。
	//哈希算法应用范围：
	//(1)安全加密领域
		//MD5：MD5信息摘要算法——MD5 Message-Digest Algorithm
		//SHA：安全散列算法
	//(2)唯一标识
	//摘要信息
	//(3)数据校验,确定两个文件内容是否完全相同。

	//负载均衡、数据分片、分布式存储。




	myHashTbl<int> myhashtbl;
	for (int i = 0; i < 100; ++i)
	{
		myhashtbl.add(i);
	}
	myhashtbl.DispHashList();
	myhashtbl.Find(24);

	for (int i = 100; i >= 13; --i)
	{
		myhashtbl.Delete(i);
	}
	myhashtbl.Find(24);
	myhashtbl.DispHashList();

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



