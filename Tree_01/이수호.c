#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct _node
{
	int data;
	struct _node * left;
	struct _node * right;
}
NODE;

typedef struct _tree
{
	NODE * root;
}
TREE;

void initTree(TREE * t, int data)
{
	t->root = (NODE*)malloc(sizeof(NODE));
	t->root->data = data;
	t->root->left = NULL;
	t->root->right = NULL;
}

int addNode(NODE * n, int data, int direction)
{
	if(direction == -1)
	{
		n->left = (NODE*)malloc(sizeof(NODE));
		n->left->data = data;
		n->left->left = NULL;
		n->left->right = NULL;
		return 1;
	}
	else if(direction == 1)
	{
		n->right = (NODE*)malloc(sizeof(NODE));
		n->right->data = data;
		n->right->left = NULL;
		n->right->right = NULL;
		return 1;
	}
	else
	{
		return 0;
	}
}

void printPreOrder(NODE *n, char * output, int * index)
{
	if(n != NULL)
	{
		printf("%d ", n->data);
		output[*index] = '0'+ n->data;
		*index += 1;
		printPreOrder(n->left, output, index);
		printPreOrder(n->right, output, index);
	}

	return;
}

void printInOrder(NODE *n, char * output, int * index)
{
	if(n != NULL)
	{
		printInOrder(n->left, output, index);
		printf("%d ", n->data);
		output[*index] = '0'+ n->data;
		*index += 1;
		printInOrder(n->right, output, index);
	}

	return;
}

void printPostOrder(NODE *n, char * output, int * index)
{
	if(n != NULL)
	{
		printPostOrder(n->left, output, index);
		printPostOrder(n->right, output, index);
		printf("%d ", n->data);
		output[*index] = '0'+ n->data;
		*index += 1;
	}

	return;
}

int getHeight(NODE *n)
{
	if(n != NULL)
	{
		int leftHeight = getHeight(n->left) + 1;
		int rightHeight = getHeight(n->right) + 1;

		if(leftHeight > rightHeight)
			return leftHeight;
		else
			return rightHeight;
	}
	else
	{
		return 0;
	}
}

int indexOf(char c, char * s)
{
	int index;

	for(index = 0; index < strlen(s); index++)
	{
		if(s[index] == c)
			return index;
	}

	return -1;
}

void trimPreWithIn(char * preOrder, char * inOrder, char * output)
{
	int outputIndex = 0;
	int preIndex;

	for(preIndex = 0; preIndex < strlen(preOrder); preIndex++)
	{
		int inIndex;

		for(inIndex = 0; inIndex < strlen(inOrder); inIndex++)
		{
			if(preOrder[preIndex] == inOrder[inIndex])
			{
				output[outputIndex] = preOrder[preIndex];
				outputIndex += 1;
				break;
			}
		}
	}
}

void makeTree(NODE ** n, char * preOrder, char * inOrder)
{
	if(strlen(preOrder) > 0)
	{
		char inCopy[MAX] = {0};
		char trimedPre1[MAX] = {0};
		char trimedPre2[MAX] = {0};

		strcpy(inCopy, inOrder);

		*n = (NODE*)malloc(sizeof(NODE));
		(*n)->data = inOrder[indexOf(preOrder[0], inOrder)] - '0';
		(*n)->left = NULL;
		(*n)->right = NULL;

		inCopy[indexOf(preOrder[0], inOrder)] = 0;
		trimPreWithIn(preOrder, inCopy, trimedPre1);
		trimPreWithIn(preOrder, &inCopy[indexOf(preOrder[0], inOrder)+1], trimedPre2);

		makeTree(&((*n)->left), trimedPre1, inCopy);
		makeTree(&((*n)->right), trimedPre2, &inCopy[indexOf(preOrder[0], inOrder)+1]);
	}
}

int main()
{
	char outputPre[MAX] = {0};
	char outputIn[MAX] = {0};
	char outputNewPre[MAX] ={0};
	char outputNewIn[MAX] ={0};
	int index;

	TREE tree;
	TREE newTree;
	newTree.root = NULL;

	initTree(&tree, 1);

	addNode(tree.root, 2, -1);
	addNode(tree.root, 3, 1);

	addNode(tree.root->left, 4, -1);
	addNode(tree.root->left, 5, 1);

	addNode(tree.root->right, 6, -1);
	addNode(tree.root->right, 7, 1);

	addNode(tree.root->left->right, 8, 1);

	index = 0;
	printPreOrder(tree.root, outputPre, &index);
	printf("\n");

	index = 0;
	printInOrder(tree.root, outputIn, &index);
	printf("\n");
	
	printf("%s\n", outputPre);
	printf("%s\n", outputIn);

	printf("%d\n", getHeight(tree.root));

	makeTree(&(newTree.root), outputPre, outputIn);

	index = 0;
	printPreOrder(tree.root, outputNewPre, &index);
	printf("\n");

	index = 0;
	printInOrder(newTree.root, outputNewIn, &index);
	printf("\n");

	printf("%s\n", outputNewPre);
	printf("%s\n", outputNewIn);
}