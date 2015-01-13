#include<stdio.h>
#pragma warning(disable:4996)
#include<stdlib.h>
//#define MAX_SIZE 100

typedef struct _STACK{
	int *stack;
	int top;
}STACK;

int isEmpty(STACK *sta);
int isFull(STACK *sta);
void Push(STACK *sta);
int POP(STACK *sta);

int mem = 1;

int main(void){
	STACK st, *sta;
	int i = 0;
	sta = &st;
	sta->top = 0;
	sta->stack = (int *)malloc(sizeof(int) * mem);
	while(1){
		printf("select(1 : Push, 2 : Pop) : ");
		scanf("%d", &i);
		if(i == 1){
			Push(sta);
		}
		else if(i == 2){
			POP(sta);
		}
		else
			break;
	}
	free(sta->stack);
	return 0;
}

int isEmpty(STACK *sta){
	if((sta->top) == 0)
		return 1;
	else
		return 0;
}
int isFull(STACK *sta){
	if((sta->top) == mem){
		mem *= 2;
		sta->stack = (int *)realloc(sta->stack, (sizeof(int) * mem));
		return 1;
	}
	else
		return 0;
}
void Push(STACK *sta){
	int i = 0;
	if(isFull(sta)){
		printf("realloc complete\n");
	}
	printf("data input(int) : ");
	scanf("%d", &i);
	sta->stack[sta->top] = i;
	(sta->top)+=1;
}
int POP(STACK *sta){
	if(isEmpty(sta)){
		printf("cant\n");
	}
	else{
		printf("data output : %d\n", sta->stack[sta->top - 1]);
		(sta->top)-=1;
	}
	return sta->stack[sta->top];
}
