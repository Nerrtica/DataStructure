#include <stdio.h>

#define MAX 100

typedef struct _stack
{
	int top;
	int data[MAX];
}
STACK;

void initStack(STACK * s)
{
	s->top = -1;
}

int push(STACK * s, int data)
{
	if(s->top < MAX-2)
	{
		s->top += 1;
		s->data[s->top] = data;
		return 1;
	}
	else
	{
		return 0;
	}
}

int pop(STACK * s, int * output)
{
	if(s->top >= 0)
	{
		s->top -= 1;
		*output = s->data[s->top+1];
		return 1;
	}
	else
	{
		return 0;
	}
}

typedef struct _queue
{
	int first;
	int last;
	int data[MAX];
}
QUEUE;

void initQueue(QUEUE * q)
{
	q->first = 0;
	q->last = 1;
}

int in(QUEUE * q, int data)
{
	if(q->last < MAX)
	{
		q->data[q->last] = data;
		q->last += 1;
		return 1;
	}
	else
	{
		return 0;
	}
}

int out(QUEUE * q, int * output)
{
	if(q->first+1 < q->last)
	{
		q->first += 1;
		*output = q->data[q->first];
		return 1;
	}
	else
	{
		return 0;
	}
}

void findDFS(int start, int end, int graph[11][11], STACK * s, int beenTo[11])
{
	int count;
	push(s, start);
	beenTo[start] = 1;
	if(start != end)
	{
		for(count = 0; count < 11; count++)
		{
			if(graph[start][count] == 1 && beenTo[count] != 1)
			{
				findDFS(count, end, graph, s, beenTo);
				break;
			}
		}

		if(count == 11)
		{
			int output;
			pop(s, &output);
			if(pop(s, &output) == 1)
				findDFS(output, end, graph, s, beenTo);
		}
	}
}

int findBFS(int start, int end, int graph[11][11], QUEUE * q, int beenTo[11], int rightBefore[11])
{
	int count;
	int outVal;

	if(out(q, &outVal) != 1)
		return 0;

	for(count = 0; count < 11; count++)
	{
		if(graph[outVal][count] == 1 && beenTo[count] != 1)
		{
			in(q, count);
			beenTo[count] = 1;
			rightBefore[count] = outVal;

			if(count == end)
				return 1;
		}
	}

	findBFS(start, end, graph, q, beenTo, rightBefore);
}

int main()
{
	int start;
	int end;

	int graph[11][11] = {
		{0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0}, 
		{1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0}, 
		{0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0}, 
		{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, 
		{0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0}, 
		{0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0}, 
		{0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0}, 
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, 
		{0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0}, 
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, 
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}};

	STACK stack;
	QUEUE queue;
	STACK route;

	int rb;

	int beenTo[11] = {0};

	int rightBefore[11] = {0 };

	initStack(&stack);
	initQueue(&queue);

	initStack(&route);

	printf("start: ");
	scanf("%d", &start);
	printf("end: ");
	scanf("%d", &end);
	
	in(&queue, start-1);
	beenTo[start-1] = 1;
	if(findBFS(start-1, end-1, graph, &queue, beenTo, rightBefore) == 1)
	{
		rb = end-1;
		while(rb != start-1)
		{
			push(&route, rb+1);
			rb = rightBefore[rb];
		}
		push(&route, rb+1);
	}
	else
	{
		printf("¸ø°¨\n");
	}

	while(1)
	{
		int val;
		if(pop(&route, &val) == 1)
		{
			printf("%d ", val);
		}
		else
		{
			printf("\n");
			break;
		}
	}
	return 0;
}