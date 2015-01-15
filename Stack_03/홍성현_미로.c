#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#define ERROR_POP -9999	
#define END -99999	

int *stack ;
int size, top = 0 ;

void push(int data) ;
int pop() ;
int isEmpty() ;
int isFull() ;
void escapeMaze(int map[16][17]);
void traceRoute(int map[16][17]);
void printMap(int map[16][17]);

void main()
{
	int map[16][17]={
						{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
						{1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
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
	size = 2 ;

	stack = (int *)malloc(sizeof(int) * size) ;

	escapeMaze(map);
	traceRoute(map);
	printMap(map);

	free(stack) ;

	return ;
}

void push(int data) 
{
	if(isFull() == 1)
		return ;
	else
	{
		stack[top] = data ;
		top++ ;
		return ;
	}
}
int pop() 
{
	if(isEmpty() == 1)
		return ERROR_POP ;
	else
	{
		top-- ;
		return stack[top] ;
	}
}
int isEmpty()	
{
	if(top == 0)
	{
		return 1 ;
	}
	else
		return 0 ;
}
int isFull()	
{
	if(top == size )
	{
		size *= 2 ;
		realloc(stack, (sizeof(int) * size)) ;
	}
		return 0 ;
}
void escapeMaze(int map[16][17])
{
	int row = 1, col = 1, order[4], i, go;

	while(1)		
	{
		printMap(map);
		Sleep(150);
		system("cls");
		order[0] = map[row][col + 1];
		order[1] = map[row + 1][col];
		order[2] = map[row][col - 1];
		order[3] = map[row - 1][col];

		for(i = 0 ; i < 4 ; i++)
		{
			if(order[i] == 5)
			{
				push(i);
				return;
			}
			if(order[i] == 0)
			{
				go = i;
				push(go);
				break;
			}
		}
		if(i == 4)				
			go = 4;

		switch(go)
		{
		case 0:
			col++;
			map[row][col] = 2;
			break;
		case 1:
			row++;
			map[row][col] = 2;
			break;
		case 2:
			col--;
			map[row][col] = 2;
			break;
		case 3:
			row--;
			map[row][col] = 2;
			break;
		}

		if(go == 4)
		{
			go = pop();

			switch(go)
			{
			case 0:
				col--;
				break;
			case 1:
				row--;
				break;
			case 2:
				col++;
				break;
			case 3:
				row++;
				break;
			}
		}
	}
}
void traceRoute(int map[16][17])
{
	int go, row = 14, col = 15;

	while(isEmpty() != 1)
	{
		printMap(map);
		Sleep(150);
		system("cls");

		go = pop();

		switch(go)
		{
		case 0:
			col--;
			map[row][col] = 3;
			break;
		case 1:
			row--;
			map[row][col] = 3;
			break;
		case 2:
			col++;
			map[row][col] = 3;
			break;
		case 3:
			row++;
			map[row][col] = 3;
			break;
		}
	}
}
void printMap(int map[16][17])
{
	int i, j;

	for(i = 0 ; i < 16 ; i++)
	{
		printf("\n");
		for(j= 0 ; j < 17 ; j++)
		{
			if(map[i][j] == 0)
				printf("¡à");
			else if(map[i][j] == 1)
				printf("¡á");
			else if(map[i][j] == 2)
				printf("££");
			else if(map[i][j] == 3)
				printf("¡Ù");
			else if(map[i][j] == 5)
				printf("¡Ú");
		}
	}
}