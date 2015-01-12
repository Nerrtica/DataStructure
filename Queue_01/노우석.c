#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

int front=0,rear=0;
int  stack[MAX_SIZE];

void push(int data);
int pop();
int isEmpty();
int isFull();

int main(){

	int data,i;
	while(1){
	
		scanf("%d",&data);
		push(data);
		if(rear == 3){
			printf("%d ",pop());
			printf("%d ",pop());
			printf("%d\n",pop());
			printf("%d %d",front,rear);
		}
	}

}

void push(int data){

	if(isFull()) return;
	else{
		stack[rear++] = data;
		return;
	}
}

int pop(){

	if(isEmpty()){
		printf("Empty error\n");
		return 0;
	}
	else{
		return stack[front++];
	}
}

int isEmpty(){
	if(rear == front) return 1;		
	else return 0;
}

int isFull(){
	if(rear == MAX_SIZE) return 1;
	else return 0;
}