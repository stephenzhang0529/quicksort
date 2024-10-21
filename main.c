#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
//第一种，全排序后再找出第find小的数
void quicksort1(int arr[], int left, int right)//小到大
{
	int key = arr[left];
	int i = left;
	int j = right;
	if (i >= j)
	{
		return;
	}
	while (i < j)
	{
		//从右向左找到比基准小的元素
		while(i<j && arr[j]>=key)
		{
			j--;
		}
		//从左向右找到比基准大的元素
		while (i<j && arr[i]<=key)
		{
			i++;
		}
		//交换arr[i]和arr[j]
		if (i < j)
		{
			swap(&arr[i], &arr[j]);
		}
	}
	//此时i==j,arr[left]==key
	//即把key值移到中间，此时其左侧数都小于key，右侧数都大于key
	swap(&arr[left], &arr[i]);
	//递归
	quicksort1(arr, left, i - 1);
	quicksort1(arr, i + 1, right);
}
//第二种，遍排序遍找
int quicksort2(int arr[], int left, int right,int find)//小到大
{
	int key = arr[left];
	int i = left;
	int j = right;
	if (i >= j)
	{
		return key;
	}
	while (i < j)
	{
		//从右向左找到比基准小的元素
		while (i < j && arr[j] >= key)
		{
			j--;
		}
		//从左向右找到比基准大的元素
		while (i < j && arr[i] <= key)
		{
			i++;
		}
		//交换arr[i]和arr[j]
		if (i < j)
		{
			swap(&arr[i], &arr[j]);
		}
	}
	//此时i==j,arr[left]==key
	//即把key值移到中间，此时其左侧数都小于key，右侧数都大于key
	swap(&arr[left], &arr[i]);
	//递归
	if (find < i+1)
	{
		quicksort2(arr, left, i - 1,find);
	}
	else if(find>i+1)
	{
		quicksort2(arr, i + 1, right,find);
	}
	else//find==i+1
	{
		return key;
	}
}
int main()
{
	clock_t start, end;
	double cpu_time_used;
	//正确性测试：
	printf("正确性测试：\n");
	int arr1[] = { 12, 3, 5, 7, 19, 8, 4 ,20,1,2,40};
	int arr2[] = { 12, 3, 5, 7, 19, 8, 4 ,20,1,2,40 };
	int size = sizeof(arr1) / sizeof(arr1[0]);
	int find = 10;  // 查找第find小的元素
	//法1
	start = clock();
	quicksort1(arr1, 0, size-1);
	end = clock();
	printf("%d\n", arr1[find - 1]);
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Time used = %f\n", cpu_time_used);
	//法2
	start = clock();
	int result = quicksort2(arr2, 0, size - 1, find);
	end = clock();
	printf("%d\n", result);
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Time used = %f\n", cpu_time_used);


	//性能比较
	printf("性能测试：\n");
	int random1[100000], random2[100000];
	for (int i = 0; i < 100000; i++) 
	{
		random1[i] = random2[i] = rand() % 1000000;  // 随机生成0到999999之间的数
	}
	//法1
	start = clock();
	quicksort1(random1, 0, 99999);
	end = clock();
	printf("%d\n", random1[find - 1]);
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Time used = %f\n", cpu_time_used);
	//法2
	start = clock();
	result = quicksort2(random2, 0, 99999, find);
    end = clock();
	printf("%d\n", result);
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Time used = %f\n", cpu_time_used);


	return 0;

}