#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "connect.h"

/*global variables*/
char* board[6][7];
int turn = 0;

/*initializes a blank board*/ /*Julian Lam*/
void initBoard(void) { /*7x6 array*/
	int i,j;
  /*builds the board array*/
	for(i=0;i<6;i++) {    
		for(j=0;j<7;j++) { 
			board[i][j] = "[ ]";
		}
	}
}

/*prints the board*/ /*Julian Lam*/
void printBoard(void) {
  
  int i,j;
  /*prints board row by row*/
  for(i=0;i<6;i++) {
    for(j=0;j<7;j++) {
      printf("%s",board[i][j]);
    }
    printf("\n");
  }
  
  
  /*add numbers at bottom to indicate column number*/

  for(i=0; i<7; i++) {
      
      printf("[%d]",i+1);
    }
    printf("\n");
}

/*checks for the lowest empty row*/ /*Julian Lam*/
int lowestValid(int column)
{
  int row;

  /*checks for empty rows from the bottom -> up*/
  for(row=6-1;row>=0;row--) {
    if(strcmp(board[row][column-1], "[ ]") == 0) {
      return row;
    }
  }
  return 10;
}

/*prompts player1 and places a chip in that column*/ /*Julian Lam & Justin Tung*/

void player1(void){

  int column, row;

  int i,j;

  /*user inputs column*/


  printf("Player 1, enter a column number: ");
  do {
    scanf("%d",&column);
    if (column < 1 || column > 7) {
      printf("Please enter a valid column number: ");
    }
    /*lowestValid returns 10 if it can't find an empty slot in that column*/
    else if (lowestValid(column) == 10) {
      printf("Please enter a column that isn't full: ");
    }
  } while(column < 1 || column > 7 || lowestValid(column) == 10);
  /*continues to loop until player inputs a valid value*/

  /*finds lowest empty row number*/
  row = lowestValid(column);


  /*fills the slot of lowest empty row*/
  board[row][column-1] = "[O]";
}

/*prompts player 2*/ /*Julian Lam & Justin Tung*/

void player2(void){
  int column, row;
  int i,j;

  /*user inputs column*/
  printf("Player 2, enter a column number: ");
  do {
    scanf("%d",&column);
    if (column < 1 || column > 7) {
      printf("Please enter a valid column number: ");
    }
    /*lowestValid returns 10 if it can't find an empty slot in that column*/
    else if (lowestValid(column) == 10) {
      printf("Please enter a column that isn't full: ");
    }
    
  } while(column < 1 || column > 7 || lowestValid(column) == 10);
  /*continues to loop until player inputs a valid value*/

  /*finds lowest empty row number*/
  row = lowestValid(column);


  /*fills the slot of lowest empty row*/
  board[row][column-1] = "[X]";

}

/** Checking for a horizontal win**/ /**Justin Tung**/
int checkHorizontal(void) {
  int row, column, i, j, k;
   /**checking for 4-in-a-row horizontal wins in each row. The loop runs through the 3 rightmost columns, since that is where the four in a row horizontal wins can start**/
  for(row = 5; row >= 0; row--){
    /** everytime there an o is encountered, the counter for O increments by 1 and the counter for x is set to zero, and vice versa for when an x is encountered  **/
    for(column = 6; column >= 3; column--){
      int countO = 0;
      int countX = 0;
      for(i=0; i<4; i++){
      if (strcmp(board[row][column-i], "[O]") == 0) {
        countO++;
        countX = 0;   
      }
      else if (strcmp(board[row][column-i], "[X]") == 0) {
        countO = 0;
        countX++;   
      }
      /** if there is nothing in the cell of the array, both the counters for x and o are set to zero**/
      else if (strcmp(board[row][column-i], "[ ]") == 0) {
        countO = 0;
        countX = 0;   
      }
      if (countO == 4) {
          return 1;
         printf("Player One wins!");  }  
      if (countX == 4) {
          return 2;
         printf("Player Two wins!");  }
      }
    }
  }
  return 0;
}

/**Checking for a vertical win**/ /**Justin Tung**/
int checkVertical(void) {
  int row, column, i, j, k;
  /**checking for 4-in-a-row vertical wins in each column. The loop runs through the bottom 3 rows, since that is where they start**/
  for(column = 6; column >= 0; column--){
    for(row = 5; row >= 3; row--){
      int countO = 0;
      int countX = 0;
      for(i=0; i<4; i++){
        /** everytime there an o is encountered, the counter for O increments by 1 and the counter for x is set to zero, and vice versa for when an x is encountered  **/
      if (strcmp(board[row-i][column], "[O]") == 0) {
        countO++;
        countX = 0;   
      }
      else if (strcmp(board[row-i][column], "[X]") == 0) {
        countO = 0;
        countX++;   
      }
      /** if there is nothing in the cell of the array, both the counters for x and o are set to zero**/
      else if (strcmp(board[row][column-i], "[ ]") == 0) {
        countO = 0;
        countX = 0;   
      }
      /**if the count for O or the count for X reaches 4, the function returns 1 or 2, respectively**/
      if (countO == 4) {
          return 1;
         printf("Player One wins!");  }  
      if (countX == 4) {
          return 2;
         printf("Player Two wins!");  }
      }
    }
  }
  return 0;
}

/*check // diagonal*/ /*Julian Lam*/

int checkUpDiagonal(void) {
  int i, j, row, column;
  /*starting points lie in bottom-left 4x3 rectangle*/
  for(row=6-1;row>=3;row--) {
    for(column=0;column<=3;column++) {
      /*resets counter to 0*/
      int countO = 0;
      int countX = 0;
      /*checks each slot on the diagonal*/
      for(i=0;i<4;i++) {
        /*resets counter when slot is filled by another type and +1 to that type*/
        if(strcmp(board[row-i][column+i], "[O]") == 0) {
          countX = 0;
          countO++;
        }
        else if(strcmp(board[row-i][column+i], "[X]") == 0) {
          countO = 0;
          countX++;
        }
        else if(strcmp(board[row-i][column+i], "[ ]") == 0) {
          countO = 0;
          countX = 0;
        }
        /**if the count for O or the count for X reaches 4, the function returns 1 or 2, respectively**/
        if(countO == 4) {
          return 1;
        }
         if(countX == 4) {
          return 2;
        }
      }
      /*1 = oWin, 2 = xWin*/
    }
  }
  return 0;
}

/*check \\ diagonal*/ /*Julian Lam*/
int checkDownDiagonal(void) {
    int i, j, row, column;
  /*starting points lie in top-left 4x3 rectangle*/
  for(row=6-4;row>=0;row--) {
    /*printf("%d\n",row);*/
    for(column=0;column<=3;column++) {
      /*printf("%d\n",column);*/
      /*resets counter to 0*/
      int countO = 0;
      int countX = 0;
      /*checks each slot on the diagonal*/
      for(i=0;i<4;i++) {
        /*resets counter when slot is filled by another type*/
        if(strcmp(board[row+i][column+i], "[O]") == 0) {
          countX = 0;
          countO++;
        }
        else if(strcmp(board[row+i][column+i], "[X]") == 0) {
          countO = 0;
          countX++;
        }
        else if(strcmp(board[row+i][column+i], "[ ]") == 0) {
          countO = 0;
          countX = 0;
        }
        if(countO == 4) {
          return 1;
        }
         if(countX == 4) {
          return 2;
        }
      }
      /*1 = oWin, 2 = xWin*/
    }
  }
  return 0;
}

/*check for a win in the board*/ /**Justin Tung**/
int isWin(void) {

/*returns 1 for player 1 win, returns 2 for player 2 win*/
  if (checkVertical() == 1 || checkHorizontal() == 1 || checkUpDiagonal() == 1 || checkDownDiagonal() == 1){
    return 1;
  }
  else if (checkHorizontal() == 2 || checkVertical() == 2 || checkUpDiagonal() == 2 || checkDownDiagonal() == 2){
    return 2;
  }
  return 0;
}

/*plays the game*/ /*Julian Lam & Justin Tung*/

void playGame(void){

  /*initialize board*/
  initBoard();

  printf("Welcome to Justin and Julian's Connect 4 Code!\nPlayer 1 will be 'O' and Player 2 will be 'X'\nLet's begin!\n");

  do {
    if (turn % 2 == 0){
      if (turn != 0){
        printf("Turn: %d\n",turn);
      }
      printBoard();
      player1();
      printf("\n");
      turn++;
    }
    else if (turn % 2 == 1){
      printf("Turn %d\n",turn);
      printBoard();      
      player2();
      printf("\n");
      turn++;
    }
  } while(isWin() == 0 && turn < 42);
  /*loop the game as long as no one has won and the board is not full*/

/*prints the final board*/

  printBoard();

  /*checks who won*/
  if (isWin() == 1) {
    printf("Player 1 wins!\n");
  }

  else if (isWin() == 2) {
    printf("Player 2 wins!\n");
  }

  else {
    printf("It's a tie!\n");
  }
}
 