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

void go(int me, int from, int graph[8][8], int vertexPoint[8])
{
	int count;

	for(count = 0; count < 8; count++)
	{
		if(graph[me][count] != 0 && count != from)
		{
			vertexPoint[count] += 1;
			if(vertexPoint[count] > 1)
				return ;

			go(count, me, graph, vertexPoint);
		}
	}
}

int cycleCheck(int graph[8][8])
{
	int count;
	int vertexPoint[8] = {0};
	vertexPoint[0] = 1;

	go(0, -1, graph, vertexPoint);

	for(count = 0; count < 8; count++)
	{
		if(vertexPoint[count] > 1)
			return 0;
	}

	return 1;
}

int kk(int graph[8][8], int output[8][8])
{
	int numOfEdge = 0;
	int lastMin = 0;
	
	int result = 0;

	while(numOfEdge < 8-1)
	{
		int count1;
		int count2;
		int min = graph[0][0];
		for(count1 = 0; count1 < 8; count1++)
		{
			for(count2 = 0; count2 < 8; count2++)
			{
				if((min == 0 && lastMin < graph[count1][count2]) || ( lastMin < graph[count1][count2] &&  graph[count1][count2] < min))
					min = graph[count1][count2];
			}
		}

		for(count1 = 0; count1 < 8; count1++)
		{
			int doBreak = 0;
			for(count2 = 0; count2 < 8; count2++)
			{
				if(min == graph[count1][count2])
				{
					output[count1][count2] = graph[count1][count2];
					output[count2][count1] = graph[count1][count2];

					if(cycleCheck(output) == 1)
					{
						result += graph[count1][count2];
						numOfEdge += 1;
						
					}
					else
					{
						output[count1][count2] = 0;
						output[count2][count1] = 0;
					}

					doBreak = 1;
					lastMin = min;
					break;
				}
			}

			if(doBreak == 1)
				break;
		}
	}

	return result;
}


int main()
{
	int result;

	int graph[8][8] = {
		{0, 2, 8, 0, 0, 0, 0, 0}, 
		{2, 0, 7, 9, 0, 0, 0, 0}, 
		{8, 7, 0, 4, 10, 0, 0, 0}, 
		{0, 9, 4, 0, 0, 12, 0, 0}, 
		{0, 0, 10, 0, 0, 6, 14, 0}, 
		{0, 0, 0, 12, 6, 0, 0, 0}, 
		{0, 0, 0, 0, 14, 0, 0, 3}, 
		{0, 0, 0, 0, 0, 0, 3, 0}};


	int output[8][8] = {0};

	result = kk(graph, output);

	return 0;
}