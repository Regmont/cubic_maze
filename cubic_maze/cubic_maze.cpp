#include <iostream>
#include <conio.h>
using namespace std;

const int matr_size = 11;
bool GameOver = false;

enum Move { LEFT = 97, RIGHT = 100, UP = 119, DOWN = 115, TP_UP = 113, TP_DOWN = 101 };

void Recogn_Input(Move& player)
{
	if (player < 90)                    //Если введена заглавная английская буква, её регистр меняется на прописную
		player = Move(player + 32);

	if (player == 130 || player == 162) //Введено 'Ф' или 'ф'
		player = RIGHT;

	if (player == 148 || player == 228) //Введено 'В' или 'в'
		player = LEFT;

	if (player == 150 || player == 230) //Введено 'Ц' или 'ц'
		player = UP;

	if (player == 155 || player == 235) //Введено 'Ы' или 'ы'
		player = DOWN;

	if (player == 137 || player == 169) //Введено 'Й' или 'й'
		player = TP_UP;

	if (player == 147 || player == 227) //Введено 'У' или 'у'
		player = TP_DOWN;
}

void Print_Wall(int matr[matr_size][matr_size], int y, int x)
{
	int L = matr[x][y - 1];
	int R = matr[x][y + 1];
	int U = matr[x - 1][y];
	int D = matr[x + 1][y];
	int max_el = matr_size - 1;

	if (x == 0 || y == 0 || x == max_el || y == max_el)
	{
		if (x == 0 && y == 0)
			cout << char(201);
		else if (x == 0 && y == max_el)
			cout << char(187);
		else if (x == max_el && y == 0)
			cout << char(200);
		else if (x == max_el && y == max_el)
			cout << char(188);
		else if (x == 0)
		{
			if (D != 1)
				cout << char(205);
			else
				cout << char(203);
		}
		else if (x == max_el)
		{
			if (U != 1)
				cout << char(205);
			else
				cout << char(202);
		}
		else if (y == 0)
		{
			if (R != 1)
				cout << char(186);
			else
				cout << char(204);
		}
		else
		{
			if (L != 1)
				cout << char(186);
			else
				cout << char(185);
		}
	}
	else
	{
		if (L != 1 && R == 1 && U != 1 && D == 1)
			cout << char(201);
		else if (L == 1 && R != 1 && U != 1 && D == 1)
			cout << char(187);
		else if (L == 1 && R != 1 && U == 1 && D != 1)
			cout << char(188);
		else if (L != 1 && R == 1 && U == 1 && D != 1)
			cout << char(200);
		else if (L != 1 && R != 1 && U == 1 && D == 1)
			cout << char(186);
		else if (L == 1 && R == 1 && U != 1 && D != 1)
			cout << char(205);
		else if (L != 1 && R == 1 && U == 1 && D == 1)
			cout << char(204);
		else if (L == 1 && R != 1 && U == 1 && D == 1)
			cout << char(185);
		else if (L == 1 && R == 1 && U != 1 && D == 1)
			cout << char(203);
		else if (L == 1 && R == 1 && U == 1 && D != 1)
			cout << char(202);
		else if (L == 1 && R == 1 && U == 1 && D == 1)
			cout << char(206);
		else if (L == 1 && R != 1 && U != 1 && D != 1)
			cout << char(184);
		else if (L != 1 && R == 1 && U != 1 && D != 1)
			cout << char(213);
		else if (L != 1 && R != 1 && U != 1 && D == 1)
			cout << char(214);
		else if (L != 1 && R != 1 && U == 1 && D != 1)
			cout << char(211);
		else
			cout << char(197);
	}
}

void Print_Level(int matr[matr_size][matr_size], int x, int y, int z)
{
	for (int i = 0; i < matr_size; i++)
	{
		for (int j = 0; j < matr_size; j++)
			if (i == y && j == x)
				cout << char(2);	//игрок
			else
				switch (matr[i][j])
				{
					case 0:
					{
						cout << ' ';	//пустое пространство
						break;
					}
					case 1:
					{
						Print_Wall(matr, j, i);	//стена
						break;
					}
					case 2:
					{
						cout << char(253);	//телепорт вверх
						break;
					}
					case 3:
					{
						cout << char(15);	//телепорт вниз
						break;
					}
					default:
					{
						cout << '?';
						break;
					}
				}

		cout << endl;
	}
}

void Logic(int matr[matr_size][matr_size], int& x, int& y, int& z, Move player)
{
	while (_kbhit)
	{
		player = (Move)_getch();    //Считывание нажатой клавиши
		Recogn_Input(player);

		//		cout << player << ' ';

		switch (player)
		{
			case LEFT:
			{
				if (matr[y][x - 1] != 1)
					x--;

				break;
			}
			case RIGHT:
			{
				if (matr[y][x + 1] != 1)
					x++;

				break;
			}
			case UP:
			{
				if (matr[y - 1][x] != 1)
					y--;

				break;
			}
			case DOWN:
			{
				if (matr[y + 1][x] != 1)
					y++;

				break;
			}
			case TP_UP:
			{
				//			if (matr[z][y][x] == 2)
				//			z++;

				break;
			}
			case TP_DOWN:
			{
				//			if (matr[z][y][x] == 3)
				//			z--;

				break;
			}
		}

		system("cls");
		Print_Level(matr, x, y, z);
		//		cout << "x = " << x << " y = " << y << " z = " << z << endl;
	}
}

int main()
{
	Move player = Move(0);

	//Пример матрицы с лабиринтом (массив будет трёхмерным)
	int matr[matr_size][matr_size] =
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1,
		1, 2, 1, 0, 0, 0, 1, 0, 0, 0, 1,
		1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1,
		1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1,
		1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1,
		1, 0, 0, 0, 1, 0, 0, 0, 1, 3, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	};

	int x = 9, y = 8, z = 0;   //правый нижний угол над цифрой 3

	/*for (int i = 0; i < 256; i++)
		cout << char(i) << " " << i << endl;*/

	Print_Level(matr, x, y, z);
	
	while (!GameOver)
		Logic(matr, x, y, z, player);
}