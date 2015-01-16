#include "common.h"

/* 블록 정보 구조체 */
typedef struct _BLOCK
{
	int index;
	BOOL Yellow;

} block;

/* 전역 변수 */
int all_block[12][2];							//모든 블록의 소유자 정보
block owner_block[3][9];						//각 플레이어의 블록 정보([n][0]은 블록 개수-블록 배분을 위함)
BOOL open_block[3][8];							//오픈된 블록의 위치 정보
BOOL wrong_block[3][8][12];						//추측이 틀렸던 블록의 정보
BOOL know_block[12][2];							//모두가 아는 블록 정보(오픈된 블록)
int guess_board[3][8][13];						//컴퓨터의 AI를 위한 추측판([n][m][0]은 가능한 수의 전체 개수)
char user_name[11];								//유저의 이름
char com_face[3][3] = {{0,0},{':','I'},{'I',':'}};

/* 함수 목록 */
void flushScanValue(void*);						//fflush + scanf("%d",value)
COORD getCursorPosition();						//현재 커서의 위치를 리턴해줌. (출처 : 인터넷)

void makeGuessBoard(int, BOOL);					//추측판을 만드는 함수
BOOL confirmAnswer(int, int, int);				//답이 맞는지 확인하는 함수

BOOL gameEnd();									//게임이 끝났는지 확인하는 함수
BOOL playerAlive(int);							//플레이어가 살았는지 확인하는 함수
void userTurn(int*, int*, int*);				//유저의 행동 정보를 받는 함수
void comTurn(int, int*, int*, int*);			//컴퓨터의 행동 정보를 받는 함수
void saveResult(BOOL);							//게임의 결과를 저장하는 함수

void printBoard();								//전체 게임 화면을 출력하는 함수
void printComBoard(int, int, int);				//컴퓨터의 블록판을 출력하는 함수(printBoard에 포함)
void printUserBoard(int);						//유저의 블록판을 출력하는 함수(printBoard에 포함)

void gamePlay()
{
	BOOL yellow;								//블록 색깔
	int new_num;								//블록 숫자
	int own_index = 0, own_count = 0;			//블록 분배를 위한 변수들
	int player = 0;								//현재 턴의 플레이어
	int guess, block_num, target;				//행동 정보를 위한 변수들
	BOOL hard;									//게임의 난이도
	int i, j;

	srand((unsigned int)time(NULL));
	setcolor(0,15);

	memset(user_name, 0, sizeof(user_name));
	memset(owner_block, 0, sizeof(owner_block));
	memset(open_block, false, sizeof(open_block));
	memset(wrong_block, false, sizeof(wrong_block));
	memset(know_block, false, sizeof(know_block));
	com_face[1][0] = ':';
	com_face[1][1] = 'I';
	com_face[2][0] = 'I';
	com_face[2][1] = ':';						//메모리 초기화

	/* 블록의 소유자 지정 */
	for(i=0;i<24;i++)
	{
		own_count = 0;
		yellow = (i%2) == 1;
		new_num = i/2 + 1;

		for(j=0;j<3;j++)
			own_count += (owner_block[j][0].index <8)? 1:0;	//블록을 8개 가지고 있지 않은 플레이어의 수를 체크
		own_count = rand() % own_count;			//플레이어의 수 안에서 랜덤한 순서로 배정
		for(j=0;j<3;j++)
		{
			if(owner_block[j][0].index < 8 && --own_count < 0)
			{
				own_index = j;	//블록을 8개 가지고 있지 않은 플레이어 중, 아까 배정한 순서의 플레이어에게 블록을 배정
				break;
			}
		}

		all_block[new_num-1][yellow] = own_index;
		owner_block[own_index][++owner_block[own_index][0].index].index = new_num;
		owner_block[own_index][owner_block[own_index][0].index].Yellow = yellow;						//정보 변수에 저장
	}

	/* 난이도 선택 */
	system("cls");
	fflush(stdin);
	printf("\n\n\n\n\n\n           난이도를 선택해주세요!\n");
	printf("\n\n                 쉬움\n");
	printf("                 어려움\n");
	setcursorNoVisible();
	hard = SelectNumber(1,2,16,10) -1;
	setcursorVisible();

	/* 유저의 이름을 입력받음 */
	system("cls");
	printf("\n\n\n\n\n\n      플레이하는 유저의 이름을 입력해주세요(한글 5글자, 영어 10글자 이내)\n");
	gotoxy(30,11);
	setcolor(0,14);
	printf("┌─────┐");
	gotoxy(30,12);
	printf("│          │");
	gotoxy(30,13);
	printf("└─────┘");
	gotoxy(32,12);
	setcolor(0,14);
	fflush(stdin);
	fgets(user_name,11,stdin);
	setcolor(0,15);
	gotoxy(1,17);
	for(i=0;i<10;i++)
		if(user_name[i] == '\n')
			user_name[i] = NULL;
	printf("      %s님, 즐거운 플레이 되세요. 3초 후 자동으로 게임이 시작됩니다.\n",user_name);
	setcursorNoVisible();
	Sleep(3000);
	gotoxy(1,1);
	setcursorVisible();

	/* 게임 진행 */
	while(!gameEnd())												//게임이 끝날때까지 턴을 반복
	{
		makeGuessBoard(player, hard);								//추측판 생성
		printBoard();												//게임 화면 출력

		if(player == 0)
			userTurn(&target, &block_num, &guess);					//player == 0 이라면 유저의 턴 진행
		else
			comTurn(player, &target, &block_num, &guess);			//그 외는 컴퓨터의 턴 진행

		if(confirmAnswer(target, block_num, guess))					//답을 확인하여 정답이라면
		{
			if(player == 1)
				com_face[player][1] = ')';
			else if(player == 2)
				com_face[player][0] = '(';							//표정을 바꾸고
			printf("정답입니다!\n");
			player --;												//턴을 계속 반복하게 하기 위해 player--를 해줌
		}
		else
		{
			if(player == 1)
				com_face[player][1] = '(';
			else if(player == 2)
				com_face[player][0] = ')';
			printf("아쉽네요, 틀렸습니다.\n");						//아니라면 다음 사람에게 턴이 넘어감
		}

		system("pause");
		while(!playerAlive(player = (player + 1)%3));				//죽은 플레이어라면 턴을 넘김
	}
	
	/* 게임 종료 */
	if(playerAlive(1))
	{
		com_face[1][0] = 'X';
		com_face[1][1] = ')';
	}
	else if(playerAlive(2))
	{
		com_face[2][0] = '(';
		com_face[2][1] = 'X';
	}
	printBoard();
	printf("게임이 끝났습니다.\n");
	if(playerAlive(0)){
		printf("1등은 %s 입니다. 축하드립니다.\n",user_name);
		saveResult(true);}
	else if(playerAlive(1)){
		printf("1등은 Com1 입니다.\n");
		saveResult(false);}
	else{
		printf("1등은 Com2 입니다.\n");
		saveResult(false);}											//1등을 출력하고 결과를 저장
	system("pause");
	return;
}

BOOL gameEnd()
{
	return (playerAlive(0) + playerAlive(1) + playerAlive(2)) <= 1;
		//살아있는 플레이어가 1명 이하일 때 true를 리턴함(게임 종료)
}

BOOL playerAlive(int player)
{
	int i;
	for(i=0;i<8;i++)
		if(!open_block[player][i])
			break;
	if(i == 8)
		if(player == 1)
			com_face[player][0] = ';';
		else if(player == 2)
			com_face[player][1] = ';';
	return i != 8;
		//플레이어의 블록이 모두 오픈되었을 때 false를 리턴함(죽음)
}

BOOL confirmAnswer(int target, int block_num, int guess)
{
	if(owner_block[target][block_num].index == guess)
	{
		open_block[target][block_num -1] = true;
		know_block[guess-1][owner_block[target][block_num].Yellow] = true;
		if(target == 1)
			com_face[target][1] = '(';
		else if(target == 2)
			com_face[target][0] = ')';
		return true;
	}	//답이 맞다면, 블록을 오픈하고 true 리턴
	else
	{
		wrong_block[target][block_num -1][guess -1] = true;
		if(target == 1)
			com_face[target][1] = ')';
		else if(target == 2)
			com_face[target][0] = '(';
		return false;
	}	//답이 틀리다면, wrong_block에 정보를 저장하고 false 리턴
}

void userTurn(int *target, int *block_num, int *guess)
{
	int confirm;
	int x, y;

	printf("%s님의 차례입니다.\n",user_name);
	START:
	do
	{
		printf("어떤 사용자의 블록을 맞추시겠습니까?(Com1 : 1, Com2 : 2) : ");
		flushScanValue(target);
	} while(*target != 1 && *target != 2);							//타겟을 입력받음. 제대로 된 값이 입력될 때까지 반복
	do
	{
		printf("몇 번째 블록을 맞추시겠습니까?(1~8) : ");
		flushScanValue(block_num);
	} while(*block_num < 1 || *block_num > 8);						//블록의 위치를 입력받음. 제대로 된 값이 입력될 때까지 반복

	if(open_block[*target][*block_num-1])
		{
			printf("이미 오픈된 블록입니다. 다른 블록을 선택해주세요.\n");
			goto START;												//이미 오픈된 블록이라면 되돌아감
		}

	x = (int)getCursorPosition().X + 1;
	y = (int)getCursorPosition().Y + 1;								//현재 커서의 위치를 저장해둠
	if(*target == 1)
	{
		gotoxy(13,3*(*block_num)-1);
		setcolor(0,11);
		printf("☜");
		gotoxy(x,y);
		setcolor(0,15);
	}
	else if(*target == 2)
	{
		gotoxy(57,26-3*(*block_num));
		setcolor(0,11);
		printf("☞");
		gotoxy(x,y);
		setcolor(0,15);
	}																//유저의 편의를 위해 지정한 블록을 가리키는 화살표 출력
	do
	{
		printf("고르신 블록이 위 화살표가 가리키는 블록이 맞습니까?(예 : 1, 아니오 : 2) : ");
		flushScanValue(&confirm);
	} while(confirm != 1 && confirm != 2);							//블록이 맞는지 여부 확인. 제대로 된 값이 입력될 때까지 반복
	
	x = (int)getCursorPosition().X + 1;
	y = (int)getCursorPosition().Y + 1;
	if(*target == 1)
	{
		gotoxy(13,3*(*block_num)-1);
		printf("  ");
		gotoxy(x,y);
	}
	else if(*target == 2)
	{
		gotoxy(57,26-3*(*block_num));
		printf("  ");
		gotoxy(x,y);
	}
	if(confirm == 2)
	{
		gotoxy(1,32);
		printf("                                                                              \n");
		printf("                                                                              \n");
		printf("                                                                              \n");
		printf("                                                                              \n");
		printf("                                                                              \n");
		printf("                                                                              \n");
		printf("                                                                              \n");
		printf("                                                                              \n");
		printf("                                                                              \n");
		gotoxy(1,32);
		goto START;													//틀리다면 처음으로 되돌아감.
	}
	do
	{
		printf("예측하는 번호는 몇입니까?(1~12) : ");
		flushScanValue(guess);
	} while(*guess < 1 || *guess > 12);								//예측하는 수를 입력받음. 제대로 된 값이 입력될 때까지 반복
}

void comTurn(int player, int *target, int *block_num, int *guess)
{
	int i, j;
	int min = 9;

	*target = -1;
	
	for(i=0;i<3;i++)
	{
		if(i == player || !playerAlive(i))							//현재 턴의 플레이어나 죽은 플레이어는 패스함
			continue;
		for(j=0;j<8;j++)
		{
			if(guess_board[i][j][0] <= 0)							//추측판에서 가능한 수가 0이라면 그 자리는 패스함
				continue;
			if(guess_board[i][j][0] < min)							//만약 가능한 개수가 min보다 작다면,
			{
				*target = i;										//타겟을 i로 변경하고
				min = guess_board[*target][j][0];					//min에 그 자리의 가능성 개수를 저장하고
				*block_num = j+1;									//block_num에 그 자리를 저장
			}
		}
	}

	if(*target == -1)
		printf("맞춰야 할 블록이 없습니다.\n");						//타겟이 없다면 맞춰야 할 블록이 없음
	else
	{
		for(i=1;i<=12;i++)
		{
			if(guess_board[*target][*block_num-1][i] == 1)
			{
				*guess = i;
				break;												//가능성이 있는 수 중 가장 작은 수를 guess로 선택
			}
		}
		if(*target == 0)
			printf("Com%d이 %s의 %d번째 블록을 가리켰습니다.\n",player,user_name,*block_num);
		else
			printf("Com%d이 Com%d의 %d번째 블록을 가리켰습니다.\n",player,*target,*block_num);
		printf("Com%d : 블록의 숫자는 %d입니다.\n",player,*guess);
	}
}

void makeGuessBoard(int owner, BOOL hard)
{
	int i, j, k, min;
	int Rmin,Ymin;
	
	for(i=0;i<3;i++)
	{
		if(owner == i || !playerAlive(i))							//현재 턴의 플레이어나 죽은 플레이어는 패스함
			continue;
		
		min = 0;
		Rmin = 0;
		Ymin = 0;

		for(j=0;j<8;j++)
		{
			guess_board[i][j][0] = 0;								//추측가능 수의 개수를 0으로 초기화
			if(open_block[i][j])									//만약 오픈된 블록 자리라면
			{
				min = owner_block[i][j+1].index - 1;				//미니멈을 오픈된 블록의 숫자보다 1 작게 설정하고 패스
				continue;
			}
			if(hard)											//난이도가 hard라면
			{
				min ++;
				if(j==0 || owner_block[i][j+1].Yellow)
				{
					if(!owner_block[i][j].Yellow)
						min --;
				}
			}													//블록의 색깔이 빨강->노랑인 경우를 제외하고 최소 숫자를 1씩 증가시킴
			for(k=0;k<12;k++)
			{
				guess_board[i][j][k+1] = 0;							//추측판을 0으로 초기화하면서
				if(!owner_block[i][j+1].Yellow)						//만약 블록이 빨간색이라면
				{
					if(k+1<=(j+1)/2)
						continue;
					if(k+1>9+j/2)
						continue;
				}
				else if(owner_block[i][j+1].Yellow)					//노란색이라면
				{
					if(k+1<=j/2)
						continue;
					if(k+1>=9+(j+1)/2)
						continue;
				}																//블록 순서에 의한 제거 - 패스
				if(k<min) continue;												//k가 미니멈보다 작다면 0인 채 패스
				if(wrong_block[i][j][k]) continue;								//이미 틀렸던 정보라면 패스
				if(know_block[k][owner_block[i][j+1].Yellow]) continue;			//이미 알려진 블록이라면 패스      ★문제가 있다!!!!!
				if(all_block[k][owner_block[i][j+1].Yellow] == owner) continue;	//턴을 플레이하는 플레이어에게 있는 블록이라면 패스

				if(hard)											//난이도가 hard라면
				{
					if(!owner_block[i][j+1].Yellow)
						if(k<Rmin) continue;
					else
						if(k<Ymin) continue;
				}
				guess_board[i][j][k+1] = 1;							//모두 아니라면 가중치 1을 주고
				guess_board[i][j][0]++;								//가능한 수에 1을 더함
			}
			
			if(!owner_block[i][j+1].Yellow)
			{
				for(k=1;k<13;k++)
				{
					if(guess_board[i][j][k] == 1)
					{
						Rmin = k;
						break;
					}
				}
			}
			else if(owner_block[i][j+1].Yellow)
			{
				for(k=1;k<13;k++)
				{
					if(guess_board[i][j][k] == 1)
					{
						Ymin = k;
						break;
					}
				}
			}
		}
	}
}

void printBoard()
{
	int i;
	system("cls");
	for(i=0;i<8;i++)
	{
		switch(i)
		{
			case 0:
			case 1:
			case 2:
			case 3:
			case 5:
			case 6:
			case 7:
				printf("        ");
				break;
			case 4:
				break;
		}
		printComBoard(1,2,i);
	}
	printUserBoard(0);
	printf("\n");
}

void printUserBoard(int index)
{
	int i;
	printf("           ");

	/* 첫번째 줄 */
	for(i=0;i<8;i++)
	{
		if(open_block[index][i])									//블록이 오픈되었다면
		{
			if(!owner_block[index][i+1].Yellow)						//블록이 빨간색이라면
			{
				setcolor(0,12);
				printf("┌─┐");
			}
			else
			{
				setcolor(0,14);
				printf("┌─┐");
			}
		}
		else
			printf("      ");										//오픈되지 않았다면
	}

	/* 두번째 줄 */
	printf("\n           ");
	for(i=0;i<8;i++)
	{
		if(open_block[index][i])	
		{
			if(!owner_block[index][i+1].Yellow)
			{
				setcolor(0,12);
				printf("│%2d│",owner_block[index][i+1].index);
			}
			else
			{
				setcolor(0,14);
				printf("│%2d│",owner_block[index][i+1].index);
			}
		}
		else
			printf("      ");
	}																//첫번째 줄과 같음

	/* 세번째 줄 */
	printf("\n           ");
	for(i=0;i<8;i++)
	{
		if(open_block[index][i])
		{
			if(!owner_block[index][i+1].Yellow)
			{
				setcolor(0,12);
				printf("│  │");
			}
			else
			{
				setcolor(0,14);
				printf("│  │");
			}
		}
		else
		{
			if(!owner_block[index][i+1].Yellow)
			{
				setcolor(0,12);
				printf("┌─┐");
			}
			else
			{
				setcolor(0,14);
				printf("┌─┐");
			}
		}
	}																	//역시 같은 방식

	/* 네번째 줄 */
	printf("\n           ");
	for(i=0;i<8;i++)
	{
		if(!owner_block[index][i+1].Yellow)
			{
				setcolor(0,12);
				printf("└─┘");
			}
			else
			{
				setcolor(0,14);
				printf("└─┘");
			}
	}																	//같은 방식
	printf("\n           ");
	setcolor(0,15);
	for(i=0;i<8;i++)
		printf("  %2d  ",owner_block[index][i+1].index);				//유저를 위해 기본적인 블록 정보를 출력
	setcolor(0,3);
	printf("\n                                %s",user_name);			//유저 이름 출력
	setcolor(0,15);
}

void printComBoard(int com1, int com2, int i)
{
	/* 첫번째 줄 */
	if(i == 4)
		printf("└─┘│");
	if(!owner_block[com1][i+1].Yellow)									//com1의 블록이 빨간색이라면
	{
		setcolor(0,12);
		printf("┌");
	}
	else
	{
		setcolor(0,14);
		printf("┌");
	}

	if(!open_block[com1][i])											//com1의 블록이 오픈되지 않았다면
		printf("┐                                          ");
	else
		printf("──┐                                      ");

	if(!open_block[com2][7-i])											//com2의 블록이 오픈되지 않았다면
	{
		if(!owner_block[com2][8-i].Yellow)								//com2의 블록이 빨간색이라면
		{
			setcolor(0,12);
			printf("    ┌┐");
		}
		else
		{
			setcolor(0,14);
			printf("    ┌┐");
		}
	}
	else																//com2의 블록이 오픈되었다면
	{
		if(!owner_block[com2][8-i].Yellow)								//com2의 블록이 빨간색이라면
		{
			setcolor(0,12);
			printf("┌──┐");
		}
		else
		{
			setcolor(0,14);
			printf("┌──┐");
		}
	}
	if(i == 4)
	{
		setcolor(0,15);
		printf("│└─┘");
	}
	printf("\n");

	/* 두번째 줄 */
	if(!owner_block[com1][i+1].Yellow)
	{
		if(i == 3)
		{
			setcolor(0,15);
			printf("┌─┐│");
			setcolor(0,12);
			printf("│");
		}
		else if(i == 4)
		{
			setcolor(0,3);
			printf("  Com1  ");
			setcolor(0,12);
			printf("│");
		}
		else
		{
			setcolor(0,3);
			printf("      ↓");
			setcolor(0,12);
			printf("│");
		}
	}
	else
	{
		setcolor(0,14);
		if(i == 3)
		{
			setcolor(0,15);
			printf("┌─┐│");
			setcolor(0,14);
			printf("│");
		}
		else if(i == 4)
		{
			setcolor(0,3);
			printf("  Com1  ");
			setcolor(0,14);
			printf("│");
		}
		else
		{
			setcolor(0,3);
			printf("      ↓");
			setcolor(0,14);
			printf("│");
		}
	}

	if(!open_block[com1][i])
		printf("│                                          ");
	else
		printf(" %2d │                                      ",owner_block[com1][i+1].index);

	if(!open_block[com2][7-i])
	{
		if(!owner_block[com2][8-i].Yellow)
		{
			setcolor(0,12);
			printf("    ││");
		}
		else
		{
			setcolor(0,14);
			printf("    ││");
		}
	}
	else
	{
		if(!owner_block[com2][8-i].Yellow)
		{
			setcolor(0,12);
			printf("│ %2d │",owner_block[com2][8-i].index);
		}
		else
		{
			setcolor(0,14);
			printf("│ %2d │",owner_block[com2][8-i].index);
		}
	}
	if(i == 3)
	{
		setcolor(0,15);
		printf("│┌─┐");
	}
	else if(i == 4)
	{
		setcolor(0,3);
		printf("  Com2  ");
	}
	else
	{
		setcolor(0,3);
		printf("↑");
	}
	printf("\n");														//첫번째 줄과 같은 방식

	/* 세번째 줄 */
	if(!owner_block[com1][i+1].Yellow)
	{
		setcolor(0,12);
		if(i == 3)
		{
			setcolor(0,15);
			printf("│%s├┤",com_face[1]);
			setcolor(0,12);
			printf("└");
		}
		else
			printf("        └");
	}
	else
	{
		setcolor(0,14);
		if(i == 3)
		{
			setcolor(0,15);
			printf("│%s├┤",com_face[1]);
			setcolor(0,14);
			printf("└");
		}
		else
			printf("        └");
	}

	if(!open_block[com1][i])
		printf("┘                                          ");
	else
		printf("──┘                                      ");

	if(!open_block[com2][7-i])
	{
		if(!owner_block[com2][8-i].Yellow)
		{
			setcolor(0,12);
			printf("    └┘");
		}
		else
		{
			setcolor(0,14);
			printf("    └┘");
		}
	}
	else
	{
		if(!owner_block[com2][8-i].Yellow)
		{
			setcolor(0,12);
			printf("└──┘");
		}
		else
		{
			setcolor(0,14);
			printf("└──┘");
		}
	}
	if(i == 3)
	{
		setcolor(0,15);
		printf("├┤%s│",com_face[2]);
	}
	setcolor(0,15);
	printf("\n");														//역시 같은 방식
}

void flushScanValue(void* value)
{
	fflush(stdin);
	scanf("%d", value);
}

void saveResult(BOOL win)
{
	char name[11];														//유저의 이름을 저장할 배열
	char buffer[100][100];												//txt의 내용을 임시로 저장할 buffer
	int i, j, k;
	BOOL find = false;													//유저를 찾았는지 여부
	FILE* user_info=fopen("users.txt","a+");							//user_info 파일포인터에 users.txt를 오픈시킴

	memset(name,0,11);
	memset(buffer,0,100*100);
	rewind(user_info);													//메모리 초기화
	for(j=0;;j++)
	{
		for(i=0;;i++)
		{
			buffer[j][i] = fgetc(user_info);							//user_info를 한글자씩 받아와 buffer에 저장
			if(buffer[j][i] == '\n')									//개행문자가 입력된다면
			{
				buffer[j][i] = NULL;									//NULL을 저장하고 탈출
				break;
			}
			if(buffer[j][i] == EOF)										//EOF(파일의 끝)이 입력된다면
				break;													//탈출
		}
		if(buffer[j][i] == EOF)											//EOF라면
		{
			buffer[j][i] = NULL;
			buffer[j][i+1] = NULL;										//NULL을 저장하고 탈출
			break;
		}
	}

	fclose(user_info);													//user_info 파일을 닫음

	for(k=0;k<j;k++)
	{
		if(strcmp(user_name, buffer[k]) == 0)							//buffer에서 user_name을 찾음
		{
			find = true;												//찾는다면 find를 true로 저장하고 탈출
			break;
		}
	}

	if(find)															//user_name을 찾았다면
	{
		for(i=0;buffer[k+1][i]!=0;i++);
		if(win)
			buffer[k+1][i] = '!';
		else
			buffer[k+1][i] = '?';										//해당하는 유저의 게임 플레이 정보에 승/패 여부를 저장
	}
	else
	{
		strcpy(buffer[k],user_name);									//찾지 못했다면 새롭게 유저를 생성
		if(win)
			buffer[k+1][0] = '!';
		else
			buffer[k+1][0] = '?';										//게임 플레이 정보에 승/패 여부를 저장
	}

	user_info = fopen("users.txt","w");									//쓰기모드로 users.txt를 다시 오픈

	if(find)															//유저를 찾았다면
	{
		for(k=0;k<j;k++)
		{
			for(i=0;buffer[k][i]!=0;i++)
				fputc(buffer[k][i],user_info);
			fputc('\n',user_info);
		}
		fclose(user_info);												//처음 오픈해서 저장해온 줄수만큼 다시 집어넣음
	}
	else
	{
		for(k=0;k<j+2;k++)
		{
			for(i=0;buffer[k][i]!=0;i++)
				fputc(buffer[k][i],user_info);
			fputc('\n',user_info);
		}
		fclose(user_info);												//못 찾았다면 유저의 정보가 새로 입력되었으므로 처음 저장해온 줄수 +2 만큼 집어넣음
	}
}

COORD getCursorPosition()
{
    CONSOLE_SCREEN_BUFFER_INFO buffInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&buffInfo);
    return   buffInfo.dwCursorPosition;
}