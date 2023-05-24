#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//structure for MineSweeper block
typedef struct{
    int isMine;
    int isFlagged;
    int isRevealed;
    int numMines;
}Block;


typedef struct{
    int x, y;
    int IsFlagged;
} TMove;


Block** createTable(int rows, int cols);
void freeTable(Block** table, int rows);
void printTable(Block** table, int rows, int cols);
void printMinesRevealed(Block** table, int rows, int cols);
void GenMines(Block** table, int rows, int cols, int mines);
void countMines(Block** table, int rows, int cols);
int CheckWin(Block** table, int rows, int cols, int mines);
void Reveal(Block** table, int rows, int cols, int i, int j);
void revealAll(Block** table, int rows, int cols, int i, int j);
void StartJoc(Block** table, double* HighScore, double* HighScore2, double* HighScore3);

