#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _tree{
	char data;
	struct _tree *left;
	struct _tree *right;
}TREE;

TREE* addNod(TREE* tree, int select, char data);
TREE* linkNod(TREE* direct, char data);
int makeTree(char inorder[], char preorder[], TREE* parent);
char* cutPreOrder(char inorder[], char preorder[]);
void preorder(TREE* root);
void inorder(TREE* root);
void postorder(TREE* root);

int main(){
	TREE *root;
	char in[11]={'7', '4', '8', '2', '5', '9', '1', '6', '0', '3'},
		pre[11] ={'1', '2', '4', '7', '8', '5', '9', '3', '6', '0'};

	root = (TREE*) malloc(sizeof(TREE));	
	root->left = NULL;
	root->right = NULL;
	makeTree(in, pre, root);
	preorder(root);
	return 0;
}
int makeTree(char inorder[], char preorder[], TREE* parent){
	
	int i;
	char *frontin, *lastin, *frontpre, *lastpre;
	
	parent->data = preorder[0];

	for(i=0; i<strlen(inorder); i++){
		if(inorder[i] == preorder[0]){
			inorder[i] = 0;
			break;
		}
	}

	frontin = &inorder[0];
	lastin = &inorder[i+1];
	frontpre = cutPreOrder(frontin, preorder);
	lastpre = cutPreOrder(lastin, preorder);
	
	if(strlen(frontin) != 0){
		addNod(parent, 1, NULL);
		makeTree(frontin, frontpre, parent->left);
	}

	if(strlen(lastin) != 0){
		addNod(parent, 2, NULL);
		makeTree(lastin, lastpre, parent->right);
	}

	return 1;
}

char* cutPreOrder(char inorder[], char preorder[]){
	
	int i,j,count=0;
	char *temp;
	temp = strdup(inorder);

	for(i=0; i< strlen(preorder); i++){
		for(j=0; j<strlen(inorder); j++){
			if(preorder[i] == inorder[j]){
				temp[count++] = preorder[i];
			}
		}
	}

	
	return temp;
}

TREE* addNod(TREE* tree, int select, char data){		// (select=1)-left (select=2)-right

	while(1){
		if(select == 1){
			if(tree->left != NULL){
				printf("Exist!\n");
				break;
			}
			tree->left = linkNod(tree->left, data);
			printf("Complete AddLeft\n");
			return tree;
		}
		else if(select == 2){
			if(tree->right != NULL){
				printf("Exist!\n");
				break;
			}
			tree->right = linkNod(tree->right, data);
			printf("Complete AddRight\n");
			return tree;
		}
		else{
			printf("Put Error!\n");
			return NULL;
		}
	}
	return tree;
}

TREE* linkNod(TREE* direct, char data){

	TREE* newNod;

	newNod = (TREE *) malloc(sizeof(TREE));

	newNod->data = data;
	newNod->left = NULL;
	newNod->right = NULL;

	direct = newNod;

	return direct;
}

/*
TREE* findTree(TREE* root, int data){
	TREE *temp = 0;

	if(root){
		if(root->data == data){
			return root;
		}
		else{
			temp = findTree(root->left, data);
			if(temp != NULL)
				return temp;
			temp = findTree(root->right, data);
			if(temp != NULL)
				return temp;
		}
	}

	return NULL;
}
*/

void inorder(TREE* root){
	if(root){
		inorder(root -> left);
		printf(" %d ", root->data);
		inorder(root -> right);
	}
}

void preorder(TREE* root){
	if(root){
		printf(" %d ", root->data);
		preorder(root -> left);
		preorder(root -> right);
	}
}

void postorder(TREE* root){
	if(root){
		postorder(root -> left);
		postorder(root -> right);
		printf(" %d ", root->data);
	}
}

