#include "FuncDeclare.h"
#include <stdlib.h>
#include <time.h>

// 최적의 좌표의 점수 중 가장 큰 값을 반환 == 이길 확률이 높은 좌표
int Max(int scoreList[], int emptyCellCount, int emptyCellList[], int* bestMove)
{
	if (!emptyCellCount)
	{
		return 0;
	}

	int max = -20;

	for (int i = 0;i < emptyCellCount;i++)
	{
		if (scoreList[i] > max)
		{
			max = scoreList[i];
			*bestMove = emptyCellList[i];
		}
	}
	return max;
}

// 최적의 좌표의 점수 중 가장 작은 값을 반환 == 이길 확률이 가장 낮은 좌표
int Min(int scoreList[], int emptyCellCount, int emptyCellList[], int* bestMove)
{
	if (!emptyCellCount)
	{
		return 0;
	}

	int min = +20;

	for (int i = 0;i < emptyCellCount;i++)
	{
		if (scoreList[i] < min)
		{
			min = scoreList[i];
			*bestMove = emptyCellList[i];
		}
	}
	return min;
}

//컴퓨터가 최선의 수를 찾을 수 있도록 함수 상난이도
int minMax_HARD(int Board[][A_SIZE], int Player, int* depth)
{
	int emptyCellList[A_SIZE * A_SIZE];
	int emptyCellCount = 0;
	int bestPosition = 0;
	int scoreList[A_SIZE * A_SIZE];
	int bestScore;

	bestScore = isAWin(Board, COMP);  // 컴퓨터의 승,무,패 확인해서 해당하는 값을 bestScore에 넣음

	if (bestScore) //bestScore가 정수이므로 0이 아니면 true, 컴퓨터가 승리 또는 패배 했을 때만 return
	{
		return bestScore - *depth;
	}

	for (int i = 0;i < A_SIZE;i++)
	{
		for (int j = 0; j < A_SIZE; j++)
		{
			if (Board[i][j] == EMPTY)
				emptyCellList[emptyCellCount++] = i * A_SIZE + j;
		}
	}

	int CurPosition;
	for (int i = 0;i < emptyCellCount;i++)
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
		// 컴퓨터 차례일 때는 컴퓨터의 최선의 수를 찾기 위해 max함수 호출
		bestScore = Max(scoreList, emptyCellCount, emptyCellList, &bestPosition);
	}

	if (Player == HUMAN)
	{
		// 사람(사용자)입장에서는 컴퓨터가 최선의 수를 내면 안되니 min함수 호출
		bestScore = Min(scoreList, emptyCellCount, emptyCellList, &bestPosition);
	}

	if (*depth != 0) // 재귀가 아직 끝나지 않았다면 bestScore 반환
	{
		return bestScore;
	}
	else //재귀가 끝났으면 최선의 위치를 반환 해야되므로 bestMove 반환
	{
		return bestPosition;
	}
}

//컴퓨터가 최선의 수를 찾을 수 있도록 함수 중 난이도
int minMax_NORMAL(int Board[][A_SIZE], int Player, int* depth)
{
	int emptyCellList[A_SIZE * A_SIZE];
	int emptyCellCount = 0;
	int bestPosition = 0;
	int scoreList[A_SIZE * A_SIZE];
	int bestScore;

	bestScore = isAWin(Board, COMP);  // 컴퓨터의 승,무,패 확인해서 해당하는 값을 bestScore에 넣음

	if (bestScore) //bestScore가 정수이므로 0이 아니면 true, 컴퓨터가 승리 또는 패배 했을 때만 return
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
			// 컴퓨터 차례일 때는 컴퓨터의 최선의 수를 찾기 위해 max함수 호출
			bestScore = Max(scoreList, emptyCellCount, emptyCellList, &bestPosition);
		}

		if (Player == HUMAN)
		{
			// 사람(사용자)입장에서는 컴퓨터가 최선의 수를 내면 안되니 min함수 호출
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
			// 컴퓨터가 이상한 값을 내게 함으로써사용자가 승리할 가능성을 올려준다.
			bestScore = Min(scoreList, emptyCellCount, emptyCellList, &bestPosition);

		}

		if (Player == HUMAN)
		{

			bestScore = Max(scoreList, emptyCellCount, emptyCellList, &bestPosition);
		}

	}

	if (*depth != 0) // 재귀가 아직 끝나지 않았다면 bestScore 반환
	{
		return bestScore;
	}
	else //재귀가 끝났으면 최선의 위치를 반환 해야되므로 bestMove 반환
	{
		return bestPosition;
	}
}

//컴퓨터가 최선의 수를 찾을 수 있도록 함수 하난이도
int minMax_EASY(int Board[][A_SIZE], int Player)
{
	int emptyCellList[A_SIZE * A_SIZE];
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





