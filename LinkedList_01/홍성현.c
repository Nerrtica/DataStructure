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
			printf("1 : ���� ��� �߰�, 2 : Ư�� ��ġ ��� �߰�, 3 : Ư�� �� ����\n4 : Ư�� ��� ����, 5 : �� ã��, 6 : ����� ���� ã��, 7 : ���, 8 : ����\n");
			printf("�� �� ���� : ") ;
			scanf("%d",&userSelect);
		}while(!(userSelect > 0 && userSelect <= 8));

		switch(userSelect)
		{
		case 0:
			putData(head, order, value);
			break ;
		case 1:
			printf("���� ������? : ");
			scanf("%d",&value);
			addNodeLast(head, value);
			break ;
		case 2:
			printf("�� ��°�� ������? : ");
			scanf("%d",&order);
			printf("���� ������? : ");
			scanf("%d",&value);
			addNodePlace(head, order, value);
			break ;
		case 3:
			printf("� ���� ���﷡? : ");
			scanf("%d",&value);
			deleteValue(head, value);
			break ;
		case 4:
			printf("�� ��° ����? : ");
			scanf("%d",&order);
			deleteNode(head, order);
			break ;
		case 5:
			printf("� ���� ã����? : ");
			scanf("%d",&value);
			num = searchValue(head, value);
			printf("find : %d \n",num);
			break ;
		case 6:
			printf("�� ��° ã����? : ");
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