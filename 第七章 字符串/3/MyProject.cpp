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


////字符节点（串的链式存储）
//struct stringNode
//{
//	char ch[4];
//	stringNode* next; //指针域，指向下一个同类型（和本节点类型相同）节点
//};


#define MAX_LEN  250 //最大字符串长度（定长）

//采用定长数组存储结构
class MySString
{
public:
	MySString() //构造函数
	{
		ch[0] = '\0'; //字符串结束标记，其实'\0'就是数字0，所以ch[0] = 0;也没有问题
		length = 0; //字符串长度
	}

	//串赋值
	void StrAssign(const char* pcontent)
	{
		size_t iLen = strlen(pcontent);
		if (iLen >= MAX_LEN) //内容太长，容纳不下，字符串存储中要给字符串结束标记'\0'
			return;

		for (int i = 0; i < (int)iLen; ++i)
		{
			ch[i] = pcontent[i];
		}//end for
		ch[iLen] = '\0'; //设置字符串结束标记。该标记不计入字符串长度中
		length = iLen; //记录字符串长度
	}

	//串拷贝（串复制）
	void StrCopy(const MySString& tmpstr)
	{
		for (int i = 0; i < (int)tmpstr.length; ++i)
		{
			ch[i] = tmpstr.ch[i];
		}//end for
		length = tmpstr.length;
		ch[length] = '\0';
	}

	//判断空串
	bool IfStrEmpty()
	{
		if (ch[0] == '\0')
			return true;
		return false;
	}

	//串比较，比较其实就是逐个比较两个字符串中每个字符的ASCII码
	//结果：大于返回1，等于返回0，小于返回-1
	int StrCmp(const MySString& tmpstr)
	{
		if (length == 0 && tmpstr.length == 0) //两个字符串都是空的，相等
		{
			return 0;
		}

		const char* p1 = ch;
		const char* p2 = tmpstr.ch;

		int result = 0;
		while (*p1 != '\0' && *p2 != '\0')
		{
			result = (*p1) - (*p2);
			if (result != 0)
			{
				if (result > 0)
					return 1;
				else
					return -1;
			}
			p1++;
			p2++;
		}//end while

		if (*p1 == '\0' && *p2 == '\0') //长度相同并且内容相等
			return 0;

		//能走到下边的流程都是两个字符串一个长一个短，但长的和短的字符串前面内容相同，比如"ab"和"abc"
		if (*p1 == '\0') //p1小，因此长度少
			return -1;

		return 1;
	}

	//串连接
	bool StrCat(const MySString& tmpstr)
	{
		if (length + tmpstr.length >= MAX_LEN) //空间不够保存不下，这里直接返回false以通知开发者
			return false;

		int idx = 0;
		size_t i;
		for (i = length; i < (length + tmpstr.length); ++i)
		{
			ch[i] = tmpstr.ch[idx++];
		}
		ch[i] = '\0';
		length += tmpstr.length;
		return true;
	}

	//获取串的一部分内容（求子串）
	void SubString(MySString& resultstr, int pos, int len)//求得的子串给到resultstr。pos：从该位置开始【注意位置从0开始算】，截取len个字符
	{
		//注意pos位置从0开始计算
		if (pos <0 || (pos + 1)>length || len <= 0) //pos位置要合法，len长度值要合法
		{
			return;
		}
		int icount = 0;
		while (true)
		{
			resultstr.ch[icount] = ch[pos + icount];
			icount++;
			if (icount == len) //截取够数量了
				break;
			if (ch[pos + icount] == '\0') //到主串的末尾了，不够截取，截取多少算多少，直接跳出循环
				break;
		} //end while
		resultstr.length = icount;
		resultstr.ch[resultstr.length] = '\0';
		return;
	}

	//串插入
	//在当前串1的pos位置（从0开始计算），插入子串substr
	void StrInsert(int pos, const MySString& substr)
	{
		if (pos < 0 || pos > length) //插入位置不合法
			return;

		if (length + substr.length >= MAX_LEN) //容纳不下插入的新内容呢，则直接返回
			return;

		//把原来的必须的内容向后挪动
		int i = (int)(length - 1);//i为int类型，这样就可以为负数，保证下面的这个for循环可以正确结束
		for (; i >= pos; --i)
		{
			ch[i + substr.length] = ch[i];
		}

		//把子串插入进来
		for (size_t i = 0; i < substr.length; ++i)
		{
			ch[pos + i] = substr.ch[i];
		}
		length += substr.length;
		ch[length] = '\0';
		return;
	}

	//串删除
	//在当前串的pos位置（从0开始计算），删除len个字符
	void StrDelete(int pos, int len)
	{
		//注意pos位置从0开始计算
		if (pos < 0 || (pos + 1) > length || len <= 0) //pos位置要合法，len长度值要合法
		{
			return;
		}
		if (pos + len > length)
		{
			//要删除的字符太多，串中没那么多可删的字符
			len = int(length - pos); //只能删除这么多
		}

		//把剩余的字符串挪位置（向左搬）
		for (int i = pos; i < length; ++i)
		{
			ch[i] = ch[i + len];
		}//end for
		length = length - len;
		ch[length] = '\0';
		return;
	}

	//串清空
	void StrClear()
	{
		ch[0] = '\0';
		length = 0;
		return;
	}

	//显示字符串内容
	void DispContent()
	{
		cout << ch << endl;
	}

	//朴素模式匹配算法接口，返回子串中第一个字符在主串中的下标，如果没有找到子串，则返回-1
	int StrIndex(const MySString& substr, int pos = 0)//默认从位置0开始匹配子串
	{
		if (length < substr.length) //主串还没子串长，那不可能找到
			return -1;

		int point1 = pos, point2 = 0;
		while (ch[point1] != '\0' && substr.ch[point2] != '\0')
		{
			if (ch[point1] == substr.ch[point2])
			{
				//两个指针都向后走
				point1++;
				point2++;
			}
			else
			{
				//两个指针都恢复到该恢复的位置
				point1 = point1 - point2 + 1;
				point2 = 0;
			}
		}//end while
		if (substr.ch[point2] == '\0')
		{
			//找到了子串
			return point1 - point2;
		}
		return -1;
	}

	//主串：abcdeabcde，把cd替换成mno，那么主串替换后变成abmnoeabmnoe
	//串替换，主串中遇到内容为substr1的子串，全部替换成substr2子串
	void StrReplace(const MySString& substr1, const MySString& substr2)
	{
		int idx = -1;
		int pos = 0;
		int addlength = int(substr2.length) - int(substr1.length);
		while (pos < length)
		{
			idx = StrIndex(substr1, pos);
			if (idx == -1)
				return; //不存在substr1这样的子串，无需替换直接返回

			//能否替换，取决于空间是否够
			if (addlength > 0)
			{
				//被替换的子串更长，要判断保存空间是否够
				if (length + addlength >= MAX_LEN)
					return; //空间不够，不能替换成新内容
			}

			StrDelete(idx, int(substr1.length)); //删除老子串
			StrInsert(idx, substr2); //插入新子串
			//位置应该向后走，跳过被替换的子串部分内容
			pos = idx + (int)(substr2.length);
		} //end while
		return;
	}

public:
	char ch[MAX_LEN]; //串内容。每个位置保存一个字符
	size_t length; //串实际长度，专门引入该变量保存，提高程序运行效率。
};


int main()
{	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口


	//第三节  串的链式存储结构
	//第四节  串的朴素模式匹配算法
	//abdecdefg  ，def：子串的定位操作通常称为串的模式匹配。子串也被称为模式串。
	//串的模式匹配算法比较多：朴素模式匹配算法（BF)，Rabin-Karp(RK)算法，KMP算法，Boyer-Moore(BM)算法，Sunday算法，Trie树，AC自动机等。
	//主讲：朴素模式匹配算法（BF)，KMP算法
	//朴素模式匹配算法（BF：Brute Force)：对主串的每个字符作为子串的开头与子串进行匹配。
	//匹配成功的最好情况时间复杂度为O(m),
	//匹配失败的最好情况时间复杂度为O(n)
	//匹配成功 / 失败的最坏情况时间复杂度为O(n * m)






	//朴素模式匹配算法接口，返回子串中第一个字符再主串中的下标，如果没找到子串，则返回-1
	MySString mys10, mys11;
	mys10.StrAssign("abdecdefg"); //主串
	mys11.StrAssign("def"); //子串
	cout << "StrIndex()结果为" << mys10.StrIndex(mys11) << endl;

	//串替换，主串中遇到内容为substr1的，全部替换为substr2
	MySString mys12, substr1, substr2;
	mys12.StrAssign("abcdeabcde");
	cout << "mys12替换前的结果为" << mys12.ch << endl;
	substr1.StrAssign("cd");
	substr2.StrAssign("mno");
	mys12.StrReplace(substr1, substr2);
	cout << "mys12替换后的结果为" << mys12.ch << endl;
		
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



