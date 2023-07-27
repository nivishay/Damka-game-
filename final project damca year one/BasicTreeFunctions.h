#ifndef BASIC_TREE_FUNCTIONS
#define BASIC_TREE_FUNCTIONS
#include"game.h"

void freeTreeHelper(SingleSourceMovesTreeNode* root);
void freeTree(SingleSourceMovesTree* tr);
bool LegalMove(SingleSourceMovesTree* tree);
int height(SingleSourceMovesTree* tr);
int heightHelper(SingleSourceMovesTreeNode* root);
void CopyBoard(SingleSourceMovesTreeNode* node, Board board);
SingleSourceMovesTreeNode* createSingleMoveTNode(unsigned short total_captures_so_far, Board board, SingleSourceMovesTreeNode* left, SingleSourceMovesTreeNode* right, checkersPos* pos);
#endif // !BASIC_TREE_FUNCTIONS
