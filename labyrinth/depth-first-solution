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

int dfs(int i, int j,int visited[10][10])
{
	if (i == rowSize - 2 && j == lineSize - 2)
	{
		printf("(%d , %d)", i, j);
		return 1;
	}
	visited[i][j] = 1;
	if (!visited[i + 1][j] && Map[i + 1][j] == 1)
	{
		if (dfs(i + 1, j, visited))
		{
			printf(" <- (%d , %d)", i, j);
			return 1;
		}
	}
	if (!visited[i][j + 1] && Map[i][j + 1] == 1) 
	{
		if (dfs(i, j + 1, visited))
		{
			printf(" <- (%d , %d)", i, j);
			return 1;
		}
	}
	if (!visited[i - 1][j] && Map[i - 1][j] == 1)
	{
		if (dfs(i - 1, j, visited))
		{
			printf(" <- (%d , %d)", i, j);
			return 1;
		}
	}
	if (!visited[i][j - 1] && Map[i][j - 1] == 1) 
	{
		if (dfs(i, j - 1, visited))
		{
			printf(" <- (%d , %d)", i, j);
			return 1;
		}
	}
	return 0;
}

int main(void)
{
	int visited[rowSize][lineSize] = { 0 };
	dfs(1, 1, visited);
	return 0;
}
