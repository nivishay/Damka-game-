#include "game.h"
#include "BasicListFunctions.h"

SingleSourceMovesListCell* CreateNewSingleSourceMoveCell(checkersPos* position, unsigned short captures, SingleSourceMovesListCell* next)
{
	SingleSourceMovesListCell* res;
	res = (SingleSourceMovesListCell*)malloc(sizeof(SingleSourceMovesListCell));
	CHECK_ALLOCATION(res, SingleSourceMovesListCell);
	res->captures = captures;
	res->next = NULL;
	res->position = position;
	return res;
}

void insertNodeToStartSingleMoveList(SingleSourceMovesListCell* newCell, SingleSourceMovesList* lst)
{
	if (lst->head == NULL)
	{
		newCell->next = NULL;
		lst->head = lst->tail = newCell;
	}
	else
	{
		newCell->next = lst->head;
		lst->head = newCell;
	}
}
void insertDataTostartSingleMoveList(SingleSourceMovesList* lst, checkersPos* position, unsigned short captures)
{
	SingleSourceMovesListCell* res;
	res = CreateNewSingleSourceMoveCell(position, captures, NULL);
	insertNodeToStartSingleMoveList(res, lst);
}

MultipleSourceMovesListCell* createNewMultipleMovesListCell(SingleSourceMovesList* data, SingleSourceMovesListCell* next)
{
	MultipleSourceMovesListCell* res;
	res = (MultipleSourceMovesListCell*)malloc(sizeof(MultipleSourceMovesListCell));
	CHECK_ALLOCATION(res, "MultipleSourceMovesListCell");
	res->single_source_moves_list = data;
	res->next = next;
	return res;
}


void MakeEmptySingleMoveList(SingleSourceMovesList* lst)
{
	lst->head = lst->tail = NULL;
}

void insertNodeToEndMultipleList(MultipleSourceMovesList* lst, MultipleSourceMovesListCell* tail)
{
	if (lst->head == NULL)
		lst->head = lst->tail = tail;
	else
	{
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;
}
void insertDataToEndMultipleList(MultipleSourceMovesList* lst, SingleSourceMovesList* data)
{
	MultipleSourceMovesListCell* newTail;
	newTail = createNewMultipleMovesListCell(data, NULL);
	insertNodeToEndMultipleList(lst, newTail);
}


void freeSingleSourceMovesList(SingleSourceMovesList* list)
{
	SingleSourceMovesListCell* current = list->head;
	while (current != NULL)
	{
		SingleSourceMovesListCell* next = current->next;
		free(current->position);
		free(current);
		current = next;
	}
}

void freeMultipleSourceMovesList(MultipleSourceMovesList* list)
{
	MultipleSourceMovesListCell* current = list->head;
	while (current != NULL)
	{
		MultipleSourceMovesListCell* next = current->next;
		freeSingleSourceMovesList(current->single_source_moves_list);
		free(current);
		current = next;
	}
}

