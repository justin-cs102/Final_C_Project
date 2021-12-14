#ifndef CONNECT_H
#define CONNECT_H

void initBoard(void);
void printBoard(void);
void player1(void);
void player2(void);
void playGame(void);
int lowestValid(int column);
int checkHorizontal(void);
int checkVertical(void);
int checkUpDiagonal(void);
int checkDownDiagonal(void);
int isWin(void);


#endif