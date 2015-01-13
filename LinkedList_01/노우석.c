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
	List *start;
	start = (List * ) malloc(sizeof(List));
	start->data = -1;
	start->next = NULL;
	
	Add(start);
	Add(start);
	Add(start);
	Add(start);
	Add_num(start,3);
	AllDataPrint(start);
	Order_Delete(start,3);
	Delete(start);
	AllDataPrint(start);
	printf("%d\n",Search(start,3));
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
		printf("%d number List Delete!", num);
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