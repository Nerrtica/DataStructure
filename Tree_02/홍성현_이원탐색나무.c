#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256
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
void makeTree(NODE *parent, int inOrder[], int preOrder[]);
int isFindValue(NODE *parent, int value);
void printSearch(int isFind);
void insert(NODE *parent, int value);
void removeData(NODE *parent, int value);
NODE *removeJudge(NODE *root, int value);
void printOrder(int inOrderArray[], int preOrderArray[],NODE *root);
int userSelect();
int valueSelect();

void main()
{
	NODE *root;
	int inOrderArray[MAX] = {2, 6, 7, 8, 10, 15, 18, 20, 25, 30, 35, 40, -1}, 
		preOrderArray[MAX] = {20, 10, 6, 2, 8, 7, 15, 18, 40, 30, 25, 35, -1}, value, select;
//		int inOrderArray[MAX], preOrderArray[MAX], value;

	root = (NODE *)malloc(sizeof(NODE));
	root->data = 0;
	root->left = NULL;
	root->right = NULL;

	makeTree(root, inOrderArray, preOrderArray);

	//1.insert 2.delete 3.search, 4.print tree 5.end
	while(1)
	{
		select = userSelect();

		switch(select)
		{
		case 1:
			value = valueSelect();
			insert(root, value);
			break;
		case 2:
			value = valueSelect();
			root = removeJudge(root, value);
			break;
		case 3:
			value = valueSelect();
			printSearch(isFindValue(root, value));
			break;
		case 4:
			printOrder(inOrderArray, preOrderArray, root);
			break;
		case 5:
			printf("End!\n");
			return ;
		}
	}

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
		printf("%3d", node->data);
		inOrder(node->right);
		return;
	}
	return;
}
void preOrder(NODE *node)
{
	if(node != NULL)
	{
		printf("%3d", node->data);
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
		printf("%3d", node->data);
		return;
	}
	return;
}

void makeTree(NODE *parent, int *inOrder, int *preOrder)
{
	NODE *node;
	int root;
	int i, location, length, length2;
	int *inOrderLeft, *inOrderRight, *preOrderLeft, *preOrderRight;

	length = 0;
	for(i = 0 ; ; i++)
	{
		if(inOrder[i] == -1)
			break;
		length++;
	}

	root = preOrder[0];
	parent->data = root;
	location = 0;
	while(inOrder[location] != root)
		location++;

	inOrderLeft = (int *)malloc(sizeof(int) * (location + 1));
	inOrderLeft[location] = -1;
	inOrderRight = (int *)malloc(sizeof(int) * (length - location));
	inOrderRight[length - location - 1] = -1;
	preOrderLeft = (int *)malloc(sizeof(int) * (location + 1));
	preOrderLeft[location] = -1;
	preOrderRight = (int *)malloc(sizeof(int) * (length - location));
	preOrderRight[length - location - 1] = -1;
	
	for(i = 0 ; i < location ; i++)
		inOrderLeft[i] = inOrder[i];
	for(i = 0 ; i < length - location - 1 ; i++)
		inOrderRight[i] = inOrder[i + location + 1];

	for(i = 0 ; i < location ; i++)
		preOrderLeft[i] = preOrder[i + 1];
	for(i = 0 ; i < length - location - 1 ; i++)
		preOrderRight[i] = preOrder[i + location + 1];

	length2 = 0;
	for(i = 0 ; ; i++)
	{
		if(inOrderLeft[i] == -1)
			break;
		length2++;
	}

	if(length2 != 0)
	{
		addNode(parent, 1);
		node = parent->left;
		makeTree(node, inOrderLeft, preOrderLeft);
	}

	length2 = 0;
	for(i = 0 ; ; i++)
	{
		if(inOrderRight[i] == -1)
			break;
		length2++;
	}

	if(length2 != 0)
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

int isFindValue(NODE *parent, int value)
{
	int result = 0;

	if(value < parent->data)
	{
		if(parent->left == NULL)
			return 0;
		result = isFindValue(parent->left, value);
	}
	else if(value > parent->data)
	{
		if(parent->right == NULL)
			return 0;
		result = isFindValue(parent->right, value);
	}
	else			//same
		return 1;

	return result;
}

void printSearch(int isFind)
{
	if(isFind == 1)
		printf("Here!\n");
	else
		printf("Not here!\n");
}

void insert(NODE *parent, int value)
{
	if(isFindValue(parent, value) == 1)
	{
		printf("already Here! \n");
		return;
	}

	if(value < parent->data)
	{
		if(parent->left == NULL)
		{
			addNode(parent, 1);
			parent->left->data = value;
			return;
		}
		else
			insert(parent->left, value);
	}
	else if(value > parent->data)
	{
		if(parent->right == NULL)
		{
			addNode(parent, 2);
			parent->right->data = value;
			return;
		}
		else
			insert(parent->right, value);
	}

	return;
}

void removeData(NODE *parent, int value)
{
	int degree = 0, i , count = 0;
	NODE *node, *temp, *root;

	if(isFindValue(parent, value) == 0)
	{
		printf("Not Here! \n");
		return;
	}

	if(value < parent->data)
		node = parent->left;
	else if(value > parent->data)
		node = parent->right;
//	else //error control용 (맨 첫 노드 삭제시)
//	{
//
//	}

	if(value < node->data)
		removeData(node, value);
	else if(value > node->data)
		removeData(node, value);
	else//같을 때
	{
		degree = 0;
		if(node->left != NULL)
			degree++;
		if(node->right != NULL)
			degree++;

		switch(degree)
		{
		case 0:
			free(node);
			if(node == parent->left)
				parent->left = NULL;
			else if(node == parent->right)
				parent->right = NULL;
			break;
		case 1:
			if(node == parent->left)
			{
				if(node->left != NULL)
					parent->left = node->left;
				else if(node->right != NULL)
					parent->left = node->right;
				
				free(node);
			}
			else if(node == parent->right)
			{
				if(node->left != NULL)
					parent->right = node->left;
				else if(node->right != NULL)
					parent->right = node->right;
				
				free(node);
			}
			break;
		case 2:
			temp = node->left;
			while(temp->right != NULL)
			{
				temp = temp->right;
				count++;
			}

			temp->left = node->left;
			if(count == 0)
				temp->left = NULL;
			temp->right = node->right;
			parent->left = temp;

			temp = node->left;
			free(node);

			for(i = 0 ; i < count - 1 ; i++)
				temp = temp->right;
	
			if(count != 0)
				temp->right = NULL;
			break;
		}
	}
	return;
}

NODE *removeJudge(NODE *root, int value)
{
	int degree = 0, i , count = 0;
	NODE *node, *temp;

	if(root->data == value)
	{
		degree = 0;
		node = root;
		if(node->left != NULL)
			degree++;
		if(node->right != NULL)
			degree++;

		switch(degree)
		{
		case 0:
			free(node);
			return NULL;
			break;
		case 1:
			if(root->left != NULL)
			{
				root = root->left;
				free(node);
			}
			else if(root->right != NULL)
			{
				root = root->right;
				free(node);
			}
			break;
		case 2:
			temp = node->left;
			while(temp->right != NULL)
			{
				temp = temp->right;
				count++;
			}

			temp->left = node->left;
			if(count == 0)
				temp->left = NULL;
			temp->right = node->right;
			root = temp;

			temp = node->left;
			free(node);

			for(i = 0 ; i < count - 1 ; i++)
				temp = temp->right;

			if(count != 0)
				temp->right = NULL;
			break;
		}
		return root;
	}
	else
	{
		removeData(root, value);
		return root;
	}
}

void printOrder(int inOrderArray[], int preOrderArray[],NODE *root)
{
	printf("inOrder   : ");
	inOrder(root);
	printf("\n");
	printf("preOrder  : ");
	preOrder(root);
	printf("\n");
	printf("postOrder : ");
	postOrder(root);
	printf("\n\n");
}

int userSelect()
{
	char *input;
	int result;

	input = (char *)malloc(sizeof(char) * MAX);

	do
	{
	printf("your select(1.insert 2.delete 3.search, 4.print tree 5.end) : ");
	scanf("%s",input);
	}while(strlen(input) != 1 || !(input[0] == '1' || input[0] == '2' || input[0] == '3' || input[0] == '4' || input[0] == '5'));

	result = (int)input[0] - '0';
	
	free(input);

	return result;
}

int valueSelect()
{
	char *input;
	int result, go, i;

	input = (char *)malloc(sizeof(char) * MAX);

	do
	{
		printf("value : ");
		scanf("%s",input);
		for(i = 0 ; i < strlen(input) ; i++)
		{
			go = 1;
			if(!(input[i] >= '0' && input[i] <= '9'))
			{
				go = -1;
				break;
			}
		}
	}while(go != 1);

	result = atoi(input);
	
	free(input);

	return result;
}