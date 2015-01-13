#include <stdio.h>
#include <stdlib.h>

#define POP_ERROR -111
#define TOTAL 4

typedef struct _stack
{
	int * data;
	int top;
	int max;
}
STACK;

void initStack(STACK *s, int max)
{
	s->data = (int*)malloc(sizeof(int)*max);
	s->top = -1;
	s->max = max;
}

void push(STACK *s, int data)
{
	if(isFull(s) == 0)
	{
		s->top += 1;
		s->data[s->top] = data;
	}

	return;
}
int pop(STACK *s)
{
	if(isEmpty(s))
	{
		return POP_ERROR;
	}
	else
	{
		int val;
		s->top -= 1;
		val = s->data[s->top+1];
		s->data[s->top+1] = 0;
		return val;
	}
}

int isEmpty(STACK *s)
{
	if(s->top <= -1)
		return 1;
	else
		return 0;
}
int isFull(STACK *s)
{
	if(s->top >= s->max-1)
	{
		s->max *= 2;
		s->data = (int*)realloc(s->data, sizeof(int)*(s->max));
	}

	return 0;
}

void hanoiMove(int disc, STACK * src, STACK * dest, STACK * aux)
{
	if(disc == 1)
	{
		int count;
		push(dest, pop(src));
		for(count = TOTAL-1; count >= 0; count--)
		{
			printf("%d %d %d\n", src->data[count], dest->data[count], aux->data[count]);
		}
		printf("\n");
	}
	else if(disc > 1)
	{
		hanoiMove(disc-1, src, aux, dest);
		hanoiMove(1, src, dest, aux);
		hanoiMove(disc-1, aux, dest, src);
	}

	return;
}

int main()
{
	int count = 0;

	STACK poll[3];

	initStack(&poll[0], TOTAL);
	initStack(&poll[1], TOTAL);
	initStack(&poll[2], TOTAL);

	for(count = 0; count < TOTAL; count++)
	{
		push(&poll[0], TOTAL-count);
		poll[1].data[count] = 0;
		poll[2].data[count] = 0;
	}

	for(count = TOTAL-1; count >= 0; count--)
	{
		printf("%d %d %d\n", poll[0].data[count], poll[1].data[count], poll[2].data[count]);
	}

	printf("\n");
	puts("start");
	hanoiMove(TOTAL, &poll[0], &poll[2], &poll[1]);
	printf("\n");

	for(count = TOTAL-1; count >= 0; count--)
	{
		printf("%d %d %d\n", poll[0].data[count], poll[1].data[count], poll[2].data[count]);
	}
}