#include <stdio.h>
#include <stdlib.h>
#define ERROR_POP -9999	
#define END -99999	

typedef struct
{
	int *stack ;
	int top ;
}STACK ;

int size ;

void push(int data, STACK *stack);
int pop(STACK *stack);
int isEmpty(STACK *stack);
int isFull(STACK *stack);
void hanoi(int disc, STACK *src, STACK *dest, STACK *aux);
void print(int disc, STACK *src, STACK *dest, STACK *aux);

void main()
{
	STACK *src, *dest, *aux ;
	int i ;

	size = 10 ;										//stack 크기

	src = (STACK *)malloc(sizeof(STACK));
	dest = (STACK *)malloc(sizeof(STACK));
	aux = (STACK *)malloc(sizeof(STACK));
	
	src->stack = (int *)malloc(sizeof(int) * size);
	dest->stack = (int *)malloc(sizeof(int) * size);
	aux->stack = (int *)malloc(sizeof(int) * size);

	src->top = 0 ;
	dest->top = 0 ;
	aux->top = 0 ;

	for( i = 0 ; i < size ; i++)
	{
		src->stack[i] = 0 ; 
		dest->stack[i] = 0 ;
		aux->stack[i] = 0 ;
	}
	for( i = size ; i >= 1 ; i--)
		push(i, src);
	
	hanoi(size, src, dest, aux);

	print(size, src, dest, aux);

	free(src->stack);
	free(dest->stack);
	free(aux->stack);
	free(src);
	free(dest);
	free(aux);

	return ;		//프로그램 종료부
}

void push(int data, STACK *stack) 
{
	if(isFull(stack) == 1)
		return ;
	else
	{
		stack->stack[stack->top] = data ;
		stack->top++ ;
		return ;
	}
}

int pop(STACK *stack) 
{
	int temp ; //

	if(isEmpty(stack) == 1)
		return ERROR_POP ;
	else
	{
		stack->top-- ;

		temp = stack->stack[stack->top] ;
		stack->stack[stack->top] = 0 ;
		return temp ;
		/*
		return stack->stack[stack->top] ;
		*/
	}
}

int isEmpty(STACK *stack)	
{
	if(stack->top == 0)
	{
		printf("STACK is empty\n");
		return 1 ;
	}
	else
		return 0 ;
}
int isFull(STACK *stack)	
{
	if(stack->top == size )
		return 1 ;
	else
		return 0 ;
}

void hanoi(int disc, STACK *src, STACK *dest, STACK *aux) 
{
	int temp ;

	if(disc == 1)
	{
		temp = pop(src);
		push(temp, dest);
		return ;
	}
	else
	{
		hanoi(disc -1, src, aux, dest);
	
		temp = pop(src);
		push(temp, dest);
		
		hanoi(disc -1, aux, dest, src);
	}
	return ;
}

void print(int disc, STACK *src, STACK *dest, STACK *aux)
{
	int i ;

	printf("  src dest  aux\n");

	for(i = disc -1 ; i >= 0 ; i--)
		printf("%5d%5d%5d\n", src->stack[i], dest->stack[i], aux->stack[i]);
}