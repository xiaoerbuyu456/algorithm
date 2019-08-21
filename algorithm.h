 

#ifndef ALGORITHM_H
#define ALGORITHM_H
#include "pch.h"
#include <iostream>
#include <cassert>
//五大基础排序
namespace sortalgorithm
{
	/*1、*///定义一个选择排序的模板函数
	/*选择排序的思想是：假设一个数组按照升序排序，那么第一轮选出一个最小的元素放在0的位置，
	之后这个元素的位置就不需要再动了，第二轮选出剩余元素中最小的一个放在1的位置，如此循环。
	因此需要两层循环，外层循环控制选择的轮数，和数组长度有关，
	内层循环负责在剩余元素中寻找最小的一个，找到后将其放在合适的位置。*/
	template<typename T>
	void selectionsort(T arr[], int n)
	{
		//进行排序
		for (int i = 0; i < n; i++)
		{
			int minIndex = i;
			for (int j = i + 1; j < n; j++)
				if (arr[j] < arr[minIndex])
					minIndex = j;
			swap(arr[i], arr[minIndex]);
		}

	}
	/*2、*///定义一个插入排序的函数模板（用的swap函数效率要低一点）
	/*  每次将一个待排序（无序区中）的数据元素，插入到前面(有序区)已经排好序的数列中的适当位置，
	使数列依然有序；直到待排序数据元素全部插入完为止。（默认划分arr[0]为有序区，arr[1-n]为无序区）*/
	template<typename T>
	void insertionsort(T arr[], int n)
	{
		for (int i = 1; i < n; i++)
		{
			//寻找元素arr[i]合适的插入位置for(int j=i;j>0 && arr[j]<arr[j-1];j--){swap(arr[j],arr[j-1])};
			for (int j = i; j > 0; j--)  
			{
				if (arr[j] < arr[j - 1])
					swap(arr[j], arr[j - 1]);
				else
					break;
			}
		}
	}
	/*2.1、*///改进后的插入排序模板函数(更为适合用于近乎有序的数组)；本算法用了很多赋值运算因此效率会高一点
	template<typename T>
	void advanceinertionsort(T arr[], int n)
	{
		for (int i = 1; i < n; i++)
		{
			T e = arr[i];
			int j;                       //保存元素e应该插入的位置
			for (j = i; j > 0 && arr[j - 1] > e; j--)
			{
				arr[j]= arr[j - 1]; 
			}
			arr[j] = e;
		}
	}
	/*3、*///d定义一个冒泡排序函数
	/*冒泡排序的思想是比较两两相邻的关键字，如果反序则进行交换，直到没有反序的为止。
	设想一个数组按照升序排列，经过第一轮比较之后最大的数就被放在最后了，因此剩下的比
	较中就不需要将它再参与进来，第二轮比较中第二大的数据被放在了倒数第二的位置，它的
	位置也就股定了，也不需要参与剩余的比较。因此我们需要两层循环，外层循环控制比较的轮数，
	和数组元素的个数有关，内层循环控制需要参与比较的元素个数，和外层循环的轮数有关，
	当比较的轮数增大时，已经找到位置的元素个数随之增大，那么内层待比较的元素个数随之减小。*/
	template<typename T>
	void bubbleSort (T arr[], int len) {
	    T temp;
	    int i, j;
	    for (i=0; i<len-1; i++) /* 外循环为排序趟数，len个数进行len-1趟 */
		for (j=0; j<len-1-i; j++) { /* 内循环为每趟比较的次数，第i趟比较len-i次 */
		    if (arr[j] > arr[j+1]) { /* 相邻元素比较，若逆序则交换（升序为左大于右，降序反之） */
			temp = arr[j];
			arr[j] = arr[j+1];
			arr[j+1] = temp;
		    }
		}
	}

	/*4、*///定义一个归并排序算法函数
	//将arr[L...mid]和arr[mid+1....R]两部分进行归并
	template<typename T>
	void __merge(T arr[], int l, int mid, int r)//实现归并排序的“治”
	{
		T aux[r - l + 1];//开辟一个临时空间
		for (int i = l; i <= r; i++)
			aux[i - l] = arr[i];
		int i = l, j = mid + 1;
		for (int k = l; k <= r; k++)
		{
			if (i > mid)             //防止数组越界问题
			{
				arr[k] = aux[j - l];
				j++;
			}
			else if (j > r)          //防止数组越界问题
			{
				arr[k] = aux[i - l];
				i++;
			}
			else if (aux[i - l] < aux[j - l])//进行排序
			{
				arr[k] = aux[i - l];
				i++;
			}
			else
			{
				arr[k] = aux[j - l];
				j++;
			}
		}
    }
	//递归使用归并排序，对arr[L....R]的范围进行排序，对这个边界要注意
	template<typename T>
	void  __mergesort (T arr[], int l, int r)//本函数主要是实现归并排序的“分”
	{
		//if (l >= r)//判断左与右边
		//	return;
		if (r - l <= 15)//优化归并排序，分割成16个元素一组的时候采用插入排序
		{
			insertionsort(arr, r - l + 1);
			return;
		}
		int mid = (l + r)/2;
		 __mergesort(arr, l, mid);
		 __mergesort(arr, mid + 1, r);
		 if(arr[mid]<arr[mid+1])//优化归并排序
            __merge(arr, l, mid, r);//__merge()函数的接口
	}
	template<typename T>
	void mergesort(T arr[], int n)
	{
		__mergesort(arr, 0, n - 1);
	}

	/*4.1、*///自底向上的归并排序(没有使用数组的特性，所以会比较快一点)自上而下的归并排序使用“递归”，自下而上的归并排序使用“迭代”
	template<typename T>
	void mergesortbu(T arr[], int n)
	{
		for(int sz=1;sz<=n;sz+=sz)//本轮循环控制每次排序的个数（分配每组元素的个数）
			for (int i = 0; i + sz < n; i += sz + sz)//对划分的各组进行排序（相邻两组进行排序）
			{
				__merge(arr, i, i + sz - 1, min(i + sz + sz - 1));
			}
	}
	
	/*5*///快速排序
	template<typename T> 
	int __partition(T arr[], int l, int r)
	{
		swap(arr[l], arr[rand() % (r - l + 1) + l]);//优化T使他随机生成是
		T v = arr[l];
		//arr[l+1....j]<v;arr[j+1...i)>v
		int j = l;
		for(int i=l+1;i<=r;i++)
			if (arr[i] < v)
			{
				swap(arr[j + 1], arr[i]);
				j++;
			}
		swap(arr[l], arr[j]);
		return j;
	}
	template<typename T>
	void __quicksort(T arr[], int l, int r)
	{
		/*if (l >= r)
			return;*/
		if (r - l <= 15)//优化归并排序，分割成16个元素一组的时候采用插入排序
		{
			insertionsort(arr, r - l + 1);
			return;
		}
		int p = __partition(arr, l, r);
		__quicksort(arr, l, p - 1);
		__quicksort(arr, p + 1, r);

	}
	template<typename T>
	void quicksort(T arr[], int n)
	{
		__quicksort(arr, 0, n - 1);
	}

	/*5.1*///双路快速排序
	template<typename T>
	int __partition2(T arr[], int l, int r)
	{
		swap(arr[l], arr[rand() % (r - l + 1) + l]);//优化T使他随机生成是
		T v = arr[l];
		//arr[l+1....j]<v;arr[j...r])>=v
		int i = l + 1, j = r;

		while (true) 
		{
		while (i <= r && arr[i] < v)
			i++;
		while (j >= l + 1 && arr[j] > v)
			j--;
		if (i > j)
			break;
		swap(arr[i], arr[j]);
		i++;
		j--;
	    }
		swap(arr[l], arr[j]);
		return j;

	}
	template<typename T>
	void __quicksort2(T arr[], int l, int r)
	{
		/*if (l >= r)
			return;*/
		if (r - l <= 15)//优化归并排序，分割成16个元素一组的时候采用插入排序
		{
			insertionsort(arr, r - l + 1);
			return;
		}
		int p = __partition2(arr, l, r);
		__quicksort2(arr, l, p - 1);
		__quicksort2(arr, p + 1, r);

	}
	template<typename T>
	void quicksort2(T arr[], int n)
	{
		srand(time(NULL));
		__quicksort2(arr, 0, n - 1);
	}

	/*5.2*///三路快速排序
	template<typename T>
	void __quicksort3(T arr[], int l, int r)
	{
		/*if (l >= r)
			return;*/
		if (r - l <= 15)//优化归并排序，分割成16个元素一组的时候采用插入排序
		{
			insertionsort(arr, r - l + 1);
			return;
		}
		//partition
		swap(arr[l], arr[rand() % (r - l + 1) + l]);
		T v = arr[l];
		int lt = l;
		int gt = r + 1;
		int i = l + 1;
		while (i < gt)
		{
			if (arr[i] < v)
			{
				swap(arr[i], arr[lt + 1]);
				lt++;
				gt++;
			}
			else if (arr[i] > v)
			{
				swap(arr[i], arr[gt - 1]);
				gt--;
			}
			else {
				i++;
			}
		}
		swap(arr[l], arr[lt]);

		__quicksort3(arr, l, lt - 1);
		__quicksort3(arr, gt, r);

	}
	template<typename T>
	void quicksort3(T arr[], int n)
	{
		srand(time(NULL));
		__quicksort3(arr, 0, n - 1);
	}


}
//堆
template<typename Item>
class MaxHeap//最大堆
{
private:
	Item* data;
	int count;
	int capacity;
    //把插入的元素进行位置确定
	void shiftup(int k)
	{
		while (k>1 &&data[k / 2] < data[k])
		{
			swap(data[k / 2], data[k]);
			k /= 2;
		}
	}
	//删除一个元素后把其他元素进行定位
	void shiftDown(int k)
	{
		while (2 * k <= count)
		{
			int j = 2 * k;//在此轮循环中，data[k]和data[j]交换位置
			if (j + 1 <= count && data[j + 1] > data[j])
				j += 1;
			if (data[k] >= data[j])
				break;
			swap(data[k], data[j]);
			k = j;
		}
	}

public:
	//构造函数，构造一个空堆，可容纳capacity个元素
	MaxHeap(int capacity)
	{
		data = new Item[capacity + 1];
		count = 0;
		this->capacity=capacity;
	}
	//析构函数，释放new的内存
	~MaxHeap()
	{
		delete[] data;
	}
	//返回堆中的元素个数
	int size()
	{
		return count;
	}
	//返回一个布尔值，表示堆中是否为空
	bool isempty()
	{
		return count == 0;
	}
	//像最大堆中插入一个新的元素
	void insert(Item item)
	{
		assert(count + 1 <= capacity);
		data[count + 1] = item;
		count++;
		shiftup(count);
	}
	//从最大堆中删除一个元素
	Item exteactMax()
	{
		assert(count > 0);
		Item ret = data[1];
		swap(data[1], data[count]);
		count--;
		shiftDown(1);

		return ret;
	}
public:
	//以树状打印整个堆结构
	void testPrint()
	{
		//我们的testPrint只能打印100个元素以内的堆的树状信息
		if (size() >= 100)
		{
			cout << "This pint function can only work for int item";
			return;
		}
		//我们的testPrint只能处理整数信息
		if (typeid(Item) != typeid(int))
		{
			cout << "This print function can only work for int item";
			return;
		}
		cout << "The max heap size is:" << size() << endl;
		cout << "Data in the max heap:";
		for (int i = 1; i <= size(); i++)
		{
			//我们的testPrint要求堆中的所有整数在[0,100)的范围内
			assert(data[i] >= 0 && data[i] < 100);
			cout << data[i] << "  ";


		}
		cout << endl;
		cout << endl;
		int n = size();
		int max_level = 0;
		int number_per_level = 1;
		while (n > 0) 
		{
			max_level += 1;
			n -= number_per_level;
			number_per_level *= 2;
		}
		int max_level_number = int(pow(2, max_level - 1));
		int cur_tree_max_level_number = max_level_number;
		int index = 1;
		for (int level = 0; level < max_level; level++)
		{
			string line1 = string(max_level_number * 3 - 1, ' ');

			int cur_level_number = min(count - int(pow(2, level)) + 1, int(pow(2, level)));
			bool isLeft = true;
			for (int index_cur_level = 0; index_cur_level < cur_level_number; index++, index_cur_level++) {
				putNumberInLine(data[index], line1, index_cur_level, cur_tree_max_level_number * 3 - 1, isLeft);
				isLeft = !isLeft;
			}
			cout << line1 << endl;
			if (level == max_level - 1)
				break;

			string line2 = string(max_level_number * 3 - 1, ' ');
			for (int index_cur_level = 0; index_cur_level < cur_level_number; index_cur_level++)
				putBranchInLine(line2, index_cur_level, cur_tree_max_level_number * 3 - 1);
			cout << line2 << endl;

			cur_tree_max_level_number /= 2;
		}
	}
private:
	void putNumberInLine(int num, string &line, int index_cur_level, int cur_tree_width, bool isLeft)
	{

		int sub_tree_width = (cur_tree_width - 1) / 2;
		int offset = index_cur_level * (cur_tree_width + 1) + sub_tree_width;
		assert(offset + 1 < line.size());
		if (num >= 10) 
		{
			line[offset + 0] = '0' + num / 10;
			line[offset + 1] = '0' + num % 10;
		}
		else 
		{
			if (isLeft)
				line[offset + 0] = '0' + num;
			else
				line[offset + 1] = '0' + num;
		}
	}

	void putBranchInLine(string &line, int index_cur_level, int cur_tree_width) 
	{

		int sub_tree_width = (cur_tree_width - 1) / 2;
		int sub_sub_tree_width = (sub_tree_width - 1) / 2;
		int offset_left = index_cur_level * (cur_tree_width + 1) + sub_sub_tree_width;
		assert(offset_left + 1 < line.size());
		int offset_right = index_cur_level * (cur_tree_width + 1) + sub_tree_width + 1 + sub_sub_tree_width;
		assert(offset_right < line.size());

		line[offset_left + 1] = '/';
		line[offset_right + 0] = '\\';
	}
};
//二分查找法，在有序数组arr中，查找target
template<typename T>
int binarysearch(T arr[], int n, T target)
{
	//在arr[l...r]之中查找target
	int l = 0, r = n - 1;
	while (l <= r)
	{
		int mid = (r + l) / 2;
		if (arr[mid] == target)
			return mid;
		//在arr[l...mid-1]中查找target
		if (target < arr[mid])
			r = mid - 1;
		else//target>arr[mid],在arr[mid+1....r]中查找target
			l = mid + 1;
	}
	return -1;//没有查找到时返回-1

}
//二分搜索树的建立以及节点的插入
template<typename key,typename value>
class BST
{
private:
	struct Node
	{
		key key;
		value value;
		Node *left;
		Node *right;
		Node(key key, value value)
		{
			this->key = key;
			this->value = value;
			this->left = this->right;

		}
	};
	Node *root;
	int count;

public:
	BST()
	{
		root = NULL;
		count = 0;
	}
	~BST()
	{
		destroy(root);
	}
	int size()
	{
		return count;
	}
	bool isempty()
	{
		return count == 0;
	}
	void insert(key key, value value)
	{
		root = insert(root, key, value);
	}
	//查找树中是否有要查找的key
	bool contain(key key)
	{
		return contain(root, key);
	}
	//在搜索树中查找key值
	value* ssearch(key key)
	{
		return ssearch(root, key);
	}
	//前序遍历
	void preorder()
	{
		preorder(root);
	}
	//中序遍历
	void inorder()
	{
		inorder(node);
	}
	//后序遍历
	void postorder()
	{
		postorder(root);
	}
private:
	//向以node为根的二叉搜索树中，插入节点（key,value)
	//返回插入新节点后的二叉搜索树的根
	Node* insert(Node *node, key key, valude value)
	{
		if (node == NULL)
		{
			count++;
			return new Node(key, value);
		}
		if (key == node->key)
			node->value = value;
		else if (key < node->key)
			node->left = insert(node->left, key, value)
		else  //key>node->key
			node->right = insert(node->right, key, value)
			
		return node;

	}
	//查看以node为根的二叉搜索树中是否包含键值为key的节点
	bool contain(Node* node, key key)
	{
		if (node == NULL)
			return false;
		if (key == node->key)
			return true;
		else if (key < node->key)
			return contain(node->left, key);
		else //key>node->key
			return contain(node->right, key);

	}
	//在以node为根的二叉搜索树中查找key所对应的value
	value* ssearch(Node* node, key key)
	{
		if (node == NULL)
			return NULL;
		if (key == node->key)
			return &(node->value);
		else if (key < node->key)
			return ssearch(node->left, key);
		else //key>node->key
			return ssearch(node->right, key);

	}
	//对以node为根的二叉树搜索树进行前序遍历
	void preorder(Node* node)
	{
		if (node != NULL)
		{
			cout << node->key << endl;
			preorder(node->left);
			preorder(node->right);
		}
	}
	//对以node为根的二叉搜索树进行中序遍历
	void inorder(Node* node)
	{
		if (node != NULL)
		{
			inorder(node->left);
			cout << node->key << endl;
			inorder(node->right);
		}
	}
	//对以node为根的二叉搜索树进行后序遍历
	void postorder(Node* node)
	{
		if (node != NULL)
		{
			postorder(node->left);
			postorder(node->right);
			cout << node->key << endl;
		}
	}
	//释放空间（析构函数中的方法）
	void destroy(Node* node)
	{
		if (node != NULL)
		{
			destroy(node->left);
			destroy(node->right);
			delete node;
			count--;
		}
	}
};

#endif //SORTALGORITHM_H
