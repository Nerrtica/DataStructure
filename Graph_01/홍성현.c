#include <stdio.h>
#include <stdlib.h>

#define ERROR_POP -9999	
#define END -99999	

int *queue ;
int queueSize, front, rear ;
int *stack ;
int stackSize, top = 0 ;

void queuePush(int data) ;
int queuePop() ;
int queueIsEmpty() ;
void queueFull() ;

void stackPush(int data) ;
int stackPop() ;
int stackIsEmpty() ;
int stackIsFull() ;
int DFS(int graph[11][11], int start, int end, int path[11]);
int BFS(int graph[11][11], int start, int trace[11], int levelArr[11]);
void tracePath(int trace[11], int start, int end);

void main()
{
	int result ;
	int i, path[11] = {0,}, trace[11] = {0,}, levelArr[11] = {0,} ;
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
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}};

	stackSize = 16;
	queueSize = 16;
	stack = (int *)malloc(sizeof(int) * stackSize) ;
	queue = (int *)malloc(sizeof(int) * queueSize) ;

	front = queueSize -1 ;
	rear = queueSize -1 ; 

	result = DFS(graph, 1, 7, path);
	
	if(result == 1)
	{
		printf("find!\n");
		printf("reverse order\n");
		while(stackIsEmpty() == 0)
		{
			printf("%2d", stackPop());
		}
	}
	else
		printf("No\n");
	printf("\n");

	BFS(graph, 7, trace, levelArr);

	printf("level Ãâ·Â\n");
	for(i = 0 ; i < 11 ; i++)
		printf("%3d",i + 1);
	printf("\n");

	for(i = 0 ; i < 11 ; i++)
		printf("%3d", levelArr[i]); 
	printf("\n");
	printf("\n");

	printf("right order\n");
	tracePath(trace, 7, 1);
	while(stackIsEmpty() == 0)
	{
		result = stackPop();
		printf("%2d", result);
	}
	printf("\n");

	free(queue);
	free(stack);

	return ;
}

void queuePush(int data) 
{
	rear = (rear + 1) % queueSize ;

	if(front == rear)
		queueFull() ;

	queue[rear] = data ;
	return ;
}
int queuePop() 
{
	if(queueIsEmpty() == 1)
		return ERROR_POP ;
	else
	{
		front = (front + 1) % queueSize ;
		return queue[front] ;
	}
}
int queueIsEmpty()	
{
	if(front == rear)
		return 1 ;
	else
		return 0 ;
}
void queueFull()	
{
	int i;
	
	printf("queueFull !!\n");

	queueSize *= 2 ;
	queue = (int *)realloc(queue, (sizeof(int) * queueSize)) ;

	for(i = front ; i < (queueSize/2) ; i++)
		queue[i + (queueSize/2)] = queue[i] ;

	front += (queueSize/2) ;

	return ;
}

void stackPush(int data) 
{
	if(stackIsFull() == 1)
		return ;
	else
	{
		stack[top] = data ;
		top++ ;
		return ;
	}
}
int stackPop() 
{
	if(stackIsEmpty() == 1)
		return ERROR_POP ;
	else
	{
		top-- ;
		return stack[top] ;
	}
}
int stackIsEmpty()	
{
	if(top == 0)
	{
		return 1 ;
	}
	else
		return 0 ;
}
int stackIsFull()	
{
	if(top == stackSize )
	{
		stackSize *= 2 ;
		stack = (int *)realloc(stack, (sizeof(int) * stackSize)) ;
	}
		return 0 ;
}

int DFS(int graph[11][11], int start, int end, int path[11])
{
	int i, j, next, countNext = 0, result = 0;
	static int count;

	if(start == end)
	{
		stackPush(end);
		return 1;
	}
	path[count] = start;
	stackPush(path[count]);
	count++;

	for(j = 0 ; j < 11; j++)
	{
		if(graph[start - 1][j] == 1)
		{
			for(i = 0 ; i < 11 ; i++)
			{
				if(path[i] == j + 1)
					break;
			}

			if(i != 11)
				continue;

			next = j + 1;
			result = DFS(graph, next, end, path);
			if(result == 1)
				return 1;
		}
	}

	stackPop();
	count--;

	if(stackIsEmpty() == 1)
		return 0;
}

int BFS(int graph[11][11], int start, int trace[11], int levelArr[11])
{
	int i, j, k, count = 0, num, level = 1, next, path[11] = {0,};

	queuePush(start);
	trace[start - 1] = 0;
	path[count] = start;
	count++;
	levelArr[start - 1] = level;
	level++;

	while(queueIsEmpty() == 0)
	{
		if(front <= rear)
			num = rear - front;
		else
			num = rear + queueSize - front;
		
		i = 0;
		while(i != num)
		{
			next = queuePop();
			i++;

			for(j = 0 ; j < 11 ; j++)
			{
				if(graph[next - 1][j] == 1)
				{
					for(k = 0 ; k < 11 ; k++)
					{
						if(path[k] == j + 1)
							break;
					}

					if(k != 11)
						continue;
					
					queuePush(j + 1);
					path[count] = j + 1;
					count++;
					trace[j] = next;
					levelArr[j] = level;
				}
			}
		}

		level++;
	}
}

void tracePath(int trace[11], int start, int end)
{
	int next, i;

	if(trace[end - 1] == 0)
	{
		printf("Don't find\n");
		return;
	}

	next = end;
	while(trace[next-1] != 0)
	{
		stackPush(next);
		next = trace[next - 1];
	}
	stackPush(start);

	return;
}