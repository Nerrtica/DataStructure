#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
#define SIZE 8

void SaveNode(int saveGraph[SIZE][SIZE], int x, int y, int min);
int SearchCycle(int saveGraph[SIZE][SIZE], int x, int y);
int SearchMin(int graph[SIZE][SIZE], int min, int *x, int *y);

int main(void){
	int graph[SIZE][SIZE] = {
		{0, 2, 8, 0, 0, 0, 0, 0}, 
		{2, 0, 7, 9, 0, 0, 0, 0}, 
		{8, 7, 0, 4, 10, 0, 0, 0}, 
		{0, 9, 4, 0, 0, 12, 0, 0}, 
		{0, 0, 10, 0, 0, 6, 14, 0}, 
		{0, 0, 0, 12, 6, 0, 0, 0}, 
		{0, 0, 0, 0, 14, 0, 0, 3}, 
		{0, 0, 0, 0, 0, 0, 3, 0}};
	int saveGraph[SIZE][SIZE] = {0, };
	int x = 0, y = 0, min = 0, checker = 0, sum = 0;
	
	while(checker != SIZE - 1){
		min = SearchMin(graph, min, &x, &y);
		if(SearchCycle(saveGraph, x, y)){
			SaveNode(saveGraph, x, y, min);
			sum += min;
			checker++;
		}
	}
	printf("Minimum cost : %d\n\n", sum);
}

void SaveNode(int saveGraph[SIZE][SIZE], int x, int y, int min){
	saveGraph[x][y] = min;
	saveGraph[y][x] = min;
}

int SearchCycle(int saveGraph[SIZE][SIZE], int x, int y){
	int i = 0, output = 1, saveX = 0, saveY = 0;
	for(i = 0; i < SIZE; i++){
		if(saveGraph[x][i] > 0){
			saveX= i;
		}
		if(saveGraph[y][i] > 0){
			saveY= i;
		}
		if(saveGraph[x][i] > 0 && saveGraph[y][i] > 0){
			output = 0;
			break;
		}
		else if(saveY > 0 && saveX > 0 && saveGraph[saveY][saveX] > 0){
			output = 0;
			break;
		}
	}
	return output;
}

int SearchMin(int graph[SIZE][SIZE], int min, int *x, int *y){
	int output = 100, i = 0, k = 0;

	for(i = 0; i < SIZE; i++){
		for(k = 0; k < SIZE; k++){
			if(graph[i][k] > min && graph[i][k] < output){
				output = graph[i][k];
				*y = i;
				*x = k;
			}
		}
	}
	return output;
}