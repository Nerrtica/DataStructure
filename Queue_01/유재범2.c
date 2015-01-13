#include <stdio.h>
#pragma warning(disable:4996)
#include <stdlib.h>
//#define MAX_SIZE 5

typedef struct _QUEUE{
	int *queue;
	int front;
	int rear;
}QUEUE;

int isEmpty(QUEUE *qu);
int isFull(QUEUE *qu);
void Push(QUEUE *qu);
int POP(QUEUE *qu);

int qSize = 4;

int main(void){
	QUEUE q, *qu;
	int i = 0;
	qu = &q;
	qu->front = qSize - 1;
	qu->rear = qSize - 1;
	qu->queue = (int *)malloc(sizeof(int) * qSize);
	while(1){
		printf("select(1 : push, 2 : pop) : ");
		scanf("%d", &i);
		if(i == 1)
			Push(qu);
		else if(i == 2)
			POP(qu);
		//return value -1 : fail to pop
		else
			break;
	}
	free(qu->queue);
	return 0;
}

int isEmpty(QUEUE *qu){
	if(qu->front == qu->rear)
		return 1;
	else
		return 0;
}

int isFull(QUEUE *qu){
	int i;
	if(qu->rear == qu->front){
		qSize *= 2;
		realloc(qu->queue, sizeof(int) * qSize);

		for(i = qu->front; i < (qSize / 2); i++){
			qu->queue[i + (qSize / 2)] = qu->queue[i];
		}

		qu->front += (qSize / 2);
		return 1;
	}
	else
		return 0;
}

void Push(QUEUE *qu){
	qu->rear = (qu->rear + 1) % qSize;
	if(qu->front == qu->rear){
		if(isFull){
			printf("realloc success\n");
		}
	}
	
	printf("input size : ");
	scanf("%d", &qu->queue[qu->rear]);
	
}

int POP(QUEUE *qu){
	if(qu->front == qu->rear){
		if(isEmpty){
			printf("have no data\n");
			return -1;
		}
	}
	else{
		qu->front = (qu->front + 1) % qSize;
		printf("pop data : %d\n", qu->queue[qu->front]);
		return qu->queue[qu->front];
	}
}