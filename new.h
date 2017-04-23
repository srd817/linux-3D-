#ifndef _NEW_H
#define _NEW_H

struct chessboard {	
	int size;
	int haut;
	char ***chess;
};
typedef struct chessboard chessboard;

chessboard creat(int n,int h);
void print_init(chessboard *board);
int board_void(chessboard *board,int stu[]);
int retirer(chessboard *board,int stu[]);
int place(chessboard *board,int stu[],int turn);
void print_board(chessboard *chess,int stu[]);
int *chess_keys(chessboard *board,int direction,int stu[]);
void print_turn(int turn);

#endif
