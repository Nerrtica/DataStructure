#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define ERROR_POP -9999	
#define END -99999	

int *stack ;
int size, top = 0 ;

void push(int data) ;
int pop() ;
int isEmpty() ;
int isFull() ;

void main()
{
	int select = 0, data, num ;

	size = 2 ;

	stack = (int *)malloc(sizeof(int) * size) ;

	while(1)
	{
		do
		{
		printf("push 1, pop 2, end %d input : ",END) ;
		scanf("%d",&select) ;
		}while(!(select == 1 || select == 2 || select == END)) ;

		if(select == 1)
		{
			printf("input : ") ;
			scanf("%d",&data) ;
			push(data) ;
		}
		else if(select == 2)
		{
			num = pop() ;
			if(num != ERROR_POP)
				printf("Here! : %d \n", num ) ;
		}
		else if(select == END)
		{
			printf("End Program\n") ;
			return ;
		}
	}
	
	free(stack) ;

	return ;
}

void push(int data) 
{
	if(isFull() == 1)
		return ;
	else
	{
		stack[top] = data ;
		top++ ;
		return ;
	}
}
int pop() 
{
	if(isEmpty() == 1)
		return ERROR_POP ;
	else
	{
		top-- ;
		return stack[top] ;
	}
}
int isEmpty()	
{
	if(top == 0)
	{
		printf("stack is empty\n") ;
		return 1 ;
	}
	else
		return 0 ;
}
int isFull()	
{
	if(top == size )
	{
		size *= 2 ;
		realloc(stack, (sizeof(int) * size)) ;
	}
		return 0 ;
}
