#include <stdio.h>

#include "List.h"
#include "snake.h"

#define INIT	0
#define UPDATE	1
#define	PRESENT	2
#define RELEASE	3

void Init(List * list);
void Update(List * list);;
void Present(List * list);
void Release(List * list);
int main(void)
{
	List list;
	int STATE = INIT;

	while (1)
	{
		switch (STATE)
		{
		case INIT:
			Init(&list);
			STATE = UPDATE;
			break;
		case UPDATE:
			Update(&list);
			STATE = PRESENT;
			if (IsDeath(&list) == 1)
				STATE = RELEASE;
			break;
		case PRESENT:
			Present(&list);
			STATE = UPDATE;
			break;
		case RELEASE:
			Release(&list);
			return 0;
		}
	}
}

void Init(List * list)
{
	ListInit(list);
}

void Update(List * list)
{
	static int delay = 0;
	delay++;
	if (_kbhit())
	{
		checkDirection(list);
	}
	if (delay > 1)
	{
		LMove(list);
		moveHead(list);
		delay = 0;
	}
	checkItem(list);
	setItem(list);
}

void Present(List * list)
{
	system("cls");
	showSnake(list);
	showItem(list);
	draw_map();
}

void Release(List * list)
{
	LRemove(list);
}