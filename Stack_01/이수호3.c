#include <stdio.h>

#define MAX_SIZE 100

typedef struct _queue
{
	int data[MAX_SIZE];
	int front;
	int rear;
}
QUEUE;

void initQueue(QUEUE *q)
{
	q->front = 0;
	q->rear = 0;
}

void push(QUEUE *q, int data)
{
	if(isFull(q) == 0)
	{
		q->data[q->rear] = data;
		q->rear += 1;
	}
}

int pop(QUEUE *q)
{
	if(isEmpty(q) == 0)
	{
		q->front += 1;
		return q->data[q->front-1];
	}
}

int isEmpty(QUEUE *q)
{
	if(q->front == q->rear)
		return 1;
	else
		return 0;
}

int isFull(QUEUE *q)
{
	if(q->rear >= MAX_SIZE)
		return 1;
	else
		return 0;
}

int main()
{
	int count  = 0;
	QUEUE q;

	initQueue(&q);

	while(count < MAX_SIZE)
	{
		push(&q, count);
		count += 1;
	}

	while(isEmpty(&q) == 0)
	{
		printf("%d\n", pop(&q));
	}
}
