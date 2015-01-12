#include <stdio.h>
#define MAX_SIZE 10

typedef struct {
	int data[MAX_SIZE];
	int top;
} _stack;

char isEmpty( _stack * Stack );
char isFull( _stack * Stack );
void push( _stack * Stack, int data );
int pop( _stack * Stack );

int main(){

	_stack Stack;
	int i, data;

	Stack.top = 0;

	while(1){

		for( i=0; i<MAX_SIZE; i++)
			printf( "%d ", Stack.data[i] );

		printf("\n\nPlease input data to PUSH : ");
		scanf("%d",&data);
		push(&Stack, data);

		if(isFull(&Stack) == 0)
			break;

	}


	printf("\nPOP\n");
	printf("==================");

	while(1){

		data = pop(&Stack);
		printf("\n%d POP!",data);

		if(isEmpty(&Stack) == 0)
			break;

	}

	getchar();
	getchar();
	return 0;
}

char isEmpty( _stack * Stack ){

	if( Stack->top == 0 )
		return 0;
	else
		return -1;

}

char isFull( _stack * Stack ){

	if( Stack->top == MAX_SIZE )
		return 0;
	else
		return -1;

}

void push( _stack * Stack, int data ){

	if( isFull(Stack) == 0 )
		printf("\nSTACK IS FULL!\n");
	else{
		Stack->data[Stack->top] = data;
		Stack->top++;
	}
}

int pop( _stack * Stack ){

	int temp;

	if( isEmpty(Stack) == 0 ){
		printf("STACK IS EMPTY!");
		return -1;

	}else{
		
		Stack->top--;
		temp = Stack->data[Stack->top];
		return temp;

	}
}