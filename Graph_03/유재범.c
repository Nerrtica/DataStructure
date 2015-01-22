#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
#define SIZE 7

void Dijkstra(int graph[SIZE][SIZE], int cost[SIZE], int parents[SIZE], int end);

int main(void){
	int end = 0;
	int graph[SIZE][SIZE] = {
		{0, 6, 2, 16, 0, 0, 14}, 
		{0, 0, 0, 5, 4, 0, 0}, 
		{0, 7, 0, 0, 3, 8, 0}, 
		{0, 0, 0, 0, 0, 0, 3}, 
		{0, 0, 0, 4, 0, 0, 10}, 
		{0, 0, 0, 0, 0, 0, 1}, 
		{0, 0, 0, 0, 0, 0, 0}};
	int cost[SIZE] = {0, };
	int parents[SIZE] = {0, };
	printf("어디까지 가시겠습니까, 호갱님? : ");
	scanf("%d", &end);
	Dijkstra(graph, cost, parents, end);

	return 0;
}

void Dijkstra(int graph[SIZE][SIZE], int cost[SIZE], int parents[SIZE],int end){
	int i = 0, j = 0, save = 0;
	int node[SIZE] = {0, };

	for(i = 0; i < SIZE - 1; i++){
		for(j = 0; j < SIZE; j++){
			save = graph[i][j] + cost[i];
			if(cost[j] == 0 && graph[i][j] > 0){
				parents[j] = i + 1;
				cost[j] = save;
			}
			else if((graph[i][j] > 0) && (cost[j] > save)){// cost[j] > save
				parents[j] = i + 1;
				cost[j] = save;
			}
		}
	}

	printf("최소 코스트 : %d\n", cost[end - 1]);
	node[0] = end;
	j = end;

	for(i = 1; j != 1; i++){
		node[i] = parents[j - 1];
		j = parents[j - 1];
	}
	for(i = end; i > 0; i--){
		if(node[i] > 0){
			printf("%d->", node[i]);
		}
	}
	printf("%d\n\n", node[0]);
}