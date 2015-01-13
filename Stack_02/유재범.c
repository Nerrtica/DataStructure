#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define RING 3

typedef struct _COLUMN{
	int ring[RING];
	int top;
}COLUMN;

void Hanoi(COLUMN *cFirst, COLUMN *cSecond, COLUMN *cThird, int ring);
int isEmpty(COLUMN *sta);
int isFull(COLUMN *sta);
void Push(COLUMN *sta, int a);
int POP(COLUMN *sta);

int main(void){
	COLUMN c1, c2, c3, *cFirst, *cSecond, *cThird;
	int i, ring = RING;

	cFirst = &c1;
	cFirst->top = RING;
	cSecond = &c2;
	cSecond->top = 0;
	cThird = &c3;
	cThird->top = 0;

	for(i = 0; i < RING; i++)
		cFirst->ring[i] = RING - i;

	Hanoi(cFirst, cSecond, cThird, ring);

	return 0;
}

void Hanoi(COLUMN *cFirst, COLUMN *cSecond, COLUMN *cThird, int ring){
	int save = 0;

	if(ring == 1){
		Push(cSecond, POP(cFirst));
	}
	else{
		Hanoi(cFirst, cThird, cSecond, ring - 1);
		Push(cSecond, POP(cFirst));
		Hanoi(cThird, cSecond, cFirst, ring - 1);
	}
}

int isEmpty(COLUMN *sta){
	if((sta->top) == 0)
		return 1;
	else
		return 0;
}

int isFull(COLUMN *sta){
	if((sta->top) == RING)
		return 1;
	else
		return 0;
}

void Push(COLUMN *sta, int a){
	if(isFull(sta)){
		printf("cant\n");
	}
	else{
		sta->ring[sta->top] = a;
		(sta->top) += 1;
	}
}

int POP(COLUMN *sta){
	if(isEmpty(sta)){
		printf("cant\n");
	}
	else{
		printf("data output : %d\n", sta->ring[sta->top - 1]);
		(sta->top) -= 1;
	}
	return sta->ring[sta->top];
}