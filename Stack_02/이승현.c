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

void Hanoi( int disc, _stack * src, _stack * aux, _stack * dest ){

	int tmp,i;

	if( disc == 1 ){
		tmp = pop(src);
		push(dest, tmp);

	}else{
		Hanoi( disc-1, src, dest, aux );
		tmp = pop(src);
		push(dest, tmp);

		Hanoi( disc-1, aux, src, dest );
			for( i=6; i>=0; i--)
				printf("%d   %d   %d \n", src->data[i], aux->data[i], dest->data[i]);
			printf("============\n");
	}
}

int main(){

	_stack src,aux,dest = {0,};
	int i, data;
	
	src.top = 0;
	aux.top = 0;
	dest.top = 0;

	for( i=6; i>=0; i--){
		push( &src, i );
	}

	Hanoi( 7, &src, &aux, &dest );

	for( i=6; i>=0; i--){
		printf("%d   %d   %d \n", src.data[i], aux.data[i], dest.data[i]);
	}

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