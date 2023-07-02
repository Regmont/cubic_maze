﻿#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "maze_gen.h"

using namespace std;

int matr_size;			//Размер уровня (сторона квадрата)
int lvl_amount;			//Количество уровней
bool GameOver = false;	//Конец игры или переход на другой уровень
int z = 0;				//Текущее положение кубе: уровень(на 1 меньше выводимого на экран)

//Считываемые символы
enum Move { LEFT = 97, RIGHT = 100, UP = 119, DOWN = 115, TP_UP = 113, TP_DOWN = 101, QUIT = 112 };

//Прототипы
int main();		//Для перезапуска игры

void Recogn_Input(Move& selection);

void Print_Custom_Dif(int size, int lvls, char elem_1, char elem_2);
void Print_Diffs(char elem_1, char elem_2, char elem_3, char elem_4);
void Print_Main_Screen(char elem_1, char elem_2);
void Print_End_Screen(char elem_1, char elem_2);
void Print_Wall(int** matr, int x, int y);
void Print_Level(int** matr, int x, int y);
void Tutorial();
void Print_Player(int x, int y, int pl_coord, int cell);

//Главные функции
void Custom_Dif()
{
	//Функция даёт возможность настроить сложность игры

	Move selection = Move(0);		//Возможность выбора
	int choice = 1;					//Переключение между строками выбора
	char elem_1, elem_2;			//Элементы, отображающие, какая строка выбрана
	int size = 5, lvls = 1;			//Предполагаемые размер уровней и количество уровней

	Print_Custom_Dif(size, lvls, char(254), ' ');	//Вывод настройки сложности

	//Ожидание нажатия Enter
	while (_kbhit && selection != 13)
	{
		selection = (Move)_getch();

		if (selection != 13)
			Recogn_Input(selection);	//Опознание вводимых данных
		else
			break;

		//Перемещение между строками настройки
		if (selection == UP || selection == DOWN)
			choice == 1 ? choice = 2 : choice = 1;

		if (choice == 1)
			switch (selection)
			{
				//Перемещение между полями сложностей
				case LEFT:
				{
					size == 5 ? size = 99 : size -= 2;
					break;
				}
				case RIGHT:
				{
					size == 99 ? size = 5 : size += 2;
					break;
				}
			}
		else
			switch (selection)
			{
				//Перемещение между полями сложностей
				case LEFT:
				{
					lvls == 1 ? lvls = 10 : lvls--;
					break;
				}
				case RIGHT:
				{
					lvls == 10 ? lvls = 1 : lvls++;
					break;
				}
			}

		//Присвоение показывающим выбранный элемент символам нужные коды для отображения
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
		Print_Custom_Dif(size, lvls, elem_1, elem_2);	//Вывод настройки сложности
	}

	system("cls");

	//Присвоение значений размерам куба
	matr_size = size;
	lvl_amount = lvls;
}

void Choose_Difficulty()
{
	//Функция предоставляет возможность выбрать сложность игры

	system("cls");

	Move selection = Move(0);				//Вохможность выбора

	int choice = 1;							//Выбранный элемент
	char elem_1, elem_2, elem_3, elem_4;	//Символы, показывающие какой элемент выбран

	Print_Diffs(char(254), ' ', ' ', ' ');	//Вывод сложностей на выбор

	//Ожидание нажатия Enter
	while (_kbhit && selection != 13)
	{
		selection = (Move)_getch();

		if (selection != 13)
			Recogn_Input(selection);	//Опознание вводимых данных
		else
			break;

		switch (selection)
		{
			//Перемещение между полями сложностей
			case LEFT:
			{
				choice == 1 ? choice = 4 : choice--;
				break;
			}
			case RIGHT:
			{
				choice == 4 ? choice = 1 : choice++;
				break;
			}
		}

		//Присвоение показывающим выбранный элемент символам нужные коды для отображения
		switch (choice)
		{
			case 1:
			{
				elem_1 = 254;
				elem_2 = ' ';
				elem_3 = ' ';
				elem_4 = ' ';
				break;
			}
			case 2:
			{
				elem_1 = ' ';
				elem_2 = 254;
				elem_3 = ' ';
				elem_4 = ' ';
				break;
			}
			case 3:
			{
				elem_1 = ' ';
				elem_2 = ' ';
				elem_3 = 254;
				elem_4 = ' ';
				break;
			}
			case 4:
			{
				elem_1 = ' ';
				elem_2 = ' ';
				elem_3 = ' ';
				elem_4 = 254;
				break;
			}
		}

		system("cls");
		Print_Diffs(elem_1, elem_2, elem_3, elem_4);	//Вывод сложностей на выбор
	}

	system("cls");

	//Присвоение значений размерам куба в зависимости от сложности
	switch (choice)
	{
		case 1:
		{
			matr_size = 17;
			lvl_amount = 6;
			break;
		}
		case 2:
		{
			matr_size = 21;
			lvl_amount = 7;
			break;
		}
		case 3:
		{
			matr_size = 31;
			lvl_amount = 8;
			break;
		}
		case 4:
		{
			Custom_Dif();		//Особая настройка сложности
			break;
		}
	}
}

void Main_Screen()
{
	//Функция отвечает за взаимодействие с главным экраном

	Move selection = Move(0);	//Возможность выбора

	int choice = 1;				//Выбранный элемент
	char elem_1, elem_2;		//Символы, показывающие какой элемент выбран

	Print_Main_Screen(char(254), ' ');	//Вывод главного экрана

	//Ожидание нажатия Enter
	while (_kbhit && selection != 13)
	{
		selection = (Move)_getch();

		if (selection != 13)
			Recogn_Input(selection);	//Опознание вводимых данных
		else
			break;

		//Перемещение между полями выбора
		if (selection == UP || selection == DOWN)
			choice == 1 ? choice = 2 : choice = 1;

		//Присвоение показывающим выбранный элемент символам нужные коды для отображения
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
		Print_Main_Screen(elem_1, elem_2);	//Вывод главного экрана
	}

	system("cls");

	if (choice == 1)
		Choose_Difficulty();	//Выбор сложности игры
	else
	{
		Tutorial();		//Вывод обучения
		Main_Screen();	//Возврат к главному экрану
	}
}

void End_Screen()
{
	//Функция отвечает за взаимодействие с экраном победы

	system("cls");

	Move selection = Move(0);	//Возможность выбора

	int choice = 1;				//Выбранный элемент
	char elem_1, elem_2;		//Символы, показывающие какой элемент выбран

	Print_End_Screen(char(254), ' ');	//Вывод экрана победы

	//Ожидание нажатия Enter
	while (_kbhit && selection != 13)
	{
		selection = (Move)_getch();

		if (selection != 13)
			Recogn_Input(selection);	//Опознание вводимых данных
		else
			break;

		//Перемещение между полями выбора
		if (selection == LEFT || selection == RIGHT)
			choice == 1 ? choice = 2 : choice = 1;

		//Присвоение показывающим выбранный элемент символам нужные коды для отображения
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
		Print_End_Screen(elem_1, elem_2);	//Вывод экрана победы
	}

	system("cls");

	if (choice == 1)
	{
		GameOver = false;	//Конец игры
		z = 0;
		main();				//Начало новой игры
	}
}

void Logic(int** matr, int& x, int& y, int& z, Move& player)
{
	while (_kbhit && !GameOver)
	{
		player = (Move)_getch();    //Считывание нажатой клавиши
		Recogn_Input(player);		//Опознание вводимых данных

		int pl_coord;	//место, откуда перместился игрок

		switch (player)
		{
			//Выполнение действий в зависимости от того, что нажал игрок
			case LEFT:
			{
				if (matr[y][x - 1] != 1)
				{
					x--;
					pl_coord = 1;	//Справа
					Print_Player(x, y, pl_coord, matr[y][x + 1]);	//Вывод местоположения игрока
				}

				break;
			}
			case RIGHT:
			{
				if (matr[y][x + 1] != 1)
				{
					x++;
					pl_coord = 2;	//Слева
					Print_Player(x, y, pl_coord, matr[y][x - 1]);	//Вывод местоположения игрока
				}

				break;
			}
			case UP:
			{
				if (matr[y - 1][x] != 1)
				{
					y--;
					pl_coord = 3;	//Снизу
					Print_Player(x, y, pl_coord, matr[y + 1][x]);	//Вывод местоположения игрока
				}

				break;
			}
			case DOWN:
			{
				if (matr[y + 1][x] != 1)
				{
					y++;
					pl_coord = 4;	//Сверху
					Print_Player(x, y, pl_coord, matr[y - 1][x]);	//Вывод местоположения игрока
				}

				break;
			}
			case TP_UP:
			{
				if (matr[y][x] == 2)
				{
					z++;
					GameOver = true;	//Прерывание игры
				}
				else

				break;
			}
			case TP_DOWN:
			{
				if (matr[y][x] == 3)
				{
					z--;
					GameOver = true;	//Прерывание игры
				}

				break;
			}
			case QUIT:
			{
				//Ручное завершение игры
				GameOver = true;
				z = lvl_amount;
				break;
			}
		}
	}
}

int main()
{
	srand(time(0));

	Move player = Move(0);	//Персонаж

	Main_Screen();			//Вывод главного экрана

	int*** cube = new int** [lvl_amount];	//Куб
	int x = 1, y = 1;						//Начальное положение персонажа

	//Массив для сохранение уже созданных уровней
	bool* arr = new bool[lvl_amount];

	for (int i = 0; i < lvl_amount; i++)
		arr[i] = false;

	//Проход по всем уровням
	while (z < lvl_amount)
	{
		//Проверка на существование уровня
		if (arr[z] == false)
		{
			//Создание нового уровня
			cube[z] = new int* [matr_size];
			for (int i = 0; i < matr_size; i++)
				cube[z][i] = new int[matr_size];

			cube[z] = generate_maze_matrix(matr_size, x, y, z);
			arr[z] = true;	//Пометка, какой уровень уже загружен
		}

		Print_Level(cube[z], x, y);			//Вывод уровня
		Logic(cube[z], x, y, z, player);	//Использование основной логики

		GameOver = false;
		system("cls");
	}

	if (player != QUIT)
		End_Screen();		//Вывод экрана победы
	else
		cout << "\n\tGame Over!";
}

//Ввод данных
void Recogn_Input(Move& selection)
{
	//Функция преобразует нежелательный способ ввода в желательный (для enum)

	switch (selection)
	{
		case 68:	//Введено 'D' или 'В' или 'в'
		case 130:
		case 162:
		{
			selection = RIGHT;
			break;
		}
		case 65:	//Введено 'A' или 'Ф' или 'ф'
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
		case 80:	//Введено 'P' или 'з' или 'З'
		case 167:
		case 135:
		{
			selection = QUIT;
			break;
		}
	}
}

//Вывод данных
void Print_Custom_Dif(int size, int lvls, char elem_1, char elem_2)
{
	//Функция выводит настройку сложности

	cout << endl << endl << "\tadjust  difficulty" << endl << endl;

	//строка 1
	cout << "        " << char(201);
	for (int i = 0; i < 16; i++)
		cout << char(205);
	cout << char(187) << endl;

	//строка 2
	cout << "        " << char(186) << "   level size   " << char(186) << endl;

	//строка 3
	cout << "       " << elem_1 << char(186);
	for (int i = 0; i < 16; i++)
		cout << ' ';
	cout << char(186) << endl;

	//строка 4
	cout << "        " << char(186) << "<-     " << size;
	if (size < 10)
		cout << ' ';
	cout << "     ->" << char(186) << endl;

	//строка 5
	cout << "        " << char(200);
	for (int i = 0; i < 16; i++)
		cout << char(205);
	cout << char(188) << endl;

	//строка 6
	cout << "        " << char(201);
	for (int i = 0; i < 16; i++)
		cout << char(205);
	cout << char(187) << endl;

	//строка 7
	cout << "        " << char(186) << "amount of levels" << char(186) << endl;

	//строка 8
	cout << "       " << elem_2 << char(186);
	for (int i = 0; i < 16; i++)
		cout << ' ';
	cout << char(186) << endl;

	//строка 9
	cout << "        " << char(186) << "<-     " << lvls;
	if (lvls != 10)
		cout << ' ';
	cout << "     ->" << char(186) << endl;

	//строка 10
	cout << "        " << char(200);
	for (int i = 0; i < 16; i++)
		cout << char(205);
	cout << char(188) << endl;

	cout << endl << endl;
	cout << "    use W, S and A, D to switch";
}

void Print_Diffs(char elem_1, char elem_2, char elem_3, char elem_4)
{
	//Функция выводит экран сложностей

	cout << endl << endl << "\tselect difficulty" << endl << endl;

	//строка 1
	cout << "  " << char(201);
	for (int i = 0; i < 4; i++)
		cout << char(205);
	cout << char(187) << char(201);
	for (int i = 0; i < 6; i++)
		cout << char(205);
	cout << char(187) << char(201);
	for (int i = 0; i < 4; i++)
		cout << char(205);
	cout << char(187) << char(201);
	for (int i = 0; i < 6; i++)
		cout << char(205);
	cout << char(187) << endl;

	//строка 2
	cout << "  " << char(186) << "easy" << char(186) << char(186) << "normal" << char(186);
	cout << char(186) << "hard" << char(186) << char(186) << "custom" << char(186) << endl;

	//строка 3
	cout << "  " << char(200);
	for (int i = 0; i < 4; i++)
		cout << char(205);
	cout << char(188) << char(200);
	for (int i = 0; i < 6; i++)
		cout << char(205);
	cout << char(188) << char(200);
	for (int i = 0; i < 4; i++)
		cout << char(205);
	cout << char(188) << char(200);
	for (int i = 0; i < 6; i++)
		cout << char(205);
	cout << char(188) << endl;

	//Отображение выбранного элемента
	cout << "  ";
	for (int i = 0; i < 6; i++)
		cout << elem_1;
	for (int i = 0; i < 8; i++)
		cout << elem_2;
	for (int i = 0; i < 6; i++)
		cout << elem_3;
	for (int i = 0; i < 8; i++)
		cout << elem_4;

	cout << endl << endl;
	cout << "       use A, D to switch";
}

void Print_Wall(int** matr, int x, int y)
{
	//Функция выводит нужную стену

	int max_el = matr_size - 1;	//Самый дальний элемент от начала

	//Является ли внешней стеной
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
			matr[y + 1][x] != 1 ? cout << char(205) : cout << char(203);	// " = " или тройник лево-право-низ
		else if (y == max_el)
			matr[y - 1][x] != 1 ? cout << char(205) : cout << char(202);	// " = " или тройник лево-право-верх
		else if (x == 0)
			matr[y][x + 1] != 1 ? cout << char(186) : cout << char(204);	// " || " или тройник право-верх-низ
		else
			matr[y][x - 1] != 1 ? cout << char(186) : cout << char(185);	// " || " или тройник лево-верх-низ
	}
	else
	{
		int L = matr[y][x - 1];
		int R = matr[y][x + 1];
		int U = matr[y - 1][x];
		int D = matr[y + 1][x];

		if (L == 1 && R == 1 && U == 1 && D == 1)
			cout << char(206);									//крест
		else if (R == 1 && U != 1 && D == 1)
			L != 1 ? cout << char(201) : cout << char(203);		//угол право-низ + тройник (лево)
		else if (L != 1 && R == 1 && U == 1)
			D != 1 ? cout << char(200) : cout << char(204);		//угол право-верх + тройник (низ)
		else if (L == 1 && R != 1 && D == 1)
			U != 1 ? cout << char(187) : cout << char(185);		//угол лево-низ + тройник (верх)
		else if (L == 1 && D != 1 && U == 1)
			R != 1 ? cout << char(188) : cout << char(202);		//угол лево-верх + тройник (право)
		else if (U != 1 && D != 1)
			cout << char(205);									// " = "
		else if (L != 1 && R != 1)
			cout << char(186);									// " || "
	}
}

void Print_Level(int** matr, int x, int y)
{
	//Функция выводит уровень

	for (int i = 0; i < matr_size; i++)
	{
		for (int j = 0; j < matr_size; j++)

			if (i == y && j == x)
				cout << char(2);	//Игрок
			else
				switch (matr[i][j])
				{
					case 0:
					{
						cout << ' ';	//Пустое пространство
						break;
					}
					case 1:
					{
						Print_Wall(matr, j, i);	//Стена
						break;
					}
					case 2:
					{
						cout << char(253);	//Телепорт вверх
						break;
					}
					case 3:
					{
						cout << char(15);	//Телепорт вниз
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

	//Вывод номера уровня
	for (int i = 0; i < matr_size / 2 - 3; i++)
		cout << ' ';
	cout << "level " << z + 1 << endl;
}

void Print_Main_Screen(char elem_1, char elem_2)
{
	//Функция выводит главный экран
	cout << endl;
	cout << "    CUBIC  MAZE" << endl << endl;

	//строка 1
	cout << "    " << char(201);
	for (int i = 0; i < 8; i++)
		cout << char(205);
	cout << char(187) << endl;

	//строка 2
	cout << "   " << elem_1 << char(186) << "  play  " << char(186) << endl;

	//строка 3
	cout << "    " << char(200);
	for (int i = 0; i < 8; i++)
		cout << char(205);
	cout << char(188) << endl;

	//строка 4
	cout << "    " << char(201);
	for (int i = 0; i < 8; i++)
		cout << char(205);
	cout << char(187) << endl;

	//строка 5
	cout << "   " << elem_2 << char(186) << "tutorial" << char(186) << endl;

	//строка 6
	cout << "    " << char(200);
	for (int i = 0; i < 8; i++)
		cout << char(205);
	cout << char(188) << endl;

	cout << endl;
	cout << "use W, S to switch";
}

void Print_End_Screen(char elem_1, char elem_2)
{
	//Функция выводит экран победы

	cout << endl << endl << "\t CONGRATULATIONS!" << endl;
	cout << " You've made it through the maze!" << endl << endl;

	//строка 1
	cout << "     " << char(201);
	for (int i = 0; i < 10; i++)
		cout << char(205);
	cout << char(187) << char(201);
	for (int i = 0; i < 9; i++)
		cout << char(205);
	cout << char(187) << endl;

	//строка 2
	cout << "     " << char(186) << "play again" << char(186) << char(186) << "quit game" << char(186) << endl;

	//строка 3
	cout << "     " << char(200);
	for (int i = 0; i < 10; i++)
		cout << char(205);
	cout << char(188) << char(200);
	for (int i = 0; i < 9; i++)
		cout << char(205);
	cout << char(188) << endl;

	//выбранный элемент
	cout << "     ";
	for (int i = 0; i < 12; i++)
		cout << elem_1;
	for (int i = 0; i < 11; i++)
		cout << elem_2;

	cout << endl << endl;
	cout << "       use A, D  to switch";
}

void Tutorial()
{
	//Функция выводит обучение

	int back = 0;

	cout << char(2) << " - you\n";
	cout << char(253) << " - portal to the next level\n";
	cout << char(15) << " - portal to the previous level\n";

	cout << endl;

	cout << "WASD - move\n";
	cout << "Q - using first portal " << char(253) << endl;
	cout << "E - using second portal " << char(15) << endl;
	cout << "P - exit the game while on the level\n";

	cout << endl << endl;

	cout << "press Enter to go back to main menu" << endl;

	while (_kbhit && back != 13)
	{
		back = _getch();
	}

	system("cls");
}

void Print_Player(int x, int y, int pl_coord, int cell)
{
	//Функция выводит местоположение игрока

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };

	SetConsoleCursorPosition(h, c);	//Курсор помещается на координаты, где игрок
	cout << char(2);

	//Затирание места, где был ранее игрок
	switch (pl_coord)
	{
		case 1:
		{
			c.X++;
			break;
		}
		case 2:
		{
			c.X--;
			break;
		}
		case 3:
		{
			c.Y++;
			break;
		}
		case 4:
		{
			c.Y--;
			break;
		}
	}

	SetConsoleCursorPosition(h, c);

	//Проверка на наличие портала в месте, где был игрок
	if (cell < 2)
		cout << ' ';
	else if (cell == 2)
		cout << char(253);	//Телепорт вверх
	else
		cout << char(15);	//Телепорт вниз

	//Курсор перемещается для удобной игры
	c.X = matr_size;
	if (y < matr_size / 4)
		c.Y = matr_size / 4;
	else if (y < matr_size / 2)
		c.Y = matr_size / 2;
	else if (y < matr_size * 3 / 4)
		c.Y = matr_size * 3 / 4;
	else
		c.Y = matr_size;
	SetConsoleCursorPosition(h, c);
}