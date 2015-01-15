#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAKE_ERROR -9999

typedef struct _node 
{
	int data;
	struct _node *left;
	struct _node *right; 
}NODE ;

void addNode(NODE *node, int direction);
void inOrder(NODE *node);
void preOrder(NODE *node);
void postOrder(NODE *node);
int makeTree(NODE *parent, char inOrder[], char preOrder[]);

void main()
{
	NODE *root;
	int value, userSelect;
	char inOrderArray[] = "gdhbeiafjc", preOrderArray[] = "abdgheicfj";

	root = (NODE *)malloc(sizeof(NODE));
	root->data = 0;
	root->left = NULL;
	root->right = NULL;

	makeTree(root, inOrderArray, preOrderArray);

	printf("inOrder   : ");
	inOrder(root);
	printf("\n");
	printf("preOrder  : ");
	preOrder(root);
	printf("\n");
	printf("postOrder : ");
	postOrder(root);
	printf("\n");
	return;  
}

void addNode(NODE *node, int direction) 
{
	NODE *node_temp;

	node_temp = (NODE *)malloc(sizeof(NODE));
	node_temp->left = NULL;
	node_temp->right = NULL;
	
	if(direction == 1)
		node->left = node_temp;
	else
		node->right = node_temp;
	
	return ;
}
void inOrder(NODE *node)
{
	if(node != NULL)
	{
		inOrder(node->left);
		printf("%c", node->data);
		inOrder(node->right);
		return;
	}
	return;
}
void preOrder(NODE *node)
{
	if(node != NULL)
	{
		printf("%c", node->data);
		preOrder(node->left);
		preOrder(node->right);
		return;
	}
	return;
}
void postOrder(NODE *node)
{
	if(node != NULL)
	{
		postOrder(node->left);
		postOrder(node->right);
		printf("%c", node->data);
		return;
	}
	return;
}

int makeTree(NODE *parent, char *inOrder, char *preOrder)
{
	NODE *node;
	char root;
	int i, location;
	char *inOrderLeft, *inOrderRight, *preOrderLeft, *preOrderRight;

	if(strlen(inOrder) != strlen(preOrder))
	{
		printf("You can't make tree\n");
		return MAKE_ERROR;
	}

	root = preOrder[0];
	parent->data = root;
	location = 0;
	while(inOrder[location] != root)
		location++;

	inOrderLeft = (char *)malloc(sizeof(char) * (location + 1));
	inOrderLeft[location] = 0;
	inOrderRight = (char *)malloc(sizeof(char) * (strlen(inOrder) - location));
	inOrderRight[strlen(inOrder) - location - 1] = 0;
	preOrderLeft = (char *)malloc(sizeof(char) * (location + 1));
	preOrderLeft[location] = 0;
	preOrderRight = (char *)malloc(sizeof(char) * (strlen(inOrder) - location));
	preOrderRight[strlen(inOrder) - location - 1] = 0;
	
	for(i = 0 ; i < location ; i++)
		inOrderLeft[i] = inOrder[i];
	for(i = 0 ; i < strlen(preOrder) - location - 1 ; i++)
		inOrderRight[i] = inOrder[i + location + 1];

	for(i = 0 ; i < location ; i++)
		preOrderLeft[i] = preOrder[i + 1];
	for(i = 0 ; i < strlen(preOrder) - location - 1 ; i++)
		preOrderRight[i] = preOrder[i + location + 1];

	if(strlen(inOrderLeft) != 0)
	{
		addNode(parent, 1);
		node = parent->left;
		makeTree(node, inOrderLeft, preOrderLeft);
	}
	if(strlen(inOrderRight) != 0)
	{
		addNode(parent, 2);
		node = parent->right;
		makeTree(node, inOrderRight, preOrderRight);
	}

	free(inOrderLeft);
	free(preOrderLeft);
	free(inOrderRight);
	free(preOrderRight);

	return;
}