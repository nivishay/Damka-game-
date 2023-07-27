#include "game.h"
#include "GameLogic.h"

extern bool reachedGameBoundaries;

void isGameBorderReached(Player player, checkersPos* pos)
{
	if ((player == PLAYER_T && pos->row == 'H') || (player == PLAYER_B && pos->row == 'A'))
		reachedGameBoundaries = true;
}

bool isEndOfDamaka(Board board, int Tcaptures, int Bcaptures)
{
	bool endGame = false;
	if (Tcaptures == MAX_CAPTURES || Bcaptures == MAX_CAPTURES || reachedGameBoundaries)
		endGame = true;

	return endGame;
}

bool BestOfTwoRoutes(checkersPos* check, checkersPos* max, Player player)
{
	bool replace = false;
	if (player == PLAYER_T)
	{
		if ((check->row > max->row) || (check->row == max->row && check->col > max->col))
			replace = true;
	}
	else
	{
		if ((check->row < max->row) || (check->row == max->row && check->col < max->col))
			replace = true;
	}
	return replace;
}
bool inCaptureMode(SingleSourceMovesTreeNode* root, char moveType, int dir)
{
	bool res = false;
	if (root->next_move[dir] != NULL && moveType != ONE_STEP_MOVE)
		res = true;
	return res;
}

bool outOfBoardBounds(checkersPos pos)
{
	bool out_of_bounds = false;
	if (pos.row < 'A' || pos.col < '0' || pos.row>'H' || pos.col>'8')
		out_of_bounds = true;
	return out_of_bounds;
}
bool LegalMove(SingleSourceMovesTree* tree)
{
	bool res = true;
	if (tree->source->next_move[0] == NULL && tree->source->next_move[1] == NULL)
		res = false;
	return res;
}
