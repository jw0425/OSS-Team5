#ifndef FuncDeclare
#define FuncDeclare

#include "basedef.h"
/*Declare of function template*/

void initBoard(int[][A_SIZE]);
void printBoard(const int[][A_SIZE]);
int isBoardFull(const int[][A_SIZE]);
void makeMove(int[][A_SIZE], int, int, const int);
int is3inARow(const int[][A_SIZE], const int);
int isAWin(const int[][A_SIZE], const int);

void HumanTurn(int[][A_SIZE]);
void runGame(void);

int minMax_EASY(int[][A_SIZE], int  );
int minMax_NORMAL(int[][A_SIZE], int , int* );
int minMax_HARD(int[][A_SIZE], int, int*);
void ComputerTurn(int[][A_SIZE], int , int );
int Max(int[], int, int[], int*);
int Min(int[], int, int[], int*);


#endif