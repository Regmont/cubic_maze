#include <iostream>
#include <conio.h>
using namespace std;

const int matr_size = 11;

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

void Print_Level(int matr[matr_size][matr_size], int x, int y)
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
			if (i == y && j == x)
				cout << 'O';
			else
				switch (matr[i][j])
				{
				case 0:
				{
					cout << ' ';
					break;
				}
				case 1:
				{
					cout << '#';
					break;
				}
				case 2:
				{
					cout << '^';
					break;
				}
				case 3:
				{
					cout << '&';
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

int main()
{
	Move player;

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

	Print_Level(matr, x, y);

	while (_kbhit)
	{
		player = (Move)_getch();    //Считывание нажатой клавиши
		Recogn_Input(player);

		//        cout << player << ' ';

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
			//                if (matr[z][y][x] == 2)
			//                    z++;

			break;
		}
		case TP_DOWN:
		{
			//                if (matr[z][y][x] == 3)
								//z--;

			break;
		}
		}

		system("cls");
		Print_Level(matr, x, y);
		//        cout << "x = " << x << " y = " << y << " z = " << z << endl;
	}
}