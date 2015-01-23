#include <stdio.h>

void setDistanceAndFound(int src, int graph[7][7], int distance[7])
{
	int count;

	for(count = 0; count < 7; count++)
	{
		if(graph[src][count] != 0 && (distance[count] == -1 || distance[src] + graph[src][count] < distance[count]))
		{
			distance[count] = distance[src] + graph[src][count];
		}
	}
}

int select(int found[7], int distance[7])
{
	int count;
	int min = -1;

	for(count = 0; count < 7; count++)
	{
		if(found[count] == 0 && distance[count] != -1 && (min == -1 || distance[count] < min))
		{
			min = distance[count];
		}
	}

	return min;
}

void shortestPath(int start, int end, int graph[7][7])
{
	int count;

	int found[7] = {0, };
	int distance[7] = {-1, -1, -1, -1, -1, -1, -1};
	
	found[start-1] = 1;
	distance[start-1] = 0;
	setDistanceAndFound(start-1, graph, distance);

	for(count = 0; count < 7-2; count++)
	{
		int u = select(found, distance);
		found[u] = 1;
		setDistanceAndFound(u, graph, distance);
	}

	if(distance[end-1] != -1)
		printf("%d\n", distance[end-1]);
	else
		printf("경로 없음\n");
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
						{0, 0, 0, 0, 0, 0, 0}
					  };

	shortestPath(5, 6, graph);
}