#include <stdio.h>
#pragma warning(disable:4996)
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct _QUEUE{
	int queue[MAX_SIZE];
	int front;
	int rear;
}QUEUE;

int isEmpty(QUEUE *qu);
int isFull(QUEUE *qu);
void Push(QUEUE *qu);
int POP(QUEUE *qu);

int main(void){
	QUEUE q, *qu;
	int i = 0;
	qu = &q;
	qu->front = 0;
	qu->rear = 0;
	while(1){
		printf("select(1 : push, 2 : pop) : ");
		scanf("%d", &i);
		if(i == 1)
			Push(qu);
		else if(i == 2)
			POP(qu);
		else
			break;
	}
	return 0;
}

int isEmpty(QUEUE *qu){
	if(qu->rear == qu->front)
		return 1;
	else
		return 0;
}

int isFull(QUEUE *qu){
	if(qu->rear == MAX_SIZE)
		return 1;
	else
		return 0;
}

void Push(QUEUE *qu){
	if(isFull(qu)){
		printf("cant\n");
	}
	else{
		printf("data input(int) : ");
		scanf("%d", &(qu->queue[qu->rear++]));
	}
}

int POP(QUEUE *qu){
	if(isEmpty(qu)){
		printf("cant\n");
	}
	else{
		printf("output : %d\n", qu->queue[qu->front++]);
	}
	return qu->queue[qu->front - 1];
}