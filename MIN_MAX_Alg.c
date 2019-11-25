/*
 * 파일명 : MIN_MAX_Alg.c
 * 기능 : 민맥스 알고리즘 관련 함수 정의
 * 수정 날짜 : 2019-11-25
 * 파일 제작자 : 세종대학교
 *				오픈소스개론[Pro.장문정] - Team5 (임정원, 강민성, 원성훈, 고선엽)
 */

#include "FuncDeclare.h"
#include <stdlib.h>
#include <time.h>

/*
-반환 : 이길확률이 높은 최적의 좌표값을 반환한다.
-매개변수 : scoreList는 빈 좌표에 대해 점수를 지정한 배열이다.
			bestMove는 최적의 좌표에 대한 인덱스를 가리킨다.
*/
int Max(int scoreList[], int emptyCellCount, int emptyCellList[], int* bestMove)
{
	if (!emptyCellCount)
	{
		return 0;
	}

	int max = -20;

	for (int i = 0; i < emptyCellCount; i++)
	{
		if (scoreList[i] > max)
		{
			max = scoreList[i];
			*bestMove = emptyCellList[i];
		}
	}
	return max;
}

/*
-반환 : 이길확률이 낮은 최적의 좌표값을 반환한다.
-매개변수 : scoreList는 빈 좌표에 대해 점수를 지정한 배열이다.
			bestMove는 최적의 좌표에 대한 인덱스를 가리킨다.
*/
int Min(int scoreList[], int emptyCellCount, int emptyCellList[], int* bestMove)
{
	if (!emptyCellCount)
	{
		return 0;
	}

	int min = +20;

	for (int i = 0; i < emptyCellCount; i++)
	{
		if (scoreList[i] < min)
		{
			min = scoreList[i];
			*bestMove = emptyCellList[i];
		}
	}
	return min;
}

/*
-기능 : 컴퓨터의 차례가 되면 말을 배치하는 상급난이도 함수
-매개변수 : depth는 함수가 재귀적으로 실행될때의 재귀횟수를 저장한다.
-반환 : 컴퓨터가 배치한 말의 인덱스를 반환한다.
-흐름 : 보드의 빈칸에 대한 정보를 저장하여 재귀적으로 사람과 컴퓨터의 말을 배치하는 과정을 반복 수행한다.
		재귀가 더이상 수행될 수 없으면 최선의 위치값을 반환한 뒤 보드를 원상태로 복구시킨다.
*/
int minMax_HARD(int Board[][A_SIZE], int Player, int* depth)
{
	int emptyCellList[A_SIZE * A_SIZE];
	int emptyCellCount = 0;
	int bestPosition = 0;
	int scoreList[A_SIZE * A_SIZE];
	int bestScore;

	bestScore = isAWin(Board, COMP);

	if (bestScore)
	{
		return bestScore - *depth;
	}

	for (int i = 0; i < A_SIZE; i++)
	{
		for (int j = 0; j < A_SIZE; j++)
		{
			if (Board[i][j] == EMPTY)
				emptyCellList[emptyCellCount++] = i * A_SIZE + j;
		}
	}

	int CurPosition;
	for (int i = 0; i < emptyCellCount; i++)
	{
		CurPosition = emptyCellList[i];
		makeMove(Board, CurPosition / A_SIZE, CurPosition % A_SIZE, Player);

		(*depth)++;
		scoreList[i] = minMax_HARD(Board, !Player, depth);
		(*depth)--;

		makeMove(Board, CurPosition / A_SIZE, CurPosition % A_SIZE, EMPTY);
	}

	if (Player == COMP)
	{

		bestScore = Max(scoreList, emptyCellCount, emptyCellList, &bestPosition);
	}

	if (Player == HUMAN)
	{

		bestScore = Min(scoreList, emptyCellCount, emptyCellList, &bestPosition);
	}

	if (*depth != 0)
	{
		return bestScore;
	}
	else
	{
		return bestPosition;
	}
}


/*
-기능 : 컴퓨터의 차례가 되면 말을 배치하는 중급난이도 함수
-매개변수 : depth는 함수가 재귀적으로 실행될때의 재귀횟수를 저장한다.
-반환 : 컴퓨터가 배치한 말의 인덱스를 반환한다.
-흐름 : 상급난이도까지의 흐름과 동일하지만, 빈칸이 적어지면 난이도를 낮추는 기능이 작동한다.
*/

int minMax_NORMAL(int Board[][A_SIZE], int Player, int* depth)
{
	int emptyCellList[A_SIZE * A_SIZE];
	int emptyCellCount = 0;
	int bestPosition = 0;
	int scoreList[A_SIZE * A_SIZE];
	int bestScore;

	bestScore = isAWin(Board, COMP);

	if (bestScore)
	{
		return bestScore - *depth;
	}

	for (int i = 0; i < A_SIZE; i++)
	{
		for (int j = 0; j < A_SIZE; j++)
		{
			if (Board[i][j] == EMPTY)
				emptyCellList[emptyCellCount++] = i * A_SIZE + j;
		}
	}

	if (emptyCellCount >= (A_SIZE*A_SIZE / 2))
	{
		int CurPosition;
		for (int i = 0; i < emptyCellCount; i++)
		{
			CurPosition = emptyCellList[i];
			makeMove(Board, CurPosition / A_SIZE, CurPosition % A_SIZE, Player);

			(*depth)++;
			scoreList[i] = minMax_NORMAL(Board, !Player, depth);
			(*depth)--;

			makeMove(Board, CurPosition / A_SIZE, CurPosition % A_SIZE, EMPTY);
		}

		if (Player == COMP)
		{
			bestScore = Max(scoreList, emptyCellCount, emptyCellList, &bestPosition);
		}

		if (Player == HUMAN)
		{
			bestScore = Min(scoreList, emptyCellCount, emptyCellList, &bestPosition);
		}
	}

	else

	{
		int CurPosition;
		for (int i = 0; i < emptyCellCount; i++)
		{
			CurPosition = emptyCellList[i];
			makeMove(Board, CurPosition / A_SIZE, CurPosition % A_SIZE, Player);

			(*depth)++;
			scoreList[i] = minMax_HARD(Board, !Player, depth);
			(*depth)--;

			makeMove(Board, CurPosition / A_SIZE, CurPosition % A_SIZE, EMPTY);
		}

		if (Player == COMP)
		{
			bestScore = Min(scoreList, emptyCellCount, emptyCellList, &bestPosition);

		}

		if (Player == HUMAN)
		{

			bestScore = Max(scoreList, emptyCellCount, emptyCellList, &bestPosition);
		}

	}

	if (*depth != 0)
	{
		return bestScore;
	}
	else
	{
		return bestPosition;
	}
}


/*
-기능 : 컴퓨터의 차례가 되면 보드의 빈칸을 확인하여 빈칸 중 무작위 칸에 말을 배치하는 초급난이도 함수
-반환 : 컴퓨터가 배치한 말의 인덱스를 반환한다.
*/
int minMax_EASY(int Board[][A_SIZE], int Player)
{
	int emptyCellList[A_SIZE * A_SIZE] = { 0 };
	int emptyCellCount = 0;
	int bestPosition;

	srand((int)time(NULL));


	for (int i = 0; i < A_SIZE; i++)
	{
		for (int j = 0; j < A_SIZE; j++)
		{
			if (Board[i][j] == EMPTY)
				emptyCellList[emptyCellCount++] = i * A_SIZE + j;
		}
	}

	bestPosition = rand() % emptyCellCount;

	return emptyCellList[bestPosition];
}





