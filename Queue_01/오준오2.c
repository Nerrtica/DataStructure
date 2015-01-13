#include<stdio.h>
#include<stdlib.h>
int SIZE=5;
int front=0;
int rear=0;
int *queue;

int push(int data){
	if(rear==SIZE-1){
		rear=0;
		SIZE=SIZE*2;
		queue=(int*)realloc(queue,sizeof(int)*SIZE);
	}
	else{
		queue[rear]=data;
		rear++;
	}
}

int pop(){
	if(front==SIZE-1){
		front=0;
		printf("queue is empty\n");
	}
	else{
		queue[front]=NULL;
		front++;
	}
	return 0;
}

//int isEmpty(int *queue1){
//	if(front==rear){
//		printf("queue is empty\n");
//		return 1;
//	}
//	else{
//		return 0;
//	}
//}
//
//int isFull(int *queue1){
//	if(rear==SIZE){
//		printf("queue is full\n");
//		return 1;
//	}
//	else{
//		return 0;
//	}
//}

int main(void){
	int i;
	int menu;
	int data;
	queue=(int*)malloc(sizeof(int)*SIZE);
	while(1){
		printf("1.push 2.pop\n");
		printf("choose menu: ");
		scanf("%d",&menu);
		if(menu==1){
			printf("input a data to push: ");
			scanf("%d",&data);
			push(data);
			for(i=0;i<SIZE;i++){
				printf("%d",queue[i]);
			}
			printf("\n");
		}
		else{
			printf("pop the data\n");
			pop();
			for(i=0;i<SIZE;i++){
				printf("%d",queue[i]);
			}
			printf("\n");
		}
	}
	free(queue);
	return 0;
}
