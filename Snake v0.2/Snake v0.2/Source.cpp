#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#define HEIGHT 25
#define WIDTH 80
#define M 25
#define N 50
#define UP 72 
#define DOWN 80
#define LEFT 75 
#define RIGHT 77
#define ESC 27
#define TAB 9
int score = 0;
int delay = 100;
using namespace std;
struct point
{
	int x, y;
	point *n;
	point()
	{
		x = y = 0;
		n = NULL;
	}
};
void gotoxy(int y, int x) 
{ 
	COORD coord; 
	coord.X = x; 
	coord.Y = y; 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); 
}
void main()
{
	for (int i = 0;i < WIDTH;i++)
	{
		gotoxy(0, i);
		cout << "-";
		gotoxy(HEIGHT - 1, i);
		cout << "-";
	}
	for (int i = 1;i < HEIGHT - 1;i++)
	{
		gotoxy(i, 0);
		cout << "|";
		gotoxy(i, WIDTH - 1);
		cout << "|";
		gotoxy(i, N - 1);
		cout << "|";
	}
	int dir = RIGHT, esc = 1, rx, ry, dir_p = RIGHT, s;
	point *l, *f, food, fxy, *temp, back;
	l = new point;
	f = new point;
	l->n = f;
	f->y++;
	char a[M][N];
	for (int i = 0;i < M;i++)
		for (int j = 0;j < N;j++)
			a[i][j] = ' ';
	l->x = 1;
	l->y = 1;
	f->x = 1;
	l->y = 2;
	a[l->x][l->y] = '*';
	a[f->x][f->y] = '*';
	food.x = M / 2;
	food.y = N / 2;
	a[food.x][food.y] = '#';
	gotoxy(food.x, food.y);
	cout << '#';
	gotoxy(8, 50 + (30 - 11) / 2);
	cout << "Esc : Exit";
	gotoxy(10, 50 + (30 - 28) / 2);
	cout << "Tab : Pause or Speed Change";
	gotoxy(12, 60);
	cout << "Score : " << score;
	gotoxy(14, 50 + (30 - 15) / 2);
	cout << "Delay : " << delay << " ms      ";
	gotoxy(HEIGHT - 1, WIDTH - 1);
	while (esc != ESC)
	{
		a[l->x][l->y] = ' ';
		gotoxy(l->x, l->y);
		cout << ' ';
		gotoxy(HEIGHT - 1, WIDTH - 1);
		back.x = l->x;
		back.y = l->y;
		temp = l;
		l = l->n;
		delete temp;
		if (_kbhit())
		{
			esc = _getch();
			if (esc == 224)
				dir = _getch();
			if (dir == UP && dir_p == DOWN)
				dir = DOWN;
			else if (dir == DOWN && dir_p == UP)
				dir = UP;
			else if (dir == RIGHT && dir_p == LEFT)
				dir = LEFT;
			else if (dir == LEFT && dir_p == RIGHT)
				dir = RIGHT;
			else
				dir_p = dir;
		}
		temp = new point;
		temp->x = f->x;
		temp->y = f->y;
		if (dir == UP)
		{
			if (temp->x == 1)
				temp->x = M - 2;
			else
				temp->x--;
		}
		if (dir == DOWN)
		{
			if (temp->x == M - 2)
				temp->x = 1;
			else
				temp->x++;
		}
		if (dir == LEFT)
		{
			if (temp->y == 1)
				temp->y = N - 2;
			else
				temp->y--;
		}
		if (dir == RIGHT)
		{
			if (temp->y == N - 2)
				temp->y = 1;
			else
				temp->y++;
		}
		f->n = temp;
		f = temp;
		if (a[f->x][f->y] == '*')
		{
			gotoxy(10, (50 - 10) / 2);
			cout << "Game Over";
			gotoxy(12, (50 - 14) / 2);
			cout << "Your score : " << score;
			gotoxy(HEIGHT - 1, WIDTH - 1);
			_getch();
			break;
		}
		a[f->x][f->y] = '*';
		gotoxy(f->x, f->y);
		cout << '*';
		gotoxy(HEIGHT - 1, WIDTH - 1);
		if (a[food.x][food.y] != '#')
		{
			{
				srand(time(0));
				rx = 1 + rand() % (M - 2);
				ry = 1 + rand() % (N - 2);
				fxy.x = rx;
				fxy.y = ry;
				while (a[fxy.x][fxy.y] == '*')
				{
					srand(time(0));
					rx = 1 + rand() % (M - 2);
					ry = 1 + rand() % (N - 2);
					fxy.x = rx;
					fxy.y = ry;
				}
				a[fxy.x][fxy.y] = '#';
				gotoxy(fxy.x, fxy.y);
				cout << '#';
				gotoxy(HEIGHT - 1, WIDTH - 1);
				food = fxy;
			}
			score++;
			gotoxy(12, 60);
			cout << "Score : " << score;
			gotoxy(25, 80);
			temp = new point;
			temp->n = l;
			temp->x = back.x;
			temp->y = back.y;
			l = temp;
			a[l->x][l->y] = '*';
			gotoxy(l->x, l->y);
			cout << '*';
			gotoxy(HEIGHT - 1, WIDTH - 1);
		}
		if (esc == TAB)
		{
			gotoxy(16, 50 + (30 - 16) / 2);
			cout << "Enter new speed";
			gotoxy(18, 50 + (30 - 3) / 2);
			cin >> s;
			delay = s;
			gotoxy(14, 50);
			cout << "                             ";
			gotoxy(16, 50);
			cout << "                             ";
			gotoxy(18, 50);
			cout << "                             ";
			gotoxy(14, 50 + (30 - 15) / 2);
			cout << "Delay : " << delay << " ms      ";
			gotoxy(HEIGHT - 1, WIDTH - 1);
			_getch();
		}
		Sleep(delay);
	}
}