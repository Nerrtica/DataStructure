#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 2

int top= 0;
int  *stack;

void push(int data);
int pop();
int isEmpty();
int isFull();

int main(){

	int data,i;
	
	stack=(int*) malloc(sizeof(int)*MAX_SIZE);
	
	while(1){
		scanf("%d",&data);
		push(data);
		if(top == 4) {
			printf("%d",pop());
			printf("%d",pop());
			printf("%d",pop());
		}
	}
}

void push(int data){

	*(stack+(top++)) = data;
}

int pop(){

	int temp;

	if(isEmpty()){
		return 0;
	}
	else{
		temp = stack[top - 1];
		top--;
		return temp;
	}
}

int isEmpty(){
	if(top == 0) return 1;		
	else return 0;
}

int isFull(){
	if(top == MAX_SIZE) {
		printf("realloc");
		realloc(stack, sizeof(int)*MAX_SIZE*2);
		return 1;
	}
	else return 0;
}