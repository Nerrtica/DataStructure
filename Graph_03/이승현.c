#include <stdio.h>

#define MAX 7
#define INF 9999

int distance[MAX];	  // cost를 담기위한 배열
int path[MAX] = {0,}; // path를 담기위한 배열

int MinimumIndex( int distance[], int found[] ){

	int i,min=INF,index;

	for(i=0; i<MAX; i++){
		if( found[i] == 0 ){
			if( min >= distance[i] ){
				min = distance[i];
				index = i;
			}
		}
	}
	
	return index;
}

void ShortestPath( int graph[MAX][MAX], int u, int v ){

	int i = 0,j; 

	////////// initialize ///////////
	int found[MAX] = {0,};

	for(i=0; i<MAX; i++)
		distance[i] = graph[u][i];

	found[u] = 1;
	distance[u] = 0;
	/////////////////////////////////

	for( i=0; i<MAX-2; i++){
		u = MinimumIndex( distance, found );
		found[u] = 1;

		for( j=0; j<MAX; j++){
			if( found[j] == 1 ) continue;
			if( distance[u] + graph[u][j] < distance[j] ){
				distance[j] = distance[u] + graph[u][j];
				path[j] = u;
			}
		}
	}

}

void showPath( int u, int v ){
	int a = path[v];
	int tempArray[MAX] = {0,}, tempIndex=0, i;

	tempArray[tempIndex] = v+1;
	path[u] = -1;

	while( path[a] != -1 ){
		tempIndex++;
		tempArray[tempIndex] = a+1;
		a = path[a];
	}

	tempIndex++;
	tempArray[tempIndex] = u+1;

	printf("\n");
	for( i=tempIndex; i>=0; i--){
		if( tempArray[i] != v+1 )
			printf("%d ->", tempArray[i]);
		else
			printf("%d", tempArray[i]);
	}

}

int main(){

	int graph[MAX][MAX] = {
		{INF,   6,   2,  16, INF, INF,  14}, 
		{INF, INF, INF,   5,   4, INF, INF}, 
		{INF,   7, INF, INF,   3,   8, INF}, 
		{INF, INF, INF, INF, INF, INF,   3}, 
		{INF, INF, INF,   4, INF, INF,  10}, 
		{INF, INF, INF, INF, INF, INF,   1}, 
		{INF, INF, INF, INF, INF, INF, INF}
	};

	int start, dest;

	printf("시작점 : ");	scanf("%d", &start); fflush(stdin);
	printf("도착점 : "); scanf("%d", &dest); fflush(stdin);


	ShortestPath( graph, start-1, dest-1 );

	if( distance[dest-1] == INF ){
		printf("=========");
		printf("\n%d->%d 경로없음", start, dest);
	}else{
		printf("=========");
		printf("\n최소 코스트 : %d", distance[dest-1]);
		showPath(start-1, dest-1);
	}
	
	getchar();

	return 0;
}
