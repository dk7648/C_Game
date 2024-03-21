#ifndef __LIST_H__
#define __LIST_H__

#define TRUE	1
#define FALSE	0


typedef struct _node
{
	struct _node * next;
	int x;
	int y;
}Node;

typedef struct _direction
{
	int vertical;
	int horizontal;
}Direction;

typedef struct _block
{
	int x;
	int y;
	int type;
	int IsBlock;
}Block;

typedef struct _list
{
	struct _node * tail;
	struct _node * head;
	struct _node * current;
	struct _direction * dir;
	struct _block * block;
}List;

void ListInit(List * list);
void LInsert(List * list);
void LMove(List * list);
void LRemove(List * list);
#endif