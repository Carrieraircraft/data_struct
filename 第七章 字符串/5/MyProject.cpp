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

	//求本串的next数组
	void getNextArray(int next[])
	{
		//next数组下标为0和为1的元素固定为0和1。其实next[0]里的值并没有用到。
		if (length < 1)
			return;

		//mext数组的前两个元素肯定是0和1
		if (length == 1) //只有一个字符
		{
			next[0] = 0;
			return;
		}

		next[0] = 0;
		next[1] = 1;

		if (length == 2)//只有两个字符
			return;

		//至少三个字符
		int nextarry_idx = 2; //当前要处理的next数组下标
		//int max_pub_zhui = 0; //最大公共前后缀包含的字符数量

		//循环的目的是给next数组赋值
		while (nextarry_idx < length)
		{
			int left_RMC_count = nextarry_idx; //如果当前字符与主串的字符不匹配，当前字符左侧有多少个字符
			int max_pub_zhui = left_RMC_count - 1; //最大公共前后缀包含的字符数量

			int start1idx = 0;
			int start2idx = left_RMC_count - max_pub_zhui;
			int xhtimes = max_pub_zhui; //循环次数

			//本循环的目的是获取最长公共前后缀长度，代码写法无固定方式，选择自己容易理解的方式写即可
			while (xhtimes > 0)
			{
				if (ch[start1idx] != ch[start2idx])
				{
					max_pub_zhui--;
					start1idx = 0;
					start2idx = left_RMC_count - max_pub_zhui;
					xhtimes = max_pub_zhui;
					continue;//要回去重新循环
				}
				else
				{
					start1idx++;
					start2idx++;
				}
				xhtimes--;
			} //end while (xhtimes > 0)

			next[nextarry_idx] = max_pub_zhui + 1; //如果公共前后缀长度为n，那么就需要用子串的第n+1个字符与主串当前位做比较
			nextarry_idx++;
		} //end while
		return;
	}


	//KMP模式匹配算法接口，返回子串中第一个字符在主串的下标，如果没找到子串，则返回-1
	//next：下一步数组（前缀表/前缀数组）
	//pos：从主串什么位置开始匹配子串，默认从位置0开始匹配子串
	int StrKMPIndex(const MySString& substr, int next[], int pos = 0)
	{
		if (length < substr.length) //主串长度还没子串长，那不可能找到
			return -1;

		int point1 = pos; //指向主串
		int point2 = 0; //指向子串

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
				//point1和point2两个指针的处理
				if (point2 == 0) //图7.5.3_1可以看到，下标0号位置子串的字符如果与主串字符不匹配则后序就要用子串的第1个字符（字符a）与主串的下一位（1号下标位）字符做比较
				{
					point1++; //主串指针指向下一位
				}
				else
				{
					//走到这个分支的，主串指针point1不用动，只动子串指针point2
					point2 = next[point2] - 1; //第这些个子串中的字符与主串当前位字符做比较
				}
			}
		} //end while
		if (substr.ch[point2] == '\0')
		{
			//找到了子串
			return point1 - point2;
		}
		return -1;
	}

	//求本串的next数组——典型的KMP算法求解next数组的代码写法
	void getNextArray_Classic(int next[])
	{
		//next数组下标为0和为1的元素固定为0和1。其实next[0]里的值并没有用到。
		if (length < 1)
			return;

		//mext数组的前两个元素肯定是0和1
		if (length == 1) //只有一个字符
		{
			next[0] = 0;
			return;
		}

		next[0] = 0;
		next[1] = 1;

		if (length == 2)//只有两个字符
			return;

		//至少三个字符
		int next_idx = 2;//需要求的next数组中下标为2的元素值
		int qz_tail_idx = 0; //前缀末尾位置
		while (next_idx < length)
		{
			if (ch[qz_tail_idx] == ch[next_idx - 1]) //next_idx-1代表后缀末尾位置
			{
				next[next_idx] = (qz_tail_idx + 1) + 1; //qz_tail_idx + 1就是前缀的宽度
				next_idx++;
				qz_tail_idx++;//前缀末尾位置：qz_tail_idx = next[next_idx-1] - 1;
			}
			else
			{
				qz_tail_idx = next[qz_tail_idx] - 1; //这句话是最难理解的

				//qz_tail_idx允许等于0，等于0有机会下次while时再比较一次，所以下面只判断qz_tail_idx < 0的情形
				if (qz_tail_idx < 0)
				{
					//没找到前缀
					qz_tail_idx = 0;
					next[next_idx] = 1;
					++next_idx;
				}
			}
		} //end while (next_idx < length)
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

	//第五节  串的KMP模式匹配算法
	//（1）朴素模式匹配算法的问题
	//D.E.Knuth, J.H.Morris ，V.R.Pratt。
	// 
	//（2）KMP模式匹配算法观察1
	// abbab
	//前缀  ，后缀，公共前后缀
	//最长公共前后缀
	// 
	//（3）KMP模式匹配算法观察2
	//a)如果下标为0的位置就和主串不匹配，则子串右移一个位置
	//b)如果下标为1的位置和主串不匹配，子串右移动了一个位置
	//c)如果下标为2的位置和主串不匹配，子串右移动了一个位置
	//d)如果下标为3的位置和主串不匹配，。。。。
	//e)如果下标为4的位置和主串不匹配，。。。。
	//f)如果下标为5的位置和主串不匹配，。。。。
	//g)如果下标为6的位置和主串不匹配，。。。。
	//h)如果下标为7的位置和主串不匹配，。。。。

	//“下一步数组”。next数组/前缀表/前缀数组
	//next数组存在的意义：指示当子串中某个位置的字符与主串相应位置字符不匹配时，
	   //应该将子串中的哪一位字符与主串中的当前位/下一位 字符做比较。
	 
	//（4）KMP模式匹配算法实现代码
	//主串S（point1），子串T（point2）
	//next[point2]含义：当S[point1] != T[point2]时，point2指针需要退到的位置（point2 = next[point2] - 1）。
	//a)当前next[15] = 8 ，如果T[7] == T[15],那么next[16] = next[15]+1 = 9；
	//b)当前next[7] = 4，如果T[3]==T[15]，那么next[16] = next[7]+1 = 5;
	//c)当前next[3] = 2，如果T[1]==TT[15]，那么next[16] = next[3]+1 = 3;
	//d)如果一直推到next[0] 这里，那么next[16] = 1，表示没有公共前后缀。
	// 
	//（5）KMP模式匹配算法性能分析
	//假设子串（模式串）长度为m，主串长度为n。
	//(a)求解next数组时间，时间复杂度O(m)。
	//(b)根据next数组在主串中寻找子串的时间,时间复杂度O(n)。
	//KMP算法时间复杂度O(m+n)。
	//KMP算法需要一个额外的next数组，因此空间复杂度O(m)。






	//KMP模式匹配算法接口，返回子串中第一个字符在主串中的下标，如果没找到子串，则返回-1
	//MySString mys13sub; //子串
	//mys13sub.StrAssign("ababaaababaa");
	//int* mynextarray = new int[mys13sub.length];
	//mys13sub.getNextArray(mynextarray); //获取next数组

	//MySString mys13master; //主串
	//mys13master.StrAssign("abbabbababaaababaaa");
	//                           //ababaaababaa
	//cout << "StrKMPIndex()结果为" << mys13master.StrKMPIndex(mys13sub, mynextarray) << endl;
	//delete[] mynextarray;
		

	MySString mys14sub; //子串
	mys14sub.StrAssign("ababaaababaa");
	int* mynextarray14 = new int[mys14sub.length];
	cout << "本次采用典型KMP算法求解next数组：---" << endl;
	mys14sub.getNextArray_Classic(mynextarray14); //获取next数组
	MySString mys14master; //主串
	mys14master.StrAssign("abbabbababaaababaaa");	                          
	cout << "StrKMPIndex()结果为" << mys14master.StrKMPIndex(mys14sub, mynextarray14) << endl;
	delete[] mynextarray14; //释放资源
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



