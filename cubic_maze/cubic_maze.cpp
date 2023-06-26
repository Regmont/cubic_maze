#include <iostream>
#include <conio.h>
using namespace std;

const int matr_size = 11;
bool GameOver = false;

enum Move { LEFT = 97, RIGHT = 100, UP = 119, DOWN = 115, TP_UP = 113, TP_DOWN = 101 };

int main();		//прототип main для перезапуска игры

void Recogn_Input(Move& selection);

void Print_Main_Screen(char elem_1, char elem_2);
void Print_End_Screen(char elem_1, char elem_2);
void Print_Wall(int matr[matr_size][matr_size], int x, int y);
void Print_Level(int matr[matr_size][matr_size], int x, int y, int z);
void Tutorial();

//main part
void Main_Screen()
{
	Move selection = Move(0);

	int choice = 1;
	char elem_1;
	char elem_2;

	Print_Main_Screen(char(254), ' ');

	while (_kbhit && selection != 13)
	{
		selection = (Move)_getch();

		if (selection != 13)
			Recogn_Input(selection);
		else
			break;

		switch (selection)
		{
			case UP:
			{
				choice == 1 ? choice = 2 : choice = 1;
				break;
			}
			case DOWN:
			{
				choice == 2 ? choice = 1 : choice = 2;
				break;
			}
		}

		if (choice == 1)
		{
			elem_1 = 254;
			elem_2 = ' ';
		}
		else
		{
			elem_1 = ' ';
			elem_2 = 254;
		}

		system("cls");
		Print_Main_Screen(elem_1, elem_2);
	}

	system("cls");

	if (choice == 2)
	{
		Tutorial();
		Main_Screen();
	}
}

void End_Screen()
{
	system("cls");

	Move selection = Move(0);

	int choice = 1;
	char elem_1;
	char elem_2;

	Print_End_Screen(char(254), ' ');

	while (_kbhit && selection != 13)
	{
		selection = (Move)_getch();

		if (selection != 13)
			Recogn_Input(selection);
		else
			break;

		switch (selection)
		{
			case LEFT:
			{
				choice == 1 ? choice = 2 : choice = 1;
				break;
			}
			case RIGHT:
			{
				choice == 2 ? choice = 1 : choice = 2;
				break;
			}
		}

		if (choice == 1)
		{
			elem_1 = 254;
			elem_2 = ' ';
		}
		else
		{
			elem_1 = ' ';
			elem_2 = 254;
		}

		system("cls");
		Print_End_Screen(elem_1, elem_2);
	}

	system("cls");

	if (choice == 1)
	{
		GameOver = false;
		main();
	}
}

void Logic(int matr[matr_size][matr_size], int& x, int& y, int& z, Move player)
{
	while (_kbhit && !GameOver)
	{
		player = (Move)_getch();    //Считывание нажатой клавиши
		Recogn_Input(player);

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
			default:	//временно для проверки
			{
				GameOver = true;
				break;
			}
		}

		system("cls");
		Print_Level(matr, x, y, z);
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

	Main_Screen();

	Print_Level(matr, x, y, z);
	Logic(matr, x, y, z, player);

	End_Screen();
}

//input
void Recogn_Input(Move& selection)
{
	switch (selection)
	{
		case 68:	//Введено 'A' или 'Ф' или 'ф'
		case 130:
		case 162:
		{
			selection = RIGHT;
			break;
		}
		case 65:	//Введено 'В' или 'В' или 'в'
		case 148:
		case 228:
		{
			selection = LEFT;
			break;
		}
		case 87:	//Введено 'W' или 'Ц' или 'ц'
		case 150:
		case 230:
		{
			selection = UP;
			break;
		}
		case 83:	//Введено 'S' или 'Ы' или 'ы'
		case 155:
		case 235:
		{
			selection = DOWN;
			break;
		}
		case 81:	//Введено 'Q' или 'Й' или 'й'
		case 137:
		case 169:
		{
			selection = TP_UP;
			break;
		}
		case 69:	//Введено 'E' или 'У' или 'у'
		case 147:
		case 227:
		{
			selection = TP_DOWN;
			break;
		}
	}
}

//output
void Print_Wall(int matr[matr_size][matr_size], int x, int y)
{
	int L = matr[y][x - 1];
	int R = matr[y][x + 1];
	int U = matr[y - 1][x];
	int D = matr[y + 1][x];
	int max_el = matr_size - 1;

	//является ли внешней стеной
	if (x == 0 || y == 0 || x == max_el || y == max_el)
	{
		if (x == 0 && y == 0)
			cout << char(201);								//угол право-низ
		else if (x == 0 && y == max_el)
			cout << char(200);								//право-верх
		else if (x == max_el && y == 0)
			cout << char(187);								//угол лево-низ
		else if (x == max_el && y == max_el)
			cout << char(188);								//угол лево-верх
		else if (y == 0)
			D != 1 ? cout << char(205) : cout << char(203);	// " = " или тройник лево-право-низ
		else if (y == max_el)
			U != 1 ? cout << char(205) : cout << char(202);	// " = " или тройник лево-право-верх
		else if (x == 0)
			R != 1 ? cout << char(186) : cout << char(204);	// " || " или тройник право-верх-низ
		else
			L != 1 ? cout << char(186) : cout << char(185);	// " || " или тройник лево-верх-низ
	}
	else
	{
		if (L == 1 && R == 1 && U == 1 && D == 1)
			cout << char(206);									//крест
		else if (R == 1 && U != 1 && D == 1)
			L != 1 ? cout << char(201) : cout << char(203);	//угол право-низ + тройник (лево)
		else if (L != 1 && R == 1 && U == 1)
			D != 1 ? cout << char(200) : cout << char(204);		//угол право-верх + тройник (низ)
		else if (L == 1 && R != 1 && D == 1)
			U != 1 ? cout << char(187) : cout << char(185);		//угол лево-низ + тройник (верх)
		else if (L == 1 && R != 1 && U == 1)
			D != 1 ? cout << char(188) : cout << char(185);		//угол лево-верх (низ)
		else if (U != 1 && D != 1)
			cout << char(205);									// " = "
		else if (L != 1 && R != 1)
			cout << char(186);									// " || "
		else
			cout << char(197);									//доп. элемент
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
						cout << '?';		//Неопознанный объект (ошибка)
						break;
					}
				}

		cout << endl;
	}

	for (int i = 0; i < matr_size / 2 - 3; i++)
		cout << ' ';

	cout << "level " << z + 1 << endl;
}

void Print_Main_Screen(char elem_1, char elem_2)
{
	cout << "   CUBIC MAZE" << endl << endl;

	cout << "   " << char(201);
	for (int i = 0; i < 8; i++)
		cout << char(205);
	cout << char(187) << endl;

	cout << "  " << elem_1 << char(186) << "  play  " << char(186) << endl;

	cout << "   " << char(200);
	for (int i = 0; i < 8; i++)
		cout << char(205);
	cout << char(188) << endl;

	cout << "   " << char(201);
	for (int i = 0; i < 8; i++)
		cout << char(205);
	cout << char(187) << endl;

	cout << "  " << elem_2 << char(186) << "tutorial" << char(186) << endl;

	cout << "   " << char(200);
	for (int i = 0; i < 8; i++)
		cout << char(205);
	cout << char(188) << endl;

	cout << endl;
	cout << "use W, S to switch";
}

void Print_End_Screen(char elem_1, char elem_2)
{
	cout << endl << endl << "\tCONGRATULATIONS!" << endl;
	cout << " You've made it through the maze!" << endl << endl;

	cout << "     " << char(201);
	for (int i = 0; i < 10; i++)
		cout << char(205);
	cout << char(187) << char(201);
	for (int i = 0; i < 9; i++)
		cout << char(205);
	cout << char(187) << endl;

	cout << "     " << char(186) << "play again" << char(186) << char(186) << "quit game" << char(186) << endl;

	cout << "     " << char(200);
	for (int i = 0; i < 10; i++)
		cout << char(205);
	cout << char(188) << char(200);
	for (int i = 0; i < 9; i++)
		cout << char(205);
	cout << char(188) << endl;

	cout << "     ";
	for (int i = 0; i < 12; i++)
		cout << elem_1;
	for (int i = 0; i < 11; i++)
		cout << elem_2;

	cout << endl << endl;
	cout << "       use A, D to switch";
}

void Tutorial()
{
	int back = 0;

	cout << char(2) << " - you\n";
	cout << char(253) << " - portal to the next level\n";
	cout << char(15) << " - portal to the previous level\n";

	cout << endl;

	cout << "WASD - move\n";
	cout << "Q - using first portal " << char(253) << endl;
	cout << "E - using second portal " << char(15) << endl;

	cout << endl << endl;

	cout << "press Enter to go back to main menu" << endl;

	while (_kbhit && back != 13)
	{
		back = _getch();
	}

	system("cls");
}