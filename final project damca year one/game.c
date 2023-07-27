
#include "game.h"
#include"BasicListFunctions.h"
#include "BasicTreeFunctions.h"
#include "GameLogic.h"

bool reachedGameBoundaries = false;
int T_Total_Moves = 0, B_Total_Moves = 0, T_Captures = 0, B_Captures = 0;
MaxCapturesInTurn maxCapturesGlobal = { 0,0 };

char checkMoveTypeOfSingleNode(Board board, char player, checkersPos location, int index, checkersPos nextLocation)
{
	char moveType, board_pos = board_position(location.row, location.col), board_N_pos = board_position(nextLocation.row, nextLocation.col);// saves the curr postion and next posion

	if (outOfBoardBounds(location) || board_pos == player)
		moveType = CANT_MOVE;
	else if (board_pos == EMPTY_BOARD_SQUARE)
		moveType = ONE_STEP_MOVE;
	else
	{
		if (outOfBoardBounds(nextLocation) || board_N_pos != EMPTY_BOARD_SQUARE)
			moveType = CANT_MOVE;
		else
			moveType = CAPTURE_MOVE;
	}
	return moveType;
}
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src)
{
	SingleSourceMovesTree* res;
	res = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
	CHECK_ALLOCATION(res, "SingleSourceMovesTree");
	res->source = createSingleMoveTNode(0, board, NULL, NULL, src);

	Player player = board_position(src->row, src->col);
	if (player == EMPTY_BOARD_SQUARE)// if there is no game piece in that location 
		return res;
		FindSingleSourceMovesHelper(res->source,player);
		return res;
}
checkersPos findPos(checkersPos curr, int index,char c)
{
	checkersPos res;
	res.row = curr.row - index;
	if (c == LEFT)
		res.col = curr.col + index;
	else
		res.col = curr.col - index;
	return res;
}
SingleSourceMovesTreeNode* casesOfMoveCreateNode(char move_type, SingleSourceMovesTreeNode* root, checkersPos pos, checkersPos nextPos, Board board)
{
	SingleSourceMovesTreeNode* Child = NULL;
	Player player = board_position(root->pos->row, root->pos->col);
	switch (move_type)
	{

	case CANT_MOVE:
		Child = NULL;
		break;

	case ONE_STEP_MOVE:
	{
		if (root->total_captures_so_far == 0)
		{
			// Update the board positions to reflect the move
			board_position(pos.row, pos.col) = player;
			board_position(root->pos->row, root->pos->col) = EMPTY_BOARD_SQUARE;
			Child = createSingleMoveTNode(root->total_captures_so_far, board, NULL, NULL, &pos);
		}
		else 
			Child = NULL;
		break;
	}
	case CAPTURE_MOVE:
	{
		// Update the board positions to reflect the move
		board_position(pos.row, pos.col) = EMPTY_BOARD_SQUARE;
		board_position(nextPos.row, nextPos.col) = player;
		board_position(root->pos->row, root->pos->col) = EMPTY_BOARD_SQUARE;
		Child = createSingleMoveTNode(root->total_captures_so_far + 1, board, NULL, NULL, &nextPos);
		break;
	}
	}
	return Child;
}

void FindSingleSourceMovesHelper(SingleSourceMovesTreeNode* root, Player player)
{
	int index = (player == PLAYER_B) ? UP : DOWN;
	char LeftMoveType, RightMoveType;
	checkersPos LeftPos, RightPos, LnextPos, RnextPos;

	// Find the positions for left and right moves
	LeftPos = findPos(*(root->pos), index, LEFT);
	LnextPos = findPos(LeftPos, index, LEFT);
	RightPos = findPos(*(root->pos), index, RIGHT);
	RnextPos = findPos(RightPos, index, RIGHT);

	// Determine the move types for left and right moves
	LeftMoveType = checkMoveTypeOfSingleNode(root->board, player, LeftPos, index, LnextPos);
	RightMoveType = checkMoveTypeOfSingleNode(root->board, player, RightPos, index, RnextPos);

	// Create nodes for left and right moves based on their move types
	root->next_move[0] = casesOfMoveCreateNode(LeftMoveType, root, LeftPos, LnextPos, root->board);
	root->next_move[1] = casesOfMoveCreateNode(RightMoveType, root, RightPos, RnextPos, root->board);

	// Recursively moves if capture mode is active for left move
	if (inCaptureMode(root, LeftMoveType, L_CHILD))
		FindSingleSourceMovesHelper(root->next_move[0], player);

	// Recursively moves if capture mode is active for right move
	if (inCaptureMode(root, RightMoveType, R_CHILD))
		FindSingleSourceMovesHelper(root->next_move[1], player);
}


void PrintBoard(Board board)
{
	checkersPos pos;
	char c = 'A';
	char player;
	for (size_t i = 0; i <= BOARD_SIZE * 2; i++)
	{
		if (i % 2 == 0 | i == 1)
			printLine(i);

		else {
			for (int j = 0; j <= BOARD_SIZE * 2; j++)
			{
				pos.col = ((j - 1) / 2) + FIRST_COL;
				pos.row = ((i - 1) / 2) + FIRST_ROW;
				player = board_position(pos.row, pos.col);
				if (j == 1)
				{
					printf("%c", c);
					c++;
				}
				else if (j % 2 == 0)
					printf("|");
				else if (player == 'T' || player == 'B')
					printf("%c", player);
				else
					printf(" ");
			}
		}
		printf("\n");
	}
}
void printLine(int i)
{
	int j = 0;
	if (i % 2 == 0)
	{
		while (j <= 18)
		{
			if (j % 2 == 0)
				printf("+");
			else
				printf("-");
				j++;
		}	
	}
	else
	{
		if (i == 1)
			printf("+ |1|2|3|4|5|6|7|8|");
	}
}


//Q3
MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player) 
{
	MultipleSourceMovesList* res;
	res = (MultipleSourceMovesList*)calloc(1,sizeof(MultipleSourceMovesList));

	CHECK_ALLOCATION(res, "MultipleSourceMovesList");
	for (int i = 1; i < BOARD_SIZE; i++)
		for (int j = 1; j < BOARD_SIZE; j++)
			if (board[i][j] == player)
				findAndAddBestPlayerMove(board, player, i, j, res);
	return res;
}

void findAndAddBestPlayerMove(Board board, Player player, int row, int col, MultipleSourceMovesList* res)
{
	checkersPos gamePiece;
	SingleSourceMovesList* bestMove;
	gamePiece.row = row + FIRST_ROW;
	gamePiece.col = col + FIRST_COL;

	SingleSourceMovesTree* movesTree = FindSingleSourceMoves(board, &gamePiece);

	if (LegalMove(movesTree))//(at least one step option)
	{
		bestMove = FindSingleSourceOptimalMove(movesTree);
		insertDataToEndMultipleList(res, bestMove);
		freeTree(movesTree);
	}
}

SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree)
{
	int max = height(moves_tree);
	if (max == 0)
		return NULL;
	bool found = false;
	SingleSourceMovesList* res;
	res = (SingleSourceMovesList*)calloc(SINGLE_ELEMENT,sizeof(SingleSourceMovesList));
	CHECK_ALLOCATION(res, "SingleSourceMovesList");
	if (max == 1 && moves_tree->source->next_move[1] != NULL&&moves_tree->source->next_move[0]!=NULL)
	{
		bool OneStepOrGo = (moves_tree->source->next_move[0]->total_captures_so_far == 1 && moves_tree->source->next_move[1]->total_captures_so_far == 0);
		if (OneStepOrGo)
		{
			insertDataTostartSingleMoveList(res, moves_tree->source->next_move[0]->pos, 1);
			insertDataTostartSingleMoveList(res, moves_tree->source->pos, 0);
			return res;
		}
	}

	FindSingleSourceOptimalMoveHelper(moves_tree->source, &max, 0, res, &found);// 0 is level

	return res;
}
void FindSingleSourceOptimalMoveHelper(SingleSourceMovesTreeNode* source, int* max, int level, SingleSourceMovesList* res, bool* found)
{
	if (!found || source == NULL) //if the recurssion got to the end of the tree or the most otimal route was found 
		return;
	else
	{
		FindSingleSourceOptimalMoveHelper(source->next_move[1],max, level + 1, res, found);
		FindSingleSourceOptimalMoveHelper(source->next_move[0],max, level + 1, res, found);
		if (level == *max) 
		{
			insertDataTostartSingleMoveList(res, source->pos, source->total_captures_so_far);
			(*max)--;
		}
	}
}
void Turn(Board board, Player player)
{

	MultipleSourceMovesList* moveOptions;
	SingleSourceMovesList* BestRoute;
	SingleSourceMovesListCell* curr;

	moveOptions = FindAllPossiblePlayerMoves(board, player);
	BestRoute = FindBestMoveFromMultipleList(moveOptions, player);
	curr = BestRoute->head;
		printPlayerTurn(curr, board, player);
		CaptureStatistic(player, BestRoute);
		freeMultipleSourceMovesList(moveOptions);
} 
void CaptureStatistic(Player player, SingleSourceMovesList* bestRoute)
{
	if (bestRoute->head == NULL)
		return;

		// Update captures and total moves for the respective player
		if (PLAYER_B == player)
		{
			B_Captures += bestRoute->tail->captures;
			B_Total_Moves++;
		}
		else
		{
			T_Captures += bestRoute->tail->captures;
			T_Total_Moves++;
		}

	// Update global maximum captures if applicable
	if (bestRoute->tail->captures > maxCapturesGlobal.max)
	{
		maxCapturesGlobal.player = player;
		maxCapturesGlobal.max = bestRoute->tail->captures;
	}
}
SingleSourceMovesList* FindBestMoveFromMultipleList(MultipleSourceMovesList* lst, Player player)
{
	if (lst->head == NULL)
		return NULL;

	SingleSourceMovesList* res = lst->head->single_source_moves_list;
	int maxCaptures = res->tail->captures;
	bool isBestOfTwoRoutes;

	if (lst->head == lst->tail)
		return res;

	MultipleSourceMovesListCell* curr = lst->head->next;

	while (curr != NULL)
	{
		SingleSourceMovesList* currMovesList = curr->single_source_moves_list;
		int currCaptures = currMovesList->tail->captures;
		maxCaptures = res->tail->captures;
		isBestOfTwoRoutes = BestOfTwoRoutes(currMovesList->head->position, res->head->position, player);
		if (currCaptures > maxCaptures || (currCaptures == maxCaptures && isBestOfTwoRoutes))
			res = currMovesList;

		curr = curr->next;
	}

	return res;
}

void NewBoard(SingleSourceMovesListCell* curr, Board board, Player player)
{
	int value = player == PLAYER_T ? -2 : 2;
	checkersPos Delete;
	board_position(curr->position->row, curr->position->col) = ' ';

	// Update the board with the new positions and actions

	// If the difference is 2 rows, meaning the piece is in Skip mode
	if (curr->position->row - curr->next->position->row == value)
	{
		Delete.row = (curr->position->row + curr->next->position->row) / 2;
		Delete.col = (curr->position->col + curr->next->position->col) / 2;
		board_position(Delete.row, Delete.col) = ' ';
	}

	board_position(curr->next->position->row, curr->next->position->col) = player;

	// Update the board by removing the captured piece if Skip mode
}

void printPlayerTurn(SingleSourceMovesListCell* curr, Board board, Player player)
{
	printf("%c's turn: ", player);
	while (curr->next != NULL)
	{
		printf("%c%c->%c%c\n", curr->position->row, curr->position->col, curr->next->position->row, curr->next->position->col);
		NewBoard(curr, board, player);
		PrintBoard(board);
		printf("\n");	
		curr = curr->next;
	}
	isGameBorderReached(player, curr->position); // flicker the gloabl varible reachedGameBoundaries
}
//Q5
void PlayGame(Board board, Player Starting_player)
{
	int counter = 0;
	Player nextPlayer = Starting_player;
	bool gameOver = false;
	PrintBoard(board);
	printf("\n");
	while (!gameOver)
	{
		Turn(board, nextPlayer);
		if (isEndOfDamaka(board, T_Captures, B_Captures))
		{
			printGameStatistic(nextPlayer);
			gameOver = true;
		}
		else
		{
			nextPlayer = (nextPlayer == PLAYER_B ? PLAYER_T : PLAYER_B);
		}
	}
}
void printGameStatistic(Player player)
{
	int counter = player == PLAYER_T ? T_Total_Moves : B_Total_Moves;
	printf("%c wins!\n", player);
	printf("%c performed %d moves.\n", player, counter);
	printf("%c performed the highest number of captures in a single move - %d", maxCapturesGlobal.player, maxCapturesGlobal.max);
}

