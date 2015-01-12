#include <stdio.h>

#define MAX_SIZE 100
#define POP_ERROR -111

typedef struct _stack
{
	int data[MAX_SIZE];
	int top;
}
STACK;

void initStack(STACK *s)
{
	s->top = -1;
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
	if(s->top >= MAX_SIZE)
		return 1;
	else
		return 0;
}

int main()
{
	int count = 0;

	STACK s;
	initStack(&s);

	while(isFull(&s) == 0)
	{
		push(&s, count);
		count += 1;
	}


	while(isEmpty(&s) == 0)
	{
		printf("%d\n", pop(&s));
	}
}