#include <stdio.h>
#include <stdlib.h>

typedef struct _tree{
	int data;
	struct _tree *left;
	struct _tree *right;
}TREE;

int  searchData(TREE* root, int data);
void MakeTree(TREE **point);
void AddChild(TREE **child, int input);
void Goto(TREE **point, TREE *node);
void addTree(TREE** root, int data);
void deleteTree(TREE** root, int data);
void inorder(TREE* root);
void preorder(TREE* root);
void postorder(TREE* root);

int main(){
	TREE *root;

	MakeTree(&root);

	addTree(&root, 1);

	deleteTree(&root,20);
	preorder(root);
	printf("\n");
	inorder(root);
	printf("\n");
	printf("%d\n",searchData(root, 10));
	printf("%d\n",searchData(root, 18));

	return 0;
}

int searchData(TREE* root, int data){
	int temp;

	if(root){
		if(root->data > data){
			temp = searchData(root->left, data);
		}
		else if(root->data < data){
			temp = searchData(root->right, data);
		}
		else{
			return 1;
		}
	}
	else return -1;

	return temp;
}

void deleteTree(TREE** root, int data){

	TREE *temp,*min,*finish;
	int tempint;

	if(searchData(*root, data) == 1){
		if((*root)->data > data){
			if((*root)->left->data == data){
				if((*root)->left->right == NULL && (*root)->left->left == NULL){
					free((*root)->left);
					(*root)->left = NULL;
				}
				else if((*root)->left->right == NULL && (*root)->left->left != NULL){
					temp = (*root)->left;
					(*root)->left = (*root)->left->left;
					free(temp);
				}
				else if((*root)->left->right != NULL && (*root)->left->left == NULL){
					temp = (*root)->left;
					(*root)->left = (*root)->left->right;
					free(temp);
				}
				else{
					min = (*root)->left->right;
					while((min->left) != NULL){
						if(min->data > min->left->data)	min = min->left;

					}
					finish = min;
					while(1){
						if(finish->right == NULL){
							break;
						}
						else{
							finish = finish->right;
						}
					}
					min->left = (*root)->left->left;
					if((*root)->left->right == min){
						temp = (*root)->left;
						(*root)->left = min;
						free(temp);
					}
					else{
						finish->right = (*root)->left->right;
						temp = (*root)->left;
						(*root)->left = min;
						free(temp);
					}
				}
			}
			else{
				deleteTree(&(*root)->left, data);
			}
		}
		else if((*root)->data < data){
			if((*root)->right->data == data){
				if((*root)->right->right == NULL && (*root)->right->left == NULL){
					free((*root)->right);
					(*root)->right = NULL;
				}
				else if((*root)->right->right == NULL && (*root)->right->left != NULL){
					temp = (*root)->right;
					(*root)->right = (*root)->right->left;
					free(temp);
				}
				else if((*root)->right->right != NULL && (*root)->right->left == NULL){
					temp = (*root)->right;
					(*root)->right = (*root)->right->right;
					free(temp);
				}
				else{
					min = (*root)->right->left;
					while((min->left) != NULL){
						if(min->data > min->left->data)	min = min->left;

					}
					finish = min;
					while(1){
						if(finish->right == NULL){
							break;
						}
						else{
							finish = finish->right;
						}
					}

					finish->right = (*root)->right->right;
					temp = (*root)->right;
					(*root)->right = min;
					free(temp);
				}
			}
			else{
				deleteTree(&(*root)->right, data);
			}
		}
		
		else if((*root)->data == data){
			min = (*root)->right;
			while((min->left) != NULL){
				if(min->data > min->left->data)	min = min->left;
			}
			tempint = min->data;
			deleteTree(root,tempint);
			(*root)->data = tempint;
		}
	}

	else{
		printf("Not Exist the data!\n");
	}
}
void addTree(TREE** root, int data){

	if(searchData(*root, data) == 1){
		printf("Exist the data!\n");
	}
	else{
		if((*root)->data > data){
			if((*root)->left == NULL){
				AddChild(&(*root)->left, data);
			}
			else{
				addTree(&(*root)->left, data);
			}
		}
		else{
			if((*root)->right == NULL){
				AddChild(&(*root)->right, data);
			}
			else{
				addTree(&(*root)->right, data);
			}
		}
	}

}

void Goto(TREE **point, TREE *node){
	(*point) = node;
}

void MakeTree(TREE **point){
	AddChild(point, 20);
	AddChild(&(*point)->left, 10);
	AddChild(&(*point)->left->left, 6);
	AddChild(&(*point)->left->left->left, 2);
	AddChild(&(*point)->left->left->right, 8);
	AddChild(&(*point)->left->left->right->left, 7);
	AddChild(&(*point)->left->right, 15);
	AddChild(&(*point)->left->right->right, 18);
	AddChild(&(*point)->right, 40);
	AddChild(&(*point)->right->left, 30);
	AddChild(&(*point)->right->left->left, 25);
	AddChild(&(*point)->right->left->right, 35);
}

void AddChild(TREE **child, int input){
	*child = (TREE *)malloc(sizeof(TREE) * 1);
	(*child)->left = NULL;
	(*child)->right = NULL;
	(*child)->data = input;
}

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
