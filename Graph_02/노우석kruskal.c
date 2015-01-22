#include <stdio.h>
#include <stdlib.h>

#define SIZE 8
#define MAX_SIZE 8

int top=0;
int stack[SIZE];

int graph[SIZE][SIZE] = {
	{0, 2, 8, 0, 0, 0, 0, 0}, 
	{2, 0, 7, 9, 0, 0, 0, 0}, 
	{8, 7, 0, 4, 10, 12, 0, 0}, 
	{0, 9, 4, 0, 0, 0, 0, 0}, 
	{0, 0, 10, 0, 0, 6, 14, 0}, 
	{0, 0, 12, 0, 6, 0, 0, 0}, 
	{0, 0, 0, 0, 14, 0, 0, 3}, 
	{0, 0, 0, 0, 0, 0, 3, 0}
};


void addEdge(int mygraph[]);
void queuePush(int data);
int DFS(int start, int finish, int path[11], int mygraph[SIZE][SIZE]);
void stackPush(int data);
int stackPop();
int stackIsEmpty();
int stackIsFull();

int main(){
	int mygraph[SIZE][SIZE]={0};
	int i,j;


	addEdge(mygraph);

	
	for(i=0; i<SIZE; i++){
		for(j=0; j<SIZE; j++) printf("%3d", mygraph[i][j]);
		printf("\n");
	}
	
}


void addEdge(int mygraph[SIZE][SIZE]){

	int minimum, i, j, xpos, ypos, edgenum = 0, tempgraph[SIZE][SIZE] = {0},path[SIZE];

	for(i=0; i<SIZE; i++){
		for(j=0; j<SIZE; j++) tempgraph[i][j] = graph[i][j];
	}

	while(1){
		minimum = 9999;
		for(i=0; i<SIZE; i++) path[i] = i+1;
		top = 0;

		for(i=0; i<SIZE; i++){
			for(j=0; j<SIZE; j++){
				if(minimum > tempgraph[i][j] && tempgraph[i][j] != 0){
					minimum = tempgraph[i][j];
					xpos = j;
					ypos = i;
				}
			}
		}

		if(DFS(ypos+1, xpos+1, path, mygraph) == -1){	//Not Connected
			mygraph[xpos][ypos] = minimum;
			mygraph[ypos][xpos] = minimum;
			edgenum++;
		}
		tempgraph[xpos][ypos] = 0;
		tempgraph[ypos][xpos] = 0;
		if(edgenum == SIZE-1) break;
	}
}

int DFS(int start, int finish, int path[SIZE], int mygraph[SIZE][SIZE]){

	int i, j, temp, rtemp = -1, count=0;

	stackPush(start);
	for(i=0; i<SIZE; i++){
		if(path[i] == start) path[i] = -1;
	}
	if(start == finish) return 1;

	for(i=0; i<SIZE; i++){
		if(mygraph[start-1][i] != 0){
			if(path[i] != -1){
				rtemp = DFS(i+1,finish,path, mygraph);
			}
			else continue;
		}
		if(rtemp == 1) return 1;
	}
	stackPop();
	temp = stackPop();
	if(top == 0) return rtemp;
	DFS(temp, finish, path, mygraph);
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