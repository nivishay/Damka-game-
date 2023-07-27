#ifndef GAME_H_
#define GAME_H_
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define PLAYER_B 'B'
#define PLAYER_T 'T'
#define LEFT 'L'
#define RIGHT 'R'
#define ONE_STEP_MOVE 'G'
#define CAPTURE_MOVE 'S'
#define CANT_MOVE 'X'
#define UP 1
#define DOWN -1
#define SINGLE_ELEMENT 1
#define BOARD_SIZE 9
#define EMPTY_BOARD_SQUARE ' '
#define FIRST_COL '0'
#define FIRST_ROW '@'
#define L_CHILD 0
#define R_CHILD 1
#define MAX_CAPTURES 12

// Represents the location on the board
#define board_position(row,col) board[(row) - (FIRST_ROW)][(col) - (FIRST_COL)] 

#define fillBoardCondition(i,j)(i % 2 == 0 && j % 2 != 0 || j % 2 == 0 && i % 2 != 0)

#define CHECK_ALLOCATION(ptr,type)\
    if (ptr == NULL) {\
        printf("Error: Allocation failed for type '%s'\n",#type);\
        exit(1);\
    }
\
typedef struct _checkersPos
{
	char row;
	char col;
} checkersPos;
typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];

typedef unsigned char Player;

typedef struct max_captures
{
	Player player;
	int max;
} MaxCapturesInTurn;


typedef struct _SingleSourceMovesTreeNode //Tree node
{
	Board board;
	checkersPos* pos;
	unsigned short total_captures_so_far;
	struct _SingleSourceMovesTreeNode* next_move[2];
} SingleSourceMovesTreeNode;


typedef struct _SingleSourceMovesTree //Tree
{
	SingleSourceMovesTreeNode* source;
} SingleSourceMovesTree;

typedef struct _SingleSourceMovesListCell //List node
{
	checkersPos* position;
	unsigned short captures;
	struct _SingleSourceMovesListCell* next;
} SingleSourceMovesListCell;

typedef struct _SingleSourceMovesList //List
{
	SingleSourceMovesListCell* head;
	SingleSourceMovesListCell* tail;
} SingleSourceMovesList;

typedef struct _multipleSourceMovesListCell //Linked list node
{
	SingleSourceMovesList* single_source_moves_list;
	struct _multipleSourceMovesListCell* next;
} MultipleSourceMovesListCell;

typedef struct _multipleSourceMovesList //Linked list
{
	MultipleSourceMovesListCell* head;
	MultipleSourceMovesListCell* tail;
} MultipleSourceMovesList;

//extra
void PrintBoard(Board board);


//Q1
char checkMoveTypeOfSingleNode(Board board, char player, checkersPos location, int inedx, checkersPos nextLocation);
checkersPos findPos(checkersPos curr, int index, char c);
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src);
void FindSingleSourceMovesHelper(SingleSourceMovesTreeNode* root, Player player);
SingleSourceMovesTreeNode* casesOfMoveCreateNode(char move_type, SingleSourceMovesTreeNode* root, checkersPos pos, checkersPos nextPos, Board board);


//Q2

// builds a tree for one checker on the board of all of the possible moves he can do in the current turn

int heightHelper(SingleSourceMovesTreeNode* root);
int height(SingleSourceMovesTree* tr);


//Q3
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree);
void FindSingleSourceOptimalMoveHelper(SingleSourceMovesTreeNode* source, int* max, int level, SingleSourceMovesList* res, bool* found);
MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player);
void findAndAddBestPlayerMove(Board board, Player player, int row, int col, MultipleSourceMovesList* res);


//Q4
void Turn(Board board, Player player);
SingleSourceMovesList* FindBestMoveFromMultipleList(MultipleSourceMovesList* lst, Player player);
void printPlayerTurn(SingleSourceMovesListCell* curr, Board board, Player player);
void NewBoard(SingleSourceMovesListCell* curr, Board board, Player player);


//Q5
void CaptureStatistic(Player player, SingleSourceMovesList* bestRoute);
void PlayGame(Board board, Player Starting_player);
void printGameStatistic(Player player);
void printLine(int i);

#endif
