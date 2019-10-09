#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 114514

//normal qsort
void foosort(int *nums, int left, int right)
{
	if (left >= right)
	{
		return;
	}
	int pivot = nums[left];
	int i = left, j = right;
	while (i < j)
	{
		while (i < j && nums[j] >= pivot)
		{
			j--;
		}
		nums[i] = nums[j];
		while (i < j && nums[i] <= pivot)
		{
			i++;
		}
		nums[j] = nums[i];
	}
	nums[i] = pivot;
	foosort(nums,left,i-1);
	foosort(nums,i+1,right);
	return;
}


//iterative qsort
typedef struct
{
	int left;
	int right;
}argnode;

void barsort(int *nums, int numsSize)
{
	argnode stack[MAX_SIZE]; //macro
	int top = -1;
	argnode cur;
	cur.left = 0;
	cur.right = numsSize-1;
	stack[++top] = cur;
	while (top != -1)
	{
		//pop arguments
		cur = stack[top--];
		int left = cur.left;
		int right = cur.right;
		if (cur.left >= cur.right)
		{
			continue;
		}

		//same
		int pivot = nums[left];
		int i = left, j = right;
		while (i < j)
		{
			while (i < j && nums[j] >= pivot)
			{
				j--;
			}
			nums[i] = nums[j];
			while (i < j && nums[i] <= pivot)
			{
				i++;
			}
			nums[j] = nums[i];
		}
		nums[i] = pivot;


		//push arguments
		cur.left = left;
		cur.right = i - 1;
		stack[++top] = cur;
		cur.left = i + 1;
		cur.right = right;
		stack[++top] = cur;
	}
	return;
}

int main(void)
{
	int x[10] = { 32,16,78};
	barsort(x,3);
	return 0;
}
