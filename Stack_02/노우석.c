#include <stdio.h>
#include <stdlib.h>


int disk = 3;


void push(int arr[],int data,int *top);
int pop(int arr[],int *top);
int isEmpty(int *top);
int isFull(int *top);
void hanoi(int disk, int *src, int *lux, int *dest, int *src_top, int *lux_top, int *dest_top);

int main(){
	int *src,*lux,*dest;
	int data,i;
	int src_top = 0,lux_top=0,dest_top=0;
	src  = (int *)malloc(sizeof(int)*disk);
	lux  = (int *)malloc(sizeof(int)*disk);
	dest = (int *)malloc(sizeof(int)*disk);
	
	for(i=0;i<disk;i++) push(src,i,&src_top);
	
	hanoi(disk, src, lux, dest,&src_top,&lux_top,&dest_top);
	for(i=0;i<disk;i++)	printf("%d ", dest[i]);
	printf("\n");
	for(i=0;i<disk;i++) printf("%d ", src[i]);
	printf("\n");
	for(i=0;i<disk;i++) printf("%d ", lux[i]);
	printf("\n");
	
}

void push(int arr[],int data,int *top){

	if(isFull(top)) return;
	else {
		arr[*top] = data;
		(*top)++;
	}
}

int pop(int arr[],int *top){

	int temp;

	if(isEmpty(top)){
		return 0;
	}
	else{
		temp = arr[*(top) - 1];
		(*top)--;

		return temp;
	}
}

int isEmpty(int *top){
	if(*top == 0) return 1;		
	else return 0;
}

int isFull(int *top){
	if(*(top) == disk) return 1; 
	else return 0;
}
void hanoi(int disk, int *src, int *lux, int *dest, int *src_top, int *lux_top, int *dest_top){

	int i;
	int temp;
	if(disk == 1) {
		temp = pop(src, src_top);
		push(dest,temp,dest_top);
	}
	else{
		hanoi(disk-1, src, dest, lux, src_top, dest_top, lux_top);
		temp = pop(src, src_top);
		push(dest,temp,dest_top);
		hanoi(disk-1,lux,src,dest, lux_top, src_top, dest_top);
	}
}