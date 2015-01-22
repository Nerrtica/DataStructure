#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
#define SIZE 11

typedef struct _CONTAINER{
	int stack[SIZE];
	int queue[SIZE];
	int twice[SIZE];
	int stackTop;
	int queueTop;
	int queueTail;
}CONTAINER;

void DFS(CONTAINER point, int graph[11][11], int start, int end);
int CheckCanGo(CONTAINER point, int graph[11][11], int spot);
void BFS(CONTAINER point, int graph, int start, int end);
void StackPush(CONTAINER *point, int spot);
int StackPop(CONTAINER *point);
void QueuePush(CONTAINER *point, int spot);
int QueuePop(CONTAINER *point);

int main(void){
	CONTAINER point;
	int graph[SIZE][SIZE] = {
		{0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0}, 
		{1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0}, 
		{0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0}, 
		{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, 
		{0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0}, 
		{0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0}, 
		{0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0}, 
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, 
		{0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0}, 
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, 
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}};
	int i = 0, k = 0, j = 0;
	int input = 0, start = 0, end = 0, checker = 1;

	for(i = 0; i < SIZE; i++){
		point.stack[i] = 0;
		point.queue[i] = 0;
		point.twice[i] = 1;
	}
	point.stackTop = 0;
	point.queueTail = 0;
	point.queueTop = 0;

	printf("어떤 방법으로 미로를 찾으시겠습니까?(1 : DFS, 2 : BFS) : ");
	scanf("%d", &input);
	printf("시작점은? : ");
	scanf("%d", &start);
	printf("종착점은? : ");
	scanf("%d", &end);
	if(input){
		DFS(point, graph, start, end);
	}
	else{
		BFS(point, graph, start, end);
	}

	return 0;
}

void DFS(CONTAINER point, int graph[11][11], int start, int end){
	int i = 0, j = 1, here = start;
	int out[SIZE] = {0, };
	point.twice[start - 1] = 0;
	while(j){
		if(here == end){
			printf("노드가 완성되었습니다.");
			printf("%d", start);
			for(i = 0; i < point.stackTop; i++){
				printf("->%d", point.stack[i]);
			}
			printf("\n");
			j = 0;
		}
		else{
			for(i = 0; i < SIZE; i++){
				if(graph[here - 1][i] == 1 && point.twice[i] == 1){
					here = i + 1;
					point.twice[i] = 0;
					StackPush(&point, here);
					break;
				}
				else if(i == SIZE - 1){
					if(CheckCanGo(point, graph, here)){
						printf("도달할 수 없습니다.\n");
						j = 0;
					}
					else{
						here = StackPop(&point);
					}
				}
			}
		}
	}
	
}

int CheckCanGo(CONTAINER point, int graph[11][11], int spot){
	int i = 0, output = 0;
	for(i = 0; i < SIZE; i++){
		if(graph[spot - 1][i] == 1 && point.twice[i] == 1){
			output = 1;
		}
		
	}
	return output;
}

void BFS(CONTAINER point, int graph[11][11], int start, int end){
	int checker = 1, i = 0, here = start, count = 0;
	int saveNode[11] = {0, };
	QueuePush(&point, start);
	point.twice[start - 1] = 0;
	while(checker){
		for(i = 0; i < SIZE; i++){
			if(graph[here - 1][i] == 1 && point.twice[here - 1] == 1){
				QueuePush(&point, i + 1);
				count++;
			}
			if(count > 0){
				StackPush(&point, QueuePop(&point));
			}
			else{
				QueuePop(&point);
			}
			count = 0;
		}
		
		if(point.queueTail == point.queueTop){
			checker = 0;
		}
	}
	printf("노드 완성\n%d", point.queue[0]);
	for(i = 1; i < point.queueTop; i++){
		printf("->%d", point.queue[i]);
	}
	printf("\n\n");
}

void StackPush(CONTAINER *point, int spot){
	(*point).stack[(*point).stackTop] = spot;
	(*point).stackTop++;
}

int StackPop(CONTAINER *point){
	(*point).stackTop--;
	return (*point).stack[(*point).stackTop - 1];
}

void QueuePush(CONTAINER *point, int spot){
	(*point).queue[(*point).queueTop] = spot;
	(*point).queueTop++;
}

int QueuePop(CONTAINER *point){
	(*point).queueTail++;
	return (*point).queue[(*point).queueTail - 1];
}