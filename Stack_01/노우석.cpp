#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 8

int top= 0;
int *stack;
void push(int data);
int pop();
int isEmpty();
int isFull();

int main(){

	int data,i;
	
	stack=(*int) malloc(sizeof(int)*MAX_SIZE);

	
}

void push(int data){

	if(isFull()) return;
	else {
		*(stack+top++) = data;
	}
}

int pop(){

	if(isEmpty){
		return 0;
	}
	else{
		temp = stack[(top--) - 1];
		return temp;
	}
}

int isEmpty(){
	if(top == 0) return 1;		
	else return 0;
}

int isFull(){
	if(top == MAX_SIZE) realloc(stack, sizeof(int)*MAX_SIZE*2);
	else return 0;
}