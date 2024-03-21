#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "Turboc.h"
BOOL IsKeyDown(int Key)
{
	return ((GetAsyncKeyState(Key) & 0x8000) != 0);
}
typedef struct _PLAYAER_ {
	float posX;
	float posY;
}Player;
int main(void)
{
	// init
	int i;
	float gravity = 0.25;
	float accel = 0;
	int limit = 20;
	Player player;
	player.posX = 0;
	player.posY = 0;
	while (1)
	{
		
		
		if (player.posY > 0)
		{
			gotoxy(player.posX, player.posY);
			printf("%c", 'o');

			gotoxy(0, 20);
			for (i = 0; i < 20; i++)
				printf("%s", "бс");
		}
		else if (player.posY > -10)
		{
			gotoxy(player.posX,0);
			printf("%c", 'o');

			gotoxy(0, 20 - player.posY);
			for (i = 0; i < 20; i++)
				printf("%s", "бс");
		}
		else
		{
			gotoxy(player.posX, 0);
			printf("%c", 'o');
		}
		accel += gravity;
		player.posY += accel;

		if (player.posY > 19)
		{
			accel = 0;
			player.posY = 19;
		}
		else
		{
			player.posY += accel;
		}

		if (_kbhit())
		{
			if (IsKeyDown(VK_LEFT))
				player.posX--;
			if (IsKeyDown(VK_RIGHT))
				player.posX++;
			if (IsKeyDown(VK_SPACE))
				accel = -1.2;
		}
		gotoxy(50, 0);
		printf("player.posX, Y : %f, %f",player.posX, player.posY);
		printf(", accel : %.1f", accel);
		Sleep(5);
		system("cls");
		
	}
	
	_getch();
	return 0;
}