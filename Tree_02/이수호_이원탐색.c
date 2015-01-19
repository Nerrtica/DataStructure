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

int addNodeBy(NODE ** n, int data)
{
	while(*n != NULL)
	{
		if(data > (*n)->data)
		{
			n = &((*n)->right);
		}
		else if(data < (*n)->data)
		{
			n = &((*n)->left);
		}
		else
		{
			return 0;
		}
	}

	(*n) = (NODE*)malloc(sizeof(NODE));
	(*n)->data = data;
	(*n)->left = NULL;
	(*n)->right = NULL;
	return 1;
}
int searchNode(NODE **n, int data)
{
	while(*n != NULL)
	{
		if(data > (*n)->data)
		{
			n = &((*n)->right);
		}
		else if(data < (*n)->data)
		{
			n = &((*n)->left);
		}
		else
		{
			return 1;
		}
	}

	return 0;
}
int deleteNode(NODE **n, int data)
{
	NODE ** parent = n;
	while(*n != NULL)
	{
		if(data > (*n)->data)
		{
			parent = n;
			n = &((*n)->right);
		}
		else if(data < (*n)->data)
		{
			parent = n;
			n = &((*n)->left);
		}
		else
		{
			int degree = 0;
			if((*n)->left != NULL)
				degree += 1;

			if((*n)->right != NULL)
				degree += 1;

			switch(degree)
			{
				NODE * toDel;
				NODE * rightsSmallest;
			case 0:
				if((*parent)->left == *n)
					(*parent)->left = NULL;
				else if((*parent)->right == *n)
					(*parent)->right = NULL;

				free(*n);
				break;
			case 1:
				if((*parent)->left == *n)
				{
					if((*n)->left != NULL)
						(*parent)->left = (*n)->left;
					else if((*n)->right != NULL)
						(*parent)->left = (*n)->right;
				}
				else if((*parent)->right == *n)
				{
					toDel = *n;
					if((*n)->left != NULL)
						(*parent)->right = (*n)->left;
					else if((*n)->right != NULL)
						(*parent)->right = (*n)->right;
				}

				//(*n)->left = NULL;
				//(*n)->right = NULL;
				free(toDel);
				break;
			default:
				toDel = *n;
				rightsSmallest = (*n)->right;

				while(rightsSmallest->left != NULL)
				{
					rightsSmallest = rightsSmallest->left;
				}

				if((*parent)->left == *n)
					(*parent)->left = toDel->right;
				else if((*parent)->right == *n)
					(*parent)->right = toDel->right;

				rightsSmallest->left = toDel->left;

				free(toDel);
				break;
			}
			return 1;
		}
	}

	return 0;
}

int main()
{
	char output[MAX] = {0};
	int index;

	TREE tree;
	initTree(&tree, 5);

	addNodeBy(&tree.root, 6);
	addNodeBy(&tree.root, 2);
	addNodeBy(&tree.root, 3);
	addNodeBy(&tree.root, 4);
	addNodeBy(&tree.root, 1);
	addNodeBy(&tree.root, 7);
	addNodeBy(&tree.root, 8);

	index = 0;
	printInOrder(tree.root, output, &index);

	printf("\n");

	index = 0;
	printPreOrder(tree.root, output, &index);

	printf("\n");
	printf("%d\n", searchNode(&tree.root, 2));
	printf("%d\n", searchNode(&tree.root, 8));
	printf("%d\n", searchNode(&tree.root, 10));

	deleteNode(&tree.root, 2);

	index = 0;
	printInOrder(tree.root, output, &index);

	printf("\n");
}