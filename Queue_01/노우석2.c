#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 2

int front=0, rear=0, total_size=MAX_SIZE;
int *stack;

void push(int data);
int pop();
int isEmpty();
int isFull();

int main(){

	int data,i,select;
	stack = (int *)malloc(sizeof(int)*MAX_SIZE);
	while(1){
		printf("1.push 2.pop\n");
		scanf("%d",&select);
		if(select == 1){
			printf("Value: ");
			scanf("%d", &data);
			push(data);
		}
		else if(select == 2) printf("pop: %d\n",pop());
		else break;
		for(i=0;i<total_size; i++) printf("%d ", stack[i]);
		printf("\n");
	}
	free(stack);
	return;
}



void push(int data){

	if(isFull()) stack[(rear)] = data;
	else stack[(rear)] = data;
	return;

}

int pop(){

	if(isEmpty()){
		printf("Empty error\n");
		return -1;
	}
	else{
		front=(front+1)%total_size;
		return stack[front];
	}
}

int isEmpty(){
	if(rear == front){
		return 1;
	}
	else return 0;
}

int isFull(){
	int i,j;

	rear=(rear+1)%total_size;
	if(rear == front) {
		printf("Full\n");
		total_size *= 2;
		stack = (int *)realloc(stack, sizeof(int)*total_size);
		for(i=front+1; i<(total_size/2); i++)
			stack[i+total_size/2] = stack[i];
		front += (total_size) / 2;
		return 1;
	}
	else {
		return 0;
	}
}