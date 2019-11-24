#include <stdio.h>
#include <time.h>
#include "basedef.h"
#include "FuncDeclare.h"

void printRanking() {
	//랭킹 파일의 구성
	/*시간 승/무승 이름\n*/
	struct ranking r[5];

	FILE *fp = NULL;

	fopen_s(&fp, "rank.txt", "r");


	//init
	for (int i = 0; i < 5; i++)
	{
		r[i].id = -1;
		r[i].score = -1;
		r[i].status = -1;
	}



	if (fp != NULL)
	{

		for (int i = 0; i < 5; i++)
		{
			if (feof(fp) == EOF) { break; }
			fscanf_s(fp, "%f %d %d\n", &r[i].score, &r[i].status, &r[i].id);
		}

		fclose(fp);
	}
	else
	{
		fopen_s(&fp, "rank.txt", "w");
		fclose(fp);
	}

	/*score status name*/
	printf_s("\nNow Ranking\nScore(time)\tStatus\t\tStudent ID\n");
	for (int i = 0; i < 5; i++)
	{
		char status = '\0';
		if (r[i].score == -1) { break; }

		if (r[i].status == WIN)
		{
			status = 'W';
		}
		else
		{
			status = 'D';
		}

		printf_s("%.2f\t\t%c\t\t%d\n", r[i].score, status, r[i].id);
	}

	printf_s("\n\n");

}

int insertRanking(float time, int status) {

	if (status == LOSE) { return 0; }

	/*시간 승/무승 이름\n*/
	struct ranking r[5];

	//init
	for (int i = 0; i < 5; i++)
	{
		r[i].score = -1;
		r[i].status = -1;
		r[i].id = -1;
	}

	int seat = -1;
	int id = -1;
	FILE *fp = NULL;

	fopen_s(&fp, "rank.txt", "r");

	if (fp != NULL)
	{
		for (int i = 0; i < 5; i++)
		{
			if (feof(fp) == EOF) { break; }
			fscanf_s(fp, "%f %d %d\n", &r[i].score, &r[i].status, &r[i].id);
		}
		fclose(fp);
	}


	for (int i = 0; i < 5; i++)
	{
		if (r[i].score == -1)
		{
			seat = i;
			break;
		}

		if (r[i].score > time)
		{
			seat = i;
			break;
		}
	}

	if (seat == -1)
	{
		printf_s("Your score is not good enough to rank. Play the game faster\n\n");
	}
	else
	{

		printf_s("Your score is %.2f\n\n", time);
		printf_s("Scores can be ranked. Please enter your student ID\nID(To int) : ");
		scanf_s("%d", &id);
		printf_s("\n\n");

		for (int i = 4; i > seat; i--)
		{
			r[i].id = r[i - 1].id;
			r[i].score = r[i - 1].score;
			r[i].status = r[i - 1].status;
		}

		r[seat].score = time;
		r[seat].id = id;
		r[seat].status = status;

		fopen_s(&fp, "rank.txt", "w");

		for (int i = 0; i < 5; i++)
		{
			if (r[i].score == -1) { break; }
			fprintf_s(fp, "%.2f %d %d\n", r[i].score, r[i].status, r[i].id);
		}

		fclose(fp);
	}

	printf_s("Well saved!\n\n");

	return 0;
}


/*
- 기능 : 보드판 초기화 함수
- 예시 : Board[i][j] = EMPTY, 0 <= i <= A_SIZE, 0 <= j <= A_SIZE
초기화 된 배열을 모습 (#define EMPTY 0)
0 0 0
0 0 0
0 0 0
*/
void initBoard(int Board[][A_SIZE])
{
	for (int i = 0; i < A_SIZE; i++)
	{
		for (int j = 0; j < A_SIZE; j++)
		{
			Board[i][j] = EMPTY;
		}
	}
}


/*
- 기능 : 전체 보드판 출력 (3x3)
각 원소에 지정된 심볼 값으로 변화하여 출력한다.
- 반환 : void
- 출력예시:    빈 칸 출력		O입력 칸 출력			X입력 칸 출력
--------		 ----------			 ----------
|      |		 |  OOOO  |			 | X    X |
|      |		 | OO  OO |			 |  X  X  |
| ==== |		 | O    O |			 |   XX   |
| ==== |		 | O    O |			 |   XX   |
|      |		 | OO  OO |			 |  X  X  |
|      |		 |  OOOO  |			 | X    X |
--------		 ----------			 ----------
*/
void printBoard(int Board[][A_SIZE])
{
	int widthHeight = 6;

	char X[6][6] = { {"X    X"},{" X  X "},{"  XX  "},{"  XX  "} ,{" X  X "} ,{"X    X"} };
	char O[6][6] = { {" OOOO "},{"OO  OO"},{"O    O"} ,{"O    O"},{"OO  OO"} ,{" OOOO "} };
	char nothing[6][6] = { {"      "},{"      "},{" ==== "},{" ==== "},{"      "},{"      "} };

	system("cls");


	printf_s("\n               BOARD\n\n");
	printf_s("     0        1        2\n\n");
	printf_s("    ---------------------------\n");

	for (int i = 0; i < A_SIZE; i++)
	{
		for (int l = 0; l < widthHeight; l++)
		{


			if (l == 0) { printf_s(" %d  |", i); }

			else { printf_s("    |"); }

			for (int j = 0; j < A_SIZE; j++)
			{
				int status = Board[i][j];

				for (int k = 0; k < widthHeight; k++) {
					if (status == 0) {
						printf_s("%c", O[l][k]);
					}
					else if (status == 1) {
						printf_s("%c", X[l][k]);
					}
					else {
						printf_s("%c", nothing[l][k]);
					}
				}
				printf_s(" | ");
			}
			printf_s("\n");
		}
		printf_s("    ---------------------------\n");
	}

	printf_s("\n\n");
}



/*
-기능 : 보드 원소가 빈 공간으로 할당된 것이 있는지 확인하는 기능
빈 공간이 있을 경우는 모든 차례가 끝난경우
빈 공간이 없는 경우는 아직 경기가 안끝난 경우
-반환 : 보드 공간이 다 찼을 경우 - TURE,   빈 보드 공간이 있을 경우 - FALSE
*/
int isBoardFull(const int Board[][A_SIZE])
{
	for (int i = 0; i < A_SIZE; i++)
	{
		for (int j = 0; j < A_SIZE; j++)
		{
			if (Board[i][j] == EMPTY)
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}



/*
-기능 : 플레이어가 입력한 위치에 그 플레이어의 심볼을 입력
-예시:
조건 - input : (1,2), playerSimbol : 'O', 이때 'O'의 정수값은 1이라 가정
결과 - 보드 인덱스1,인덱스2 위치에 O에 할당된 정수 값 대입, Board[1][2] = 1
*/
void makeMove(int Board[][A_SIZE], int Col, int Row, const int Player)
{
	Board[Col][Row] = Player;
}


/*
-기능 : 가로, 세로, 대각선으로 3개의 동일한 심볼을 확인
-반환 : 3개가 연속적으로 동일할 때 : TRUE,  불연속일 때 : FALSE
-예시 : 대각선 일치	가로 일치	세로 일치	 불일치
O O X 		 O O O		 O X O		 O X O
O X O		 O X X		 X X O		 X O O
X O X		 X O X		 O X X		 O X X
*/
int is3inARow(const int Board[][A_SIZE], const int Player)
{
	int rowCount = 0;
	int columnCnt = 0;
	int downDiagonalCnt = 0;
	int upDiagonalCnt = 0;

	for (int i = 0; i < A_SIZE; i++)
	{
		rowCount = 0;
		columnCnt = 0;

		for (int j = 0; j < A_SIZE; j++)
		{
			if (Board[i][j] == Player)
			{
				rowCount++;
			}
			if (Board[j][i] == Player)
			{
				columnCnt++;
			}
			if (i == j)
			{
				if (Board[i][j] == Player)
					downDiagonalCnt++;
			}

			if (i + j + 1 == A_SIZE)
			{
				if (Board[i][j] == Player)
				{
					upDiagonalCnt++;
				}
			}
		}
		if (rowCount == A_SIZE || columnCnt == A_SIZE || downDiagonalCnt == A_SIZE || upDiagonalCnt == A_SIZE)
			return TRUE;
	}

	return FALSE;
}

/*
-기능 : 자신의 승패 여부에 따라 할당된 점수 값을 반환
-반환 :
자신이 이길 경우 - 10점 (WIN)
상대방이 이길 경우 - 10점 (LOSE)
비길 경우 - 0 (DRAW)
예시 :		  이긴 경우				   		  진 경우				     	  비긴 경우
(현 플레이어의 심볼을 O라 가정)	 (현 플레이어의 심볼을 X라 가정)    (현 플레이어의 심볼을 X라 가정)
O O O				  		   O O O				  		   O X O
O X X				  		   O X X				  		   O X X
X O X 				  		   X O X 				  		   X O X
WIN(10) 반환				  LOSE(-10) 반환			   			 DRAW(0) 반환
*/
int isAWin(const int Board[][A_SIZE], const int Player)
{
	if (is3inARow(Board, Player)) // 이기는 경우
	{
		return WIN;
	}

	if (is3inARow(Board, !Player)) // 상대방이 이기는 경우
	{
		return LOSE;
	}

	return DRAW; // 비기는 경우
}




/*
-기능 : 컴퓨터가 수를 두는 기능
사람 VS 컴퓨터 경기일 경우 사용
*/

void ComputerTurn(int Board[][A_SIZE], int Player, int level)
{
	int depth = 0;
	int bestPos;

	switch (level)
	{
	case 1:
		bestPos = minMax_EASY(Board, Player);				//초급모드 실행
		break;

	case 2:
		bestPos = minMax_NORMAL(Board, Player, &depth);		//중급모드 실행
		break;

	case 3:
		bestPos = minMax_HARD(Board, Player, &depth);		//고급모드 실행
		break;

	default:
		printf("System Error\n");
		bestPos = ERROR;
		break;
	}
	makeMove(Board, bestPos / A_SIZE, bestPos%A_SIZE, Player);


}




/*
-기능 : 사람의 수를 입력 받고 플레이어의 심볼에 일치하는 값을 보드에 입력
사람 VS 컴퓨터, 사람 VS 사람의 경기에 사용
*/
void HumanTurn(int Board[][A_SIZE], const int player)
{
	printf_s("\nEnter your move !!\n\n");
	int inputCol, inputRow;
	while (1)
	{
		scanf_s("%d %d", &inputCol, &inputRow);

		if (Board[inputCol][inputRow] == EMPTY)
		{
			break;
		}
		else
		{
			printf_s("try again : ");
		}
	}
	makeMove(Board, inputCol, inputRow, player);
}




/*
-기능 : 난이도를 조절하는 화면을 출력한다.
-반환 : 사용자가 지정한 컴퓨터의 난이도를 반환한다.
*/
int computerLvlSelect(void)
{
	int level = 0;
	while (level == 0)
	{

		printf("\t난이도를 선택해주세요!!\n");
		printf("\t      1. 초급\n");
		printf("\t      2. 중급\n");
		printf("\t      2. 고급\n");
		scanf_s("%d", &level);



		if (level < 1 || level>3)

		{
			printf("Choose correct level\n");
			level = 0;
		}
	}

	return level;
}

/*
-기능 : 사람의 수를 입력 받고 플레이어의 심볼에 일치하는 값을 보드에 입력
사람 VS 컴퓨터, 사람 VS 사람의 경기에 사용
*/
void runGameVSCom(void)
{
	int Player = 0;
	int level = computerLvlSelect();

	//프린트 랭킹
	printRanking();

	printf_s("\nChoose X or O. O moves first !!\n\n");
	while (1)
	{
		getchar();
		char choice;
		scanf_s("%c", &choice, sizeof(char));

		getchar();

		if (choice == 'O')
		{
			Player = HUMAN;

			break;
		}

		if (choice == 'X')
		{
			Player = COMP;
			break;
		}
		else
		{
			printf_s("Choose correct symbols\n");
		}
	}

	int gameOver = 0;
	int Board[A_SIZE][A_SIZE];
	int startTime;
	int endTime;
	int status = -1;

	initBoard(Board);
	printBoard(Board);

	//랭킹 시간 시작
	startTime = clock();

	while (!gameOver)
	{

		if (Player == HUMAN)
		{
			HumanTurn(Board, Player);
		}
		else
		{
			ComputerTurn(Board, Player, level);
		}

		printBoard(Board);

		if (is3inARow(Board, Player))
		{
			printf_s("Game Over\n");
			gameOver = 1;
			if (Player == COMP)
			{
				status = LOSE;
				printf_s("Computer Wins\n");
			}
			else
			{
				status = WIN;
				printf_s("Human Wins\n");
			}
		}

		if (isBoardFull(Board))
		{
			printf_s("Game Over\n");
			gameOver = 1;
			status = DRAW;
			printf_s("It's a Draw\n");
		}

		Player = !Player;
	}

	//랭킹 시간 끝
	endTime = clock();
	insertRanking((float)(endTime - startTime) / CLOCKS_PER_SEC, status);
}


//사람 VS 사람 대결인 경우
void runGameVSHuman(void)
{
	int Player = 0;

	int gameOver = 0;
	int Board[A_SIZE][A_SIZE];

	initBoard(Board);
	printBoard(Board);

	while (!gameOver)
	{

		if (Player == HUMAN)
		{
			//Player1의 차례
			printf_s("Player1의 차례입니다.\n");
			HumanTurn(Board, Player);
		}
		else
		{
			//Player2의 차례
			printf_s("Player2의 차례입니다.\n");
			HumanTurn(Board, Player);
		}

		printBoard(Board);

		if (is3inARow(Board, Player))
		{
			printf_s("Game Over\n");
			gameOver = 1;
			if (Player == COMP)
			{
				printf_s("Player2 Wins\n");
			}
			else
			{
				printf_s("Player1 Wins\n");
			}
		}

		if (isBoardFull(Board))
		{
			printf_s("Game Over\n");
			gameOver = 1;
			printf_s("It's a Draw\n");
		}

		Player = !Player;
	}
}


/*
-기능 : 초기 메뉴 화면을 출력
*/
void showMenu()
{
	printf("\n\n\n\t\tTicTacToe Game\n\n");
	printf("\t     모드를 선택해 주세요.\n\n");
	printf("\t      1. Player VS Player\n");
	printf("\t      2. Player VS Computer\n");

	int choice;
	scanf_s("%d", &choice);
	getchar();

	while (!(choice == 1 || choice == 2)) { // choice가 1또는 2가 아니라면
		printf("1또는 2를 선택해주세요!\n");
		scanf_s("%d", &choice);
		getchar();
	}

	if (choice == 1)
	{
		runGameVSHuman();
	}
	else // choice = 2
		runGameVSCom();
}