#include <stdio.h>
#include <stdlib.h>

#define POP_ERROR -111

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
		s->top -= 1;
		return s->data[s->top+1];
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

int main()
{
	int count = 0;

	STACK s;
	initStack(&s, 10);

	while(count <= 100)
	{
		push(&s, count);
		count += 1;
	}


	while(isEmpty(&s) == 0)
	{
		printf("%d\n", pop(&s));
	}
}