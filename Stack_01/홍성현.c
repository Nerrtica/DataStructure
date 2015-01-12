#include <stdio.h>

#define MAX_SIZE 2
#define ERROR_POP -9999	
#define END -99999	

int stack[MAX_SIZE] ;
int top = 0 ;

void push(int data) ;
int pop() ;
int isEmpty() ;
int isFull() ;

void main()
{
	int select = 0, data, num ;

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
				printf("Tyeo! : %d \n", num ) ;
		}
		else if(select == END)
		{
			printf("End Program\n") ;
			return ;
		}
	}

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
	if(top == MAX_SIZE )
	{
		printf("stack is full\n") ;
		return 1 ;
	}
	else
		return 0 ;
}
