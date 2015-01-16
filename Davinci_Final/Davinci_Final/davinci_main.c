#include "common.h"

void howToPlay();							//���� ��� �޴�
void lookRank();							//��� ���� �޴�
void printExample();						//�Ŵ��� ������ ���� UI ���

/*�⺻���� ����, Ŀ�� ���� �Լ�. ��ó ���ͳ�*/
void setcolor(int bgcolor, int color)	//�������ϱ�
{ 
	color &= 0xf;
	bgcolor &= 0xf;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}
void gotoxy(int x, int y)	//Ŀ�� �̵��ϱ�
{
	COORD Pos = {x-1,y-1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Pos);
}
void setcursorNoVisible(){ // Ŀ�� �Ⱥ��̰� �ϱ�
	CONSOLE_CURSOR_INFO CurInfo;
	CurInfo.dwSize=1;
	CurInfo.bVisible=FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CurInfo);
}
void setcursorVisible(){ // Ŀ�� ���̰� �ϱ�
	CONSOLE_CURSOR_INFO CurInfo;
	CurInfo.dwSize=20;
	CurInfo.bVisible=TRUE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CurInfo);
}
int SelectNumber(int low, int high, int x, int y)	//�޴� ���ÿ� �Լ�
{
	char input = 0 ;
	int Select = 1 ;
	BOOL out = false;

	setcursorNoVisible();
	gotoxy(x,y);
	printf("��");

	while(!out){
		input=getch();
		if (input==0 || input==0x00)
			input=getch();

		switch(input){

		case 72://����
			if(Select==low)
				break;
			else{
				--Select;
				gotoxy(x,y);
				printf("  ");
				gotoxy(x,--y);
				printf("��");
			}
			break;

		case 80://�Ʒ���
			if(Select==high)
				break;
			else{
				++Select;
				gotoxy(x,y);
				printf("  ");
				gotoxy(x,++y);
				printf("��");
			}
			break;

		case 13:
			out = true;
		default:
			break;
		}
	}
	setcursorVisible();
	return Select;
}

void main()
{
	int selec;

	while(1)
	{
		system("cls");
		gotoxy(1,1);
		setcolor(0,11);
		printf("\t###############################################################\n");
		printf("\t####      #####  ####  ####  ###  ###  ####  ###      ###  ####\n");
		printf("\t####  ###  ### ## ####  ##  ####  ###    ##  ##  ########  ####\n");
		printf("\t####  ###  ##      ####    #####  ###  #  #  ##  ########  ####\n");
		printf("\t####     ###  ####  ####  ######  ###  ##    ###      ###  ####\n");
		printf("\t###############################################################\n");
		printf("\t#############      #####      #####      #####      ###########\n");
		printf("\t###########  #########  ####  ####  ###  ####  ################\n");
		printf("\t##########  #########  #####  ###  ####  ###      #############\n");
		printf("\t#########  #########  ####  ####  ###  ####  ##################\n");
		printf("\t##########      ####      #####      #####      ###############\n");
		printf("\t###############################################################\n\n");
		printf("\t                          ���� ����\n");
		printf("\t                          ���� ���\n");
		printf("\t                          ��� ����\n");
		printf("\t                          ���� ����\n");
		setcolor(0,10);
		selec = SelectNumber(1,4,33,14);
		switch(selec){
		case 1:
			gamePlay();
			break;
		case 2:
			howToPlay();
			break;
		case 3:
			lookRank();
			break;
		case 4:
			gotoxy(1,19);
			setcolor(0,15);
			printf("������ �����մϴ�.\n");
			system("pause");
			return;
			break;
		}
	}
}

void howToPlay()
{
	/*1�� �Ŵ��� - ������ ���̵�*/
	setcolor(0,15);
	system("cls");
	printf("\n\n\n\n\n\n           ���̵��� �������ּ���!\n");
	printf("\n\n               �ѽ���\n");
	printf("                 �����\n");
	printf("\n\n���̵��� �����ϴ� â�Դϴ�.\n");
	printf("���̵��� ����� ��ǻ�Ͱ� �󸶳� �ȶ������� �����մϴ�.\n");
	printf("������� �����ϸ� ��ǻ�Ͱ� �ٸ� �÷��̾��� ����� ���� Ȯ���� �����մϴ�.\n");
	printf("������ �Ƿ¿� �´� ���̵��� �������ּ���.\n\n");
	system("pause");

	/*2�� �Ŵ��� - ���� �̸� �Է�*/
	system("cls");
	setcolor(0,15);
	printf("\n\n      �÷����ϴ� ������ �̸��� �Է����ּ���(�ѱ� 5����, ���� 10���� �̳�)\n");
	gotoxy(30,11);
	setcolor(0,14);
	printf("��������������");
	gotoxy(30,12);
	printf("��          ��");
	gotoxy(30,13);
	printf("��������������");
	setcolor(0,15);
	gotoxy(28,12);
	printf("��");
	gotoxy(1,17);
	printf("ó�� ������ �����ϸ� �÷��̾��� �̸��� �Է��մϴ�.\n");
	printf("ȭ��ǥ�� ����Ű�� ������ �̸��� �Է��մϴ�.\n");
	printf("������ �̸��� �ѱ� 5����, ���� 10���ڸ� �Ѿ�� �ʵ��� �������ּ���.\n");
	printf("������ �̸��� ��ŷ�� �ݿ��ǹǷ� ������ ���� �÷��̿��� ���� �̸��� ������ּ���.\n");
	printf("���� �Էµ� �̸��� �ִ� ���ڼ��� �Ѿ ���, �ִ� ���ڼ������� �̸����� ����˴ϴ�.\n\n");
	system("pause");

	/*3�� �Ŵ��� - ������ ��Ģ*/
	printExample();
	gotoxy(1,32);
	printf("�ʱ� ȭ���Դϴ�.\n");
	printf("�� �÷��̾�� �ڽſ��� �־��� ����� ���� ���� ����� ������ �̿���,\n");
	printf("���� ����� ���ڸ� ����� �մϴ�.\n");
	printf("����� �ڵ������� �������� 3���� �÷��̾�� �����˴ϴ�.\n");
	printf("���� ����� ���� ���ڰ� ���� Ŀ������ ���ĵǾ� �������ϴ�.\n");
	printf("���� ���� ������ ����� 2�� ������ �ִٸ�, �������� �������� ���ϴ�.\n\n");
	system("pause");
	
	printExample();
	gotoxy(12,29);
	printf("��");
	gotoxy(1,32);
	printf("ȭ��ǥ�� ����Ű�� ���� ������ ���ڴ� ���� ����� ���ڵ��Դϴ�.\n");
	printf("���� ���ʿ� ��ġ�� ����� �����Դϴ�.\n");
	printf("���ڰ� ���ʿ��� ���������� ���� Ŀ���� ���� �� �� �ֽ��ϴ�.\n");
	printf("�Ȱ��� ���ڰ� �ִ� 4, 5, 8�� �������� ���ʿ� ��ġ�ϰ� �ֽ��ϴ�.\n");
	printf("���� �� ��Ģ�� ��ǻ���� ��Ͽ��� �Ȱ��� ����˴ϴ�.\n\n");
	system("pause");

	printExample();
	gotoxy(5,2);
	printf("��");
	gotoxy(1,32);
	printf("�� û�ϻ� ȭ��ǥ�� ���ڰ� ��� �������� Ŀ���� ���� ��Ȯ�ϰ� ��Ÿ���ݴϴ�.\n");
	printf("Com1���� ȭ��ǥ�� �Ʒ����� ���ϰ������Ƿ�, ���ڰ� �Ʒ��� �� ���� Ŀ���ٴ� ����,\n");
	printf("Com2���� ������ ���ϰ� �����Ƿ� ���� �� ���� Ŀ���ٴ� ���� �˷��ݴϴ�.\n\n");
	system("pause");

	printExample();
	gotoxy(1,32);
	printf("������ �����ϸ� ������ ���ʿ��� ������� ����� ���½�ų �� �ֽ��ϴ�.\n");
	printf("� ������� ����� ���� ��, �� ��° ����� ���� ��, �����ϴ� ���ڴ� ������,\n");
	printf("�⺻���� �÷��� �帧�� ���� �ڿ������� �Է��ϰ� �ȴٸ�,\n\n");
	system("pause");

	printExample();
	gotoxy(11,1);
	setcolor(0,14);
	printf("������");
	gotoxy(11,2);
	printf("  3 ��");
	gotoxy(11,3);
	printf("������");
	setcolor(0,15);
	gotoxy(17,2);
	printf("��");
	gotoxy(1,32);
	printf("�����մϴ�! ����� �� �ٸ� ������� ����� ���½��׽��ϴ�.\n");
	printf("����� �����ϰ� ��Ȯ�ϰ� ���ڸ� ����ٸ� �� ����� ��ο��� ���µ˴ϴ�.\n");
	printf("�׸��� ����� ����ؼ� ���� ������ �� �ֽ��ϴ�.\n");
	printf("���� Ʋ���ٸ�, ���� ���� ������ ������� �Ѿ�� �˴ϴ�.\n");
	printf("\n�̷� ������� �ݺ��Ͽ�, �� ���� �÷��̾ ������ ����� ����� ���µȴٸ�,\n");
	printf("����ڴ� ������ ����� �����ִ� �� �� ���� �Ǹ�, ������ ����˴ϴ�.\n");
	printf("\n�ٺ�ġ �ڵ�� ������ ���Ӱ�����, �پ��� ������ �����ϴ� ����ִ� �����Դϴ�.\n");
	printf("������ �÷����ϸ� �������� ���������.\n\n");
	system("pause");

	/*4�� �Ŵ��� - ��� ����*/
	system("cls");
	printf("��� ���� �޴��� ���ٸ�, ���ݱ��� �÷��� �ߴ� �������� ����� �� �� �ֽ��ϴ�.\n");
	printf("�·��� (����� Ƚ��/�� �÷��� Ƚ��) �� ����˴ϴ�.\n");
	printf("���� �̸����� ��� ����Ͽ� ���� 1���� ���������!\n\n");
	printf("�Ŵ����� ��������Դϴ�. ��ſ� ���� �Ǽ����\n\n");
	system("pause");
}

void printExample()
{
	//1
	system("cls");
	printf("        ");
	setcolor(0,14);
	printf("����                                              ����\n");
	setcolor(0,3);
	printf("      ��");
	setcolor(0,14);
	printf("����                                              ����");
	setcolor(0,3);
	printf("��\n");
	printf("        ");
	setcolor(0,14);
	printf("����                                              ����\n");
	//2
	setcolor(0,12);
	printf("        ");
	printf("����                                              ");
	setcolor(0,14);
	printf("����\n");
	setcolor(0,3);
	printf("      ��");
	setcolor(0,12);
	printf("����                                              ");
	setcolor(0,14);
	printf("����");
	setcolor(0,3);
	printf("��\n");
	printf("        ");
	setcolor(0,12);
	printf("����                                              ");
	setcolor(0,14);
	printf("����\n");
	//3
	setcolor(0,12);
	printf("        ");
	printf("����                                              ");
	setcolor(0,14);
	printf("����\n");
	setcolor(0,3);
	printf("      ��");
	setcolor(0,12);
	printf("����                                              ");
	setcolor(0,14);
	printf("����");
	setcolor(0,3);
	printf("��\n");
	printf("        ");
	setcolor(0,12);
	printf("����                                              ");
	setcolor(0,14);
	printf("����\n");
	//4
	setcolor(0,14);
	printf("        ");
	printf("����                                              ����\n");
	setcolor(0,3);
	printf("      ��");
	setcolor(0,14);
	printf("����                                              ����");
	setcolor(0,3);
	printf("��\n");
	printf("        ");
	setcolor(0,14);
	printf("����                                              ����\n");
	//5
	setcolor(0,12);
	printf("        ");
	printf("����                                              ");
	setcolor(0,14);
	printf("����\n");
	setcolor(0,3);
	printf("      ��");
	setcolor(0,12);
	printf("����                                              ");
	setcolor(0,14);
	printf("����");
	setcolor(0,3);
	printf("��\n");
	printf("        ");
	setcolor(0,12);
	printf("����                                              ");
	setcolor(0,14);
	printf("����\n");
	//6
	setcolor(0,12);
	printf("        ");
	printf("����                                              ");
	setcolor(0,14);
	printf("����\n");
	setcolor(0,3);
	printf("      ��");
	setcolor(0,12);
	printf("����                                              ");
	setcolor(0,14);
	printf("����");
	setcolor(0,3);
	printf("��\n");
	printf("        ");
	setcolor(0,12);
	printf("����                                              ");
	setcolor(0,14);
	printf("����\n");
	//7
	setcolor(0,12);
	printf("        ");
	printf("����                                              ����\n");
	setcolor(0,3);
	printf("      ��");
	setcolor(0,12);
	printf("����                                              ����");
	setcolor(0,3);
	printf("��\n");
	printf("        ");
	setcolor(0,12);
	printf("����                                              ����\n");
	//8
	setcolor(0,12);
	printf("        ");
	printf("����                                              ����\n");
	setcolor(0,3);
	printf("      ��");
	setcolor(0,12);
	printf("����                                              ����");
	setcolor(0,3);
	printf("��\n");
	printf("        ");
	setcolor(0,12);
	printf("����                                              ����\n");
	//~comPrint

	printf("\n\n           ");
	setcolor(0,14);
	printf("������������");
	setcolor(0,12);
	printf("������������");
	setcolor(0,14);
	printf("������");
	setcolor(0,12);
	printf("������������");
	setcolor(0,14);
	printf("������\n");

	printf("           ");
	setcolor(0,14);
	printf("������������");
	setcolor(0,12);
	printf("������������");
	setcolor(0,14);
	printf("������");
	setcolor(0,12);
	printf("������������");
	setcolor(0,14);
	printf("������\n");
	setcolor(0,15);
	printf("              1     2     3     5     5     6     7     7  ");
	setcolor(0,3);
	printf("\n                                user_name\n");

	setcolor(0,15);
	gotoxy(1,11);
	printf("��������\n");
	printf("��:I����\n");
	printf("��������\n");
	setcolor(0,3);
	printf("  Com1  ");

	setcolor(0,15);
	gotoxy(63,11);
	printf("��������");
	gotoxy(63,12);
	printf("����I:��");
	gotoxy(63,13);
	printf("��������");
	gotoxy(63,14);
	setcolor(0,3);
	printf("  Com2  ");
	setcolor(0,15);
}

void lookRank()
{
	int temp,i=0,m,n,len;								//���� �� �� �ӽ÷� ���� temp�� �迭�� ���̸� ���ϱ� ���� len ����
	int num_space, color;								//�׷����� ����� �� �ʿ��� ����
	float total, win, swap_grade;						//���� �÷��� Ƚ��, �̱� Ƚ��, �·� ������ �� ����� ����
	float grade[100];									//�ش��ϴ� �·�
	char names[100][11]={NULL,};						//�̸� ���
	char* swap_name;									//�̸��� �ٲ� �� ����� ������ ����
	FILE* user_info=fopen("users.txt","a+");			//���� ������ ����ִ� ������ �ҷ���

	srand((unsigned)(time(NULL)));
	
	system("cls");
	setcolor(0,15);
	fseek(user_info,0,SEEK_SET);						//Ŀ���� �� ������ �ű�
	swap_name=(char*)malloc(sizeof(char)*10);			//�����Ҵ�
	while(fgets(names[i],100,user_info))				//������� �̸��� �޴� ���� �ݺ�
	{
		win=0;
		total=0;
		if (names[i]==0)								//���� �̸��� ������ Ż��
			break;
		len=strlen(names[i]) -1;
		names[i][len]=NULL;								//���๮�� ��ġ�� NULL ����
		while(1)
		{
			temp=fgetc(user_info);						//�¼��� �÷���Ƚ���� ���� ���� �� ���ھ� �޾ƿ�
			if(temp==10||temp==-1)						//���๮�ڳ� EOF�� ������ Ż��
				break;
			else if(temp=='!')							//'!'�� ������ �¼� ����
				win++;
			total++;									//�� �ܴ� �÷��� Ƚ�� ����
		}
		grade[i]=win/total;								//�ش� ������� �·��� ���
		i++;
	}

	/* �������ķ� �·������� ����*/
	for(m=0;m<i;m++)
	{
		for(n=0;n<i-m-1;n++)
			if(grade[n]<grade[n+1])
			{
				swap_grade=grade[n];
				grade[n]=grade[n+1];
				grade[n+1]=swap_grade;
				strcpy(swap_name,names[n]);
				strcpy(names[n],names[n+1]);
				strcpy(names[n+1],swap_name);
			}
	}

	/* �׷����� ���� ��� */
	printf("������� �ٺ�ġ�ڵ带 �÷����� �������� �����Դϴ�.\n\n\n");
	for(m=0;m<i;m++)
	{
		color = rand()%14 +1;							//������ �÷� ���
		num_space = (int)(grade[m]*50);					//50ĭ�� ��ü ���̷� �Ͽ� �·�*50��ŭ �׷����� ��µǵ��� ��
		setcolor(color,0);
		for(n=0;n<num_space;n++)
			printf(" ");
		setcolor(0,15);
		for(;n<50;n++)
			printf(" ");
		printf(" %d�� : %s (�·�:%1.2f)\n",m+1, names[m], grade[m]);	//����, ������ �̸��� �·� ���
	}
	fclose(user_info);									//������ ����
	printf("\n");
	system("pause");
}