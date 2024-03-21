#include <stdio.h>
#include "snake.h"

void draw_map()
{
	int i;
	gotoxy(0, 0);
	printf("####################");
	for (i = 0; i < 20; i++)
	{
		gotoxy(0, i);
		printf("#");
		gotoxy(20, i);
		printf("#");

	}
	gotoxy(0, 20);
	printf("####################");
}

void checkDirection(List * list)
{
	char ch = _getch();
	switch (ch)
	{
	case 'a':
		list->dir->horizontal = -1;
		list->dir->vertical = 0;
		break;
	case 's':
		list->dir->horizontal = 0;
		list->dir->vertical = 1;
		break;
	case 'd':
		list->dir->horizontal = 1;
		list->dir->vertical = 0;
		break;
	case 'w':
		list->dir->horizontal = 0;
		list->dir->vertical = -1;
		break;
	default:
		break;
	}
}

void moveHead(List * list)
{
	if (list->dir->horizontal)
	{
		list->head->x += list->dir->horizontal;
	}
	if (list->dir->vertical)
		list->head->y += list->dir->vertical;
}

int IsDeath(List * list)
{
	if (list->head->x < 1 || list->head->y < 1)
		return 1;
	if (list->head->x > 19 || list->head->y > 19)
		return 1;
	return 0;
}
void checkItem(List * list)
{
	if (list->block->IsBlock)
		if (list->head->x == list->block->x && list->head->y == list->block->y && list->block->type)
				if (list->block->type == COIN)
				{
					LInsert(list);
					list->block->IsBlock = FALSE;
				}
}
void setItem(List * list)
{
	if (list->block->IsBlock == FALSE)
	{
		list->block->x = (rand() % (19)) + 1; //1~19
		list->block->y = (rand() % (19)) + 1;
		list->block->type = COIN;
		list->block->IsBlock = TRUE;
	}
}
void showSnake(List * list)
{
	list->current = list->tail;
	while (list->current != NULL)
	{
		gotoxy(list->current->x, list->current->y);
		printf("o");
		list->current = list->current->next;
	}
}
void showItem(List * list)
{
	gotoxy(0, 0);
	printf("item pos : %d %d", list->block->x, list->block->y);
	if (list->block->IsBlock)
	{
		gotoxy(list->block->x, list->block->y);
		switch (list->block->type)
		{
		case COIN:
			printf("c");
			break;
		case WALL:
			printf("H");
			break;
		}
	}
}