#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

typedef struct {
	char data[MAX_SIZE];
	int top;
} _stack;

char isEmpty( _stack * Stack );
char isFull( _stack * Stack );
void push( _stack * Stack, char data );
void pop( _stack * Stack );

char isOppend( char Char ){

	if( Char == ')' || Char == '*' || Char == '/' || Char == '(' || Char == '(' || Char == '+' || Char == '-'  )
		return 1;	
	else
		return 0;

}

int main(){

	_stack Stack;
	int  i, j, leftParenthess, rightParenthess, count;
	char Equation[MAX_SIZE];

	Stack.top = 0;

	while(1){

		i=0;
		leftParenthess=0;
		rightParenthess=0;

		printf("Please input Equation : "); scanf("%s",Equation); fflush(stdin);

		while( Equation[i] != '\0' ){
			if(Equation[i] == '(') leftParenthess++;
			if(Equation[i] == ')') rightParenthess++;
			i++;
		}

		if( leftParenthess == rightParenthess ){
			break;
		}else{
			printf("WRONG EQUATION!\n");
			continue;
		}

	}

	/////// STACK CALCULATE //////
	i=0;

	while( Equation[i] != '\0' ){

		count = Stack.top;

		if( isOppend(Equation[i]) == 1 ){

			switch( Equation[i] ){
				
			case ')':
				if( isEmpty(&Stack) != 0 ){
					for(j=Stack.top; j>=0; j--){
						if( Stack.data[j] != '(' ){
							pop(&Stack);
						}
					}
				}
				break;

			case '*':
				if( isEmpty(&Stack) != 0 ){
					for(j=Stack.top; j>=0; j--){
						if( Stack.data[j] == '*' || Stack.data[j] == '/' ){
							pop(&Stack);
						}
						if( Stack.data[j] == '(' )
							break;
					}
				}
				push(&Stack,'*');
				break;

			case '/':
				if( isEmpty(&Stack) != 0 ){
					for(j=Stack.top; j>=0; j--){
						if( Stack.data[j] == '/' || Stack.data[j] == '*' ){
							pop(&Stack);
						}
						if( Stack.data[j] == '(' )
							break;
					}
				}
				push(&Stack, '/');
				break;

			case '+':
				if( isEmpty(&Stack) != 0 ){
					for(j=Stack.top; j>=0; j--){
						if( Stack.data[j] == '+' || Stack.data[j] == '-' || Stack.data[j] == '*' || Stack.data[j] == '/' ){
							pop(&Stack);
						}
						if( Stack.data[j] == '(' )
							break;
					}
				}
				push(&Stack,'+');
				break;

			case '-':
				if( isEmpty(&Stack) != 0 ){
					for(j=Stack.top; j>=0; j--){
						if( Stack.data[j] == '+' || Stack.data[j] == '-' || Stack.data[j] == '*' || Stack.data[j] == '/' ){
							pop(&Stack);
						}
						if( Stack.data[j] == '(' )
							break;
					}
				}
				push(&Stack, '-');
				break;

			case '(':
				push(&Stack, '(');
				break;

			default:
				break;

			}

		}else
			printf("%c",Equation[i]);
		
		i++;
	}

	if( Equation[i] == '\0' ){
		if( isEmpty(&Stack) != 0 ){
			pop(&Stack);
		}
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

void pop( _stack * Stack ){

	int temp;

	if( isEmpty(Stack) == 0 ){
		//printf("STACK IS EMPTY!");
		return;

	}else{
		
		Stack->top--;
		temp = Stack->data[Stack->top];

		if( temp == '(' || temp == ')' )
			printf("");
		else
			printf("%c",temp);

	}
}