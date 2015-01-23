#include <stdio.h>

#define INF 9999

int numOfIncoming(int src, int graph[7][7])
{
	int count = 0;
	int i;

	for(i = 0; i < 7; i++)
	{
		if(graph[i][src] != INF)
			count += 1;
	}

	return count;
}

void bf(int start, int end, int graph[7][7])
{
	int k;
	int u;
	int i;
	int dist[7] = {999, 999, 999, 999, 999, 999, 999};

	for(k = 0; k < 7; k++)
	{
		dist[k] = graph[start-1][k];
	}

	for(k = 0; k <= 6; k++)
	{
		for(u = 0; u < 7; u++)
		{
			if(u != start-1 && numOfIncoming(u, graph) > 0)
			{
				for(i = 0; i < 7; i++)
				{
					if(dist[u] > dist[i] + graph[i][u])
						dist[u] = dist[i] + graph[i][u];
				}
			}
		}
	}

	if(dist[end-1] > 100)
		printf("Failed\n");
	else
		printf("%d\n", dist[end-1]);
}

int main()
{
	int graph[7][7] = {
		{INF,   6, INF,   5, INF, INF, INF}, 
		{INF, INF, INF, INF,  -1, INF, INF}, 
		{INF,  -2, INF, INF,   1, INF, INF}, 
		{INF, INF,  -2, INF, INF,  -1, INF}, 
		{INF, INF, INF, INF, INF, INF,   3}, 
		{INF, INF, INF, INF, INF, INF,   3}, 
		{INF, INF, INF, INF, INF, INF, INF}
	};

	bf(3, 4, graph);
}