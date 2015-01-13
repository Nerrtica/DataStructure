#include <stdio.h>
#define MAX_SIZE 10

typedef struct {
	int data[MAX_SIZE];
	int front;
	int rear;
}_queue;

char isEmpty( _queue Q ){

	if( Q.rear == Q.front ){
		return 0;
	}else
		return -1;

}

char isFull( _queue Q ){

	if( Q.rear == MAX_SIZE ){
		return 0;
	}else
		return -1;

}

void add( _queue * Q, int data ){

	if( isFull(*Q) == 0 ){
		printf("Queue is Full!");
	}else{
		Q->data[Q->rear] = data;
		Q->rear++;
	}

}

int del( _queue * Q ){

	int temp;

	if( isEmpty(*Q) == 0 ){
		printf("Queue is Empty!");
	}else{
		temp = Q->data[Q->front];
		Q->front++;
		return temp;
	}

}


int main(){

	_queue Q={0,};
	int i,data;

	while(1){

		for( i=0; i<MAX_SIZE; i++)
			printf( "%d ", Q.data[i] );

		printf("\n\nPlease input data to PUSH : ");
		scanf("%d",&data);
		add(&Q, data);

		if(isFull(Q) == 0)
			break;

	}


	printf("\nPOP\n");
	printf("==================");

	while(1){

		data = del(&Q);
		printf("\n%d POP!",data);

		if(isEmpty(Q) == 0)
			break;

	}

	getchar();
	getchar();


	return 0;
}