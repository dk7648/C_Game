#include "Turboc.h"
#define TRUE	1
#define	FALSE	0
#define MAX		1024
#define	RIGHT	77
#define LEFT	75
#define	UP		72
#define	DOWN	80
#define ESC		27


typedef struct Signal
{
	int exist;
	char ch;
	int x, y;
	int distance;
	int nFrame;
	int nStay;
}Signal;

Signal S[MAX];

int openGame(void);

void delSignal(int i);

void checkScore(int x, int* perfect, int* normal, int* bad);


int main(void)
{
	int i, ch;
	int freq = 15;
	int frame = 200;
	int stay = 10;
	int signalSpace = 4;
	int perfect=0;
	int normal=0;
	int bad=0;
	clrscr();
	randomize();

	int select = openGame();
	
	while (1)
	{
		setcursortype(NOCURSOR);
		for (i = 0; i < 4; i++)
		{
			gotoxy(i*signalSpace, 20);
			printf("○");
		}
		gotoxy(0, 23);
		printf("상하 : 속도 증감,	좌우 : 빈도 증감,	ESC : 종료,	 속도 : %4d,빈도 : %2d 대기시간:%d\n", frame, freq, stay);//아랫부분에 설명문. 23번째 줄.
		gotoxy(20, 10);
		printf("perfect : %4d", perfect);
		gotoxy(20, 11);
		printf("normal : %4d", normal);
		gotoxy(20, 12);
		printf("bad : %4d", bad);
		//키 입력 처리
		if (_kbhit())
		{
			ch = _getch();
			if (ch == 0xE0 || ch == 0)
			{
				ch = _getch();
				switch (ch)
				{
				case UP:
					if (frame < 1000)	//천이 될 때 까지만 frame을 추가해준다.
						frame += 10;
					else
						frame = 1000; // 1000까지 도달 시, 더이상 추가안함
					break;
				case DOWN:
					if (frame > 10)
						frame -= 10;
					else
						frame = 10;//반대로 10미만으로는 떨어지지 않는다.
					break;
				case RIGHT:
					if (freq > 1)
						freq -= 1;
					else
						freq = 1;
					break;
				case LEFT:
					if (freq < 50)
						freq += 1;
					else
						freq = 50;
					break;
				}
			}
			else if (ch == ESC)
			{
				exit(1);
			}
			else
			{

				switch (ch)
				{
				case 'z':
				case 'Z':
					checkScore(0 * signalSpace, &perfect, &normal, &bad);
					break;
				case 'x':
				case 'X':
					checkScore(1 * signalSpace, &perfect, &normal, &bad);
					break;
				case 'c':
				case 'C':
					checkScore(2 * signalSpace, &perfect, &normal, &bad);
					break;
				case 'v':
				case 'V':
					checkScore(3 * signalSpace, &perfect, &normal, &bad);
					break;

				}
			}
		}


		if (random(freq) == 0) //0~14까지 만든 랜던값의 결과가 0이므로 1/15의 확률을 의미한다.
		{
			for (i = 0; i < MAX; i++)
			{
				if (S[i].exist == FALSE)//값이 들어있는지 확인
				{
					S[i].exist = TRUE;//값을 넣었다면 트루!(값이있음!)
					S[i].ch = 'o';//random('Z' - 'A' + 1) + 'A';//Z-A+1 = 알파벳 개수. 그것 +A는 A~Z를 야기한다. //A에서 Z까지의 랜덤.
					S[i].x = (int)random(4)*signalSpace;//랜덤한 x좌표값 지정.
					S[i].y = 0;//y는 항상 0에서부터 떨어짐
					S[i].distance = 23;//사라질때까지 움직일 거리
					S[i].nFrame = S[i].nStay = stay;//이동 대기시간
					break;
				}
			}
		}

		for (i = 0; i < MAX; i++)
		{
			if (S[i].exist == TRUE)
			{
				S[i].nStay--;
				if (S[i].nStay == 0)
				{
					S[i].nStay = S[i].nFrame;
					gotoxy(S[i].x, S[i].y); _putch(' ');//원래있던 공간 비우기
					S[i].y++;
					if (S[i].y < S[i].distance)
					{
						gotoxy(S[i].x, S[i].y); _putch(S[i].ch);//한칸 아래에 새로 그리기
					}
					else
					{
						S[i].exist = FALSE;
					}
				}
			}
		}

		delay(1000 / frame);
	}
}
int openGame(void)
{
	system("cls");
	int select = -1;

	printf("                                                                                      \n");
	printf("                ■        ■■■■                                   ■               \n");
	printf("    ■■■■    ■        ■                 ■■■■■       ■■   ■               \n");
	printf("          ■    ■        ■■■■           ■      ■     ■   ■  ■               \n");
	printf("    ■■■■    ■     ■■■■■■■        ■■■■■     ■   ■  ■■■           \n");
	printf("    ■          ■        ■■■■               ■           ■■   ■               \n");
	printf("    ■■■■    ■        ■    ■               ■                  ■               \n");
	printf("                ■        ■■■■         ■■■■■■■                             \n");
	printf("                                                                                      \n");
	printf("                                                                                      \n");
	printf("                                                                                      \n");
	printf("                                   조작키 z,x,c,v, 방향키                             \n");
	printf("                                   게임시작 : 1                                       \n");
	printf("                                   설정     : 2                                       \n");
	printf("                                   끝내기   : 3                                       \n");

	do {
		select = _getch();

	} while (select < '1' || select > '3');
	system("cls");
	return select;
}


void delSignal(int i)
{
	gotoxy(S[i].x, S[i].y); _putch(' ');//원래있던 공간 비우기
	S[i].exist = FALSE;
}

void checkScore(int x, int* perfect, int* normal, int* bad)
{
	int i;
	for (i = 0; i < MAX; i++)
	{
		if (S[i].exist == TRUE && S[i].x == x)
		{
			switch (S[i].y)
			{
			case 20:
				*perfect += 1;
				delSignal(i);
				break;
			case 19:
			case 21:
				*normal += 1;
				delSignal(i);
				break;
			case 18:
			case 22:
				*bad += 1;
				delSignal(i);
				break;
			}

		}
	}
}