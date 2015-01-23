#include <stdio.h>
#include <stdlib.h>

#define SIZE 7

void dije(int graph[SIZE][SIZE], int d[SIZE], int p[SIZE], int start);
void printPath(int p[SIZE], int start, int end, int d[SIZE]);

void main()
{
	int d[SIZE] = {0,}, p[SIZE] = {0,}, start, end;
	int graph[SIZE][SIZE] = {
		{0, 6, 2, 16, 0, 0, 14}, 
		{0, 0, 0, 5, 4, 0, 0}, 
		{0, 7, 0, 0, 3, 8, 0}, 
		{0, 0, 0, 0, 0, 0, 3}, 
		{0, 0, 0, 4, 0, 0, 10}, 
		{0, 0, 0, 0, 0, 0, 1}, 
		{0, 0, 0, 0, 0, 0, 0}};

	start = 2;
	end = 7;
	dije(graph, d, p, start - 1);
	printPath(p, start, end, d);
	printf("cost : %3d\n", d[end - 1]);
}

void dije(int graph[SIZE][SIZE], int d[SIZE], int p[SIZE], int start)
{
	int c[SIZE] = {0,}, i, j, k, cost, row, min;

	row = start;

	for(i = 0 ; i < SIZE ; i++)
	{
		if(graph[row][i] != 0)
		{
			p[i] = row;
			cost = graph[row][i];
			d[i] = cost;
		}
	}
	c[row] = 1;

	for(i = 0 ; i < SIZE - 2 ; i++)
	{
		min = 999999999;
		for(j = 0 ;  j < SIZE ; j++)
			if(min > d[j] && d[j] != 0)
			{
				if(c[j] == 1)
					continue;
				min = d[j];
				row = j;
			}
		c[row] = 1;

		for(j = 0 ; j < SIZE ; j++)
		{
			if(c[j] == 1)
				continue;

			if(graph[row][j] != 0)
			{
				if(d[j] == 0)
				{
					d[j] = d[row] + graph[row][j];
					p[j] = row;
				}
				else if(d[row] + graph[row][j] < d[j])
				{
					d[j] = d[row] + graph[row][j];
					p[j] = row;
				}
			}
		}
	}
}

void printPath(int p[SIZE], int start, int end, int d[SIZE])
{
	int i, now;

	start--;
	end--;
	now = end;

	if(d[end] == 0)
	{
		printf("You can't go there\n");
		return;
	}
	printf("reverse!\n");
	while(now != start)
	{
		printf("%3d", now + 1);
		now = p[now];
	}
	printf("%3d\n", start + 1);
}