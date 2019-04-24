

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "student.h"
#include "sorttesthelper.h"
#include "algorithm.h"
#include <string>
#include <time.h>
 
using namespace std;


template<typename T>
class A
{
private:
	//归并排序
	void merge(T &arr[], int l, int mid, int r)
	{
		//int*aux=new int[r-l+1]();
		T aux[r - l + 1];
		for (int i = 0; i < r - l; i++)
		{
			aux[i] = arr[i];
		}
		int i = l, j = mid + 1;
		for (int k = 0; k < r - l; k++)
		{
			if (i > mid)
			{
				aux[k] = arr[j];
				j++;
			}
			else if (j > r)
			{
				aux[k] = arr[i];
				i++;
			}
			else if (arr[i] > arr[j])
			{
				aux[k] = arr[j];
				j++;
			}
			else
			{
				aux[k] = arr[i];
				i++;
			}
		}

	}
public:
	 
	void mergesort(T &arr[], int l, int r)
	{
		if (l >= r)
			return;
		int mid = (r + l) / 2;
		mergesort(arr, l, mid);
		mergesort(arr, mid + 1, r);
		merge(arr, l, mid, r);
	}
};


int main()
{
	int arr[]{ 2,5,4,6,3 };
	 
	/*int[] arr = new int[](){3,4,5,6,7};*/
	A<int> b;
	b.mergesort(arr, 0, 5);

	return 0;
	

	
	

	//int m = 10000;
	//int*arr1 = sorttesthelper::generaterandomarray(m, 0, m);
	//sortalgorithm::quicksort(arr1, m);
	//sorttesthelper::isSorted(arr1, m);
	//sorttesthelper::printf(arr1, m);
	//sorttesthelper::testsort("arr1的插入排序", sortalgorithm::quicksort, arr1, m);

	////归并排序
	////int c = 100;
	////int *arr2 = sorttesthelper::generaterandomarray(c, 0, c);
	////sortalgorithm::__merge(arr2, 0,(0+c)/2, c);
	////sortalgorithm::mergesort(arr2, c);
	////sorttesthelper::isSorted(arr2, c);
	////sorttesthelper::testsort("归并排序：", sortalgorithm::mergesort, arr2, c);
	////sorttesthelper::printf(arr2, c);



	//delete[] arr1;
	//delete[] arr2;
//	MaxHeap<int> maxheap = MaxHeap<int>(100);
	//MaxHeap<int> maxheap(100);
	//cout << maxheap.size() << endl;

	//srand(time(NULL));
	//for (int i = 0; i < 50; i++)
	//	maxheap.insert(rand() % 100);
	//maxheap.testPrint();
	//while (!maxheap.isempty())
	//	cout << maxheap.exteactMax() << "  ";
	//cout << endl;
	//return 0;
	 
	
}







//student.h文件中类型的初始化方法
//student d[4] = { {"D",90},{"C",100},{"B",95},{"A",95} };
//selectionsort(d, 4);
//sorttesthelper::printf(d, 4);



//int b[10];
//////选择排序1
/*	for (i = 0; i < 10; i++)
	{
		for (j = i+1; j < 10; j++)
		{
			if (a[i] > a[j])
			{
				tamp = a[i];
				a[i] = a[j];
				a[j] = tamp;
			}
			//cout << a[i] << endl;

		}
		//cout << a[i];
	//	cout << a[j];
	}
	cout << endl;*/
	/*//选择排序2（利用数组下角标）
	for (i = 0; i < 10; i++)
	{
		int min;
		min = i;
		for (j = i + 1; j < 10; j++)
		{
			if (a[i] > a[j])
			{
				min = j;
				tamp = a[i];
				a[i] = a[min];
				a[min] = tamp;
			}

		}
	}*/

	//选择排序（利用c++中的容器和迭代器）


	//vector <int> arr = { 3,5,2,6,1,9,4,7,8 };
	//if (arr.empty != 0)
	//{
	//	cout << "arr.empty检测成功" << endl;
	//}
	////使用for对容器进行遍历
	//for (auto vel : arr)
	//{
	//	cout << vel << endl;
	//}
	//vector<int>::iterator pos;//定义一个名为POS的变量
	//vector<int>::iterator pos1=arr.begin;//定义POS1使他指向arr的第一个元素
	//vector<int>::iterator pos2 = arr.end;//定义POS2使他指向arr的最后+1个元素
	//if (pos1 != pos2)
	//{
	//	for (pos1; pos1 != pos2; pos1++)
	//	{
	//		for (pos1 + 1; pos1 != pos2; pos1++)
	//		{
	//			if (pos1 > pos1 + 1)
	//			{
	//				pos = pos1;
	//				pos1 = pos2;
	//				pos2 = pos;
	//			}
	//		}
	//	}
	//}
	//for (auto vel : arr)
	//{
	//	cout<<vel<<endl;
	//}