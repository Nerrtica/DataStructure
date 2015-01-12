#include <stdio.h>
#include <stdlib.h>

typedef struct _queue
{
	int *data;
	int front;
	int rear;
	int max;
}
QUEUE;

void initQueue(QUEUE *q, int max)
{
	q->data = (int*)malloc(sizeof(int)*max);
	q->front = 0;
	q->rear = 1;
	q->max = max;
}

int push(QUEUE *q, int data)
{
	isFull(q);
	q->data[q->rear] = data;
	q->rear += 1;
	q->rear %= q->max;
	return 1;
}

int pop(QUEUE *q, int *data)
{
	if(isEmpty(q) == 0)
	{
		q->front += 1;
		q->front %= q->max;
		*data = q->data[q->front];
		return 1;
	}

	return 0;
}

int isEmpty(QUEUE *q)
{
	if((q->front+1)%q->max == q->rear)
	{
		printf("Empty!\n");
		return 1;
	}
	else
		return 0;
}

int isFull(QUEUE *q)
{
	if((q->rear+1)%q->max == q->front)
	{
		q->max *= 2;
		q->data = (int*)realloc(q->data, sizeof(int)*(q->max));

		if(q->front > q->rear)
		{
			int count = 1;

			while((q->max/2)-count > q->front)
			{
				q->data[q->max - count] = q->data[(q->max/2)-count];
				count += 1;
			}

			q->front = q->max - count;
		}

		return 1;
	}
	else
		return 0;
}

int main()
{
	int count  = 0;
	QUEUE q;

	initQueue(&q, 5);

	while(1)
	{
		int input;
		int val;
		scanf("%d", &input);
		if(1<= input && input <= 9)
		{
			push(&q, input);
		}
		else
		{
			if(pop(&q, &val))
				printf("%d!\n", val);
		}

		for(count = 0; count < q.max; count++)
		{
			if(q.front < q.rear)
			{
				if(q.front < count && count < q.rear)
					printf("%d ", q.data[count]);
				else
					printf("E ");
			}
			else
			{
				if(count < q.rear || q.front < count)
					printf("%d ", q.data[count]);
				else
					printf("E ");
			}
		}
		printf("\n");
	}
}
