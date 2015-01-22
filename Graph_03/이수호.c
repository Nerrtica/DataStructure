#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void copy(int newBeenTo[7], int beenTo[7])
{
	int count;

	for(count = 0; count < 7; count++)
	{
		newBeenTo[count] = beenTo[count];
	}
}

void ddd(int start, int end, int graph[7][7], int beenTo[7], int p[7], int d[7])
{
	int count;
	beenTo[start] = 1;

	if(start != end)
	{
		for(count = 0; count < 7; count++)
		{
			if(graph[start][count] != 0 && beenTo[count] != 1)
			{
				int * newBeenTo = (int*)malloc(sizeof(int)*7);
				copy(newBeenTo, beenTo);
				
				if(d[count] == 0 || d[count] > graph[start][count] + d[start])
				{
					p[count] = start;
					d[count] = graph[start][count] + d[start];
				}
				ddd(count, end, graph, newBeenTo, p, d);
				free(newBeenTo);
			}
		}
	}
}

void dd(int start, int end, int graph[7][7])
{
	int cur = end-1;
	int beenTo[7] = {0};
	int p[7] = {0};
	int d[7] = {0};
	ddd(start-1, end-1, graph, beenTo, p, d);
	printf("%d\n", d[end-1]);

	

	while(cur != start-1)
	{
		printf("%d ", cur);
		cur = p[cur];
	}
	printf("%d\n", cur);

	return;
}

int main()
{
	int graph[7][7] = {
		{0, 6, 2, 16, 0, 0, 14}, 
		{0, 0, 0, 5, 4, 0, 0}, 
		{0, 7, 0, 0, 3, 8, 0}, 
		{0, 0, 0, 0, 0, 0, 3}, 
		{0, 0, 0, 4, 0, 0, 10}, 
		{0, 0, 0, 0, 0, 0, 1}, 
		{0, 0, 0, 0, 0, 0, 0}};

	int start;
	int end;

	
	printf("start: ");
	scanf("%d", &start);

	printf("end: ");
	scanf("%d", &end);
	
	dd(start, end, graph);
	//dd(1, 7, graph);
	return;
}