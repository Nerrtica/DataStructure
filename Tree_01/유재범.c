#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct _TRYEE{
	char data;
	struct _TRYEE *leftChild;
	struct _TRYEE *rightChild;
}TREE;

void Goto(TREE **point, TREE *node);
void AddChild(TREE **child, char input);
int MakeTree_In_Pre(TREE **point, char *tOne, char *tTwo, int start);
void Read_Post(TREE *point);
int printTree_ (TREE * root, int isLeft, int offset, int depth, char str[20][255]);
void printTree (TREE * root);

int main(void){
	TREE *rOne;
	char tOne[100] = {0, }, tTwo[100] = {0, }, n = 0;
	int sOne = 0, sTwo = 0;

	rOne = (TREE *)malloc(sizeof(TREE) * 1);
	rOne->data = 0;
	rOne->leftChild = NULL;
	rOne->rightChild = NULL;

	while(1){
		printf("어떤 형식입니까?(1. Inorder, 2. Preorder, 3. Postorder) : ");
		scanf("%d", &sOne);
		printf("tree를 입력하십시오. : ");
		scanf("%s", tOne);
	
		printf("어떤 형식입니까?(1. Inorder, 2. Preorder, 3. Postorder) : ");
		scanf("%d", &sTwo);
		printf("tree를 입력하십시오. : ");
		scanf("%s", tTwo);
	
		if((sOne == sTwo) || (sOne + sTwo > 4)){
			printf("주어진 tree로는 형성할 수 없습니다. 다시 입력해 주십시오.\n\n");
			continue;
		}
		else{
			break;
		}
	}

	MakeTree_In_Pre(&rOne, tOne, tTwo, 0);
	printTree(rOne);
	//return 0;
	printf("\n\n\n");
	Read_Post(rOne);
	printf("\n");
	free(rOne);
	return 0;
}
void Read_Post(TREE *point){
	if(point->leftChild != NULL){
		Read_Post(point->leftChild);
	}
	if(point->rightChild != NULL){
		Read_Post(point->rightChild);
	}
	printf("%c", point->data);
}
int MakeTree_In_Pre(TREE **point, char *tOne, char *tTwo, int start){
	TREE *here = NULL;
	char stOne[100] = {0, };
	char stTwo[100] = {0, };
	int count = 0, lNum = 0, rNum = 0, i = 0;
	
	for(count = 0; tTwo[start] != tOne[count]; count++){
		if(count == strlen(tOne) - 1){
			break;
		}
	}

	lNum = count;
	rNum = strlen(tOne) - 1 - count;
	
	for(i = 0; i < count; i++){
		stOne[i] = tOne[i];
	}
	for(i = count + 1; i < strlen(tOne); i++){
		stTwo[i - count - 1] = tOne[i];
	}

	if((lNum < 1) && (rNum < 1)){
		(*point)->data = tTwo[start];
		return 0;
	}
	else if(lNum < 1){
		(*point)->data = tTwo[start];
		AddChild(&(*point)->rightChild, 0);
		MakeTree_In_Pre(&(*point)->rightChild, stTwo, tTwo, start + 1);
		return 0;
	}
	else{
		(*point)->data = tTwo[start];
		AddChild(&(*point)->leftChild, 0);
		MakeTree_In_Pre(&(*point)->leftChild, stOne, tTwo, start + 1);
		start += strlen(stOne) - 1;
		if(strlen(stTwo) > 0){
			AddChild(&(*point)->rightChild, 0);
			MakeTree_In_Pre(&(*point)->rightChild, stTwo, tTwo, start + 2);
		}
	}
	return 0;
}
void Goto(TREE **point, TREE *node){
	(*point) = node;
}

void AddChild(TREE **child, char input){
	*child = (TREE *)malloc(sizeof(TREE) * 1);
	(*child)->leftChild = NULL;
	(*child)->rightChild = NULL;
	(*child)->data = input;
}