#ifndef __SNAKE_H__
#define __SNAKE_H__
#include "List.h"

#define COIN	1
#define WALL	0

void draw_map();
void checkDirection(List * list);
void moveHead(List * list);
int IsDeath(List * list);
void checkItem(List * list);
void setItem(List * list);
void showSnake(List * list);
void showItem(List * list);

#endif