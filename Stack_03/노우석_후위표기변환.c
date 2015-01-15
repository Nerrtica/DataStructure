#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct _stack
{
	char data[MAX];
	int top;
}
STACK;

void initStack(STACK *s);
void push(STACK *s, char data);
char pop(STACK *s);
int  isFull(STACK *s);
int  isEmpty(STACK *s);
int toPostfix(STACK *s, char equation[], int length);
int checkError(char equation[]);

int main(){
	int i,count=0;
	char equation[30];

	STACK result;
	initStack(&result);


	fflush(stdin);
	scanf("%s",equation);
	if(checkError(equation) == -1) {
		printf("Equation Error!\n");
		return 0;
	}
	
	toPostfix(&result, equation, strlen(equation));
	for(i=0; i<=result.top; i++){
		printf("%c", result.data[i]);
	}

	return 0;
}
int checkError(char equation[]){
	int i,count=0;
	for(i=0; i<strlen(equation); i++){
		if(equation[i] >= '0' && equation[i] <= '9'){
			continue;
		}
		else{
			if(equation[i] == '(') count++;
			else if(equation[i] == ')') count--;
			else if(equation[i] == '+' || equation[i] == '-' || equation[i] == '/' || equation[i] == '*') continue;
			else return -1;
		}
	}

	if(count == 0) return 1;
	else return -1;

}

void initStack(STACK *s)
{
	s->top = -1;
}

void push(STACK *s, char data)
{
	if(isFull(s) == 0)
	{
		s->top += 1;
		s->data[s->top] = data;
	}
}

char pop(STACK *s)
{
	if(isEmpty(s) == 0)
	{
		s->top -= 1;
		return s->data[s->top+1];
	}
	else return 'F';
}

int isFull(STACK *s)
{
	if(s->top == MAX -1)
		return 1;
	else
		return 0;
}

int isEmpty(STACK *s)
{
	if(s->top == -1)
		return 1;
	else
		return 0;
}

int toPostfix(STACK *s, char equation[], int length){

	int i;
	char c,temp;
	STACK tempstack;

	initStack(&tempstack);

	for(i=0; i<length; i++){
		if(equation[i] >= 48 && equation[i] <= 57){
			push(s,equation[i]);
		}
		else{
			if(equation[i] == '('){
				push(&tempstack, equation[i]);
			}
			else if(equation[i] == ')'){
				while((c = pop(&tempstack)) != '('){
					push(s, c);
				}
			}
			else{
				if(equation[i] == '*' || equation[i] == '/'){
					temp = pop(&tempstack);
					if(temp == '+' || temp == '-'){
						push(&tempstack, temp);
						push(&tempstack, equation[i]);
					}
					else if(temp == '*' || temp == '/'){
						push(s,temp);
						push(&tempstack, equation[i]);
					}
					else push(&tempstack, equation[i]);
				}
				else if(equation[i] == '+' || equation[i] == '-'){
					while(1){
						temp = pop(&tempstack);
						if(temp == '*' || temp == '/'){
							push(s, temp);
						}
						else if(temp == '+' || temp == '-'){
							push(s, temp);
							push(&tempstack, equation[i]);
							break;
						}
						else{
							push(&tempstack, temp);
							push(&tempstack, equation[i]);
							break;
						}
					}
				}
			}
		}
	}
	while(1){
		temp=pop(&tempstack);
		if(temp == 'F') break;
		else push(s,temp);
	}
}