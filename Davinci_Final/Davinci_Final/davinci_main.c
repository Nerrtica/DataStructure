#include "common.h"

void howToPlay();							//게임 방법 메뉴
void lookRank();							//등수 보기 메뉴
void printExample();						//매뉴얼 설명을 위한 UI 출력

/*기본적인 색깔, 커서 등의 함수. 출처 인터넷*/
void setcolor(int bgcolor, int color)	//색깔설정하기
{ 
	color &= 0xf;
	bgcolor &= 0xf;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}
void gotoxy(int x, int y)	//커서 이동하기
{
	COORD Pos = {x-1,y-1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Pos);
}
void setcursorNoVisible(){ // 커서 안보이게 하기
	CONSOLE_CURSOR_INFO CurInfo;
	CurInfo.dwSize=1;
	CurInfo.bVisible=FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CurInfo);
}
void setcursorVisible(){ // 커서 보이게 하기
	CONSOLE_CURSOR_INFO CurInfo;
	CurInfo.dwSize=20;
	CurInfo.bVisible=TRUE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CurInfo);
}
int SelectNumber(int low, int high, int x, int y)	//메뉴 선택용 함수
{
	char input = 0 ;
	int Select = 1 ;
	BOOL out = false;

	setcursorNoVisible();
	gotoxy(x,y);
	printf("☞");

	while(!out){
		input=getch();
		if (input==0 || input==0x00)
			input=getch();

		switch(input){

		case 72://위쪽
			if(Select==low)
				break;
			else{
				--Select;
				gotoxy(x,y);
				printf("  ");
				gotoxy(x,--y);
				printf("☞");
			}
			break;

		case 80://아래쪽
			if(Select==high)
				break;
			else{
				++Select;
				gotoxy(x,y);
				printf("  ");
				gotoxy(x,++y);
				printf("☞");
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
		printf("\t                          게임 시작\n");
		printf("\t                          게임 방법\n");
		printf("\t                          등수 보기\n");
		printf("\t                          게임 종료\n");
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
			printf("게임을 종료합니다.\n");
			system("pause");
			return;
			break;
		}
	}
}

void howToPlay()
{
	/*1번 매뉴얼 - 게임의 난이도*/
	setcolor(0,15);
	system("cls");
	printf("\n\n\n\n\n\n           난이도를 선택해주세요!\n");
	printf("\n\n               ☞쉬움\n");
	printf("                 어려움\n");
	printf("\n\n난이도를 선택하는 창입니다.\n");
	printf("난이도는 상대할 컴퓨터가 얼마나 똑똑할지를 결정합니다.\n");
	printf("어려움을 선택하면 컴퓨터가 다른 플레이어의 블록을 맞출 확률이 증가합니다.\n");
	printf("본인의 실력에 맞는 난이도를 선택해주세요.\n\n");
	system("pause");

	/*2번 매뉴얼 - 유저 이름 입력*/
	system("cls");
	setcolor(0,15);
	printf("\n\n      플레이하는 유저의 이름을 입력해주세요(한글 5글자, 영어 10글자 이내)\n");
	gotoxy(30,11);
	setcolor(0,14);
	printf("┌─────┐");
	gotoxy(30,12);
	printf("│          │");
	gotoxy(30,13);
	printf("└─────┘");
	setcolor(0,15);
	gotoxy(28,12);
	printf("☞");
	gotoxy(1,17);
	printf("처음 게임을 시작하면 플레이어의 이름을 입력합니다.\n");
	printf("화살표가 가리키는 공간에 이름을 입력합니다.\n");
	printf("유저의 이름이 한글 5글자, 영어 10글자를 넘어가지 않도록 주의해주세요.\n");
	printf("유저의 이름은 랭킹에 반영되므로 가급적 이후 플레이에도 같은 이름을 사용해주세요.\n");
	printf("만약 입력된 이름이 최대 글자수를 넘어갈 경우, 최대 글자수까지의 이름만이 저장됩니다.\n\n");
	system("pause");

	/*3번 매뉴얼 - 게임의 규칙*/
	printExample();
	gotoxy(1,32);
	printf("초기 화면입니다.\n");
	printf("각 플레이어는 자신에게 주어진 블록의 수와 상대방 블록의 색깔만을 이용해,\n");
	printf("상대방 블록의 숫자를 맞춰야 합니다.\n");
	printf("블록은 자동적으로 랜덤으로 3명의 플레이어에게 배정됩니다.\n");
	printf("또한 블록은 적힌 숫자가 점점 커지도록 정렬되어 놓아집니다.\n");
	printf("만약 같은 숫자의 블록을 2개 가지고 있다면, 빨간색이 왼쪽으로 갑니다.\n\n");
	system("pause");
	
	printExample();
	gotoxy(12,29);
	printf("☞");
	gotoxy(1,32);
	printf("화살표가 가리키는 곳에 나열된 숫자는 본인 블록의 숫자들입니다.\n");
	printf("각각 위쪽에 위치한 블록의 숫자입니다.\n");
	printf("숫자가 왼쪽에서 오른쪽으로 점점 커지는 것을 볼 수 있습니다.\n");
	printf("똑같은 숫자가 있는 4, 5, 8은 빨간색이 왼쪽에 위치하고 있습니다.\n");
	printf("물론 이 규칙은 컴퓨터의 블록에도 똑같이 적용됩니다.\n\n");
	system("pause");

	printExample();
	gotoxy(5,2);
	printf("☞");
	gotoxy(1,32);
	printf("이 청록색 화살표는 숫자가 어느 방향으로 커지는 지를 명확하게 나타내줍니다.\n");
	printf("Com1쪽의 화살표는 아래쪽을 향하고있으므로, 숫자가 아래로 갈 수록 커진다는 것을,\n");
	printf("Com2쪽은 위쪽을 향하고 있으므로 위로 갈 수록 커진다는 것을 알려줍니다.\n\n");
	system("pause");

	printExample();
	gotoxy(1,32);
	printf("게임을 진행하면 본인의 차례에서 상대편의 블록을 오픈시킬 수 있습니다.\n");
	printf("어떤 사용자의 블록을 맞출 지, 몇 번째 블록을 맞출 지, 추측하는 숫자는 몇인지,\n");
	printf("기본적인 플레이 흐름을 따라 자연스럽게 입력하게 된다면,\n\n");
	system("pause");

	printExample();
	gotoxy(11,1);
	setcolor(0,14);
	printf("──┐");
	gotoxy(11,2);
	printf("  3 │");
	gotoxy(11,3);
	printf("──┘");
	setcolor(0,15);
	gotoxy(17,2);
	printf("☜");
	gotoxy(1,32);
	printf("축하합니다! 당신은 막 다른 사용자의 블록을 오픈시켰습니다.\n");
	printf("블록을 지정하고 정확하게 숫자를 맞춘다면 그 블록은 모두에게 오픈됩니다.\n");
	printf("그리고 당신은 계속해서 턴을 진행할 수 있습니다.\n");
	printf("만약 틀린다면, 턴은 다음 순서의 사람에게 넘어가게 됩니다.\n");
	printf("\n이런 방식으로 반복하여, 한 명의 플레이어를 제외한 모두의 블록이 오픈된다면,\n");
	printf("우승자는 숨겨진 블록이 남아있는 그 한 명이 되며, 게임이 종료됩니다.\n");
	printf("\n다빈치 코드는 간단한 게임같지만, 다양한 공략이 존재하는 재미있는 게임입니다.\n");
	printf("게임을 플레이하며 공략들을 배워보세요.\n\n");
	system("pause");

	/*4번 매뉴얼 - 등수 보기*/
	system("cls");
	printf("등수 보기 메뉴로 들어간다면, 지금까지 플레이 했던 유저들의 등수를 볼 수 있습니다.\n");
	printf("승률은 (우승한 횟수/총 플레이 횟수) 로 산출됩니다.\n");
	printf("같은 이름으로 계속 우승하여 유저 1등을 노려보세요!\n\n");
	printf("매뉴얼은 여기까지입니다. 즐거운 게임 되세요♬\n\n");
	system("pause");
}

void printExample()
{
	//1
	system("cls");
	printf("        ");
	setcolor(0,14);
	printf("┌┐                                              ┌┐\n");
	setcolor(0,3);
	printf("      ↓");
	setcolor(0,14);
	printf("││                                              ││");
	setcolor(0,3);
	printf("↑\n");
	printf("        ");
	setcolor(0,14);
	printf("└┘                                              └┘\n");
	//2
	setcolor(0,12);
	printf("        ");
	printf("┌┐                                              ");
	setcolor(0,14);
	printf("┌┐\n");
	setcolor(0,3);
	printf("      ↓");
	setcolor(0,12);
	printf("││                                              ");
	setcolor(0,14);
	printf("││");
	setcolor(0,3);
	printf("↑\n");
	printf("        ");
	setcolor(0,12);
	printf("└┘                                              ");
	setcolor(0,14);
	printf("└┘\n");
	//3
	setcolor(0,12);
	printf("        ");
	printf("┌┐                                              ");
	setcolor(0,14);
	printf("┌┐\n");
	setcolor(0,3);
	printf("      ↓");
	setcolor(0,12);
	printf("││                                              ");
	setcolor(0,14);
	printf("││");
	setcolor(0,3);
	printf("↑\n");
	printf("        ");
	setcolor(0,12);
	printf("└┘                                              ");
	setcolor(0,14);
	printf("└┘\n");
	//4
	setcolor(0,14);
	printf("        ");
	printf("┌┐                                              ┌┐\n");
	setcolor(0,3);
	printf("      ↓");
	setcolor(0,14);
	printf("││                                              ││");
	setcolor(0,3);
	printf("↑\n");
	printf("        ");
	setcolor(0,14);
	printf("└┘                                              └┘\n");
	//5
	setcolor(0,12);
	printf("        ");
	printf("┌┐                                              ");
	setcolor(0,14);
	printf("┌┐\n");
	setcolor(0,3);
	printf("      ↓");
	setcolor(0,12);
	printf("││                                              ");
	setcolor(0,14);
	printf("││");
	setcolor(0,3);
	printf("↑\n");
	printf("        ");
	setcolor(0,12);
	printf("└┘                                              ");
	setcolor(0,14);
	printf("└┘\n");
	//6
	setcolor(0,12);
	printf("        ");
	printf("┌┐                                              ");
	setcolor(0,14);
	printf("┌┐\n");
	setcolor(0,3);
	printf("      ↓");
	setcolor(0,12);
	printf("││                                              ");
	setcolor(0,14);
	printf("││");
	setcolor(0,3);
	printf("↑\n");
	printf("        ");
	setcolor(0,12);
	printf("└┘                                              ");
	setcolor(0,14);
	printf("└┘\n");
	//7
	setcolor(0,12);
	printf("        ");
	printf("┌┐                                              ┌┐\n");
	setcolor(0,3);
	printf("      ↓");
	setcolor(0,12);
	printf("││                                              ││");
	setcolor(0,3);
	printf("↑\n");
	printf("        ");
	setcolor(0,12);
	printf("└┘                                              └┘\n");
	//8
	setcolor(0,12);
	printf("        ");
	printf("┌┐                                              ┌┐\n");
	setcolor(0,3);
	printf("      ↓");
	setcolor(0,12);
	printf("││                                              ││");
	setcolor(0,3);
	printf("↑\n");
	printf("        ");
	setcolor(0,12);
	printf("└┘                                              └┘\n");
	//~comPrint

	printf("\n\n           ");
	setcolor(0,14);
	printf("┌─┐┌─┐");
	setcolor(0,12);
	printf("┌─┐┌─┐");
	setcolor(0,14);
	printf("┌─┐");
	setcolor(0,12);
	printf("┌─┐┌─┐");
	setcolor(0,14);
	printf("┌─┐\n");

	printf("           ");
	setcolor(0,14);
	printf("└─┘└─┘");
	setcolor(0,12);
	printf("└─┘└─┘");
	setcolor(0,14);
	printf("└─┘");
	setcolor(0,12);
	printf("└─┘└─┘");
	setcolor(0,14);
	printf("└─┘\n");
	setcolor(0,15);
	printf("              1     2     3     5     5     6     7     7  ");
	setcolor(0,3);
	printf("\n                                user_name\n");

	setcolor(0,15);
	gotoxy(1,11);
	printf("┌─┐│\n");
	printf("│:I├┤\n");
	printf("└─┘│\n");
	setcolor(0,3);
	printf("  Com1  ");

	setcolor(0,15);
	gotoxy(63,11);
	printf("│┌─┐");
	gotoxy(63,12);
	printf("├┤I:│");
	gotoxy(63,13);
	printf("│└─┘");
	gotoxy(63,14);
	setcolor(0,3);
	printf("  Com2  ");
	setcolor(0,15);
}

void lookRank()
{
	int temp,i=0,m,n,len;								//수를 셀 때 임시로 받을 temp와 배열의 길이를 구하기 위한 len 변수
	int num_space, color;								//그래프를 출력할 때 필요한 변수
	float total, win, swap_grade;						//게임 플레이 횟수, 이긴 횟수, 승률 변경할 때 사용할 변수
	float grade[100];									//해당하는 승률
	char names[100][11]={NULL,};						//이름 목록
	char* swap_name;									//이름을 바꿀 때 사용할 포인터 변수
	FILE* user_info=fopen("users.txt","a+");			//유저 정보가 들어있는 파일을 불러옴

	srand((unsigned)(time(NULL)));
	
	system("cls");
	setcolor(0,15);
	fseek(user_info,0,SEEK_SET);						//커서를 맨 앞으로 옮김
	swap_name=(char*)malloc(sizeof(char)*10);			//동적할당
	while(fgets(names[i],100,user_info))				//사용자의 이름을 받는 동안 반복
	{
		win=0;
		total=0;
		if (names[i]==0)								//받을 이름이 없으면 탈출
			break;
		len=strlen(names[i]) -1;
		names[i][len]=NULL;								//개행문자 위치에 NULL 삽입
		while(1)
		{
			temp=fgetc(user_info);						//승수와 플레이횟수를 세기 위해 한 글자씩 받아옴
			if(temp==10||temp==-1)						//개행문자나 EOF를 받으면 탈출
				break;
			else if(temp=='!')							//'!'를 받으면 승수 증가
				win++;
			total++;									//그 외는 플레이 횟수 증가
		}
		grade[i]=win/total;								//해당 사용자의 승률을 기록
		i++;
	}

	/* 버블정렬로 승률순으로 저장*/
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

	/* 그래프로 순위 출력 */
	printf("현재까지 다빈치코드를 플레이한 유저들의 순위입니다.\n\n\n");
	for(m=0;m<i;m++)
	{
		color = rand()%14 +1;							//랜덤한 컬러 사용
		num_space = (int)(grade[m]*50);					//50칸을 전체 길이로 하여 승률*50만큼 그래프가 출력되도록 함
		setcolor(color,0);
		for(n=0;n<num_space;n++)
			printf(" ");
		setcolor(0,15);
		for(;n<50;n++)
			printf(" ");
		printf(" %d등 : %s (승률:%1.2f)\n",m+1, names[m], grade[m]);	//순위, 유저의 이름과 승률 출력
	}
	fclose(user_info);									//파일을 닫음
	printf("\n");
	system("pause");
}