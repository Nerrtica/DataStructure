#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int top=0;
int size=10;
int *stack;

int isEmpty(){
	int i;
	if(top==0){
			return 1;
		}
		else{
			return 0;
		}
}

int isFull(){
	int i;

	if(top==10){
		size*=2;
		stack=(int*)realloc(stack,size*sizeof(int));
	}
	else{
		return 0;
	}
}

void push(int data){
	if(isFull()==1){
		printf("stack is full\n");
	}
	else{
		stack[top]=data;
		top++;
	}
}

int pop(){
	int tmp;
	if(isEmpty()==1){
		printf("cannot pop,\n");
	}
	else{
		top--;
		tmp=stack[top];
		stack[top]=NULL;
		return tmp;
	}
}
int main(void){
	char str[10];
	int val1;
	int val2;
	int i;
	stack=(int*)malloc(sizeof(int)*10);
	scanf("%s",str);
	for(i=0;i<strlen(str);i++){
		if(str[i]>='0'&&str[i]<='9'){
			push(str[i]-'0');
		}
		else{
			switch(str[i])
			{
				case '+':
					val1=pop();
					val2=pop();
					push(val2+val1);
					break;
				case '-':
					val1=pop();
					val2=pop();
					push(val2-val1);
					break;
				case '*':
					val1=pop();
					val2=pop();
					push(val2*val1);
					break;
				case '/':
					val1=pop();
					val2=pop();
					push(val2/val1);
					break;
			}
		}
	}
	if(top!=1){
		printf("You enter a wrong equation\n");
		return 0;
	}
	printf("%d",stack[0]);
	return 0;
}


