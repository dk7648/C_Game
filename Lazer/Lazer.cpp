#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<time.h>

#define S 5
#define M 7
#define B 10

void setColor(unsigned short text, unsigned short back);
int death(int score);
void openGame();
void map(int *nMap);
void game(int a);
int main(void)
{
	int nMap;
	openGame();
	map(&nMap);
	game(nMap);
	return 0;
}

void map(int *nMap)
{
	int x = 0, y = 0;
	int size = 0;
	int time = 0;
	int select_x = 0;
	int select = 0;
	char botton;

	system("cls");
	while (1)
	{
		printf("\n\n\t\t맵을 선택하세요\t\t");

		for (select_x = 0; select_x < 3; select_x++)
		{
			if (select == select_x)
			{
				printf("★%d번맵★\t", select_x + 1);
				switch (select_x)
				{
				case 0:
					size = S;
					time = 10;
					break;
				case 1:
					size = M;
					time = 5;
					break;
				case 2:
					size = B;
					time = 2;
					break;
				}
			}
			else
			{
				printf("☆%d번맵☆\t", select_x + 1);
			}
		}
		printf("\n\n\n");

		for (y = 0; y < size; y++)
		{
			for (x = 0; x < size; x++)
			{
				if ((x == 0) || (x == size - 1) || (y == 0) || (y == size - 1))
				{
					printf("■");
					Sleep(time);
				}
				else
				{
					printf("□");
					Sleep(time);
				}
			}

			if (y == 0)
			{
				printf("\t\t\t맵 번호 : %d번 맵", select + 1);
				printf("\n");
			}
			else if (y == 2)
			{
				printf("\t\t\t맵 크기 : %dX%d", size - 2, size - 2);
				printf("\n");
			}
			else if (y == 4)
			{
				printf("\t\t\t선택 : s");
				printf("\n");
			}
			else
			{
				printf("\n");
			}
		}

		switch (botton = _getch())
		{
		case 'a':
		case 'A':
			if (select >= 1)
				select--;

			break;
		case 'd':
		case 'D':
			if (select <= 1)
				select++;
			break;
		case 's':
		case 'S':
			*nMap = select;
			return;
		default:
			continue;
		}
		system("cls");
	}

}
void game(int nMap)
{
	int size, mx, my, score = 0;
	int player_x, player_y;

	switch (nMap)
	{
	case 0:
		size = S;
		break;
	case 1:
		size = M;
		break;
	case 2:
		size = B;
		break;
	}

	int laser_x = size, laser_y = size;
	int laser_count = 0, laser_speed = 30;

	player_x = player_y = size / 2;
	srand((int)time(NULL));

	while (1)
	{

		if (laser_count == laser_speed)
		{
			laser_x = player_x + rand() % 5 - 2;
			laser_y = player_y + rand() % 5 - 2;

			if (laser_x < 1)
				laser_x += 2;
			else if (laser_x > size - 2)
				laser_x -= 2;

			if (laser_y < 1)
				laser_y += 2;
			else if (laser_y > size - 2)
				laser_y -= 2;

			laser_count = 0;
			score += 100;

			if (laser_speed>8)
				laser_speed -= 2;
		}

		Sleep(20);
		system("cls");


		for (my = 0; my < size; my++)
		{
			for (mx = 0; mx < size; mx++)
			{
				if (my == 0 && mx == laser_x)
				{
					printf("▽");
				}
				else if (my == size - 1 && mx == laser_x)
				{
					printf("△");
				}
				else if (mx == 0 && (my == laser_y))
				{
					printf("▷");
				}
				else if (mx == size - 1 && my == laser_y)
				{
					printf("◁");
				}
				else if (mx == 0 || mx == size - 1 || my == 0 || my == size - 1)
				{
					printf("■");

				}
				else if (player_x == mx && player_y == my)
				{
					printf("◎");
				}
				else
				{
					if (((laser_count == laser_speed - 2) && ((laser_x == mx) || (laser_y == my))))
					{
						setColor(12, 0);
						printf("□");	//붉은 색 레이저
						setColor(7, 0);
						if ((laser_x == player_x) || (laser_y == player_y))
						{
							death(score);
							return;
						}
					}
					else
						printf("□");


				}
			}
			printf("\n");
		}
		printf("\n\n\t score : %d", score);


		if (_kbhit())
		{
			switch (_getch())
			{
			case 'd':
				player_x++;
				if (player_x >= size - 1) { player_x = size - 2; }
				break;
			case 'a':
				player_x--;
				if (player_x <= 0) { player_x = 1; }
				break;
			case 's':
				player_y++;
				if (player_y >= size - 1) { player_y = size - 2; }
				break;
			case 'w':
				player_y--;
				if (player_y <= 0) { player_y = 1; }
				break;
			}
		}

		laser_count++;
	}
}
void openGame()
{
	printf("                                                                                   \n");
	printf("                                                                                   \n");
	printf("                                                                                   \n");
	printf("                                                                                   \n");
	printf("                       ■       ■■    ■■■  ■■■   ■■■                    \n");
	printf("                       ■      ■  ■  ■       ■       ■   ■                   \n");
	printf("                       ■      ■■■   ■■■  ■■■   ■■■                    \n");
	printf("                       ■      ■  ■       ■  ■       ■   ■                   \n");
	printf("                       ■■■  ■  ■   ■■■  ■■■   ■   ■                   \n");
	printf("                                                                                   \n");
	printf("                                                                                   \n");
	printf("                                    PRESS ANY KEY                                  \n");
	printf("                                   조작 : w a s d                                  \n");
	printf("                                                                                   \n");
	printf("                                                                                   \n");
	printf("                                                                                   \n");

	_getch();
}
void setColor(unsigned short text, unsigned short back)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}
int death(int score)
{
	int ch;
	system("cls");
	printf("\n\n\n\n\t\t\tGAME OVER...");
	printf("\n\n\n\n\n\t\tYour Socre : %d", score);
	Sleep(3000);
	return 0;
}