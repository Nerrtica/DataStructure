#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 3

typedef struct _stack
{
	int data[MAX];
	int top;
}
STACK;

void initStack(STACK *s);
void push(STACK *s, int data);
int  pop(STACK *s);
int  isFull(STACK *s);
int  isEmpty(STACK *s);
int toPostfix(STACK *s, char equation[], int length);

int main(){
	int i,count=0;
	char equation[10];
	STACK result;
	initStack(&result);
	
	fflush(stdin);
	scanf("%s",equation);
	toPostfix(&result, equation, strlen(equation));
	
	printf(" %d ", result.data[0]);
}
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
}

int pop(STACK *s)
{
	if(isEmpty(s) == 0)
	{
		s->top -= 1;
		return s->data[s->top+1];
	}
}

int isFull(STACK *s)
{
	if(s->top == MAX -1)
		return 1;
	else
		return 0;
}

int isEmpty(STACK *s)
{
	if(s->top == -1)
		return 1;
	else
		return 0;
}

int toPostfix(STACK *s, char equation[], int length){
	
	int i,value1,value2,finalData;

	for(i=0; i<length; i++){
		if(equation[i] >= 48 && equation[i] <= 57){
			push(s,equation[i] - '0');
		}
		else{
			value1=pop(s);
			value2=pop(s);
			if(equation[i] == '*') finalData = value1 * value2;
			else if(equation[i] == '/') finalData = value2 / value1;
			else if(equation[i] == '+') finalData = value1 + value2;
			else if(equation[i] == '-') finalData = value1 - value2;
			else printf("잘못된 수식을 입력하셨습니다.\n");
			push(s,finalData);
		}
	}
}