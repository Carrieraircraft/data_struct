// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//公众号：程序员速成 ，内含一辈子都让你感激自己的优质视频教程，欢迎关注

#include <iostream>
#include <iomanip>

#pragma warning (disable: 4996) 
using namespace std;

//求得最大数组内容及和值
class  CMaxSubArraySum
{
public:
	//暴力计算法
	void Calc1()
	{
		//下标：     0 1  2 3  4 5 6  7 8
		int a[] = { -2,1,-3,4,-1,2,1,-5,4 };
		int aelmcount = sizeof(a) / sizeof(int); //求数组元素个数。
		
		//初始化一些值
		int iCurrMaxHe = INT_MIN; //记录当前最大和值
		int iCurrStartIdx; //记录当前最大和值开始的元素下标
		int iCurrEndIdx;//记录当前最大和值结束的元素下标

		int iHe, iMaxHe; //记录当前和值和最大和值
		int iPosi = 0;
		for (int icurridx = 0; icurridx < aelmcount; ++icurridx)
		{
			iMaxHe = iHe = a[icurridx];
			for (int j = icurridx + 1; j < aelmcount; ++j)
			{
				iHe += a[j];
				if (iHe > iMaxHe)
				{
					iMaxHe = iHe; //记录最大和值
					iPosi = j;//记录和最大的这个元素对应的下标
				}
			} //end for j

			//当前值更大，可以采用
			if (iCurrMaxHe < iMaxHe)
			{
				iCurrMaxHe = iMaxHe; //当前最大和值
				iCurrStartIdx = icurridx; //当前最大和值开始的元素下标
				iCurrEndIdx = iPosi; //当前最大和值结束的元素下标
			}
		} //end for icurridx

		//输出结果
		cout << "该子数组的最大和值为 " << iCurrMaxHe << endl;
		cout << "该子数组的内容为：";
		for (int i = iCurrStartIdx; i <= iCurrEndIdx; ++i)
		{
			cout << a[i] << "  ";
		}
		cout << endl;
	}

	//求取最大和值
	//tmpresultleft：保存最大和值开始的元素下标
	//tmpresultright：保存最大和值结束的元素下标
	int maxSumRec(int a[], int left, int right, int& tmpresultleft, int& tmpresultright)
	{
		if (left >= right)
		{			
			tmpresultleft = left;
			tmpresultright = right;
			return a[left]; //递归出口
		}

		int resultidx1left, resultidx1right;
		int resultidx2left, resultidx2right;
		int resultidxleft, resultidxright;
		int mid = (left + right) / 2; //中间分开
		int maxLeftSum = maxSumRec(a, left, mid, resultidx1left, resultidx1right); //对左半部分求最大和值
		int maxRightSum = maxSumRec(a, mid + 1, right, resultidx2left, resultidx2right); //对右半部分求最大和值
		
		//求跨边界和，以mid为中心分别向两边计算最大和值
		//a)先计算mid到left的最大和值保存到下面的Kua_Left_Bound_MaxHe
		int Kua_Left_Bound_MaxHe;
		int itmpHe;
		for (int i = mid; i >= left; --i)
		{
			if (i == mid)
			{
				resultidxleft = i;
				Kua_Left_Bound_MaxHe = a[i];
				itmpHe = Kua_Left_Bound_MaxHe;
			}
			else
			{
				itmpHe += a[i];
			}

			if (itmpHe > Kua_Left_Bound_MaxHe)
			{
				resultidxleft = i;
				Kua_Left_Bound_MaxHe = itmpHe;
			}
		} //end for i
		//b)再计算mid+1到right的最大和值
		int Kua_Right_Bound_MaxHe;
		for (int i = mid + 1; i <= right; ++i)
		{
			if (i == mid + 1)
			{
				resultidxright = i;
				Kua_Right_Bound_MaxHe = a[i];
				itmpHe = Kua_Right_Bound_MaxHe;
			}
			else
			{
				itmpHe += a[i];
			}

			if (itmpHe > Kua_Right_Bound_MaxHe)
			{
				resultidxright = i;
				Kua_Right_Bound_MaxHe = itmpHe;
			}
		} //end for i

		//现在就看maxLeftSum、maxRightSum、Kua_Left_Bound_MaxHe+Kua_Right_Bound_MaxHe三者谁大了
		int iMax = maxLeftSum;
		tmpresultleft = resultidx1left;
		tmpresultright = resultidx1right;
		if (iMax < maxRightSum)
		{
			iMax = maxRightSum;
			tmpresultleft = resultidx2left;
			tmpresultright = resultidx2right;
		}
		if (iMax < (Kua_Left_Bound_MaxHe + Kua_Right_Bound_MaxHe))
		{
			iMax = Kua_Left_Bound_MaxHe + Kua_Right_Bound_MaxHe;
			tmpresultleft = resultidxleft;
			tmpresultright = resultidxright;
		}

		//显示必要信息辅助理解begin--------------------
		//setw和setfill用于输出的数字宽度保持一致，注意#include <iomanip>
		cout << "maxSumRec():left,mid,right|ml,mr,mb=" << left
			<< "," << mid << "," << right << "|" <<
			setw(2) << setfill(' ') << maxLeftSum << "," <<
			setw(2) << setfill(' ') << maxRightSum << "," <<
			setw(2) << setfill(' ') << (Kua_Left_Bound_MaxHe + Kua_Right_Bound_MaxHe);
		cout << "|元素值：";
		for (int i = left; i <= right; ++i)
		{
			cout << setw(2) << setfill(' ');
			cout << a[i] << " ";
			if (i != right)
				cout << ",";
		}
		cout << endl; //换行
		//显示必要信息辅助理解end--------------------
		return iMax;
	}

	//分治算法实现计算最大数组连续子序列
	void CalcDaC()
	{
		//下标：     0 1  2 3  4 5 6  7 8
		int a[] = { -2,1,-3,4,-1,2,1,-5,4 };
		int aelmcount = sizeof(a) / sizeof(int); //求数组元素个数。
		int resultidxleft, resultidxright;
		int lastresult = maxSumRec(a, 0, aelmcount - 1, resultidxleft, resultidxright);
		cout << "该子数组的最大和值为 " << lastresult << endl;
		cout << "该子数组的内容为：";
		for (int i = resultidxleft; i <= resultidxright; ++i)
		{
			cout << a[i] << "  ";
		}
		cout << endl;
	}

};

int main()
{	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

	//第8章 算法设计方法
	//第二节  分治算法(Divide and Conquer Algorithm):分而治之
	//（1）分治算法案例——粗暴法求最大数组连续子序列和值
	//{-2,1,-3,4,-1,2,1,-5,4}
	//（2）分治算法案例——分治法求最大数组连续子序列和值




	/*CMaxSubArraySum myobj;
	myobj.Calc1();*/


	CMaxSubArraySum myobj;
	myobj.CalcDaC();

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



