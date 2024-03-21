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
			printf("��");
		}
		gotoxy(0, 23);
		printf("���� : �ӵ� ����,	�¿� : �� ����,	ESC : ����,	 �ӵ� : %4d,�� : %2d ���ð�:%d\n", frame, freq, stay);//�Ʒ��κп� ����. 23��° ��.
		gotoxy(20, 10);
		printf("perfect : %4d", perfect);
		gotoxy(20, 11);
		printf("normal : %4d", normal);
		gotoxy(20, 12);
		printf("bad : %4d", bad);
		//Ű �Է� ó��
		if (_kbhit())
		{
			ch = _getch();
			if (ch == 0xE0 || ch == 0)
			{
				ch = _getch();
				switch (ch)
				{
				case UP:
					if (frame < 1000)	//õ�� �� �� ������ frame�� �߰����ش�.
						frame += 10;
					else
						frame = 1000; // 1000���� ���� ��, ���̻� �߰�����
					break;
				case DOWN:
					if (frame > 10)
						frame -= 10;
					else
						frame = 10;//�ݴ�� 10�̸����δ� �������� �ʴ´�.
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


		if (random(freq) == 0) //0~14���� ���� �������� ����� 0�̹Ƿ� 1/15�� Ȯ���� �ǹ��Ѵ�.
		{
			for (i = 0; i < MAX; i++)
			{
				if (S[i].exist == FALSE)//���� ����ִ��� Ȯ��
				{
					S[i].exist = TRUE;//���� �־��ٸ� Ʈ��!(��������!)
					S[i].ch = 'o';//random('Z' - 'A' + 1) + 'A';//Z-A+1 = ���ĺ� ����. �װ� +A�� A~Z�� �߱��Ѵ�. //A���� Z������ ����.
					S[i].x = (int)random(4)*signalSpace;//������ x��ǥ�� ����.
					S[i].y = 0;//y�� �׻� 0�������� ������
					S[i].distance = 23;//����������� ������ �Ÿ�
					S[i].nFrame = S[i].nStay = stay;//�̵� ���ð�
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
					gotoxy(S[i].x, S[i].y); _putch(' ');//�����ִ� ���� ����
					S[i].y++;
					if (S[i].y < S[i].distance)
					{
						gotoxy(S[i].x, S[i].y); _putch(S[i].ch);//��ĭ �Ʒ��� ���� �׸���
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
	printf("                ��        �����                                   ��               \n");
	printf("    �����    ��        ��                 ������       ���   ��               \n");
	printf("          ��    ��        �����           ��      ��     ��   ��  ��               \n");
	printf("    �����    ��     ��������        ������     ��   ��  ����           \n");
	printf("    ��          ��        �����               ��           ���   ��               \n");
	printf("    �����    ��        ��    ��               ��                  ��               \n");
	printf("                ��        �����         ��������                             \n");
	printf("                                                                                      \n");
	printf("                                                                                      \n");
	printf("                                                                                      \n");
	printf("                                   ����Ű z,x,c,v, ����Ű                             \n");
	printf("                                   ���ӽ��� : 1                                       \n");
	printf("                                   ����     : 2                                       \n");
	printf("                                   ������   : 3                                       \n");

	do {
		select = _getch();

	} while (select < '1' || select > '3');
	system("cls");
	return select;
}


void delSignal(int i)
{
	gotoxy(S[i].x, S[i].y); _putch(' ');//�����ִ� ���� ����
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