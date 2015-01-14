#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct _point
{
	int x;
	int y;
}
POINT;

typedef struct _stack
{
	POINT data[MAX];
	int top;
}
STACK;

void initStack(STACK *s);
void push(STACK *s, int x, int y);
POINT pop(STACK *s);
int isFull(STACK *s);
int isEmpty(STACK *s);
void go(int x, int y, int map[16][17]);
int isNearFinish(POINT * curPosition, STACK * route, int map[16][17]);
void moveTo(int x, int y, POINT * curPosition, STACK * route, int map[16][17]);



void initStack(STACK *s)
{
	s->top = -1;
}

void push(STACK *s, int x, int y)
{
	if(isFull(s) == 0)
	{
		s->top += 1;
		s->data[s->top].x = x;
		s->data[s->top].y = y;
	}
}
POINT pop(STACK *s)
{
	if(isEmpty(s) == 0)
	{
		s->top -= 1;
		return s->data[s->top+1];
	}
}

int isFull(STACK *s)
{
	if(s->top == MAX -1)
		return 1;
	else
		return 0;
}

int isEmpty(STACK *s)
{
	if(s->top == -1)
		return 1;
	else
		return 0;
}

void go(int x, int y, int map[16][17]) 
{
	POINT curPosition;
	map[y][x] = 2;
	curPosition.x = x;
	curPosition.y = y;

	STACK route;
	initStack(&route);

	while(isNearFinish(&curPosition, &route, map) == 0)
	{
		if(map[curPosition.y-1][curPosition.x] == 0)
		{
			moveTo(curPosition.x, curPosition.y-1, &curPosition, &route, map);
		}
		else if(map[curPosition.y][curPosition.x+1] == 0)
		{
			moveTo(curPosition.x+1, curPosition.y, &curPosition, &route, map);
		}
		else if(map[curPosition.y+1][curPosition.x] == 0)
		{
			moveTo(curPosition.x, curPosition.y+1, &curPosition, &route, map);
		}
		else if(map[curPosition.y][curPosition.x-1] == 0)
		{
			moveTo( curPosition.x-1, curPosition.y, &curPosition, &route, map);
		}
		else
		{
			map[curPosition.y][curPosition.x] = 3;
			POINT back = pop(&route);
			curPosition.x = back.x;
			curPosition.y = back.y;
		}
	}

	printf("%d %d\n", curPosition.x, curPosition.y);
}

int isNearFinish(POINT * curPosition, STACK * route, int map[16][17]) 
{
	if(map[curPosition->y-1][curPosition->x] == 5)
	{
		moveTo(curPosition->x, curPosition->y-1, curPosition, route, map);
		return 1;
	}
	else if(map[curPosition->y][curPosition->x+1] == 5)
	{
		moveTo(curPosition->x+1, curPosition->y, curPosition, route, map);
		return 1;
	}
	else if(map[curPosition->y+1][curPosition->x] == 5)
	{
		moveTo(curPosition->x, curPosition->y+1, curPosition, route, map);
		return 1;
	}
	else if(map[curPosition->y][curPosition->x-1] == 5)
	{
		moveTo(curPosition->x-1, curPosition->y, curPosition, route, map);
		return 1;
	}
	else
	{
		return 0;
	}
}

void moveTo(int x, int y, POINT * curPosition, STACK * route, int map[16][17])
{
	push(route, curPosition->x, curPosition->y);
	map[y][x] = 2;

	curPosition->x = x;
	curPosition->y = y;
}

int main()
{
	int count1;
	int count2;


	int map[16][17]={
						{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
						{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
						{1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1},
						{1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1},
						{1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
						{1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1},
						{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
						{1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1},
						{1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
						{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 5, 1},
						{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
					};
	
	go(1, 1, map);
	
	for(count1 = 0; count1 < 16; count1++)
	{
		for(count2 = 0; count2 < 17; count2++)
		{
			switch(map[count1][count2])
			{
			case 1:
				printf("бс");
				break;
			case 2:
				printf("бу");
				break;
			default:
				printf("  ");
				break;
			}
		
		}
		printf("\n");
	}
	
}