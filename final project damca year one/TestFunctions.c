#include "game.h"
SingleSourceMovesTree* buildTree()
{
        Board board;
        checkersPos src = { 'C', '4' };

        SingleSourceMovesTreeNode* rootNode = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
        rootNode->pos = (checkersPos*)malloc(sizeof(checkersPos));
        rootNode->pos->row = src.row;
        rootNode->pos->col = src.col;
        rootNode->total_captures_so_far = 0;
        rootNode->next_move[0] = NULL;
        rootNode->next_move[1] = NULL;

        // Create child nodes
        SingleSourceMovesTreeNode* childNode1 = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
        childNode1->pos = (checkersPos*)malloc(sizeof(checkersPos));
        childNode1->pos->row = 'D';
        childNode1->pos->col = '3';
        childNode1->total_captures_so_far = 2;
        childNode1->next_move[0] = NULL;
        childNode1->next_move[1] = NULL;

        SingleSourceMovesTreeNode* childNode2 = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
        childNode2->pos = (checkersPos*)malloc(sizeof(checkersPos));
        childNode2->pos->row = 'D';
        childNode2->pos->col = '5';
        childNode2->total_captures_so_far = 1;
        childNode2->next_move[0] = NULL;
        childNode2->next_move[1] = NULL;

        SingleSourceMovesTreeNode* childNode3 = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
        childNode3->pos = (checkersPos*)malloc(sizeof(checkersPos));
        childNode3->pos->row = 'B';
        childNode3->pos->col = '3';
        childNode3->total_captures_so_far = 3;
        childNode3->next_move[0] = NULL;
        childNode3->next_move[1] = NULL;

        SingleSourceMovesTreeNode* childNode4 = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
        childNode4->pos = (checkersPos*)malloc(sizeof(checkersPos));
        childNode4->pos->row = 'B';
        childNode4->pos->col = '5';
        childNode4->total_captures_so_far = 0;
        childNode4->next_move[0] = NULL;
        childNode4->next_move[1] = NULL;

        SingleSourceMovesTreeNode* childNode5 = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
        childNode5->pos = (checkersPos*)malloc(sizeof(checkersPos));
        childNode5->pos->row = 'E';
        childNode5->pos->col = '2';
        childNode5->total_captures_so_far = 2;
        childNode5->next_move[0] = NULL;
        childNode5->next_move[1] = NULL;

   // Connect child nodes to the root node
        rootNode->next_move[0] = childNode1;
        rootNode->next_move[1] = childNode2;
        childNode1->next_move[0] = childNode3;
        childNode1->next_move[1] = childNode4;
        childNode2->next_move[0] = childNode5;

        // Create the single source moves tree
        SingleSourceMovesTree* movesTree = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
        movesTree->source = rootNode;
}