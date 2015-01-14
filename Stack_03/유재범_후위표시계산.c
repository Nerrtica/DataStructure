#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

void Push(char schar, int *save, int *top);
int POP(int *save, int *top);

int main(void){
	int i = 0, num1 = 0, num2 = 0, top = 0, save[100] = {0, };
	char *function = NULL, schar = 0;

	function = (char *)malloc(sizeof(char) * 100);

	printf("give me a function(dont press space) : ");
	gets(function);

	for(i = 0; i < strlen(function); i++){
		schar = function[i];

		switch(schar){
		case (43):// +
			if(top == 2){
					num2 = POP(save, &top);
					num1 = POP(save, &top);
					Push(num2 + num1, save, &top);
			}
			else{
				Push(schar - '0', save, &top);
			}
			break;
		case (45):// -
			if(top == 2){
					num2 = POP(save, &top);
					num1 = POP(save, &top);
					Push(num1 - num2, save, &top);
			}
			else{
				Push(schar - '0', save, &top);
			}
			break;
		case (42):// *
			if(top == 2){
					num2 = POP(save, &top);
					num1 = POP(save, &top);
					Push(num2 * num1, save, &top);
			}
			else{
				Push(schar - '0', save, &top);
			}
			break;
		case (47):// /
			if(top == 2){
					num2 = POP(save, &top);
					num1 = POP(save, &top);
					Push(num1 / num2, save, &top);
			}
			else{
				Push(schar - '0', save, &top);
			}
			break;
		default:
			Push(schar - '0', save, &top);
			break;
		}
	}
	i = POP(save, &top);
	if(top < 1){
		printf("결과 : %d\n", i);
	}
	else{
		printf("잘못된 수식\n");
	}
	free(function);
	return 0;
}
void Push(int schar, int *save, int *top){
	save[*top] = schar;
	(*top)++;
}
int POP(int *save, int *top){
	int re = 0;
	(*top)--;
	re = save[*top];
	save[*top] = 0;
	return re;
}