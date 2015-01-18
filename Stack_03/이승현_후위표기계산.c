#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

typedef struct {
	int data[MAX_SIZE];
	int top;
} _stack;

char isEmpty( _stack * Stack );
char isFull( _stack * Stack );
void push( _stack * Stack, char data );
int pop( _stack * Stack );

int isNum( char Char ){

	if( Char == ')' || Char == '*' || Char == '/' || Char == '(' || Char == '(' || Char == '+' || Char == '-'  )
		return 0;	
	else
		return -1;

}

int main(){

	_stack Stack;
	int  i=0, j, var1, var2;
	char Equation[MAX_SIZE];

	Stack.top = 0;

	printf("Expression : "); scanf("%s",Equation); fflush(stdin);

	/////// STACK CALCULATE //////

	while( Equation[i] != '\0' ){

		if( isNum(Equation[i]) == 0 ){
			
			switch(Equation[i]){

			case '+':
				var1 = pop(&Stack);
				var2 = pop(&Stack);
				push(&Stack, var2+var1);
				break;

			case '-':
				var1 = pop(&Stack);
				var2 = pop(&Stack);
				push(&Stack, var2-var1);
				break;

			case '*':
				var1 = pop(&Stack);
				var2 = pop(&Stack);
				push(&Stack, var2*var1);
				break;

			case '/':
				var1 = pop(&Stack);
				var2 = pop(&Stack);
				push(&Stack, var2/var1);
				break;

			default:
				break;

			}

		}else{
			push(&Stack, Equation[i]-'0');
		}

		i++;
	}
	//////////////////////////////

	if( Stack.top == 0 )
		printf("Result : %d",Stack.data[0]);
	else{
		printf("WRONG EXPRESSION!\n");
		for(i=0; i<Stack.top; i++)
		printf("%d \n",Stack.data[i]);
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

void push( _stack * Stack, char data ){

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
		temp = Stack->data[Stack->top];
		Stack->top--;

		return temp;

	}
}