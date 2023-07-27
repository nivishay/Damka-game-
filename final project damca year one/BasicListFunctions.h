#ifndef BASIC_LIST_FUNCTIONS
#define BASIC_LIST_FUNCTIONS

/////////////////////////////
//SingleMovesList Functions//
/////////////////////////////

SingleSourceMovesListCell* CreateNewSingleSourceMoveCell(checkersPos* position, unsigned short captures, SingleSourceMovesListCell* next);

void insertDataTostartSingleMoveList(SingleSourceMovesList* lst, checkersPos* position, unsigned short captures);

void insertNodeToStartSingleMoveList(SingleSourceMovesListCell* newCell, SingleSourceMovesList* lst);  

void MakeEmptySingleMoveList(SingleSourceMovesList* lst);

MultipleSourceMovesListCell* createNewMultipleMovesListCell(SingleSourceMovesList* data, SingleSourceMovesListCell* next);

void MakeEmptySingleMoveList(SingleSourceMovesList* lst);

void insertDataToEndMultipleList(MultipleSourceMovesList* lst, SingleSourceMovesList* data);

void insertNodeToEndMultipleList(MultipleSourceMovesList* lst, MultipleSourceMovesListCell* tail);

void freeMultipleSourceMovesList(MultipleSourceMovesList* list);

void freeSingleSourceMovesList(SingleSourceMovesList* list);
#endif
