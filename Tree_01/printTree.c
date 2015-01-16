#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

int printTree_ (TREE * root, int isLeft, int offset, int depth, char str[20][255]) {
	char b[20];
	int left, right, width = 5;
	int i;

	if (root == NULL) { return 0; }
	sprintf(b, "( %c )", root->data);

	left = printTree_(root->leftChild, 1, offset, depth + 1, str);
	right = printTree_(root->rightChild, 0, offset + left + width, depth + 1, str);

	for (i = 0; i < width; i++) {
		str[2 * depth][offset + left + i] = b[i];
	}
	if (depth && isLeft) {
		for (i = 0; i < width + right; i++) {
			str[2 * depth - 1][offset + left + width/2 + i] = '-';
		}
		str[2 * depth - 1][offset + left + width/2] = '+';
		str[2 * depth - 1][offset + left + width + right + width/2] = '+';
	} else if (depth && !isLeft) {
		for (i = 0; i < left + width; i++) {
			str[2 * depth - 1][offset - width/2 + i] = '-';
		}
		str[2 * depth - 1][offset + left + width/2] = '+';
		str[2 * depth - 1][offset - width/2 - 1] = '+';
	}
	return left + width + right;
}

/* print out the shape of a tree */
void printTree (TREE * root) {
	char str[20][255];
	int  i;
	for (i = 0; i < 20; i++) {
		sprintf(str[i], "%100s", " ");
	}

	printTree_(root, 0, 0, 0, str);

	for(i = 0; i < 20; i++) {
		printf("%s\n", str[i]);
	}
}