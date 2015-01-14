#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define NO_SEARCH -9999

typedef struct _node 
{
	int data ;
	struct _node *next ;
}NODE ;

void addNodeLast(NODE *head, int value);
void addNodePlace(NODE *head, int order, int value);
void putData(NODE *head, int order, int value);
int searchValue(NODE *head, int value);
int searchNode(NODE *head, int order);
void deleteValue(NODE *head, int value);
void deleteNode(NODE *head, int order);
void printNode(NODE *head);

void main()
{
	NODE *head = (NODE *)malloc(sizeof(NODE));
	int i, userSelect, order, value, num ;
	
	head->next = NULL ;
	head->data = 0 ;				

	while(1)
	{
		do
		{
			printf("1 : 끝에 노드 추가, 2 : 특정 위치 노드 추가, 3 : 특정 값 삭제\n4 : 특정 노드 삭제, 5 : 값 찾기, 6 : 노드의 내용 찾기, 7 : 출력, 8 : 종료\n");
			printf("할 짓 설정 : ") ;
			scanf("%d",&userSelect);
		}while(!(userSelect > 0 && userSelect <= 8));

		switch(userSelect)
		{
		case 0:
			putData(head, order, value);
			break ;
		case 1:
			printf("뭐를 넣을래? : ");
			scanf("%d",&value);
			addNodeLast(head, value);
			break ;
		case 2:
			printf("몇 번째에 넣을래? : ");
			scanf("%d",&order);
			printf("뭐를 넣을래? : ");
			scanf("%d",&value);
			addNodePlace(head, order, value);
			break ;
		case 3:
			printf("어떤 값을 지울래? : ");
			scanf("%d",&value);
			deleteValue(head, value);
			break ;
		case 4:
			printf("몇 번째 제거? : ");
			scanf("%d",&order);
			deleteNode(head, order);
			break ;
		case 5:
			printf("어떤 값을 찾을래? : ");
			scanf("%d",&value);
			num = searchValue(head, value);
			printf("find : %d \n",num);
			break ;
		case 6:
			printf("몇 번째 찾을래? : ");
			scanf("%d",&order);
			num = searchNode(head, order);
			printf("find : %d \n",num);
			break ;
		case 7:
			printNode(head);
			break ;
		case 8:
			return ;
		}
	}

	return ;
}

void addNodeLast(NODE *head, int value) 
{
	NODE *node ;

	node = head ;
	while(node->next != NULL)
		node = node->next ;

	node->next = (NODE *)malloc(sizeof(NODE));
	node->next->data = value ;
	node->next->next = NULL ;
	
	return ;
}

void addNodePlace(NODE *head, int order, int value) 
{
	NODE *node, *temp_node ;
	int i ;

	node = head ;
	
	for(i = 0 ; i < order; i++)
		node =node->next ;
	
	temp_node = (NODE *)malloc(sizeof(NODE)) ;
	temp_node->next = node->next ;
	temp_node->data = value ;
	node->next = temp_node ;

	return ;
}

void putData(NODE *head, int order, int value)
{
	NODE *node ;
	int i ;

	node = head ;
	
	for(i = 0 ; i < order ; i++)
		node =node->next ;

	node->data = value ;

	return ;
}

int searchValue(NODE *head, int value)
{
	NODE *node ;
	int i = 0 ;

	node = head ;
	while(node->next != NULL)
	{
		i++ ;
		node = node->next ;
		if(node->data == value)
			return i ; 
	}

	return NO_SEARCH ;
}

int searchNode(NODE *head, int order)
{
	NODE *node ;
	int i ;

	node = head ;
	
	for(i = 0 ; i < order ; i++)
		node =node->next ;

	return node->data ;
}

void deleteValue(NODE *head, int value)
{
	NODE *node ;
	int order, i ;

	node = head ; 

	if(node->next->data == value)
	{
		node->next->data = 0 ;
		return ;
	}
	order = searchValue(head, value);

	for(i = 0 ; i < order ; i++)//
		node =node->next ;
	
	node->data = 0 ;
	return ;
}

void deleteNode(NODE *head, int order)
{
	NODE *node, *temp_node ;
	int i ;

	node = head ;

	for(i = 0 ; i < order - 1 ; i++)
		node =node->next ;

	temp_node = node->next ;
	node->next = node->next->next ;
	free(temp_node);
	return ;
}

void printNode(NODE *head)
{
	NODE *node ;

	node = head ;

	while(node->next != NULL)
	{
		node = node->next ;
		printf("%2d",node->data);
	}

	printf("\n");

	return ;
}