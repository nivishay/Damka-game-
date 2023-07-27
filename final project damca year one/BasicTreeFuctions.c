#include "game.h"
#include"BasicTreeFunctions.h"


void CopyBoard(SingleSourceMovesTreeNode* node, Board board)
{
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			node->board[i][j] = board[i][j];
		}
}
SingleSourceMovesTreeNode* createSingleMoveTNode(unsigned short total_captures_so_far, Board board, SingleSourceMovesTreeNode* left, SingleSourceMovesTreeNode* right,checkersPos* pos)
{
	SingleSourceMovesTreeNode* res;
	res = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	CHECK_ALLOCATION(res, "singleSourceMovesTreeNode");
	CopyBoard(res, board);
	res->next_move[0] = left;
	res->next_move[1] = right;
	res->total_captures_so_far = total_captures_so_far;
	res->pos = (checkersPos*)malloc(sizeof(checkersPos));
	CHECK_ALLOCATION(res, "checkersPos");
	*(res->pos) = *pos;
	return res;
}

void freeTree(SingleSourceMovesTree* tr)
{
	freeTreeHelper(tr->source);
	free(tr);
}
void freeTreeHelper(SingleSourceMovesTreeNode* root)
{
	if (root == NULL)
		return;
	else
	{
		freeTreeHelper(root->next_move[0]);
		freeTreeHelper(root->next_move[1]);
		free(root);
	}
}

int height(SingleSourceMovesTree* tr)
{
	return heightHelper(tr->source);
}
int heightHelper(SingleSourceMovesTreeNode* root)
{
	int heightLeft, heightRight;
	if (root == NULL)
		return -1;
	else
	{
		heightLeft = heightHelper(root->next_move[0]);
		heightRight = heightHelper(root->next_move[1]);
		return 1 + max(heightLeft, heightRight); // check sub right and sub left and add the max
	}
}