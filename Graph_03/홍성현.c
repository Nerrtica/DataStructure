#include <stdio.h>
#include <stdlib.h>

#define SIZE 7

void dije(int graph[SIZE][SIZE], int d[SIZE], int p[SIZE], int start);
int countC(int c[SIZE]);
void printPath(int p[SIZE], int start, int end);

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

	start = 1;
	end = 7;
	dije(graph, d, p, start - 1);
	printPath(p, start, end);
	printf("cost : %3d\n", d[end - 1]);
}

void dije(int graph[SIZE][SIZE], int d[SIZE], int p[SIZE], int start)
{
	int c[SIZE] = {0,}, i, j, cost, row, num;

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
	num = countC(c);

	while(num != SIZE)
	{
		for(i = 0 ; i < SIZE ; i++)
		{
			if(d[i] != 0)
			{
				row = i;

				for(j = 0 ; j < SIZE ; j++)
				{
					cost = d[i];
					if(graph[row][j] != 0)
					{
						cost += graph[row][j];
						if(cost < d[j] || d[j] == 0)
						{
							d[j] = cost;
							p[j] = row;
						}
					}
				}
				c[row] = 1;
				num = countC(c);
			}
		}
	}
}

int countC(int c[SIZE])
{
	int sum = 0, i;

	for(i = 0 ; i < SIZE ; i++)
		sum += c[i];

	return sum;
}

void printPath(int p[SIZE], int start, int end)
{
	int i, now;

	start--;
	end--;
	now = end;
	printf("reverse!\n");
	while(now != start)
	{
		printf("%3d", now + 1);
		now = p[now];
	}
	printf("%3d\n", start + 1);

}