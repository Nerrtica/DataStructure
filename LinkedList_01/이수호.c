//add, addAt, del, delAt, find, findAt, printAll

#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
	int data;
	struct _node * next;
}
NODE;

NODE* List()
{
	NODE * n = (NODE*)malloc(sizeof(NODE));
	n->data = 0;
	n->next = NULL;
	return n;
}

void add(NODE *n, int data)
{
	while(n->next != NULL)
		n = n->next;

	n->next = (NODE*)malloc(sizeof(NODE));
	n->next->data = data;
	n->next->next = NULL;

	return;
}
int addAt(NODE *n, int data, int index)
{
	int count = 1;
	while(count != index && n->next != NULL)
	{
		n = n->next;
		count += 1;

	}

	if(n->next == NULL)
	{
		n->next = (NODE*)malloc(sizeof(NODE));
		n->next->data = data;
		n->next->next = NULL;
		return 0;
	}
	else
	{
		n->next->data = data;
		return 1;
	}
	
}

int del(NODE *n, int data)
{
	while(n->next->data != data && n->next->next != NULL)
		n = n->next;

	if(n->next->data == data)
	{
		NODE * nodeTodel;
		nodeTodel = n->next;
		n->next = nodeTodel->next;
		free(nodeTodel);
		return 1;
	}
	else
	{
		return 0;
	}
}
int delAt(NODE *n, int index)
{
	int count = 1;
	while(count != index && n->next->next != NULL)
	{
		n = n->next;
		count += 1;
	}

	if(count == index)
	{
		NODE * nodeTodel;
		nodeTodel = n->next;
		n->next = nodeTodel->next;
		free(nodeTodel);
		return 1;
	}
	else
	{
		return 0;
	}
}

int find(NODE *n, int data, int *output)
{
	while(n->next->data != data && n->next->next != NULL)
		n = n->next;

	if(n->next->data == data)
	{
		*output = n->next->data;
		return 1;
	}
	else
	{
		return 0;
	}
}
int findAt(NODE *n, int index, int *output)
{
	int count = 1;
	while(count != index && n->next->next != NULL)
	{
		n = n->next;
		count += 1;
	}

	if(count == index)
	{
		*output = n->next->data;
		return 1;
	}
	else
	{
		return 0;
	}
}

void printAll(NODE *n)
{
	n = n->next;
	while(n->next != NULL)
	{
		printf("%d ", n->data);
		n = n->next;
	}
	printf("%d ", n->data);
	printf("\n");
	return;
}

int main()
{
	int val = 2;
	int index = 3;
	int output;

	NODE *list = List();
	add(list, 1);
	add(list, 2);
	add(list, 3);
	add(list, 4);
	add(list, 5);
	printAll(list);

	addAt(list, 6, 2);
	addAt(list, 7, 10);
	printAll(list);

	del(list, 1);
	printAll(list);

	delAt(list, 3);
	printAll(list);

	if(find(list, val, &output))
		printf("%d\n", output);
	else
		printf("Cannot Find %d!\n", val);

	if(findAt(list, index, &output))
		printf("%d\n", output);
	else
		printf("Cannot find at %d!\n", index);
}