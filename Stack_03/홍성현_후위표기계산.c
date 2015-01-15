#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR_POP -9999	
#define END -99999	
#define MAX_LENGTH 256

int *stack;
int size, top = 0;

void push(int data);
int pop();
int isEmpty();
int isFull();
int isOkChar(char user_input[]);
int isOkBracket(char user_input[]);
void makePostfix(char user_input[], char save[]);
int calculatePostfix(char save[]);

void main()
{
	int i, result = 0;
	char user_input[MAX_LENGTH], save[MAX_LENGTH];

	size = MAX_LENGTH;
	
	for(i = 0 ; i < MAX_LENGTH ; i++)
	{
		save[i] = 0;
		user_input[i] = 0;
	}
	stack = (int *)malloc(sizeof(int) * size);

	printf("equation : ");
	scanf("%s", user_input);
	getchar();

	if(isOkBracket(user_input) == 0)//°ýÈ£ Ã¼Å©
	{
		printf("Bye!\n");
		return;
	}
	if(isOkChar(user_input) == 0)
	{
		printf("Bye!\n");
		return;
	}

	makePostfix(user_input, save);

	printf("°á°ú : %s\n",save);

	result = calculatePostfix(save);

	printf("°á°ú : %d\n",result);

	free(stack);

	return;
}

void push(int data) 
{
	if(isFull() == 1)
		return;
	else
	{
		stack[top] = data;
		top++;
		return;
	}
}
int pop() 
{
	if(isEmpty() == 1)
		return ERROR_POP;
	else
	{
		top--;
		return stack[top];
	}
}
int isEmpty()	
{
	if(top == 0)
		return 1;
	else
		return 0;
}
int isFull()	
{
	if(top == size)
	{
		size *= 2;
		stack = (int *)realloc(stack, (sizeof(int) * size));
	}
		return 0;
}
int isOkChar(char user_input[])
{
	int i;

	for(i = 0 ; i < strlen(user_input) ; i++)
	{
		if(!((user_input[i] >= '0' && user_input[i] <= '9') || user_input[i] == '(' || user_input[i] == ')' || user_input[i] == '*' || user_input[i] == '/' || user_input[i] == '+' || user_input[i] == '-'))
			return 0;
	}

	return 1;
}
int isOkBracket(char user_input[])
{
	int checker = 0, i;

	for(i = 0 ; i < strlen(user_input) ; i++)
	{
		if(user_input[i] == '(')
			checker += 1;
		else if(user_input[i] == ')')
			checker -= 1;

		if(checker < 0)
			return 0;
	}

	if(checker == 0)
		return 1;
	else
		return 0;
}
void makePostfix(char user_input[], char save[])
{
	int i, index = 0, temp;

	for(i = 0 ; i < strlen(user_input) ; i++)
	{
		if(user_input[i] >= '0' && user_input[i] <= '9')
		{
			save[index] = user_input[i];
			index++;
		}
		else if(user_input[i] == ')')
		{
			temp = pop();
			
			while(temp != '(')
			{
				save[index] = temp;
				index++;
				temp = pop();
			}
		}
		else if(user_input[i] == '(')
		{
			push(user_input[i]);
		}
		else if(user_input[i] == '+' || user_input[i] == '-')
		{
			if(isEmpty() == 1)
				push(user_input[i]);
			else
			{
				temp = pop();
				if(temp == '(')
				{
					push('(');
					push(user_input[i]);
				}
				else
				{
					while(1)
					{
						save[index] = temp;
						index++;
						if(isEmpty() == 1)
						{
							push(user_input[i]);
							break;
						}
						temp = pop();
						if(temp == ERROR_POP)
							break;
						if(temp == '(')
						{
							push(temp);
							push(user_input[i]);
							break;
						}
					}
				}
			}
		}
		else// *¶û /
		{
			if(isEmpty() == 1)
				push(user_input[i]);
			else
			{
				temp = pop();

				if(temp == '*' || temp == '/')
				{
					save[index] = temp;
					index++;
				}
				else
					push(temp);

				push(user_input[i]);
			}
		}
 	}

	if(i == strlen(user_input))
	{
		while(isEmpty() != 1)
		{
			temp = pop();
			save[index] = temp;
			index++;
		}
	}
}
int calculatePostfix(char save[])
{
	int result = 0, i, variable1, variable2;

	for(i = 0 ; i < strlen(save) ; i++)
	{
		if(save[i] >= '0' && save[i] <= '9')
			push(save[i]);
		else
		{
			variable2 = pop() - '0';
			variable1 = pop() - '0';

			if(save[i] == '+')
			{ 
				result = (variable1 + variable2);
				push(result + '0');
			}
			else if(save[i] == '-')
			{
				result = (variable1 - variable2);
				push(result + '0');
			}
			else if(save[i] == '*')
			{
				result = (variable1 * variable2);
				push(result + '0');
			}
			else if(save[i] == '/')
			{
				result = (variable1 / variable2);
				push(result + '0');
			}
		}
	}

	return result;
}