#include <stdio.h>
#include "basedef.h"
#include "FuncDeclare.h"

//보드 내부의 모든 원소를 EMPTY로 초기화
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

// 보드판 출력
void printBoard(int Board[][A_SIZE])
{
	int widthHeight = 6;
	char X[6][6] = { {"X    X"},{" X  X "},{"  XX  "},{"  XX  "} ,{" X  X "} ,{"X    X"} };
	char O[6][6] = { {" OOOO "},{"OO  OO"},{"O    O"} ,{"O    O"},{"OO  OO"} ,{" OOOO "} };
	char nothing[6][6] = { {"      "},{"      "},{" ==== "},{" ==== "},{"      "},{"      "} };
	

	printf_s("\n               BOARD\n\n");
	printf_s("     1        2        3\n\n");
	printf_s("    ---------------------------\n");

	for (int i = 0; i < A_SIZE; i++)
	{
		for (int l = 0; l < widthHeight; l++)
		{
			if (l == 0) { printf_s(" %d  |", i+1); }
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

//보드가 다 찼는지의 유무를 반환
int isBoardFull(const int Board[][A_SIZE])
{
	for (int i = 0;i < A_SIZE; i++)
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

// 플레이어가 선택한 곳을 보드에 기입
void makeMove(int Board[][A_SIZE], int Col, int Row, const int Player)
{
	Board[Col][Row] = Player;
}


/*
연속된 3개의 플레이어 심볼 확인
일치 : 1(TRUE) 반환
불일치 : 0(FLASE) 반환
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
자신이 이길경우 10점
상대방이 이길경우 -10점
비길경우 0점
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
// 컴퓨터 차례
void ComputerTurn(int Board[][A_SIZE], int Player)
{
	int depth = 0;
	int bestPos = minMax(Board, Player, &depth); // 최선의 위치 선택
	printf_s("Searched.... bestMove: %d\n", bestPos + 1);
	makeMove(Board, bestPos / A_SIZE, bestPos % A_SIZE, COMP);
}

//사람 차례
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



//게임 실행
void runGameVSCom(void)
{
	int Player = 0;

	printf_s("\nChoose X or O. O moves first !!\n\n");
	while (1)
	{

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

	initBoard(Board);
	printBoard(Board);

	while (!gameOver)
	{

		if (Player == HUMAN)
		{
			HumanTurn(Board, Player);
		}
		else
		{
			ComputerTurn(Board, Player);
		}

		printBoard(Board);

		if (is3inARow(Board, Player))
		{
			printf_s("Game Over\n");
			gameOver = 1;
			if (Player == COMP)
			{
				printf_s("Computer Wins\n");
			}
			else
			{
				printf_s("Human Wins\n");
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

void showMenu()
{
	printf("\n\n\n\t\tTicTacToe Game\n\n");
	printf("\t     모드를 선택해 주세요.\n\n");
	printf("\t      1. Player VS Player\n");
	printf("\t      2. Player VS Computer\n");
	
	int choice;
	scanf("%d", &choice);
	getchar();
	
	while (!(choice == 1 || choice == 2)) { // choice가 1또는 2가 아니라면
		printf("1또는 2를 선택해주세요!\n");
		scanf("%d", &choice);
		getchar();
	}
	
	if (choice == 1)
		runGameVSHuman();
	else // choice = 2
		runGameVSCom();
}
