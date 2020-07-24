#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#define M 40
#define N 80
#define UP 72 
#define DOWN 80
#define LEFT 75 
#define RIGHT 77
#define START 115 
#define ENTER 13
#define BACKSPACE 8 
#define ESC 27
#define TAB 9
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
struct snake
{
	point p[M*M];
	int size;
	snake()
	{
		size = 0;
	}
};
/*int getarrow()
{
	int c;
	c = _getch();
	if (c == 224)
	c = _getch();
	return c;
	return _getch() == 224 ? _getch() : 0;
}*/
void output(char a[M][N])
{
	for (int i = 0;i < M;i++)
	{
		for (int j = 0;j < N;j++)
			cout << a[i][j];
		cout << endl;
	}
}
void main()
{
	int dir, esc = 1, rx, ry;
	point *l, *f, food, fxy, *x, *b;
	fxy.x = 0;
	fxy.y = 0;
	l = new point;
	f = new point;
	b = new point;
	l->n = f;
	f->y++;
	char a[M][N];
	for (int i = 0;i < M;i++)
		for (int j = 0;j < N;j++)
			a[i][j] = ' ';
	output(a);
	a[l->x][l->y] = '*';
	a[f->x][f->y] = '*';
	food.x = M / 2;
	food.y = N / 2;
	a[food.x][food.y] = '#';
	output(a);
	while (esc != ESC)
	{
		system("cls");
		output(a);
		b->x = l->x;
		b->y = l->y;
		a[l->x][l->y] = ' ';
		l->x = l->n->x;
		l->y = l->n->y;
		if (_kbhit())
		{
			esc = _getch();
			if (esc == 224)
				dir = _getch();
		}
		if (dir == UP)
		{
			if (f->x == 0)
				f->x = M - 1;
			else
				f->x--;
		}
		if (dir == DOWN)
		{
			if (f->x == M - 1)
				f->x = 0;
			else
				f->x++;
		}
		if (dir == LEFT)
		{
			if (f->y == 0)
				f->y = N - 1;
			else
				f->y--;
		}
		if (dir == RIGHT)
		{
			if (f->y == N - 1)
				f->y = 0;
			else
				f->y++;
		}
		a[f->x][f->y] = '*';
		if (a[food.x][food.y] != '#')
		{
			srand(time(0));
			rx = rand() % M;
			ry = rand() % N;
			fxy.x = rx;
			fxy.y = ry;
			while (a[fxy.x][fxy.y] == '*')
			{
				srand(time(0));
				rx = rand() % M;
				ry = rand() % N;
				fxy.x = rx;
				fxy.y = ry;
			}
			a[fxy.x][fxy.y] = '#';
			food = fxy;
			x = new point;
			x->n = l;
			x->x = b->x;
			x->y = b->y;
			l = x;
			a[l->x][l->y] = '*';
		}
		if (esc == TAB)
			_getch();
	}
}