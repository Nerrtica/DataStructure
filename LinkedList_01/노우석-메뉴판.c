#include <stdio.h>
#include <stdlib.h>

typedef struct p{
	int data;
	struct p *next;
}List;

void Add(List *start);
void Add_num(List *start, int num);
void Delete(List *start);
void Order_Delete(List *p);
void AllDataPrint(List *start);
int Search(List *start, int data);

int main(){
	int select,num;
	List *start;
	start = (List * ) malloc(sizeof(List));
	start->data = -1;
	start->next = NULL;
	
	printf("*****Menu*****\n");
	printf("1.Add\n");
	printf("2.Add_Order\n");
	printf("3.Delete\n");
	printf("4.Delte_Order\n");
	printf("5.Show List\n");
	printf("6.Search\n");
	printf("7.Exit\n");
	do{
		scanf("%d",&select);
		switch(select){
			case 1: Add(start);
				break;
			case 2:	printf("Order : "); 
					scanf("%d",&num);
					Add_num(start,num);
				break;
			case 3: Delete(start);
				break;
			case 4:printf("Order : ");
				   scanf("%d",&num);
				   Order_Delete(start,num);
			    break;
			case 5:AllDataPrint(start);
				break;
			case 6:printf("Find Value :");
					scanf("%d",&num);
					printf("%dth Data\n",Search(start,num));
				break;
			case 7:	printf("Exit!\n");
				break;
			default:printf("Put Error!\n");
				break;

		}
	}while(select != 7);
	
	return 0;
}

void Add(List *start){
	
	int data;
	List *temp =start ,*add;

	while(1){
		if(temp->next != NULL){
			temp = temp->next;
		}
		else{
			printf("Add final !\n");
			add = (List *) malloc (sizeof(List));
			temp->next = add;
			add->next = NULL;
			printf("Final added List Value: ");
			scanf("%d", &data);
			add->data = data;
			return;
		}
	}
}
void Add_num(List *start, int num){
	
	List *temp = start,*add;
	int data,i;

	if(num == 0) {
		printf("Number Error!\n");
		return;
	}
	else{
		for(i=0;i<num-1;i++){
			temp = temp->next;	
		}
		add = (List *) malloc(sizeof(List));
		add->next  = temp->next;
		temp->next = add;
		printf("%d nubmer Added List value: ",num);
		scanf("%d",&data);
		add->data = data;
		return;
	}

}
void Delete(List *start){
	
	List *first = start, *temp;

	while(1){
		if(first->next != NULL){
			temp = first;
			first = first->next;
		}
		else{
			printf("Delete final List!\n");
			free(first);
			temp->next = NULL;
			return;
		}
	}
}
void Order_Delete(List *start, int num){
	
	List *first = start, *temp;
	int i;
	if(num == 0) {
		printf("Number Error!\n");
		return;
	}
	else{
		for(i=0;i<num;i++){
			temp = first;
			first = first->next;
		}
		temp->next = first->next;
		free(first);
		printf("%d number List Delete!\n", num);
		return;
	}
}
void AllDataPrint(List *start){
	
	while(start->next != NULL){
		printf("%d -> ",start->data);
		start = start->next;
	}
	printf("%d\n", start->data);

	return;
}
int Search(List *start, int data){
	
	List *first=start;
	int position = 0;

	while(first->next != NULL){
		if(first->data == data){
			printf("Find!\n");
			return position;
		}
		else{
			first = first->next;
			position++;
		}
	}

	if(first->data == data){
		printf("Find!\n");
		return position;
	}
	else {
		printf("Not Find the Value\n");
		return -99;
	}
}