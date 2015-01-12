#include<stdio.h>
#pragma warning(disable:4996)
#define MAX_SIZE 100

typedef struct _STACK{
	int stack[MAX_SIZE];
	int top;
}STACK;

int isEmpty(STACK *sta);
int isFull(STACK *sta);
void Push(STACK *sta);
int POP(STACK *sta);

int main(void){
	STACK st, *sta;
	int i;
	sta = &st;
	sta->top = 0;
	for(i = 0; i < MAX_SIZE; i++)
		sta->stack[i] = 0;
	while(1){
		printf("select(1 : Push, 2 : Pop) : ");
		scanf("%d", &i);
		if(i == 1){
			Push(sta);
		}
		else if(i == 2){
			POP(sta);
		}
	}
	return 0;
}

int isEmpty(STACK *sta){
	if((sta->top) == 0)
		return 1;
	else
		return 0;
}
int isFull(STACK *sta){
	if((sta->top) == MAX_SIZE)
		return 1;
	else
		return 0;
}
void Push(STACK *sta){
	int i;
	if(isFull(sta)){
		printf("cant\n");
	}
	else{
		printf("data input(int) : ");
		scanf("%d", &i);
		sta->stack[sta->top] = i;
		(sta->top)+=1;
	}
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
