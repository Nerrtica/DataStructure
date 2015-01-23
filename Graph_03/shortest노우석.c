#include <stdio.h>

#define SIZE 7

int graph[SIZE][SIZE] = {
	{0, 6, 2, 16, 0, 0, 14}, 
	{0, 0, 0, 5, 4, 0, 0}, 
	{0, 7, 0, 0, 3, 8, 0}, 
	{0, 0, 0, 0, 0, 0, 3}, 
	{0, 0, 0, 4, 0, 0, 10}, 
	{0, 0, 0, 0, 0, 0, 1}, 
	{0, 0, 0, 0, 0, 0, 0}
};

int makepd(int path[], int dis[], int start, int finish);
void printPath(int path[], int start, int finish);
int minPosInDistance(int dis[], int found[]);

int main(){

	int path[SIZE] = {0}, dis[SIZE] = {0}, 
		result, start, finish, 
		i, j;

	printf("Put start: ");
	scanf("%d", &start);
	printf("Put finish: ");
	scanf("%d", &finish);

	result = makepd(path, dis, start-1, finish-1);
	
	if(result == 1){
		printf("Path:  ");
		printPath(path, start-1, finish-1);
		printf("Cost:  ");
		printf("%3d\n", dis[finish-1]);
	}
	else{
		printf("Not Found\n");
	}

	return 0;
}

int makepd(int path[], int dis[], int start, int finish){

	int found[SIZE] = {0}, i, min, tstart;

	for(i=0; i<SIZE; i++){
		if(graph[start][i] ){
			dis[i] = graph[start][i];
			path[i] = start;
		}
	}

	while(found[finish] != 1){

		tstart = minPosInDistance(dis, found);
		if(tstart == -1) return -1;

		found[tstart] = 1;

		for(i=0; i<SIZE; i++){
			if(graph[tstart][i] != 0 && dis[i] != 0){
				if(dis[i] > dis[tstart] + graph[tstart][i]){
					dis[i] = dis[tstart] + graph[tstart][i];
					path[i] = tstart;
				}
			}
			else if(graph[tstart][i] != 0 && dis[i] == 0){
				dis[i] = dis[tstart] + graph[tstart][i];
				path[i] = tstart;
			}
		}

	}

	return 1;
}

void printPath(int path[], int start, int finish){

	int temp[SIZE], count = 0 ,i;
	while(finish != start){
		temp[count++] = finish;
		finish = path[finish];
	}

	temp[count] = start;

	for(i=count; i>0; i--){
		printf("%d -> ", temp[i]+1);
	}
	printf("%d", temp[0]+1);
	printf("\n");
}

int minPosInDistance(int dis[], int found[]){
	int min = -1, pos = -1, i;

	for(i=0; i<SIZE; i++){
		if(dis[i] != 0 && found[i] != 1) {
			min = dis[i];
			pos = i;
		}
	}

	for(i=0; i<SIZE; i++){
		if(min > dis[i] && dis[i] != 0 && found[i] != 1){
			min = dis[i];
			pos = i;
		}
	}
	
	return pos;
}