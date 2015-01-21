#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct TRYEE{
	int data;
	struct TRYEE *leftChild;
	struct TRYEE *rightChild;
}TREE;
TREE *temp = NULL;
void MakeTree(TREE **point);
void Goto(TREE **point, TREE *node);
void AddChild(TREE **child, int input);
int DeleteContainer(TREE **point, int value);
int FindData(TREE *point);
int SearchValue(TREE **point, int value);

int main(void){
	TREE *point;
	int value = 0;

	point = (TREE *)malloc(sizeof(TREE));

	MakeTree(&point);

	while(1){
		printf("검색할 데이터의 값을 입력하시오 : ");
		scanf("%d", &value);

		SearchValue(&point, value);
		temp = NULL;
	}

	free(point);
	return 0;
}

int SearchValue(TREE **point, int value){
	TREE *node = NULL;
	int select = 0, i = 0;

	if((*point)->data > value){
		node = (*point)->leftChild;
	}
	else if((*point)->data < value){
		node = (*point)->rightChild;
	}
	else if((*point)->data == value){
		printf("Tree 안에 존재합니다. 삭제하시겠습니까?(Yes : 1, No : 0) : ");
		scanf("%d", &select);
		if(select == 0){
			printf("\n");
			return 1;
		}
		else{
			DeleteContainer(point, value);
			return -1;
		}
	}

	if(node == NULL){
		printf("Tree 안에 존재하지 않습니다. 추가하시겠습니까?(Yes : 1, No : 0) : ");
		scanf("%d", &select);
		if(select == 0){
			printf("\n");
			return 0;
		}
		else{
			AddChild(&(*point)->leftChild, value);
			return 1;
		}
	}
	else{
		i = SearchValue(&node, value);
		if(node->data < 0){
			if(node->leftChild != NULL){
				node->leftChild = NULL;
			}
			(*point)->leftChild = node->leftChild;
			if(node->rightChild != NULL){
				node->rightChild = NULL;
			}
			(*point)->rightChild = node->rightChild;
		}
		else{
			if((*point)->rightChild->data < 0){
				(*point)->rightChild = node;
			}
			else if((*point)->leftChild->data < 0){
				(*point)->leftChild = node;
			}
		}
	}

	return 0;
}
int DeleteContainer(TREE **point, int value){

	if((*point)->leftChild == NULL && (*point)->rightChild == NULL){
		free(*point);
	}
	else if((*point)->leftChild == NULL){
		temp = *point;
		(*point) = (*point)->rightChild;
		free(temp);
		temp = NULL;
	}
	else if((*point)->rightChild == NULL){
		temp = *point;
		*point = (*point)->leftChild;
		free(temp);
		temp = NULL;
	}
	else{
		temp = (*point)->leftChild;
		while(temp->rightChild != NULL){
			temp = temp->rightChild;
		}
		(*point)->data = temp->data;
		DeleteContainer(&temp, 0);
	}
	return (*point)->data;
}
int FindData(TREE *point){
	TREE *node = NULL;

	if(point->leftChild == NULL){
		return point->data;
	}
	else{
		node = point->leftChild;
		FindData(node);
	}
	return -1;
}

void MakeTree(TREE **point){
	AddChild(point, 20);
	AddChild(&(*point)->leftChild, 10);
	AddChild(&(*point)->leftChild->leftChild, 6);
	AddChild(&(*point)->leftChild->leftChild->leftChild, 2);
	AddChild(&(*point)->leftChild->leftChild->rightChild, 8);
	AddChild(&(*point)->leftChild->leftChild->rightChild->leftChild, 7);
	AddChild(&(*point)->leftChild->rightChild, 15);
	AddChild(&(*point)->leftChild->rightChild->rightChild, 18);
	AddChild(&(*point)->rightChild, 40);
	AddChild(&(*point)->rightChild->leftChild, 30);
	AddChild(&(*point)->rightChild->leftChild->leftChild, 25);
	AddChild(&(*point)->rightChild->leftChild->rightChild, 35);
}
void Goto(TREE **point, TREE *node){
	(*point) = node;
}

void AddChild(TREE **child, int input){
	*child = (TREE *)malloc(sizeof(TREE) * 1);
	(*child)->leftChild = NULL;
	(*child)->rightChild = NULL;
	(*child)->data = input;
}