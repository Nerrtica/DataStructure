#include <stdio.h>

#define SIZE 7

int graph[SIZE][SIZE] = {
	{999, 6, 5, 5, 999, 999, 999}, 
	{999, 999, 999, 999, -1, 999, 999}, 
	{999, -2, 999, 999, 1, 999, 999}, 
	{999, 999, -2, 999, 999, -1, 999}, 
	{999, 999, 999, 999, 999, 999, 3}, 
	{999, 999, 999, 999, 999, 999, 3}, 
	{999, 999, 999, 999, 999, 999, 999}
};

void BF(int n, int v, int finish);
void printPath(int path[], int start, int finish);

int main(){

	int start,finish;

	printf("Put start: ");
	scanf("%d", &start);
	printf("Put finish: ");
	scanf("%d", &finish);

	BF(SIZE, start, finish);
}

void BF(int n, int v, int finish){
	int i, j, u, k, dis[SIZE], path[SIZE], flag;

	for(i=0; i<n; i++){
		dis[i] = graph[v][i];
		path[i] = v;
	}

	for(i=2; i<=SIZE-1; i++){
		
		for(u=0; u<SIZE; u++){
			flag = -1;

			if(u == v) continue;
			else{
				for(j=0; j<SIZE; j++){
					if(graph[j][u] != 999) flag = 1;
				}
			}
			if(flag == 1){
				for(k=0; k<SIZE; k++){
					if(dis[u] > dis[k] + graph[k][u] && k != u){
						dis[u] = dis[k] + graph[k][u];
						path[u] = k;
					}
				}
			}
		}

	}

	printf("cost: %d", dis[finish]);
	printf("\n");
	printPath(path, v, finish);
}

void printPath(int path[], int start, int finish){

	int temp[SIZE], count = 0 ,i;
	while(finish != start){
		temp[count++] = finish;
		finish = path[finish];
	}

	temp[count] = start;

	for(i=count; i>0; i--){
		printf("%d -> ", temp[i]);
	}
	printf("%d", temp[0]);
	printf("\n");
}