#include<stdio.h>
int top=0;
int stack[10]={NULL, };

int isEmpty(int *stack1){
	int i;
	for(i=0;i<10;i++){
		if(stack1[i]==NULL){
			printf("stack is empty.\n");
			return 1;
		}
		else{
			return 0;
		}
	}
}

int isFull(int *stack1){
	int i;

	if(top==11){
		printf("stack is full.\n");
		return 1;
	}
	else{
		return 0;
	}
}

void push(int data){
	if(isFull(stack)==1){
		printf("cannot push,\n");
	}
	else{
		stack[top]=data;
		top++;
	}
}

void pop(){
	if(isEmpty(stack)==1){
		printf("cannot pop,\n");
	}
	else{
		top--;
		stack[top]=NULL;
	}
}

int main(void){
	int i;
	push(2);
	push(3);
	for(i=0;i<10;i++){

		printf("%d",stack[i]);
	}
	printf("\n");
	pop();
	for(i=0;i<10;i++){

		printf("%d",stack[i]);
	}
	push(1);
	printf("\n");
		for(i=0;i<10;i++){

		printf("%d",stack[i]);
	}
	return 0;
}

