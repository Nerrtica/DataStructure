#include <stdio.h>

#define MAX_SIZE 8

int top= 0;

void push(int arr[],int data);
int pop(int arr[]);
int isEmpty();
int isFull();

int main(){
	int arr[MAX_SIZE]={0};
	int data,i;
	
	while(1){
		if(top == MAX_SIZE) {
			printf("%d\n",pop(arr));
		}
		else{
			scanf("%d", &data);
			push(arr,data);
			for(i=0;i<MAX_SIZE;i++) printf("%d  ",arr[i]);
			printf("\n");
		}
	}
	
}

void push(int arr[],int data){

	int std;
	std = isFull();
	if(std) return;
	else {
		arr[top] = data;
		top++;
	}
}

int pop(int arr[]){

	int std,temp;
	std = isEmpty();

	if(std){
		return 0;
	}
	else{
		temp = arr[top - 1];
		top--;
		return temp;
	}
}

int isEmpty(){
	if(top == 0) return 1;		//비어있음
	else return 0;
}

int isFull(){
	if(top == MAX_SIZE) return 1; //꽉차있음
	else return 0;
}