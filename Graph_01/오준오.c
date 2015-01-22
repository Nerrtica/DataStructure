#include<stdio.h>
#include<stdlib.h>

int top=0;
int stack[11];

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


int stack[11];

typedef struct _graph{
	int visited;
}graph;

int Graph[11][11]={
	{0,1,0,1,0,0,0,0,0,0,0},
	{1,0,1,0,1,1,0,0,0,0,0},
	{0,1,0,0,1,0,0,0,0,0,0},
	{1,0,0,0,0,1,0,0,0,0,0},
	{0,1,1,0,0,0,1,0,1,0,0},
	{0,1,0,1,0,0,1,0,1,0,0},
	{0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0},
	{0,0,0,0,1,1,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,1,0}
};

int visted[11]={0,0,0,0,0,0,0,0,0,0,0};


int searchGraph(int j, int end){
	int i, x, arrive=0;
	for(i=0;i<11;i++){
		if(Graph[j][i] ==1 && Graph[i][j] ==1 && visted[i] ==0){
			visted[i] = 1;
			push(i+1);
			for(x=0;x<11;x++){
				if(stack[x] != 0){
					printf("%d",stack[x]);
				}
			}
			printf("\n");
			if(i+1 == end){
				printf("arrive\n");
				break;
			}
			searchGraph(i,end);
			searchGraph(pop()-1,end);

			return i;
			break;
		}
	}
}

int main(void){
	int start, end;
	printf("input start and end point: ");
	scanf("%d %d",&start,&end);
	searchGraph(start,end);

	return 0;
}