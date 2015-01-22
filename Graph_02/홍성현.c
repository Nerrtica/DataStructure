#include <stdio.h>
#include <stdlib.h>

#define SIZE 8

int kruskal(int graph[SIZE][SIZE]);
int findMinKurskal(int graph[SIZE][SIZE], int path[SIZE * SIZE]);
int isCycle(int row, int col, int cycle[SIZE]);

void main()
{
	int result;
	int graph[SIZE][SIZE] = {
		{0, 2, 8, 0, 0, 0, 0, 0}, 
		{2, 0, 7, 9, 0, 0, 0, 0}, 
		{8, 7, 0, 4, 10, 0, 0, 0}, 
		{0, 9, 4, 0, 0, 12, 0, 0}, 
		{0, 0, 10, 0, 0, 6, 14, 0}, 
		{0, 0, 0, 12, 6, 0, 0, 0}, 
		{0, 0, 0, 0, 14, 0, 0, 3}, 
		{0, 0, 0, 0, 0, 0, 3, 0}};

	result = kruskal(graph);

	printf("%3d\n", result);
}

int kruskal(int graph[SIZE][SIZE])
{
	int path[SIZE * SIZE] = {0,}, cycle[SIZE] = {0,}, min, num = 0, count = 0 , sum = 0, i, j;

	while(num != SIZE -1)
	{
		min = findMinKurskal(graph, path);
		path[count] = min;
		count++;

		for(i = 0 ; i < SIZE ; i++)
		{
			for(j = 0 ; j < SIZE ; j++)
			{
				if(graph[i][j] == min)
					break;
			}

			if(graph[i][j] == min)
				break;
		}

		if(isCycle(i, j, cycle)	== 1)
			continue;
		else
		{
			num++;
			sum += min;
		}
		
	}//while ending

	return sum;
}

int findMinKurskal(int graph[SIZE][SIZE], int path[SIZE * SIZE])
{
	int i, j, k, col, row, min;
	int graphCopy[SIZE][SIZE];

	for(i = 0 ; i < SIZE ; i++)
		for(j = 0 ; j < SIZE ; j++)
			graphCopy[i][j] = graph[i][j];

	while(1)
	{
		min = 999999999;

		for(i = 0 ; i < SIZE ; i++)
		{
			for(j = 0 ; j < SIZE ; j++)
			{
				if(graphCopy[i][j] != 0)
				{
					if(min > graphCopy[i][j])
					{
						min = graphCopy[i][j];
						row = i;
						col = j;
					}
				}
			}
		}

		for(k = 0 ; k < SIZE * SIZE ; k++)
			if(path[k] == min)
			{
				graphCopy[row][col] = 0;
				graphCopy[col][row] = 0;
				break;
			}

		if(k == SIZE * SIZE)
			break;
		
	}
	return min;
}

int isCycle(int row, int col, int cycle[SIZE])
{
	int i, num;
	static int count;

	if(cycle[row] == cycle[col] && cycle[row] != 0)
		return 1;

	count++;

	if(cycle[row] == 0)
		cycle[row] = count;
	else
	{
		num = cycle[row];
		for(i = 0 ; i < SIZE ; i++)
		{
			if(num == cycle[i])
				cycle[i] = count;
		}
	}

	if(cycle[col] == 0)
		cycle[col] = count;
	else
	{
		num = cycle[col];
		for(i = 0 ; i < SIZE ; i++)
		{
			if(num == cycle[i])
				cycle[i] = count;
		}
	}
	
	return 0;
}