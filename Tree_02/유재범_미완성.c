#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct TRYEE{
	int data;
	struct TRYEE *leftChild;
	struct TRYEE *rightChild;
}TREE;

void MakeTree(TREE **point);
void Goto(TREE **point, TREE *node);
void AddChild(TREE **child, int input);

int main(void){
	TREE *point;
	int value = 0;

	point = (TREE *)malloc(sizeof(TREE));

	MakeTree(&point);
	
	while(1){
		printf("검색할 데이터의 값을 입력하시오 : ");
		scanf("%d", &value);
	
		SearchValue(&point, value);
	}

	free(point);
	return 0;
}

int SearchValue(TREE **point, int value){
	TREE *node = NULL;
	int select = 0;

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

			return 1;
		}
	}

	if(node == NULL){
		printf("Tree 안에 존재하지 않습니다. 추가하시겠습니까?(Yes : 1, No : 0) : ");
		scanf("%d", &select);
		if(select == 0){
			printf("\n");
			return 1;
		}
		else{
			AddChild(&(*point)->leftChild, value);
			return 1;
		}
	}
	else{
		SearchValue(&node, value);
	}
	
	return 0;
}
int DeleteOneChildContainer(TREE **point, int value){
	if((*point)->data > value){

	}
	else if((*point)->data < value){

	}
	else if((*point)->data == value){

	}
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