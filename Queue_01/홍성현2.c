#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define ERROR_POP -9999	
#define END -99999	

int *Queue ;
int size, front, rear ;

void push(int data) ;
int pop() ;
int isEmpty() ;
void Full() ;

void main()
{
	int select = 0, data, num ;
	int i ;

	size = 2 ;
	front = size -1 ;
	rear = size -1 ; 

	Queue = (int *)malloc(sizeof(int) * size) ;

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

//		for(i = 0 ; i < size ; i++)
//			printf("%d  ",Queue[i]) ;
//		printf("\n");
	}
	
	free(Queue) ;

	return ;
}

void push(int data) 
{
	rear = (rear + 1) % size ;

	if(front == rear)
		Full() ;

	Queue[rear] = data ;
	return ;
}
int pop() 
{
	if(isEmpty() == 1)
		return ERROR_POP ;
	else
	{
		front = (front + 1) % size ;
		return Queue[front] ;
	}
}
int isEmpty()	
{
	if(front == rear)
	{
		printf("Queue is empty\n") ;
		return 1 ;
	}
	else
		return 0 ;
}
void Full()	
{
	int i;
	
	printf("Full !!\n");

	size *= 2 ;
	realloc(Queue, (sizeof(int) * size)) ;

	for(i = front ; i < (size/2) ; i++)
		Queue[i + (size/2)] = Queue[i] ;

	front += (size/2) ;

	return ;
}
