#include <stdio.h>
#include <stdlib.h>

#define ERROR -9999

typedef struct Node {
	int data;
	struct Node * NextNode;
} _node;

int SearchData( _node * head ){

	int data=0, order=0;
	char isFind = 0;

	_node *ptr;
	
	ptr = head;

	printf("Please input Num to search Data : "); scanf("%d",&data); fflush(stdin);

	while( ptr->NextNode != NULL ){

		if( ptr->data == data ){
			isFind = 1;
			break;
		}

		ptr = ptr->NextNode;
		order++;
	}
	
	if(isFind == 0)
		return ERROR;
	else
		return order+1;
}

int SearchNum( _node * head ){

	int data=0, order=1;
	char isFind = 0;

	_node *ptr;
	ptr = head;

	printf("Please input Num to search Node : "); scanf("%d",&data);

	while( ptr->NextNode != NULL ){

		if( order == data ){
			isFind = 1;
			break;
		}

		ptr = ptr->NextNode;
		order++;
	}
	
	if(isFind == 0)
		return ERROR;
	else
		return ptr->data;
}

void add( _node * head ){

	_node * New, *ptr;
	
	New = (_node*)malloc(sizeof(_node));
	New->NextNode = NULL;
	ptr = head;

	while( ptr->NextNode != NULL){
		ptr = ptr->NextNode;
	}
	
	ptr->NextNode = New;

	printf("Please input value in NEW Node : ");
	scanf("%d",&New->data);
	getchar();

}

void addNum( _node * head ){

	int order=0, i;
	_node * New, *ptr;
	
	New = (_node*)malloc(sizeof(_node));
	ptr = head;

	printf("Please input Num : "); scanf("%d",&order);

	for( i=0; i<order-1; i++ ){
		ptr = ptr->NextNode;
	}
	
	printf("Please input value in NEW Node : "); scanf("%d",&New->data);

	New->NextNode = ptr->NextNode;
	ptr->NextNode = New;

	getchar();

}

void ShowAllNodes( _node * head ){
	
	_node * tmp = head;
	
	while( tmp->NextNode != NULL ){
		printf("%d -> ",tmp->data);
		tmp = tmp->NextNode;
	}
		printf("%d",tmp->data);
}

void SearchDelete( _node * head ){

	int data=0, order=0;
	char isFind = 0;

	_node *ptr, *tmp;
	ptr = head;

	printf("Please input Data to delete : "); scanf("%d",&data);
	while( ptr->NextNode != NULL ){
		
		if( ptr->NextNode->data == data ){
			tmp = ptr->NextNode;
			ptr->NextNode = ptr->NextNode->NextNode;
			free(tmp);
		}

		ptr = ptr->NextNode;
	}
}

int main(){

	_node * head;
	int trial, order, i;

	///// initialize /////
	head = (_node*)malloc(sizeof(_node));
	printf("Please input value in Head : ");
	scanf("%d",&head->data);
	head->NextNode = NULL;
	//////////////////////

	printf("\nadd\n");
	printf("=================\n");
	printf("Please TRIAL number to add : "); scanf("%d",&trial);
	
	for( i=0; i<trial; i++)
		add(head);
	
	ShowAllNodes(head);


	printf("\n\nadd as order\n");
	printf("=================\n");
	addNum( head );
	ShowAllNodes(head);


	printf("\n\nData Search\n");
	printf("=================\n");
	order = SearchData(head);
	if( order == ERROR )
		printf("Not found!");
	else
		printf("There is at %dth Node",order);

	printf("\n\nNode Search\n");
	printf("=================\n");
	order = SearchNum(head);
	if( order == ERROR )
		printf("Not found!");
	else
		printf("DATA : %d",order);


	printf("\n\nDelete Data\n");
	printf("=================\n");
	SearchDelete(head);
	ShowAllNodes(head);

	getchar();
	getchar();
	return 0;
}