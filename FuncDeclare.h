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
int max(int[], int, int[], int*);
int min(int[], int, int[], int*);
int minMax(int[][A_SIZE], int, int*);
void ComputerTurn(int[][A_SIZE], int);
void HumanTurn(int[][A_SIZE], const int);
void runGameVSCom(void);
void runGameVSHuman(void);
void showMenu(void);
#endif