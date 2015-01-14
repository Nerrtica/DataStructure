#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct stack
{
	char data[MAX];
	int top;
}
STACK;

void initStack(STACK * s)
{
	s->top = -1;
}

void push(STACK *s, char data)
{
	if(isFull(s) == 0)
	{
		s->top += 1;
		s->data[s->top] = data;
	}
}

char pop(STACK *s)
{
	if(isEmpty(s) == 0)
	{
		s->top -= 1;
		return s->data[s->top+1];
	}
}

int isFull(STACK *s)
{
	if(s->top == MAX - 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int isEmpty(STACK *s)
{
	if(s->top == -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int getValue(char c)
{
	int val;

	switch(c)
	{
	case '*':
	case '/':
		val = 2;
		break;
	case '+':
	case '-':
		val = 1;
		break;
	case '(':
	case ')':
		val = 0;
		break;
	default:
		val = -1;
	}

	return val;
}

int main()
{
	char input[MAX];
	int inputIndex = 0;
	char output[MAX] = {0, };
	int outputIndex = 0;

	STACK stack;

	initStack(&stack);

	printf("식 입력: ");
	scanf("%s", input);

	while(inputIndex < strlen(input))
	{
		if(getValue(input[inputIndex]) > 0)
		{
			while(isEmpty(&stack) == 0)
			{
				char popVal = pop(&stack);
				if(getValue(input[inputIndex]) <= getValue(popVal))
				{
					output[outputIndex] = popVal;
					outputIndex += 1;
				}
				else
				{
					push(&stack, popVal);
					break;
				}
			}

			push(&stack, input[inputIndex]);
		}
		else if(getValue(input[inputIndex]) == 0)
		{
			if(input[inputIndex] == ')')
			{
				while(isEmpty(&stack) == 0)
				{
					char popVal = pop(&stack);
					if(popVal == '(')
					{
						break;
					}
					else
					{
						output[outputIndex] = popVal;
						outputIndex += 1;
					}
				}
			}
			else
			{
				push(&stack, input[inputIndex]);
			}
		}
		else
		{
			output[outputIndex] = input[inputIndex];
			outputIndex += 1;
		}

		inputIndex += 1;
	}

	while(isEmpty(&stack) == 0)
	{
		output[outputIndex] = pop(&stack);
		outputIndex += 1;
	}
	printf("%s\n", output);
}