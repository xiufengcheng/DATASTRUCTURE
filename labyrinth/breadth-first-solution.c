#include<stdio.h>
#include<stdlib.h>

#define rowSize 10
#define lineSize 10

int Map[10][10] =
{
	{ 0,0,0,0,0,0,0,0,0,0 }, //0行 
	{ 0,1,1,0,1,1,1,0,1,0 }, //1行
	{ 0,1,1,0,1,1,1,0,1,0 }, //2行
	{ 0,1,1,1,1,0,0,1,1,0 }, //3行  
	{ 0,1,0,0,0,1,1,1,1,0 }, //4行  
	{ 0,1,1,1,0,1,1,1,1,0 }, //5行
	{ 0,1,0,1,1,1,0,1,1,0 }, //6行
	{ 0,1,0,0,0,1,0,0,1,0 }, //7行
	{ 0,0,1,1,1,1,1,1,1,0 }, //8行
	{ 0,0,0,0,0,0,0,0,0,0 }  //9行
};


void printPath(int preV[rowSize][lineSize][2],int i,int j)
{
	if (i == -1)
	{
		return;
	}
	printPath(preV, preV[i][j][0], preV[i][j][1]);
	printf("(%d , %d) -> ", i, j);
	return;
}

int main(void)
{
	int preV[rowSize][lineSize][2];//previous vertex
	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < lineSize; j++)
		{
			preV[i][j][0] = -1;
			preV[i][j][1] = -1;
		}
	}
	int visited[rowSize][lineSize];
	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < lineSize; j++)
		{
			if (Map[i][j] == 1)
			{
				visited[i][j] = 0;
			}
			else
			{
				visited[i][j] = 1;
			}
		}
	}
	int queue[rowSize*lineSize][2];
	int front = 0, rear = 0;
	queue[0][0] = 1;
	queue[0][1] = 1;//enqueue starter
	visited[1][1] = 1;
	while (front <= rear)//bfs			
	{
		int i = queue[front][0];
		int j = queue[front][1];
		front++;
		if (!visited[i + 1][j])
		{
			rear++;
			queue[rear][0] = i + 1;
			queue[rear][1] = j;
			preV[i + 1][j][0] = i;
			preV[i + 1][j][1] = j;
			visited[i + 1][j] = 1;
		}
		if (!visited[i][j + 1])
		{
			rear++;
			queue[rear][0] = i;
			queue[rear][1] = j + 1;
			preV[i][j + 1][0] = i;
			preV[i][j + 1][1] = j;
			visited[i][j + 1] = 1;
		}
		if (!visited[i - 1][j])
		{
			rear++;
			queue[rear][0] = i - 1;
			queue[rear][1] = j;
			preV[i - 1][j][0] = i;
			preV[i - 1][j][1] = j;
			visited[i - 1][j] = 1;
		}
		if (!visited[i][j - 1])
		{
			rear++;
			queue[rear][0] = i;
			queue[rear][1] = j - 1;
			preV[i][j - 1][0] = i;
			preV[i][j - 1][1] = j;
			visited[i][j - 1] = 1;
		}
	}//end of bfs
	if (visited[rowSize - 2][lineSize - 2] == 0)
	{
		printf("error -- cannot be reached");
		return 1;
	}
	printPath(preV, rowSize - 2, lineSize - 2);//print path recursively
	printf("out");
	return 0;
}
