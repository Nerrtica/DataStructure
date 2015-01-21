#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 11

int top=0, front=0, rear=0, total_size=MAX_SIZE;
int  stack[11];
int *queue;
int graph[11][11] = {
	{0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0}, 
	{1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0}, 
	{0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0}, 
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, 
	{0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0}, 
	{0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0}, 
	{0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, 
	{0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0}, 
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, 
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}
};

int DFS(int start, int finish,int path[]);
void BFS(int start, int finish);
void stackPush(int data);
int stackPop();
int stackIsEmpty();
int stackIsFull();
void queuePush(int data);
int queuePop();
int queueIsFull();
int queueIsEmpty();
int canGo(int pos, int path[11], int lev[11]);

int main(){

	int data,i,path[11] = {0},level[11] = {0},
		start, finish;
	queue = (int *)malloc(sizeof(int)*MAX_SIZE);
	/*
	for(i=0; i<11; i++) path[i] = i+1;

	printf("start: ");
	scanf("%d",&start);

	printf("finish: ");
	scanf("%d",&finish);

	if(DFS(start,finish,path) == 1){
		for(i=0; i<11; i++){
			if(stack[i] != 0) printf(" %d ",stack[i]);
		}
	}
	else{
		printf("찾지 못하였습니다.\n");
	}
	*/
	BFS(1,8,level);
	//for(i=0;i<11;i++) printf(" %d ", level[i]);
}

int DFS(int start, int finish, int path[11]){

	int i, j, temp, rtemp = -1, count=0;

	stackPush(start);
	for(i=0; i<11; i++){
		if(path[i] == start) path[i] = -1;
	}
	if(start == finish) return 1;

	for(i=0; i<11; i++){
		if(graph[start-1][i] == 1){
			if(path[i] != -1){
				rtemp = DFS(i+1,finish,path);
			}
			else continue;
		}
		if(rtemp == 1) return 1;
	}
	stackPop();
	temp = stackPop();
	if(top == 0) return rtemp;
	DFS(temp, finish, path);
}

void BFS(int start, int finish, int lev[11]){

	int i, curvertex, path[11]={0}, flag, count=0, level=1, temp[10]={0};

	printf("시적점은 %d\n", start);
	queuePush(start);
	count++;
	path[start-1] = 1;
	lev[start-1] = level;
	level++;

	while(1){
		curvertex = queuePop();
		count--;
		if(curvertex == -1){	//if(isEmpty) curvertex is -1
			flag = -1;
			break;
		}
		for(i=0; i<11; i++){
			if(graph[curvertex-1][i] == 1){
				if(path[i] == 0){
					queuePush(i+1);
					path[i] = curvertex;
					lev[i] = level;
				}
				if((i+1) == finish) flag = 1;
			}
		}
		if(count == 0){
			level++;
			count = rear - front;
		}
		if(flag == 1) break;
	}

	if(flag == 1) {
		count = 0;
		while(finish != start){
			temp[count++] = finish;
			finish = path[finish-1];
		}
		temp[count] = start;
		for(i=count; i>=0; i--){
			printf(" %d ", temp[i]);
		}
	}
	else printf("못 찾았습니다.\n");
}
void stackPush(int data){

	if(stackIsFull()){
		printf("Full");
	}
	else{
		stack[top++] = data;
	}
}

int stackPop(){

	int temp;

	if(stackIsEmpty()){
		return 0;
	}
	else{
		temp = stack[--top];
		return temp;
	}
}

int stackIsEmpty(){
	if(top == 0) return 1;		
	else return 0;
}

int stackIsFull(){
	if(top == MAX_SIZE) {
		return 1;
	}
	else return 0;
}

void queuePush(int data){

	if(queueIsFull()) stack[(rear)] = data;
	else stack[(rear)] = data;
	return;

}

int queuePop(){

	if(queueIsEmpty()){
		return -1;
	}
	else{
		front=(front+1)%total_size;
		return stack[front];
	}
}

int queueIsEmpty(){
	if(rear == front){
		return 1;
	}
	else return 0;
}

int queueIsFull(){
	int i,j;

	rear=(rear+1)%total_size;
	if(rear == front) {
		printf("Full\n");
		total_size *= 2;
		queue = (int *)realloc(stack, sizeof(int)*total_size);
		for(i=front+1; i<(total_size/2); i++)
			stack[i+total_size/2] = stack[i];
		front += (total_size) / 2;
		return 1;
	}
	else {
		return 0;
	}
}