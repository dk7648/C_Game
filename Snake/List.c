#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "Turboc.h"
void ListInit(List * list)
{
	setcursortype(NOCURSOR);
	srand((unsigned)time(NULL));

	list->head = (Node*)malloc(sizeof(Node));	//뱀의 머리 부분
	list->head->next = NULL;

	list->dir = (Direction*)malloc(sizeof(Direction));
	list->head->x = 5; list->head->y = 5;
	list->dir->horizontal = 0; list->dir->vertical = 0;

	list->block = (Block*)malloc(sizeof(Block));
	list->block->IsBlock = FALSE;

	list->tail = list->head;
}
void LInsert(List * list)
{
	Node * newNode = (Node*)malloc(sizeof(Node));
	newNode->x = list->tail->x;
	newNode->y = list->tail->y;	//위치 정보

	newNode->next = list->tail;
	list->tail = newNode;
}
void LMove(List * list)
{
	list->current = list->tail;
	while (list->current->next != NULL)		//뱀 머리 빼고 나머지의 위치값 이동
	{
		list->current->x = list->current->next->x;
		list->current->y = list->current->next->y;

		list->current = list->current->next;
	}

	//뱀 머리 한 칸 움직이기
}
void LRemove(List * list)
{
	
	while (list->tail->next != NULL)		//몸통 삭제
	{
		Node * rnode = list->tail;
		list->tail = list->tail->next;
		free(rnode);
	}

	free(list->head);
	free(list->dir);
}
