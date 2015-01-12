#include<stdio.h>
#include<stdlib.h>

int top=0;
int *stack;

int isEmpty(int *stack1){
	int i;
	if(top==0){
			return 1;
		}
		else{
			return 0;
		}
}

int isFull(int *stack1){
	int i;

	if(top==10){
		stack=(int*)realloc(stack,10*sizeof(int));
	}
	else{
		return 0;
	}
}

void push(int data){
		stack[top]=data;
		top++;
	}

int pop(){
	int tmp;
	if(isEmpty(stack)==1){
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
	int i;
	int data,menu;
	stack=(int*)malloc(sizeof(int)*10);
	while(1){
		printf("1.push 2.pop\n");
		scanf("%d",&menu);
			if(menu==1){
				printf("input a data to push\n");
				scanf("%d",&data);
				push(data);
				for(i=0;i<top;i++){
					printf("%d",stack[i]);
				}
				printf("\n");
			}
			else{
				printf("pop the data");
				pop();
				for(i=0;i<top;i++){
					printf("%d",stack[i]);
				}
				printf("\n");
			}
	}
	return 0;
}

