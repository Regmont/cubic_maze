#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "maze_gen.h"
#include "ConsolePrint.h"

using namespace std;

bool GameOver = false;	//Конец игры или переход на другой уровень

//Считываемые символы
enum Move { LEFT = 97, RIGHT = 100, UP = 119, DOWN = 115, TP_UP = 113, TP_DOWN = 101, QUIT = 112 };

class Level
{
public:
	int** matr;
	int lvlSize;

	~Level()
	{
		delete[] matr;
	}
};

class CubeMaze : Level
{
	Level* cube;
	int currentLvl = 0;
	int lvlAmount;
public:
	~CubeMaze()
	{
		delete[] cube;
	}

	int GetLevelSize()
	{
		return lvlSize;
	}
	void SetLevelSize(int size)
	{
		lvlSize = size;
	}

	int& GetCurrentLevel()
	{
		return currentLvl;
	}
	void SetCurrentLevel(int level)
	{
		currentLvl = level;
	}

	void SetCube(int lvlAmount, int lvlSize)
	{
		this->lvlAmount = lvlAmount;
		cube = new Level[lvlAmount];
		this->lvlSize = lvlSize;
	}

	int& GetLevelAmount()
	{
		return lvlAmount;
	}

	void SetLevel(int level, int** matr)
	{
		cube[level].matr = matr;
	}
	int** GetLevel(int index)
	{
		return cube[index].matr;
	}

	int& operator() (int currentLvl, int y, int x)
	{
		return cube[currentLvl].matr[y][x];
	}
};

class Player
{
	Move movement = Move(0);
	
public:
	int x = 1;
	int y = 1;

	Move GetMove()
	{
		return movement;
	}
	Move& SetMove()
	{
		return movement;
	}
};

//Прототипы
int main();		//Для перезапуска игры

void Recogn_Input(Move& selection);
void Print_Level(CubeMaze& maze, int x, int y);

//Главные функции
void Custom_Dif(CubeMaze& maze)
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
	maze.SetCube(lvls, size);
}

void Choose_Difficulty(CubeMaze& maze)
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
			maze.SetCube(6, 17);
			break;
		}
		case 2:
		{
			maze.SetCube(7, 21);
			break;
		}
		case 3:
		{
			maze.SetCube(8, 31);
			break;
		}
		case 4:
		{
			Custom_Dif(maze);		//Особая настройка сложности
			break;
		}
	}
}

void Main_Screen(CubeMaze& maze)
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
		Choose_Difficulty(maze);	//Выбор сложности игры
	else
	{
		Tutorial();		//Вывод обучения
		Main_Screen(maze);	//Возврат к главному экрану
	}
}

void End_Screen(CubeMaze& maze)
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
		maze.SetCurrentLevel(0);
		main();				//Начало новой игры
	}
}

void Logic(CubeMaze& maze, Player& player)
{
	int lvlSize = maze.GetLevelSize();
	int currentLvl = maze.GetCurrentLevel();

	int& x = player.x;
	int& y = player.y;

	while (_kbhit && !GameOver)
	{
		player.SetMove() = (Move)_getch();		//Считывание нажатой клавиши
		Recogn_Input(player.SetMove());			//Опознание вводимых данных

		int pl_coord;	//место, откуда перместился игрок

		switch (player.GetMove())
		{
			//Выполнение действий в зависимости от того, что нажал игрок
			case LEFT:
			{
				if (maze(currentLvl, y, x - 1) != 1)
				{
					x--;
					pl_coord = 1;	//Справа
					Print_Player(x, y, pl_coord, maze(currentLvl, y, x + 1), lvlSize);	//Вывод местоположения игрока
				}

				break;
			}
			case RIGHT:
			{
				if (maze(currentLvl, y, x + 1) != 1)
				{
					x++;
					pl_coord = 2;	//Слева
					Print_Player(x, y, pl_coord, maze(currentLvl, y, x - 1), lvlSize);	//Вывод местоположения игрока
				}

				break;
			}
			case UP:
			{
				if (maze(currentLvl, y - 1, x) != 1)
				{
					y--;
					pl_coord = 3;	//Снизу
					Print_Player(x, y, pl_coord, maze(currentLvl, y + 1, x), lvlSize);	//Вывод местоположения игрока
				}

				break;
			}
			case DOWN:
			{
				if (maze(currentLvl, y + 1, x) != 1)
				{
					y++;
					pl_coord = 4;	//Сверху
					Print_Player(x, y, pl_coord, maze(currentLvl, y - 1, x), lvlSize);	//Вывод местоположения игрока
				}

				break;
			}
			case TP_UP:
			{
				if (maze(currentLvl, y, x) == 2)
				{
					maze.SetCurrentLevel(currentLvl + 1);
					GameOver = true;	//Прерывание игры
				}

				break;
			}
			case TP_DOWN:
			{
				if (maze(currentLvl, y, x) == 3)
				{
					maze.SetCurrentLevel(currentLvl - 1);
					GameOver = true;	//Прерывание игры
				}

				break;
			}
			case QUIT:
			{
				//Ручное завершение игры
				GameOver = true;
				maze.SetCurrentLevel(maze.GetLevelAmount());
				break;
			}
		}
	}
}

int main()
{
	srand(time(0));

	Player player;				//Персонаж
	CubeMaze maze;				//Лабиринт

	Main_Screen(maze);			//Вывод главного экрана

	int& lvlAmount = maze.GetLevelAmount();
	int& currentLvl = maze.GetCurrentLevel();

	for (int i = 0; i < lvlAmount; i++)
	{
		maze.SetLevel(i, generate_maze_matrix(maze.GetLevelSize(), player.x, player.y, currentLvl));
	}

//Массив для сохранение уже созданных уровней
	bool* arr = new bool[lvlAmount];

	for (int i = 0; i < lvlAmount; i++)
		arr[i] = false;

//Проход по всем уровням
while (currentLvl < lvlAmount)
{
	//Проверка на существование уровня
	if (arr[currentLvl] == false)
	{
		
		maze.SetLevel(currentLvl, generate_maze_matrix(maze.GetLevelSize(), player.x, player.y, currentLvl));
		arr[currentLvl] = true;			//Пометка, какой уровень уже загружен
	}

	Print_Level(maze, player.x, player.y);	//Вывод уровня
	Logic(maze, player);					//Использование основной логики

	GameOver = false;
	system("cls");
}
	if (player.GetMove() != QUIT)
		End_Screen(maze);		//Вывод экрана победы
	else
	{
		cout << "\n\tGame Over!\n";
		system("pause");
	}
}

//Ввод данных
void Recogn_Input(Move& selection)
{
	//Функция преобразует нежелательный способ ввода в желательный (для enum)
	//Move selection = player.GetMove();

	switch (selection)
	{
		case 68:	//Введено 'D' или 'В' или 'в'
		case 130:
		case 162:
		{
			//player.SetMove(RIGHT);
			selection = RIGHT;
			break;
		}
		case 65:	//Введено 'A' или 'Ф' или 'ф'
		case 148:
		case 228:
		{
			//player.SetMove(LEFT);
			selection = LEFT;
			break;
		}
		case 87:	//Введено 'W' или 'Ц' или 'ц'
		case 150:
		case 230:
		{
			//player.SetMove(UP);
			selection = UP;
			break;
		}
		case 83:	//Введено 'S' или 'Ы' или 'ы'
		case 155:
		case 235:
		{
			//player.SetMove(DOWN);
			selection = DOWN;
			break;
		}
		case 81:	//Введено 'Q' или 'Й' или 'й'
		case 137:
		case 169:
		{
			//player.SetMove(TP_UP);
			selection = TP_UP;
			break;
		}
		case 69:	//Введено 'E' или 'У' или 'у'
		case 147:
		case 227:
		{
			//player.SetMove(TP_DOWN);
			selection = TP_DOWN;
			break;
		}
		case 80:	//Введено 'P' или 'з' или 'З'
		case 167:
		case 135:
		{
			//player.SetMove(QUIT);
			selection = QUIT;
			break;
		}
	}
}

//Вывод данных
void Print_Level(CubeMaze& maze, int x, int y)
{
	//Функция выводит уровень

	int lvlSize = maze.GetLevelSize();
	int currentLvl = maze.GetCurrentLevel();

	for (int i = 0; i < lvlSize; i++)
	{
		for (int j = 0; j < lvlSize; j++)

			if (i == y && j == x)
				cout << char(2);	//Игрок
			else
				switch (maze(currentLvl, i, j))
				{
					case 0:
					{
						cout << ' ';	//Пустое пространство
						break;
					}
					case 1:
					{
						Print_Wall(maze.GetLevel(currentLvl), lvlSize, j, i);	//Стена
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
	for (int i = 0; i < lvlSize / 2 - 3; i++)
		cout << ' ';
	cout << "level " << currentLvl + 1 << endl;
}