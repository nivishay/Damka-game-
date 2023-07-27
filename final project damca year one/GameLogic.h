#pragma once
#include "game.h"

void isGameBorderReached(Player player, checkersPos* pos);

bool isEndOfDamaka(Board board, int Tcaptures, int Bcaptures);

bool BestOfTwoRoutes(checkersPos* check, checkersPos* max, Player player);

bool inCaptureMode(SingleSourceMovesTreeNode* root, char moveType, int dir);

bool outOfBoardBounds(checkersPos pos);

bool LegalMove(SingleSourceMovesTree* tree);


